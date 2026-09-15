# 独立 MuJoCo 质量、质心标定

整个目录可单独复制到其他位置。所有代码、配置、URDF、网格和自定义 ROS 接口都在目录内，
不需要原机械臂项目、CAN 驱动或原项目的 install。需要安装 ROS 2 Humble（Ubuntu 22.04 / Python 3.10）及下列依赖。

## 1. 安装依赖和构建接口

以下命令在复制后的 `simulation` 目录中执行：

```bash
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

使用与系统 ROS 一致的 Python。接口首次运行前构建一次即可。
复制目录到新位置后重新构建接口和虚拟环境，不要沿用旧位置的 `build/`、`install/`、`log/`、`.venv/`。

## 2. 启动仿真与采集

两个终端均进入此目录，并执行：

```bash
source /opt/ros/humble/setup.bash
source install/local_setup.bash
source .venv/bin/activate
export ROS_DOMAIN_ID=173
export ROS_LOCALHOST_ONLY=1
```

终端一：

```bash
python3 mujoco_arm.py --side --mass-scale 1.1 --viewer
```

无桌面环境时去掉 `--viewer`。默认关节角度全为零。

终端二：

```bash
python3 calibrate_links.py collect --side --config config.yaml --plan plan.yaml --output run_01
```

输出目录必须不存在；再次运行换成 `run_02` 等。采集完成后自动拟合，输出：

- `raw.jsonl`：稳定段位置（deg）、速度（deg/s）、原始千分比力矩。
- `inputs.yaml`：本次配置、计划、重力快照。
- `paired.csv`：配对平均后的力矩。
- `report.json`：参数、有效秩、奇异值和力矩拟合误差。
- `candidate_drag.yaml`：质量为正时输出的候选质量、质心。

仅重新拟合（不启动仿真、不需要ROS接口）：

```bash
python3 calibrate_links.py fit --side \
  --config config.yaml --plan plan.yaml --data run_01/raw.jsonl --output fit_01
```

使用采集时相同的配置、计划及安装方向。正装时仿真和标定命令均去掉 `--side`。

## 扫描计划与参数

`plan.yaml` 是第7轴 ±3° 短扫描，便于快速检查流程，末端运动可能不明显。
`plan_template.yaml` 是带参数解释的空模板。每个任务形如：

```yaml
sweeps:
  - joint: 6
    pose_deg: [0, -30, 20, 45, 10, 0, 0]
    range_deg: [-10, 10]
    points_deg: [-5, 0, 5]
```

`joint` 使用1～7；扫描轴按范围正反向运动，其他轴保持 `pose_deg`。
可重复同一关节的不同姿态增加信息覆盖。采样点需避开加减速及稳定时间。
正式验证需增加各轴多姿态扫描，并用独立姿态验证重力矩预测。

- **真值**来自本目录 `urdf/coludata_arm.urdf`；网格相对引用本目录 `meshes/`。
- **先验**来自 `config.yaml` 中的质量与质心，保持现有 `arm_driver/ros__parameters/drag` 数据结构。
- `--mass-scale 1.1` 仅将仿真质量与惯量乘1.1，质心不变，先验不变。
- 可复制URDF修改真实质心，再通过 `--urdf 文件路径` 加载；不会写入原URDF。
- URDF与MDH部分连杆坐标原点不同，不能直接逐项比较两者质心坐标。
- 拟合变量是每根连杆 `[m, mcx, mcy, mcz]`。SVD只修正可观测方向，其他方向保留先验。
  因此候选参数不代表所有连杆质量、质心被独立测准；质量变化可能表现为拟合质心变化。
- `config.yaml` 的50千分比/N·m是仿真编码系数，不能用作真机配置。

## 最小 ROS 接口

| 名称 | 类型 |
|---|---|
| `/arm_driver/servo_j` | `arm_calibration_interfaces/action/ServoJ` |
| `/arm_driver/quick_stop` | `std_srvs/srv/Trigger` |
| `/joint_states` | `sensor_msgs/msg/JointState`（rad、rad/s、N·m） |
| `/arm_driver/torque_permille` | `std_msgs/msg/Float64MultiArray` |

接口包在 `ros/arm_calibration_interfaces` 中，仿真和采集端均使用它。
它与原驱动接口字段相同但包名不同，不能直接连接原驱动的action服务器。
`--namespace`、`--joint-states` 可更改接口名称，两端传相同参数即可。
不发布TF，不需要使能服务，使用独立ROS域避免与真机接口冲突。

## 仿真边界与测试

固定2 ms物理步长、墙钟实时运行。位置轨迹线性插值，MuJoCo逆动力学加PD计算施加力矩，
再通过正向动力学积分；没有使用标定回归矩阵生成反馈。
采用理想力矩源，不模拟电机限幅、摩擦、传感器噪声；关闭碰撞。
`quick_stop` 立即清零速度并保持位置，不代表真实制动过程。

```bash
python3 -m unittest discover -s tests -p 'test_*.py'
```

测试覆盖回归参考值、梯形轨迹、正反向配对、欠秩拟合、离线入口及无效计划拒绝。
实际摩擦、反馈延迟及真实机械臂运动安全不在本仿真验证范围内。
