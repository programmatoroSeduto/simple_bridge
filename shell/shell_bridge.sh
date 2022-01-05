#! /bin/bash

# run the ROS1 bridge

source /opt/ros/noetic/setup.bash
source /opt/ros/foxy/setup.bash
source /root/simple_bridge/ws_bridge/install/setup.sh

ros2 run ros1_bridge dynamic_bridge --bridge-all-topics
