# ROS1 BRIDGE SUPPORT

*Francesco Ganci*, 2022

This repository contains a overlay of the ROS1 BRIDGE which can map custom messages and services between ROS1 and ROS2 using the vanilla version of the bridge. 

## Prerequisites and depts

Before building and running this package, I suggest you to un-source all your distros. 

The code here is compatible only with **ROS1 noetic** and **ROS2 foxy**. You don't need to clone the bridge, because there's a script inside for downloading a clean version of the bridge.

[Here](https://github.com/ros2/ros1_bridge.git) you can find the official vanilla code of the ROS1 BRIDGE.

## Set up and build

1. clone this repository into the */root* folder. 

```bash
git clone https://github.com/programmatoroSeduto/simple_bridge.git /root
```

2. go inside the folder */root/simple_bridge/shell* and from there run the script **shell_build.sh**. Remember to make all the files executable. The script also downloads and compiles the bridge: it requires 5 minutes on my PC, but it could require much time.

```
# chmod +x /root/simple_bridge/shell/*

# complete build process
source /root/simple_bridge/shell/shell_build.sh

# workspaced only
source /root/simple_bridge/shell/shell_build_ws_only.sh
```

The scripts also writes some logs you can read from the folder */root/simple_bridge/logs*. If you only need to build the workspaces without the bridge, you can use the script */root/simple_bridge/shell/shell_build_ws_only.sh*. 

# How this project works

The principle is super easy: all the channels are transmitted between ROS1 and ROS2 *using standard strings and topics*. Informations are serialized into strings (in the code, this operation is called *cast*), then sent to the other side using strings, then it is recomposed (in the code, this operation is called *cast back*) and returned to the end-point. 

# Limitations

- the actual version has static mapping only: each time a new topic is added, the bridge support package should be rewritten and recompiled
- string conversion of numbers with high precision could cause issues
