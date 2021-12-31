#! /bin/bash
# terminator --working-directory="/root/simple_bridge/ws_" --title="ROS " -e "source /root/simple_bridge/shell/shell_.sh"

clear
set -e 

echo "executing the ROS1 main ..."
terminator --working-directory="/root/shell" --title="ROS MASTER" --hidden -e "source /root/simple_bridge/shell/shell_roscore.sh"
echo "waiting for the ROS MASTER ..."
sleep 5s
echo "OK! -- ROS MASTER online"

echo "executing -> ROS BRIDGE"
terminator --working-directory="/root/simple_bridge/ws_bridge" --title="ROS BRIDGE" -e "source /root/simple_bridge/shell/shell_bidge.sh"
echo "waiting for the ROS1 BRIDGE ..."
sleep 5s
echo "OK! -- bridge online"

echo "executing -> ROS2 publisher"
terminator --working-directory="/root/simple_bridge/ws_ros1" --title="ROS1 listener" -e "source /root/simple_bridge/shell/shell_ros1_listener.sh"
sleep 2s
echo "OK! -- ROS2 publisher online"

echo "executing -> ROS1 listener"
terminator --working-directory="/root/simple_bridge/ws_ros2" --title="ROS2 publisher" -e "source /root/simple_bridge/shell/shell_ros2_publisher.sh"
sleep 2s
echo "OK! -- ROS1 listener online"
