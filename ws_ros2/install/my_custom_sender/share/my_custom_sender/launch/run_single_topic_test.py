from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
   return LaunchDescription([
		Node(
			package = "ros2_bridge_support_pkg",
			executable = "ROS2_bridge_topic_sender",
			output="screen",
			emulate_tty=True
		),
		Node(
			package = "my_custom_sender",
			executable = "ros2_sender",
			output="screen",
			emulate_tty=True
		)
   ])
