#! /bin/bash

set -e

source /opt/ros/foxy/setup.bash
source /root/simple_bridge/ws_ros2/install/setup.sh

echo "pub on topic -- /bridge_topic/custom_topic_b"
# ros2 topic pub /custom_topic_b ros2_bridge_support_pkg/msg/MyCustomMessage &
ros2 topic pub -t 5 /bridge_topic/custom_topic_b std_msgs/msg/String "{data: '1 1 1.1 /{ciao ciao ci/}'}" &

echo "echo from topic -- /custom_topic_b"
# ros2 topic echo /bridge_topic/custom_topic_b
ros2 topic echo /custom_topic_b
