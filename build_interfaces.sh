#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "${BASH_SOURCE[0]}")"
if [[ -z "${ROS_DISTRO:-}" ]]; then
  echo '请先 source /opt/ros/humble/setup.bash' >&2
  exit 1
fi
colcon build --base-paths ros --build-base build --install-base install \
  --packages-select arm_calibration_interfaces \
  --cmake-args -DPython3_EXECUTABLE=/usr/bin/python3 -DPYTHON_EXECUTABLE=/usr/bin/python3
