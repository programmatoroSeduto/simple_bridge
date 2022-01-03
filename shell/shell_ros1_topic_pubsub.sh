#! /bin/bash

## DESCRIPTION
#    this script first sends a stub message to /custom_topic_b
#    the bridge should receive the message and cast it 
#    the message should be casted then sent through /bridge_topic/custom_topic_b

source /opt/ros/noetic/setup.bash
source /root/simple_bridge/ws_ros1/devel/setup.bash

# roslaunch my_custom_listener run_single_topic_test.launch 
echo "pub on topic -- /custom_topic_b"
rostopic pub --once /custom_topic_b ros1_bridge_support_pkg/MyCustomMessage "value_boolean: false
value_integer: 0
value_float: 0.0
value_string: 'ciao ciao ciao'" &
echo "PUB done!"

echo "echo from topic -- /bridge_topic/custom_topic_b"
rostopic echo /bridge_topic/custom_topic_b
