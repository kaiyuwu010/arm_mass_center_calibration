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


def calibrate_motor(joint, start_deg, end_deg, speed_deg_s=.5):
    rclpy.init(signal_handler_options=SignalHandlerOptions.NO)
    node = rclpy.create_node('midpoint_torque')
    client = ActionClient(node, ServoJ, '/arm_driver/servo_j')
    stop = node.create_client(Trigger, '/arm_driver/quick_stop')
    names, j = [f'joint{i}' for i in range(1, 8)], joint - 1
    q, direction, state_time = None, 0, 0.
    samples, window, midpoint = {1: [], -1: []}, 2., (start_deg + end_deg) / 2
    cruise_samples, velocity, elapsed, flat = {1: [], -1: []}, float('nan'), 0., (0., 0.)

    def state_cb(msg):
        nonlocal q, state_time, velocity
        indices = [msg.name.index(name) for name in names]
        q = np.degrees([msg.position[i] for i in indices])
        velocity = np.degrees(msg.velocity[indices[j]]) if len(msg.velocity) > indices[j] else float('nan')
        state_time = time.monotonic()

    def torque_cb(msg):
        if direction and q is not None and time.monotonic() - state_time < .02 and np.isfinite([q[j], msg.data[j]]).all():
            samples[direction].append((q[j], msg.data[j]))
            if flat[0] < elapsed < flat[1] and abs(velocity - direction * speed_deg_s) <= .15 * speed_deg_s:
                cruise_samples[direction].append(msg.data[j])

    def motion_cb(msg):
        nonlocal elapsed
        elapsed = msg.feedback.elapsed_seconds

    node.create_subscription(JointState, '/joint_states', state_cb, qos_profile_sensor_data)
    node.create_subscription(Float64MultiArray, '/arm_driver/torque_permille', torque_cb, 10)

    def wait(future):
        rclpy.spin_until_future_complete(node, future)
        return future.result()

    try:
        client.wait_for_server()
        while q is None:
            rclpy.spin_once(node)
        target = q.copy()
        for angle, scan in [(start_deg, 0), (end_deg, 1), (start_deg, -1)]:
            target[j] = angle
            times, positions, flat = motion(q.copy(), target, speed_deg_s, 3., .01)
            goal = ServoJ.Goal()
            goal.trajectory.joint_names = names
            for t, position in zip(np.r_[times, times[-1] + 1.], np.vstack([positions, target])):
                point = JointTrajectoryPoint()
                point.positions = np.radians(position).tolist()
                point.time_from_start.sec, point.time_from_start.nanosec = divmod(round(t * 1e9), 10**9)
                goal.trajectory.points.append(point)
            direction = scan
            elapsed = 0.
            handle = wait(client.send_goal_async(goal, feedback_callback=motion_cb))
            if not handle.accepted:
                raise RuntimeError('ServoJ rejected')
            result = wait(handle.get_result_async()).result
            direction = 0
            if not result.success:
                raise RuntimeError(result.message)
        for scan, label in [(1, 'Forward'), (-1, 'Reverse')]:
            values = cruise_samples[scan]
            print(f'{label} 匀速段 mean: {np.mean(values):.3f} permille, samples={len(values)}' if values else f'{label}: no cruise samples')
        if cruise_samples[1] and cruise_samples[-1]:
            print(f'双向匀速段 mean: {(np.mean(cruise_samples[1]) + np.mean(cruise_samples[-1])) / 2:.3f} permille')
        means = []
        print(f'Midpoint: {midpoint:.3f} deg, averaging window: +/-{window:g} deg')
        for scan, label in [(1, 'Forward'), (-1, 'Reverse')]:
            nearby = [torque for angle, torque in samples[scan] if abs(angle - midpoint) <= window]
            if len(nearby) < 3:
                print(f'{label}: fewer than 3 samples in the same angle window')
                return
            median, count = float(np.median(nearby)), len(nearby)
            nearby = [torque for torque in nearby if abs(torque - median) <= max(abs(median) * .1, 1.)]
            if len(nearby) < 3:
                print(f'{label}: fewer than 3 samples after filtering')
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


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--joint', type=int, required=True)
    parser.add_argument('--start-deg', type=float, required=True)
    parser.add_argument('--end-deg', type=float, required=True)
    parser.add_argument('--speed-deg-s', type=float, default=.5)
    calibrate_motor(**vars(parser.parse_args()))
