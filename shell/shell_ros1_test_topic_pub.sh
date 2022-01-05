#! /bin/bash

## DESCRIPTION
#     this script sends a string message to /bridge_topic/custom_topic_a
#     this message should be read from the bridge and sent to 
#        /custom_topic_a after being casted back
#     the end node should print this message. 

source /opt/ros/noetic/setup.bash
source /root/simple_bridge/ws_ros1/devel/setup.bash

# roslaunch my_custom_listener run_single_topic_test.launch 
echo "pub on topic -- /bridge_topic/custom_topic_a"
rostopic pub /bridge_topic/custom_topic_a std_msgs/String "data: '0 32 15.6 /{ciao ciao ciao ciao/}'"
