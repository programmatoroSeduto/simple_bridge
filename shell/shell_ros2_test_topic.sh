#! /bin/bash

set -e

source /opt/ros/foxy/setup.bash
source /root/simple_bridge/ws_ros2/install/setup.sh

# terminator -e "source /opt/ros/foxy/setup.bash && source /root/simple_bridge/ws_ros2/install/setup.sh && ros2 topic pub /custom_topic ros2_bridge_support_pkg/msg/MyCustomMessage" -T "ros2 publisher"
terminator -e "source /opt/ros/foxy/setup.bash && source /root/simple_bridge/ws_ros2/install/setup.sh && ros2 topic echo /bridge_topic/custom_topic_a std_msgs/msg/String" -T "ros2 subscriber"
