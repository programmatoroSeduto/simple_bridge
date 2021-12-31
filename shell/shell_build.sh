#! /bin/bash

rm -rf /root/simple_bridge/logs
mkdir /root/simple_bridge/logs
terminator --working-directory=/root/simple_bridge/ws_ros1 --title="ROS1 build" -e "source ./build.sh > /root/simple_bridge/logs/ws_ros1_build.log"
terminator --working-directory=/root/simple_bridge/ws_ros2 --title="ROS2 build" -e "source ./build.sh > /root/simple_bridge/logs/ws_ros2_build.log"
terminator --working-directory=/root/simple_bridge/ws_bridge --title="BRIDGE build" -e "source ./build_bridge_base.sh > /root/simple_bridge/logs/ws_bridge_build.log"
