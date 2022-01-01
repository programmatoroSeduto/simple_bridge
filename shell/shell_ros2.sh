#! /bin/bash

source /opt/ros/foxy/setup.bash
source /root/simple_bridge/ws_ros2/install/setup.sh

ros2 launch my_custom_sender run_single_topic_test.py
