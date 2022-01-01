#! /bin/bash

source /opt/ros/noetic/setup.bash
source /root/simple_bridge/ws_ros1/devel/setup.bash

roslaunch my_custom_listener run_single_topic_test.launch 
