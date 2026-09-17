#!/usr/bin/env python3
import argparse
import csv
import json
import math
from pathlib import Path
import time

import numpy as np
import yaml


def load_config(path):
    cfg = yaml.safe_load(Path(path).read_text())["arm_driver"]["ros__parameters"]
    for key in ("joint_names", "joint_directions", "position_min_deg", "position_max_deg"):
        if len(cfg[key]) != 7:
            raise ValueError(f"{key}必须有7项!!!")
    drag = cfg["drag"]
    scales = np.asarray(drag["torque_permille_per_nm"], dtype=float)
    mass = np.asarray(drag["link_mass_kg"], dtype=float)
    com = np.asarray(drag["link_com_m"], dtype=float).reshape(7, 3)
    if scales.shape != (7,) or not np.all(np.isfinite(scales) & (scales > 0)):
        raise ValueError("先填写drag.torque_permille_per_nm, 不能由未知质量同时标定力矩比例!!!")
    if mass.shape != (7,) or not np.all(np.isfinite(mass) & (mass > 0)) or not np.isfinite(com).all():
        raise ValueError("质量先验必须为正，质心必须有限!!!")
    if not all(x in (-1, 1) for x in cfg["joint_directions"]):
        raise ValueError("joint_directions必须为±1 !!!")
    return cfg

# 根据参数得到重力向量
def gravity_vector(cfg, side):
    g = np.asarray(cfg["drag"]["side_gravity"] if side else [0, 0, -9.81], dtype=float)
    if g.shape != (3,) or not np.isfinite(g).all() or abs(np.linalg.norm(g) - 9.81) > 0.1:
        raise ValueError("重力向量无效!!!")
    return g

# 生成参数m、mcx、mcy、mcz的回归矩阵
def regressor(q_deg, cfg, g):
    k = cfg["kinematics"]
    origins, axes, rotations = [], [], []
    T = np.eye(4)
    # 正运动学，计算个关节坐标系相对基坐标系的原点、旋转轴、旋转矩阵
    for i in range(7):
        a = k["a_mm"][i] / 1000.0
        d = k["d_mm"][i] / 1000.0
        alpha = math.radians(k["alpha_deg"][i])
        theta = math.radians(q_deg[i] + k["theta_offset_deg"][i])
        ca, sa, ct, st = math.cos(alpha), math.sin(alpha), math.cos(theta), math.sin(theta)
        T = T @ np.array([[ct, -st, 0, a], [st*ca, ct*ca, -sa, -d*sa], [st*sa, ct*sa, ca, d*ca], [0, 0, 0, 1]])
        origins.append(T[:3, 3].copy())
        axes.append(T[:3, 2].copy())
        rotations.append(T[:3, :3].copy())
    Y = np.zeros((7, 28))
    # 构造回归矩阵，Y的形状是7X28
    for j in range(7):
        for l in range(j, 7):
            Y[j, 4*l] = -axes[j] @ np.cross(origins[l] - origins[j], g)     # 质量系数，1行1列
            for c in range(3):
                Y[j, 4*l+c+1] = -axes[j] @ np.cross(rotations[l][:, c], g)  # 质心乘质量的系数，1行1列
    return Y

# 生成从关节角度q0运动到q1的轨迹，梯形速度曲线; speed: 最大关节速度; ramp: 加减速段各自持续时间; dt: 轨迹采样时间间隔; 单位: deg/s, s
def motion(q0, q1, speed, ramp, dt):
    distance = float(np.max(np.abs(q1 - q0)))
    if distance < 1e-10:
        return np.array([dt]), q1[None, :], (0., 0.)
    ramp = min(ramp, distance / speed)           # 加减速的平均速度是speed/2，所以短距离不要匀速段
    cruise = max(0., distance / speed - ramp)    # 匀速时间
    total = 2*ramp + cruise                        
    t = np.arange(0., total, dt)
    # 末点按ROS纳秒精度去重，避免浮点误差生成相同的time_from_start。
    t = np.r_[t[np.rint(t*1e9) < round(total*1e9)], total]
    s = np.empty(len(t))
    # 对恒加速、匀速、恒减速的速度积分，得到公共位移s（deg）
    for n, x in enumerate(t):
        if x <= ramp:
            s[n] = speed * x * x / (2*ramp)                        # 加速段
        elif x <= ramp + cruise:
            s[n] = speed * (ramp/2 + x - ramp)                     # 匀速段
        else:
            u = x - ramp - cruise
            s[n] = speed * (ramp/2 + cruise + u - u * u/(2*ramp))  # 减速段
    s[-1] = distance
    # 返回采样时间数组、运动进度的每个时刻关节角度、匀速段起止时间
    return t, q0 + s[:, None]/distance*(q1 - q0), (ramp, ramp + cruise)


def validate_plan(plan, cfg):
    plan.setdefault("transfer_speed_deg_s", plan.get("speed_deg_s", .5))
    for name, default in (("speed_deg_s", .5), ("transfer_speed_deg_s", .5), ("ramp_s", 3.), ("settle_s", 1.), ("sample_tolerance_deg", .15), ("velocity_tolerance", .15),
                          ("stable_s", .5), ("feedback_timeout_s", 1.), ("hold_tolerance_deg", .2)):
        plan.setdefault(name, default)
        if not math.isfinite(plan[name]) or plan[name] <= 0:
            raise ValueError(f"{name}必须为有限正数!!!")
    if plan["speed_deg_s"] > 10.0:
        raise ValueError("本脚本限制标定速度≤10 deg/s!!!")
    plan.setdefault("min_samples", 3)
    if not isinstance(plan["min_samples"], int) or plan["min_samples"] < 2:
        raise ValueError("min_samples至少为2!!!")
    if max(plan["speed_deg_s"], plan["transfer_speed_deg_s"]) > min(cfg["velocity_limit_deg_s"]):
        raise ValueError("扫描速度超过关节速度限制!!!")
    acceleration = max(plan["speed_deg_s"], plan["transfer_speed_deg_s"]) / plan["ramp_s"]
    if acceleration > min(cfg["acceleration_limit_deg_s2"] + cfg["deceleration_limit_deg_s2"]):
        raise ValueError("加减速超过关节限制, 请增加ramp_s!!!")
    if not plan.get("sweeps"):
        raise ValueError("需在计划文件sweeps中填写已确认可达且无碰撞的姿态与扫描区间!!!")
    lo, hi = np.asarray(cfg["position_min_deg"]), np.asarray(cfg["position_max_deg"])
    for sweep in plan["sweeps"]:
        j = sweep["joint"] - 1
        q = np.asarray(sweep["pose_deg"], dtype=float)
        points = np.asarray(sweep["points_deg"], dtype=float)
        start, end = sweep["range_deg"]
        if not 0 <= j < 7 or q.shape != (7,) or not np.isfinite(q).all():
            raise ValueError("joint使用1~7, pose_deg必须有7个有限角度!!!")
        if not np.all((q > lo) & (q < hi)) or not lo[j] < start < end < hi[j]:
            raise ValueError("姿态或扫描范围超出关节限制!!!")
        if len(points) < 3 or not np.isfinite(points).all() or np.any(np.diff(points) <= 0):
            raise ValueError("points_deg至少3个严格递增的有限角度!!!")
        margin = plan["speed_deg_s"]*(plan["ramp_s"]/2 + plan["settle_s"] + plan["stable_s"]) + plan["sample_tolerance_deg"]
        if points[0] <= start + margin or points[-1] >= end - margin:
            raise ValueError("采样点离两端太近, 必须留足加速、稳定和减速距离!!!")
    return plan

# 把正反向扫描的原始数据，整理成用于辨识的线性方程
def paired_rows(raw, plan, cfg, g):
    A, b, metadata = [], [], []      # A是重力回归矩阵 b是平均力矩 
    scales = np.asarray(cfg["drag"]["torque_permille_per_nm"])
    signs = np.asarray(cfg["joint_directions"])
    # 遍历plan中的每个扫描
    for sweep_id, sweep in enumerate(plan["sweeps"]):
        j = sweep["joint"] - 1
        # 遍历每个扫描中的点
        for point in sweep["points_deg"]:
            selected = []
            # 筛选出正反两个方向的数据
            for direction in (1, -1):
                # 遍历每行数据，筛选出满足id、方向、位置误差三个条件的数据
                rows = [r for r in raw if r["sweep"] == sweep_id and r["direction"] == direction and abs(r["q"][j] - point) <= plan["sample_tolerance_deg"]]
                if len(rows) < plan["min_samples"]:
                    raise ValueError(f"扫描id: {sweep_id}, 关节: {j+1} ,角度: {point} ,方向: {direction} ,稳定采样不足!!!")
                selected.append(rows)
            # 反向样本
            reverse = list(selected[1])
            pairs = []
            # 遍历正向样本
            for fwd in selected[0]:
                # 反向样本用完结束配对
                if not reverse:
                    break
                # 从反向样本中配对到当前正向样本
                idx = int(np.argmin([abs(r["q"][j] - fwd["q"][j]) for r in reverse]))
                rev = reverse[idx]
                # 正反向角度差要在容差内
                if np.max(np.abs(np.asarray(fwd["q"]) - rev["q"])) > plan["sample_tolerance_deg"]:
                    continue
                # 正反向速度差要在容差内
                if abs(abs(fwd["v"][j]) - abs(rev["v"][j])) > plan["speed_deg_s"] * plan["velocity_tolerance"]:
                    continue
                reverse.pop(idx)
                # 采样点处的正向和反向回归矩阵行
                yf = regressor(fwd["q"], cfg, g)[j]
                yr = regressor(rev["q"], cfg, g)[j]
                # 平均力矩并转换方向
                tau = (fwd["torque"][j] + rev["torque"][j]) / 2*signs[j] / scales[j]
                pairs.append(((yf + yr)/2, tau))
            if len(pairs) < plan["min_samples"]:
                raise ValueError(f"扫描id: {sweep_id}，角度: {point}正反向同角度等速配对不足!!!")
            # 保存数据
            A.append(np.mean([p[0] for p in pairs], axis=0))
            b.append(float(np.mean([p[1] for p in pairs])))
            metadata.append({"sweep": sweep_id, "joint": j+1, "point_deg": point, "pairs": len(pairs)})
    return np.asarray(A), np.asarray(b), metadata

# 根据输入数据辨识参数
def identify(A, b, cfg, metadata):
    if A.ndim != 2 or A.shape[0] == 0 or A.shape[1] != 28 or not np.isfinite(A).all() or not np.isfinite(b).all():
        raise ValueError("拟合数据为空或包含无效值!!!")
    # 将配置文件中的质量、质心转化为先验参数
    masses = np.asarray(cfg["drag"]["link_mass_kg"])
    com = np.asarray(cfg["drag"]["link_com_m"]).reshape(7, 3)
    prior = np.column_stack((masses, masses[:, None] * com)).ravel()
    # 使用单位尺度归一化，避免kg和kg*m混合使秩判断失真
    scale = np.tile([1., .1, .1, .1], 7)
    stages = []
    estimate = prior.copy()
    observable = np.zeros(28)
    # 从末端向根部遍历
    for joint in range(7, 0, -1):
        rows = [i for i, item in enumerate(metadata) if item["joint"] >= joint]
        if not rows:
            continue
        cols = slice(4*(joint - 1), 28)
        X = A[rows, cols] * scale[cols]
        # svd分解找到能辨识的参数
        U, singular, Vt = np.linalg.svd(X, full_matrices=False)
        rank = int(np.sum(singular > max(1e-10, singular[0]*1e-4))) if singular.size else 0
        delta = np.zeros(X.shape[1])
        if rank:
            delta = Vt[:rank].T @ ((U[:, :rank].T @ (b[rows] - A[rows] @ prior))/singular[:rank])
        estimate = prior.copy()
        estimate[cols] += scale[cols] * delta
        observable[:] = 0
        # 可观测的参数对应的回归矩阵
        observable[cols] = np.sum(Vt[:rank]**2, axis=0)
        stages.append({"joint": joint, 
                       "rank": rank, 
                       "unknowns": X.shape[1], 
                       "rmse_nm": float(np.sqrt(np.mean((A[rows] @ estimate - b[rows])**2))), 
                       "singular_values": singular.tolist()})
    params = estimate.reshape(7, 4)
    valid = bool(np.isfinite(params).all() and np.all(params[:, 0] > 0))
    report = {"stages": stages, 
              "physical_mass_valid": valid,
              "note": "不可辨识方向保留先验，单独质量和质心不是唯一标定结果。摩擦平均仅近似抵消对称库仑/粘性摩擦。",
              "observable_fraction_m_hx_hy_hz": observable.reshape(7, 4).tolist(),
              "parameters_m_hx_hy_hz": params.tolist(), 
              "samples": metadata,
              "rmse_nm": float(np.sqrt(np.mean((A @ estimate - b)**2)))}
    patch = None
    if valid:
        patch = {"arm_driver": {"ros__parameters": {"drag": {"link_mass_kg": params[:, 0].tolist(), "link_com_m": (params[:, 1:]/params[:, :1]).ravel().tolist()}}}}
    return report, patch


def collect(args, cfg, plan, output):
    # 延迟导入，离线拟合不依赖ROS运行环境。
    import rclpy
    from rclpy.signals import SignalHandlerOptions
    from rclpy.action import ActionClient
    from rclpy.qos import qos_profile_sensor_data
    from sensor_msgs.msg import JointState
    from std_msgs.msg import Float64MultiArray
    from std_srvs.srv import Trigger
    from trajectory_msgs.msg import JointTrajectoryPoint
    from arm_calibration_interfaces.action import ServoJ

    rclpy.init(signal_handler_options=SignalHandlerOptions.NO)
    node = rclpy.create_node("calibrate_links")
    client = ActionClient(node, ServoJ, args.namespace + "/servo_j")
    stop = node.create_client(Trigger, args.namespace + "/quick_stop")
    latest = {"state": None, "torque": None}
    active = None
    raw = []
    context = None
    stable_since = None
    previous_v = None
    failure = None
    log = (output/"raw.jsonl").open("w")

    # 状态回调函数
    def state_cb(msg):
        if any(n not in msg.name for n in cfg["joint_names"]):
            return
        idx = [msg.name.index(n) for n in cfg["joint_names"]]
        # 检查数据长度
        if len(msg.position) < len(msg.name) or len(msg.velocity) < len(msg.name):
            return
        # 更新最近数据，state包括当前时间、位置、速度
        latest["state"] = (time.monotonic(), np.degrees([msg.position[i] for i in idx]), np.degrees([msg.velocity[i] for i in idx]))

    # 力矩回调函数
    def torque_cb(msg):
        nonlocal stable_since, previous_v, failure
        now = time.monotonic()
        latest["torque"] = now
        state = latest["state"]
        # 力矩话题没有Header，只能按到达时间近似配对，拒绝超过半个发布周期的状态。
        if state is None:
            return
        if len(msg.data) != 7 or not np.isfinite(np.r_[state[1], state[2], msg.data]).all():
            failure = "反馈包含无效位置、速度或力矩"
            return
        if np.any(np.abs(msg.data) >= np.asarray(cfg["torque_limit_permille"])):
            failure = "力矩达到配置上限"
            return
        if np.any(state[1] <= np.asarray(cfg["position_min_deg"])) or np.any(state[1] >= np.asarray(cfg["position_max_deg"])):
            failure = "反馈位置达到关节限制"
            return
        if np.any(np.abs(state[2]) > np.asarray(cfg["velocity_limit_deg_s"])):
            failure = "反馈速度超出关节限制"
            return
        if context is None:
            return
        # 半个状态发布周期
        max_skew = .5/cfg.get("state_publish_rate_hz", 20.)
        # 力矩接收时间与最近关节状态时间超过半个状态发布周期拒绝
        if now-state[0] > max_skew or len(msg.data) != 7:
            stable_since = None
            return
        q, v = state[1], state[2]
        torque = np.asarray(msg.data)
        if not np.isfinite(np.r_[q, v, torque]).all():
            failure = "反馈包含无效位置、速度或力矩"
            return
        if np.any(np.abs(torque) >= np.asarray(cfg["torque_limit_permille"])):
            failure = "力矩达到配置上限"
            return
        j = context["joint"]
        others = np.arange(7) != j
        if np.any(np.abs(q[others] - context["pose"][others]) > plan["hold_tolerance_deg"]):
            failure = "非扫描关节未保持固定"
            return
        low, high = context["range"]
        if q[j] < low - plan["hold_tolerance_deg"] or q[j] > high + plan["hold_tolerance_deg"]:
            failure = "实际位置超出扫描范围"
            return
        # 计算期望速度
        expected_v = context["direction"]*plan["speed_deg_s"]
        # 计算当前时间距离该段运动开始经过了多久
        elapsed = now - context["started"]
        # 取出motion()返回的匀速段起止时间
        flat = context["flat"]
        # 判断是否稳定
        stable = (flat[0] + plan["settle_s"] < elapsed < flat[1] - plan["settle_s"]                  # 需要避开匀速段两端plan["settle_s"]的距离
                  and abs(v[j] - expected_v) <= plan["speed_deg_s"] * plan["velocity_tolerance"]     # 扫描关节实际速度需要接近期望速度
                  and np.all(np.abs(v[others]) < plan["speed_deg_s"] * plan["velocity_tolerance"]))  # 其它关节基本静止
        # 前一时刻速度不能超过当前速度太多
        if previous_v is not None:
            stable &= abs(v[j] - previous_v) <= plan["speed_deg_s"] * plan["velocity_tolerance"]
        previous_v = v[j]
        if not stable:
            stable_since = None
            return
        # 记录稳定的时刻
        if stable_since is None:
            stable_since = now
        # 必须在稳定后再过plan["stable_s"]的时间记录数据
        if now - stable_since < plan["stable_s"]:
            return
        # 组织并添加数据
        row = {"time": now, "sweep": context["sweep"], "direction": context["direction"], "q": q.tolist(), "v": v.tolist(), "torque": torque.tolist()}
        raw.append(row)
        log.write(json.dumps(row)+"\n")
        log.flush()

    node.create_subscription(JointState, args.joint_states, state_cb, qos_profile_sensor_data)
    node.create_subscription(Float64MultiArray, args.namespace + "/torque_permille", torque_cb, 10)

    # 等待消息返回
    def wait(future, timeout):
        deadline = time.monotonic() + timeout
        while rclpy.ok() and not future.done():
            rclpy.spin_once(node, timeout_sec=.02)
            if failure:
                raise RuntimeError(failure)
            if time.monotonic() > deadline:
                raise TimeoutError("等待运动服务超时")
            if active is not None:
                now = time.monotonic()
                if latest["state"] is None or latest["torque"] is None or min(latest["state"][0], latest["torque"]) < now-plan["feedback_timeout_s"]:
                    raise RuntimeError("反馈中断，停止标定")
        if not rclpy.ok():
            raise RuntimeError("ROS已停止")
        if failure:
            raise RuntimeError(failure)
        return future.result()

    # 控制机械臂运动
    def run(q0, q1, scan=None):
        nonlocal active, context, stable_since, previous_v
        if not np.isfinite(q0).all() or not np.isfinite(q1).all():
            raise ValueError("起止位置必须有限!!!")
        if np.any(q0 <= np.asarray(cfg["position_min_deg"])) or np.any(q0 >= np.asarray(cfg["position_max_deg"])):
            raise ValueError("当前位置超出配置范围!!!")
        if np.max(np.abs(latest["state"][2])) > .1:
            raise RuntimeError("请待机械臂静止后开始下一段!!!")
        # 姿态切换使用独立速度；扫描仍按标定速度运动。
        speed = plan["transfer_speed_deg_s"] if scan is None else plan["speed_deg_s"]
        # 控制周期转为ms
        dt = cfg["control_period_ms"]/1000.
        if not .002 <= dt <= .1:
            raise ValueError("control_period_ms必须为2~100!!!")
        if np.max(np.abs(q1 - q0))/speed/dt > 200000:
            raise ValueError("轨迹超过20万点, 请缩短移动距离或分段执行!!!")
        # 根据梯形速度规划轨迹
        t, positions, flat = motion(q0, q1, speed, plan["ramp_s"], dt)
        if flat[0] > 0 and speed / flat[0] > min(cfg["acceleration_limit_deg_s2"] + cfg["deceleration_limit_deg_s2"]):
            raise ValueError("短距离移动加速度超限, 请减小当前段的扫描或切换速度!!!")
        # 额外静止保持，等实际电机停止后才开始下一段
        t = np.r_[t, t[-1] + plan["settle_s"]]
        # 构造ros控制消息
        positions = np.vstack((positions, q1))
        goal = ServoJ.Goal()
        goal.trajectory.joint_names = cfg["joint_names"]
        for x, q in zip(t, positions):
            p = JointTrajectoryPoint()
            p.positions = np.radians(q).tolist()
            ns = int(round(x*1e9))
            p.time_from_start.sec, p.time_from_start.nanosec = divmod(ns, 10**9)
            goal.trajectory.points.append(p)
        context = None
        started = time.monotonic()
        # 发送消息
        active = wait(client.send_goal_async(goal), 5.)
        if not active.accepted:
            active = None
            raise RuntimeError("ServoJ拒绝目标, 请确认机械臂已使能、未处于拖动或其他运动中!!!")
        if scan is not None:
            context = dict(scan, started=started, flat=flat)
        stable_since, previous_v = None, None
        result = wait(active.get_result_async(), t[-1] + 10.)
        active, context = None, None
        if not result.result.success:
            raise RuntimeError(result.result.message)
        if latest["state"] is None or np.max(np.abs(latest["state"][1] - q1)) > plan["hold_tolerance_deg"]:
            raise RuntimeError("实际关节未到达段终点!!!")

    try:
        if not client.wait_for_server(timeout_sec=5.) or not stop.wait_for_service(timeout_sec=5.):
            raise RuntimeError("找不到servo_j或quick_stop接口!!!")
        deadline = time.monotonic() + 5.
        while latest["state"] is None or latest["torque"] is None:
            rclpy.spin_once(node, timeout_sec=.1)
            if time.monotonic() > deadline:
                raise RuntimeError("没有收到关节和力矩反馈!!!")
        # 按关节编号从大到小排序，再依次取出任务下标sweep_id
        for sweep_id in sorted(range(len(plan["sweeps"])), key=lambda i: -plan["sweeps"][i]["joint"]):
            sweep = plan["sweeps"][sweep_id]
            # 对应关节索引
            j = sweep["joint"] - 1
            q0 = np.asarray(sweep["pose_deg"], dtype = float)
            q1 = q0.copy()
            # 读取关节运动范围
            q0[j], q1[j] = sweep["range_deg"]
            print(f"扫描{sweep_id}: 关节{j + 1}, {q0[j]} -> {q1[j]} -> {q0[j]} deg", flush=True)
            # 运行到初始位置q0
            run(latest["state"][1].copy(), q0)
            # 从初始位置开始正反扫
            ctx = {"sweep": sweep_id, "joint": j, "pose": q0, "range": sweep["range_deg"]}
            run(q0, q1, dict(ctx, direction=1))
            run(q1, q0, dict(ctx, direction=-1))
        return raw
    except BaseException:
        context = None
        if active is not None:
            active.cancel_goal_async()
        # 中断时尝试停止，不自动重新使能或返回起始姿态
        if rclpy.ok() and stop.service_is_ready():
            future = stop.call_async(Trigger.Request())
            rclpy.spin_until_future_complete(node, future, timeout_sec=2.)
        raise
    finally:
        log.close()
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("mode", choices=["collect", "fit"])
    parser.add_argument("--config", required=True, type=Path)
    parser.add_argument("--plan", required=True, type=Path)
    parser.add_argument("--output", required=True, type=Path, help="新建结果目录，不覆盖已有目录")
    parser.add_argument("--data", type=Path, help="fit模式的raw.jsonl")
    parser.add_argument("--side", action="store_true", help="侧装, 使用drag.side_gravity")
    parser.add_argument("--namespace", default="/arm_driver")
    parser.add_argument("--joint-states", default="/joint_states")
    args = parser.parse_args()
    # 加载配置文件
    cfg = load_config(args.config)
    # 验证关节扫描计划
    plan = validate_plan(yaml.safe_load(args.plan.read_text()), cfg)
    # 获取重力在基坐标系向量
    g = gravity_vector(cfg, args.side)
    if args.mode == "fit" and args.data is None:
        parser.error("fit需要--data")
    args.output.mkdir(parents=True, exist_ok=False)
    (args.output/"inputs.yaml").write_text(yaml.safe_dump({"config": cfg, "plan": plan, "gravity": g.tolist()}, allow_unicode=True))
    # 收集数据
    raw = collect(args, cfg, plan, args.output) if args.mode == "collect" else [json.loads(line) for line in args.data.read_text().splitlines() if line.strip()]
    # 整理数据
    A, b, metadata = paired_rows(raw, plan, cfg, g)
    # 辨识参数
    report, patch = identify(A, b, cfg, metadata)
    # 保存参数相关内容
    (args.output/"report.json").write_text(json.dumps(report, ensure_ascii=False, indent=2))
    # 保存pair
    with (args.output/"paired.csv").open("w") as f:
        writer = csv.writer(f)
        writer.writerow(["sweep", "joint", "point_deg", "pairs", "gravity_torque_nm"])
        for item, torque in zip(metadata, b):
            writer.writerow([*item.values(), torque])
    if patch is not None:
        (args.output/"candidate_drag.yaml").write_text("# 不可辨识部分依赖先验, 检查report.json后再使用。\n" + yaml.safe_dump(patch, sort_keys=False, allow_unicode=True))
    print(f"结果:{args.output}, 力矩拟合RMSE={report['rmse_nm']:.6g} N·m")
    print(report["note"])


if __name__ == "__main__":
    main()
