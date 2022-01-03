#! /bin/bash

source /opt/ros/noetic/setup.bash
source /root/simple_bridge/ws_ros1/devel/setup.bash

# roslaunch my_custom_listener run_single_topic_test.launch 
echo "pub on topic -- /bridge_topic/custom_topic"
rostopic pub /bridge_topic/custom_topic std_msgs/String "data: '0 32 15.6 /{ciao ciao ciao ciao/}'"
