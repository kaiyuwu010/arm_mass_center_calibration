#!/usr/bin/env python3
import argparse
import time
import numpy as np
import rclpy
from rclpy.action import ActionClient
from rclpy.qos import qos_profile_sensor_data
from rclpy.signals import SignalHandlerOptions
from sensor_msgs.msg import JointState
from std_msgs.msg import Float64MultiArray
from std_srvs.srv import Trigger
from trajectory_msgs.msg import JointTrajectoryPoint
from coludata_arm_ros.action import ServoJ
from calibrate_links import motion


# 库伦摩擦模式:不同速度、往返测量次数
FRICTION_SPEEDS = [0.5, 1.0, 2.0, 5.0]
FRICTION_REPEATS = 3


def calibrate_motor(joint, start_deg, end_deg, speed_deg_s=0.5, friction=False):
    rclpy.init(signal_handler_options=SignalHandlerOptions.NO)
    node = rclpy.create_node('midpoint_torque')
    client = ActionClient(node, ServoJ, '/arm_driver/servo_j')
    stop = node.create_client(Trigger, '/arm_driver/quick_stop')
    names, j = [f'joint{i}' for i in range(1, 8)], joint - 1
    # 关节角、方向、状态时间
    q, direction, state_time = None, 0, 0.0
    # 样本、窗口、扫描中点
    samples, window, midpoint = {1: [], -1: []}, 2.0, (start_deg + end_deg) / 2
    # 匀速段样本、速度、经过时间、匀速段范围
    cruise_samples, velocity, elapsed, flat = {1: [], -1: []}, float('nan'), 0.0, (0.0, 0.0)
    # 不同速度下的摩擦半差
    friction_results = []
    completed = False
    # 定义扫描方向，1表示从start_deg到end_deg角度增大，-1相反
    forward = np.sign(end_deg - start_deg)
    # 状态回调，记录当前关节角度和速度
    def state_cb(msg):
        nonlocal q, state_time, velocity
        indices = [msg.name.index(name) for name in names]
        q = np.degrees([msg.position[i] for i in indices])
        velocity = np.degrees(msg.velocity[indices[j]]) if len(msg.velocity) > indices[j] else float('nan')
        state_time = time.monotonic()
    # 扭矩回调，记录扭矩样本
    def torque_cb(msg):
        if direction and q is not None and time.monotonic() - state_time < 0.02 and np.isfinite([q[j], msg.data[j]]).all():
            # 判断是否在匀速段: elapsed在flat范围内，且速度接近目标速度
            cruising = flat[0] < elapsed < flat[1] and abs(velocity - direction * speed_deg_s) <= 0.15 * speed_deg_s
            # 非匀速段的样本，只在重力矩测量中记录
            if not friction or cruising:
                samples[direction].append((q[j], msg.data[j]))
            # 记录匀速段的扭矩样本
            if cruising:
                cruise_samples[direction].append(msg.data[j])
    # 运动反馈回调
    def motion_cb(msg):
        nonlocal elapsed
        elapsed = msg.feedback.elapsed_seconds
    node.create_subscription(JointState, '/joint_states', state_cb, qos_profile_sensor_data)
    node.create_subscription(Float64MultiArray, '/arm_driver/torque_permille', torque_cb, 10)
    # 等待服务端响应
    def wait(future):
        rclpy.spin_until_future_complete(node, future)
        return future.result()

    try:
        client.wait_for_server()
        while q is None:
            rclpy.spin_once(node)
        target = q.copy()
        # 构造扫描: 以指定速度speed_deg_s移动到起点start_deg，0表示只定位不采样
        scans = [(start_deg, 0, speed_deg_s)]
        # 测量摩擦使用预设速度列表，测量重力矩使用指定速度
        speeds = FRICTION_SPEEDS if friction else [speed_deg_s]
        for speed in speeds:
            # 如果测量摩擦，构造多次往返扫描，否则只进行一次往返扫描
            for _ in range(FRICTION_REPEATS if friction else 1):
                # forward表示从start_deg到end_deg，-forward相反
                scans.extend([(end_deg, int(forward), speed), (start_deg, -int(forward), speed)])
        # 执行扫描
        for angle, scan, speed_deg_s in scans:
            if scan == forward:
                # 每轮往返开始前，清空正反向数据
                samples, cruise_samples = {1: [], -1: []}, {1: [], -1: []}
            target[j] = angle
            times, positions, flat = motion(q.copy(), target, speed_deg_s, 3.0, 0.01)
            # 构造轨迹消息并发送给ServoJ
            goal = ServoJ.Goal()
            goal.trajectory.joint_names = names
            for t, position in zip(np.r_[times, times[-1] + 1.0], np.vstack([positions, target])):
                point = JointTrajectoryPoint()
                point.positions = np.radians(position).tolist()
                point.time_from_start.sec, point.time_from_start.nanosec = divmod(round(t * 1e9), 10**9)
                goal.trajectory.points.append(point)
            direction = scan
            elapsed = 0.0
            handle = wait(client.send_goal_async(goal, feedback_callback=motion_cb))
            if not handle.accepted:
                raise RuntimeError('ServoJ未执行!!!')
            result = wait(handle.get_result_async()).result
            direction = 0
            if not result.success:
                raise RuntimeError(result.message)
            # 如果计算摩擦力，并且是反向扫描
            if friction and scan == -forward:
                means = []
                for sign in (1, -1):
                    # 从samples中提取中点附近的扭矩样本
                    nearby = [torque for angle, torque in samples[sign] if abs(angle - midpoint) <= window]
                    if len(nearby) < 3:
                        raise RuntimeError('中点窗口内匀速样本不足，请扩大运动范围!!!')
                    means.append(float(np.mean(nearby)))
                # 计算摩擦
                half_difference = (means[0] - means[1]) / 2
                # 保存速度和对应摩擦力
                friction_results.append((speed_deg_s, half_difference))
                print(f'速度 {speed_deg_s:g} deg/s, 摩擦力: {half_difference:.3f} permille', flush=True)
        # 如果是测量摩擦到此结束
        if friction:
            completed = True
            return
        # 如果不是测量摩擦输出匀速段的平均扭矩
        for scan, label in [(1, 'Forward'), (-1, 'Reverse')]:
            values = cruise_samples[scan]
            print(f'{label} 匀速段 mean: {np.mean(values):.3f} permille, samples={len(values)}' if values else f'{label}: no cruise samples')
        if cruise_samples[1] and cruise_samples[-1]:
            print(f'双向匀速段 mean: {(np.mean(cruise_samples[1]) + np.mean(cruise_samples[-1])) / 2:.3f} permille')
        means = []
        print(f'中点: {midpoint:.3f} deg, 平均窗口: +/-{window:g} deg')
        # 计算中点附近的平均扭矩
        for scan, label in [(1, 'Forward'), (-1, 'Reverse')]:
            nearby = [torque for angle, torque in samples[scan] if abs(angle - midpoint) <= window]
            if len(nearby) < 3:
                print(f'{label}: 在相同的角度窗口内样本数小于3!!!')
                return
            median, count = float(np.median(nearby)), len(nearby)
            nearby = [torque for torque in nearby if abs(torque - median) <= max(abs(median) * 0.1, 1.0)]
            if len(nearby) < 3:
                print(f'{label}: 过滤后样本数小于3!!!')
                return
            means.append(float(np.mean(nearby)))
            print(f'{label}: {means[-1]:.3f} permille, samples={len(nearby)}, removed={count - len(nearby)}')
        print(f'Mean是: {np.mean(means):.3f} permille')
    except BaseException:
        if stop.wait_for_service(timeout_sec=1.):
            rclpy.spin_until_future_complete(node, stop.call_async(Trigger.Request()), timeout_sec=2.)
        raise
    finally:
        node.destroy_node()
        rclpy.shutdown()
        if completed:
            plot_friction(joint, friction_results)

# 画图显示不同速度下库伦摩擦的变化
def plot_friction(joint, results):
    import matplotlib.pyplot as plt
    speeds, differences = np.asarray(results).T
    viscous, coulomb = np.polyfit(speeds, differences, 1)
    print(f'库伦摩擦 Fc: {coulomb:.3f} permille')
    print(f'黏性系数 b: {viscous:.3f} permille/(deg/s)')
    fig, ax = plt.subplots()
    ax.scatter(speeds, differences, label='Measured half-difference')
    v = np.linspace(0, max(speeds), 100)
    ax.plot(v, coulomb + viscous * v, label=f'Fc={coulomb:.3f}, b={viscous:.3f}')
    ax.set(xlabel='Speed (deg/s)', ylabel='Torque (permille)', title=f'Joint {joint}: D(v) = Fc + b v')
    ax.grid(True)
    ax.legend()
    fig.tight_layout()
    plt.show()

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--joint', type=int, required=True)
    parser.add_argument('--start-deg', type=float, required=True)
    parser.add_argument('--end-deg', type=float, required=True)
    parser.add_argument('--speed-deg-s', type=float, default=.5)
    parser.add_argument('--friction', action='store_true', help='按脚本配置的速度和次数测量摩擦并绘图')
    calibrate_motor(**vars(parser.parse_args()))
