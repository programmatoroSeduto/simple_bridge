#! /bin/bash

source /opt/ros/foxy/setup.sh
rm -rf log
rm -rf install
rm -rf build
# rm build_log.log

set -e 

colcon build
