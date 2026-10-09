# 机械臂质量、质心标定

使用 MuJoCo 和 ROS 2 仿真采集关节力矩，再拟合连杆质量与质心。支持正装、侧装，以及扫描计划优化。

## 1. 首次安装

需要 Ubuntu 22.04、ROS 2 Humble。以下命令均在项目根目录执行：

```bash
cd /home/wky/MyWorkspace/arm_mass_center_calibration
sudo apt install python3-venv python3-pip python3-colcon-common-extensions \
  ros-humble-rclpy ros-humble-rosidl-default-generators \
  ros-humble-sensor-msgs ros-humble-std-msgs ros-humble-std-srvs \
  ros-humble-trajectory-msgs
source /opt/ros/humble/setup.bash
./build_interfaces.sh
/usr/bin/python3 -m venv --system-site-packages .venv
source .venv/bin/activate
python3 -m pip install -r requirements.txt
```

接口和虚拟环境只需准备一次。若移动或复制项目，请在新目录重新构建接口和虚拟环境。

## 2. 运行仿真与标定

打开两个终端，**两个终端都执行**：

```bash
cd /home/wky/MyWorkspace/arm_mass_center_calibration
source /opt/ros/humble/setup.bash
source install/local_setup.bash
source .venv/bin/activate
export ROS_DOMAIN_ID=173
export ROS_LOCALHOST_ONLY=1
```

**终端一：启动仿真**

```bash
python3 mujoco_arm.py --side --mass-scale 1.1 --viewer
```

- `--side`：侧装；正装时仿真、采集和优化命令都去掉此参数。
- `--mass-scale 1.1`：仿真质量和惯量乘以 1.1，质心及标定先验不变；默认倍率为 1。
- `--viewer`：打开可视化窗口，无桌面环境时去掉。

**终端二：执行扫描、采集并自动拟合**

```bash
python3 calibrate_links.py collect --side \
  --config config.yaml --plan plan.yaml --output run_01
```

输出目录必须不存在，再次运行请改为 `run_02` 等。主要结果：

| 文件 | 内容 |
|---|---|
| `raw.jsonl` | 采集的位置、速度和原始千分比力矩 |
| `inputs.yaml` | 本次配置、扫描计划和重力快照 |
| `paired.csv` | 正反向配对平均后的力矩 |
| `report.json` | 拟合参数、有效秩、奇异值和力矩误差 |
| `candidate_drag.yaml` | 质量为正时输出的候选质量、质心 |

仅重新拟合已有数据，无需启动仿真：

```bash
python3 calibrate_links.py fit --side \
  --config config.yaml --plan plan.yaml \
  --data run_01/raw.jsonl --output fit_01
```

重新拟合须使用采集时相同的配置、计划和安装方向。

## 3. 扫描计划优化

```bash
python3 optimize_sweeps.py --side --count 21 --output plan_balanced.yaml
```

`--count` 必须是 7 的正整数倍，21 表示每个关节 3 组扫描，默认 42。
输出文件必须不存在。优化先按各轴等量贪心选择，再尝试同轴替换，以有效秩和正则化 logdet 评分筛选计划；结果是局部最优，不保证全局最优。

采集时使用优化后的计划：

```bash
python3 calibrate_links.py collect --side \
  --config config.yaml --plan plan_balanced.yaml --output run_02
```

`plan.yaml` 中每组扫描指定关节、基准姿态和范围，例如：

```yaml
sweeps:
  - joint: 6
    pose_deg: [0, -15, 20, 45, 10, 0, 0]
    range_deg: [-30, 30]
```

关节编号为 1～7，角度单位为度。扫描轴正反向运动，其他轴保持基准姿态。
有效区间按 5° 间隔采样，自动排除加减速等端点区域，至少需要 3 个采样中心。
`sample_tolerance_deg` 必须小于 2.5°；旧的 `points_deg` 配置会被忽略。

## 4. 真机单关节力矩测量

启动并使能真机驱动后，在新的终端加载 ROS 和驱动环境：

```bash
cd /home/wky/MyWorkspace/arm_mass_center_calibration
source /opt/ros/humble/setup.bash
source /home/wky/MyWorkspace/coludata_arm_ros/install/setup.bash
python3 calibrate_motor_torque_ros.py \
  --joint 6 --start-deg -10 --end-deg 10 --speed-deg-s 0.5
```

自动读取当前姿态，其他关节保持原位，指定关节往返扫描后停在起点。
结果直接打印，单位为驱动原始千分比（permille），不换算 N·m、不保存文件。
起点需小于终点，速度需为正，范围需留出加减速距离。脚本不自动使能、不检查碰撞，异常时尝试调用 `quick_stop`。
ROS_DOMAIN_ID 应与真机一致；真机脚本使用 `coludata_arm_ros` 接口，仿真使用独立的 `arm_calibration_interfaces` 接口。

## 说明与测试

- 仿真真值来自 `urdf/coludata_arm.urdf`，先验来自 `config.yaml`；可用 `--urdf 文件路径` 加载修改后的模型。
- 拟合每根连杆的 `[m, mcx, mcy, mcz]`，仅修正可观测方向，其他方向保留先验。候选参数不代表所有连杆质量、质心都能独立测准。
- URDF 与 MDH 的部分坐标原点不同，质心坐标不能直接逐项比较。
- `config.yaml` 中 50 千分比/N·m 是仿真编码系数，不能用于真机。
- 仿真步长为 2 ms，采用理想力矩源，关闭碰撞，不模拟摩擦、传感器噪声或电机限幅。扫描计划也不验证碰撞。
- 仿真接口：`/arm_driver/servo_j`、`/arm_driver/quick_stop`、`/joint_states`、`/arm_driver/torque_permille`。

运行测试：

```bash
python3 -m unittest discover -s tests -p 'test_*.py'
```
