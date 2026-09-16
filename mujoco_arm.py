#!/usr/bin/env python3
import argparse
from pathlib import Path
import time
import xml.etree.ElementTree as ET

import mujoco
import numpy as np
import yaml
import rclpy
from rclpy.action import ActionServer, CancelResponse, GoalResponse
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.node import Node
from rclpy.task import Future
from rclpy.executors import ExternalShutdownException
from rclpy.impl.implementation_singleton import rclpy_implementation
from sensor_msgs.msg import JointState
from std_msgs.msg import Float64MultiArray
from std_srvs.srv import Trigger
from arm_calibration_interfaces.action import ServoJ

ROOT = Path(__file__).resolve().parent


def load_model(path, names, side=False, mass_scale=1.):
    root = ET.parse(path).getroot()
    # 直接读已有URDF，只在内存中解析网格路径并保留可视几何
    assets = {}
    for mesh in root.iter('mesh'):
        filename = mesh.get('filename')
        local = ROOT / filename.split('package://coludata_arm_ros/')[-1] if filename.startswith('package://') else path.parent / filename
        mesh.set('filename', local.name)
        assets[local.name] = local.read_bytes()
    # 修改内存中的XML，给urdf增加mujoco专用加载配置
    extension = ET.SubElement(root, 'mujoco')
    ET.SubElement(extension, 'compiler', discardvisual='false', fusestatic='false')
    # 加载urdf和mesh
    spec = mujoco.MjSpec.from_string(ET.tostring(root, encoding='unicode'), assets=assets)
    # 纯白背景
    spec.add_texture(type=mujoco.mjtTexture.mjTEXTURE_SKYBOX, builtin=mujoco.mjtBuiltin.mjBUILTIN_GRADIENT, rgb1=[1, 1, 1], rgb2=[1, 1, 1], width=32, height=32)
    # 浅灰白棋盘格地面，仅显示，不参与碰撞。
    spec.add_texture(name='floor', type=mujoco.mjtTexture.mjTEXTURE_2D, builtin=mujoco.mjtBuiltin.mjBUILTIN_CHECKER, rgb1=[.85, .85, .85], rgb2=[1, 1, 1], width=64, height=64)
    floor = spec.add_material(name='floor', texrepeat=[5, 5], texuniform=True)
    floor.textures[mujoco.mjtTextureRole.mjTEXROLE_RGB] = 'floor'
    # 0.3×0.3×1m底座柱，柱顶位于基座原点z=0；地面移到柱底。
    spec.worldbody.add_geom(name='pedestal', type=mujoco.mjtGeom.mjGEOM_BOX,
                            size=[.05, .05, .5], pos=[0, 0, -.5],
                            rgba=[.55, .57, .60, 1], contype=0, conaffinity=0)
    spec.worldbody.add_geom(name='floor', type=mujoco.mjtGeom.mjGEOM_PLANE, size=[2, 2, .1], pos=[0, 0, -1.0], material='floor', contype=0, conaffinity=0)
    # 生成模型
    model = spec.compile()
    if model.nq != 7 or model.nv != 7:
        raise ValueError('模型必须是固定基座的7轴机械臂!!!')
    if [model.joint(i).name for i in range(7)] != names:
        raise ValueError('URDF关节顺序与配置不一致!!!')
    model.opt.timestep = .002                                           # 每调用一次mj_step()，仿真时间推进2ms
    model.opt.gravity[:] = [-9.81, 0, 0] if side else [0, 0, -9.81]     # 设置世界坐标系下重力加速度
    model.geom_contype[:] = 0                                           # 碰撞类型设为0
    model.geom_conaffinity[:] = 0                                       # 碰撞匹配掩码设为0
    # 可改变仿真真值，拟合先验仍来自配置，同时缩放惯量以保持一致
    model.body_mass[1:] *= mass_scale
    model.body_inertia[1:] *= mass_scale
    data = mujoco.MjData(model)
    mujoco.mj_setConst(model, data)
    mujoco.mj_forward(model, data)
    return model, data


class ArmSimulation(Node):
    def __init__(self, args):
        super().__init__('mujoco_arm')
        cfg = yaml.safe_load(args.config.read_text())['arm_driver']['ros__parameters']
        self.names = cfg['joint_names']                                                         # 关节名
        self.scale = np.asarray(cfg['drag']['torque_permille_per_nm'])                          # 力矩换算系数
        self.sign = np.asarray(cfg['joint_directions'])                                         # 关节方向
        if self.scale.shape != (7,) or not np.all(np.isfinite(self.scale) & (self.scale > 0)):
            raise ValueError('仿真配置的torque_permille_per_nm必须为7个正数!!!')
        self.model, self.data = load_model(args.urdf, self.names, args.side, args.mass_scale)
        if args.side:
            self.model.opt.gravity[:] = cfg['drag']['side_gravity']
        self.target = self.data.qpos.copy()
        self.busy = False
        self.pending = None
        self.goal = None
        self.tau = np.zeros(7)
        self.wall = time.monotonic()
        self.pub_time = 0.
        self.period = 1 / cfg.get('state_publish_rate_hz', 20.)
        group = ReentrantCallbackGroup()
        ns = args.namespace.rstrip('/')
        # 发布关节状态
        self.states = self.create_publisher(JointState, args.joint_states, 10)
        # 发布原始力矩
        self.torques = self.create_publisher(Float64MultiArray, ns + '/torque_permille', 10)
        # 接收运动轨迹
        self.server = ActionServer(self, ServoJ, ns+'/servo_j', self.execute, goal_callback=self.accept, cancel_callback=lambda _: CancelResponse.ACCEPT, callback_group=group)
        # 停止服务
        self.create_service(Trigger, ns+'/quick_stop', self.stop, callback_group=group)
        self.create_timer(.002, self.tick, callback_group=group)
        # 可视化
        self.viewer = None
        if args.viewer:
            import mujoco.viewer
            self.viewer = mujoco.viewer.launch_passive(self.model, self.data)
        self.get_logger().info(f'仿真就绪：{ns}/servo_j, 真值来自 {args.urdf}')

    # 轨迹接收检查
    def accept(self, request):
        tr = request.trajectory
        # 时间戳转化为秒
        times = np.array([p.time_from_start.sec + p.time_from_start.nanosec * 1e-9 for p in tr.points])
        try:
            positions = np.array([p.positions for p in tr.points], dtype=float)
            valid = (not self.busy                                                              # 没有其他任务
                     and tr.joint_names == self.names                                           # 关节名称和排列顺序一致
                     and len(times) > 0                                                         # 轨迹点不为0
                     and positions.shape == (len(times), 7)                                     # 每个点有7个关节角度
                     and np.isfinite(positions).all()                                           # 角度没有无穷大
                     and times[0] >= 0                                                          # 第一个时间点非负
                     and np.all(np.diff(times) > 0)                                             # 时间严格递增
                     and np.all(positions >= self.model.jnt_range[:, 0])                        # 所有角度大于等于关节下限
                     and np.all(positions <= self.model.jnt_range[:, 1]))                       # 所有角度小于等于关节上限
        except ValueError:
            valid = False
        if not valid:
            return GoalResponse.REJECT
        self.busy = True
        return GoalResponse.ACCEPT

    # 轨迹执行
    async def execute(self, goal):
        self.goal = goal
        points = goal.request.trajectory.points
        # 时间戳转化为秒
        self.times = np.array([p.time_from_start.sec + p.time_from_start.nanosec * 1e-9 for p in points])
        self.positions = np.array([p.positions for p in points])
        # 如果第一个点在未来，补上当前位置
        if self.times[0] > 0:
            self.times = np.r_[0., self.times]
            self.positions = np.vstack((self.data.qpos.copy(), self.positions))
        # 记录开始时刻
        self.started = self.data.time
        future = self.pending = Future()
        return await future

    # 结束当前任务，清除忙碌状态
    def finish(self, success, message, canceled=False):
        if self.pending is None:
            return
        if canceled:
            self.goal.canceled()
        elif success:
            self.goal.succeed()
        else:
            self.goal.abort()
        self.pending.set_result(ServoJ.Result(success=success, message=message))
        self.pending = self.goal = None
        self.busy = False  # 允许下一次运动

    # 立即停止仿真，保持当前位置
    def stop(self, request, response):
        self.target = self.data.qpos.copy()
        self.data.qvel[:] = 0
        # 结束当前任务
        self.finish(False, 'quick_stop')
        response.success, response.message = True, '仿真已停止并保持当前位置'
        return response

    def tick(self):
        # 按墙钟推进固定步长，避免ROS定时器抖动改变扫描速度
        now = time.monotonic()
        # 根据当前时间计算需要推进几个时间步
        steps = min(int((now - self.wall)/self.model.opt.timestep), 100)
        for _ in range(steps):
            velocity = np.zeros(7)
            if self.pending is not None:
                # 处理取消指令
                if self.goal.is_cancel_requested:
                    self.target = self.data.qpos.copy()
                    self.data.qvel[:] = 0
                    self.finish(False, 'canceled', canceled=True)
                else:
                    elapsed = self.data.time - self.started                   # 计算运动经过的时间
                    i = np.searchsorted(self.times, elapsed, side='right')    # 找到第一个时间大于elapsed的轨迹点
                    # 没到最后一个点
                    if i < len(self.times):
                        a, b = max(0, i-1), i                                                   # 当前时刻前后的两个轨迹点
                        duration = self.times[b] - self.times[a]                                # 计算持续时间
                        velocity = (self.positions[b] - self.positions[a])/duration             # 计算目标速度
                        self.target = self.positions[a] + velocity*(elapsed - self.times[a])    # 线性插值得到目标角度
                    else:
                        self.target = self.positions[-1].copy()     # 保持最终位置
                        if np.max(np.abs(self.data.qpos - self.target)) < 1e-4 and np.max(np.abs(self.data.qvel)) < 1e-3:
                            self.finish(True, '轨迹完成')
                        elif elapsed > self.times[-1]+5:
                            self.finish(False, '跟踪超时')
            # MuJoCo独立计算惯性/重力力矩，再进行正向动力学积分，不调用标定回归矩阵
            self.data.qacc[:] = 400*(self.target - self.data.qpos) + 40*(velocity - self.data.qvel) # PD控制计算期望加速度
            mujoco.mj_inverse(self.model, self.data)                # 逆动力学
            self.tau = self.data.qfrc_inverse.copy()                # 计算力矩
            self.data.qfrc_applied[:] = self.tau                    # 应用计算出的力矩
            mujoco.mj_step(self.model, self.data)                   # 推进仿真步，计算实际加速度，更新位置、速度、仿真时间
            self.wall += self.model.opt.timestep                    # 更新基准时间
        # 距离上次发布超过一个周期
        if now - self.pub_time >= self.period:
            self.pub_time = now                                 # 记录发布时间
            msg = JointState()                                  # 初始化消息
            msg.header.stamp = self.get_clock().now().to_msg()  # 填时间戳
            msg.name = self.names                               # 填关节名称
            msg.position = self.data.qpos.tolist()              # 填实际位置
            msg.velocity = self.data.qvel.tolist()              # 填实际速度
            msg.effort = self.tau.tolist()                      # 填施加的力矩
            self.states.publish(msg)                            # 发布状态
            self.torques.publish(Float64MultiArray(data=(self.tau * self.scale * self.sign).tolist())) # 发布力矩
            if self.viewer is not None and self.viewer.is_running():
                self.viewer.sync()                              # 刷新窗口


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--urdf', type=Path, default=ROOT/'urdf/coludata_arm.urdf')
    parser.add_argument('--config', type=Path, default=ROOT/'config.yaml')
    parser.add_argument('--namespace', default='/arm_driver')
    parser.add_argument('--joint-states', default='/joint_states')
    parser.add_argument('--side', action='store_true')
    parser.add_argument('--viewer', action='store_true')
    parser.add_argument('--mass-scale', type=float, default=1., help='仿真质量和惯量倍率，不修改先验')
    args = parser.parse_args()
    if not np.isfinite(args.mass_scale) or args.mass_scale <= 0:
        parser.error('--mass-scale必须为有限正数')
    rclpy.init(args=[])
    node = ArmSimulation(args)
    try:
        rclpy.spin(node)
    except (KeyboardInterrupt, ExternalShutdownException):
        pass
    except rclpy_implementation.RCLError:
        if rclpy.ok():
            raise
    finally:
        if node.viewer is not None:
            node.viewer.close()
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == '__main__':
    main()
