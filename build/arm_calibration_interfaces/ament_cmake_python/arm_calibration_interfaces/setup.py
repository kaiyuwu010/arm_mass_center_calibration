from setuptools import find_packages
from setuptools import setup

setup(
    name='arm_calibration_interfaces',
    version='0.1.0',
    packages=find_packages(
        include=('arm_calibration_interfaces', 'arm_calibration_interfaces.*')),
)
