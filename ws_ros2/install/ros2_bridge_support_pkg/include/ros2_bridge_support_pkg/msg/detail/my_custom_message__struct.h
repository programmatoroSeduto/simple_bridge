// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from ros2_bridge_support_pkg:msg/MyCustomMessage.idl
// generated code does not contain a copyright notice

#ifndef ROS2_BRIDGE_SUPPORT_PKG__MSG__DETAIL__MY_CUSTOM_MESSAGE__STRUCT_H_
#define ROS2_BRIDGE_SUPPORT_PKG__MSG__DETAIL__MY_CUSTOM_MESSAGE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'value_string'
#include "rosidl_runtime_c/string.h"

// Struct defined in msg/MyCustomMessage in the package ros2_bridge_support_pkg.
typedef struct ros2_bridge_support_pkg__msg__MyCustomMessage
{
  bool value_boolean;
  int32_t value_integer;
  float value_float;
  rosidl_runtime_c__String value_string;
} ros2_bridge_support_pkg__msg__MyCustomMessage;

// Struct for a sequence of ros2_bridge_support_pkg__msg__MyCustomMessage.
typedef struct ros2_bridge_support_pkg__msg__MyCustomMessage__Sequence
{
  ros2_bridge_support_pkg__msg__MyCustomMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ros2_bridge_support_pkg__msg__MyCustomMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROS2_BRIDGE_SUPPORT_PKG__MSG__DETAIL__MY_CUSTOM_MESSAGE__STRUCT_H_
