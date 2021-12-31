#! /bin/bash

source /opt/ros/noetic/setup.bash
source /root/simple_bridge/ws_ros1/devel/setup.bash

rosrun ros1_listener_pkg ros1_client
