# Simple ROS1 BRIDGE example -- a first work

Here is a simple example of usage of the bridge between ROS2 and ROS1: it only makes use of standard messages, because of some limitations in the implementation of the current verison of the ROS1 bridge. 

## Prerequisites

Before testing this package, I suggest you to un-source all your distros. 

The code here is compatible only with **ROS1 noetic** and **ROS2 foxy**. You don't need to clone the bridge, because there's a script inside for downloading a clean version of the bridge.

[Here](https://github.com/ros2/ros1_bridge.git) you can find the code of the ROS1 bridge. 

## Package structure

Here is the structure of the package:

```
/root/simple_bridge
├── shell                      (build and run the project from here) 
├── ws_bridge                  (the worksapce containing the ROS1 bridge)
│   ├── build
│   │   └── ...
│   ├── install
│   │   └── ...
│   ├── log
│   │   └── ...
│   └── src
│       └── ros1_bridge        (the ros bridge package)
│           └── ...
├── ws_ros1
│   └── ...
│   └── src
│       └── ros1_listener_pkg  (the package containing client and subscriber for ROS1)
│           └── src
└── ws_ros2
    └── ...
    └── src
        └── ros2_publisher_pkg  (the package containing publisher and service for ROS2)
            └── src
```

## Set up and build

1. clone this repository into the */root* folder.

2. go inside the folder */root/simple_bridge/shell* and from there run the script **shell_build.sh**. Remember to make all the files executable. The script also downloads and compiles the bridge: it requires 5min on my PC, but iit could require much time.

The scripts also writes some logs you can read from the folder */root/simple_bridge/logs*. 

# How to use this project

We're goigg to open 4 shells in order to run this project. **Remember to un-source all your distros before starting.**

## First test -- publisher in ROS2 and subscriber in ROS1

We're going to test the publisher subscriber using the standard message *std_msgs/msg/String*. Just follow there four steps: 

1. open the first shell, and launch the script */root/simple_bridge/shell/shell_roscore.sh*
2. open the second shell, and run */root/simple_bridge/shell/shell_ros1_listener.sh*
3. open the third shell and run */root/simple_bridge/shell/shell_ros2_publisher.sh*
4. finally, launch the bridge using the script */root/simple_bridge/shell/shell_bridge.sh*

If everythig goes well, you should see that the message from the console ROS2 is sent and received by the console running the ROS1 node. 

## Second test -- service in ROS2 and client in ROS1

In this test, there's a node in ROS1 which sends true or false alternately as a request to a service running on ROS2 of the type *std_srvs/srv/SetBool*. Here are the steps to test out this functionality:

1. open the first shell, and launch the script */root/simple_bridge/shell/shell_roscore.sh*
2. open the second shell, and run */root/simple_bridge/shell/shell_ros1_client.sh*
3. open the third shell and run */root/simple_bridge/shell/shell_ros2_service.sh*
4. finally, launch the bridge using the script */root/simple_bridge/shell/shell_bridge.sh*

# Issues and limitations

- this is just a tiny test with a clean version of the ROS1 bridge; it only shows how to use it, not mentioning how to compile other custom messages and services. 
- the script */root/simple_bridge/shell/shell_main_pub_sub.sh* doesn't work right now. 
