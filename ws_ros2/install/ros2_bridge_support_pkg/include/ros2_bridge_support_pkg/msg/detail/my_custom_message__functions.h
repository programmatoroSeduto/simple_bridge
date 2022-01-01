// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from ros2_bridge_support_pkg:msg/MyCustomMessage.idl
// generated code does not contain a copyright notice

#ifndef ROS2_BRIDGE_SUPPORT_PKG__MSG__DETAIL__MY_CUSTOM_MESSAGE__FUNCTIONS_H_
#define ROS2_BRIDGE_SUPPORT_PKG__MSG__DETAIL__MY_CUSTOM_MESSAGE__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "ros2_bridge_support_pkg/msg/rosidl_generator_c__visibility_control.h"

#include "ros2_bridge_support_pkg/msg/detail/my_custom_message__struct.h"

/// Initialize msg/MyCustomMessage message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * ros2_bridge_support_pkg__msg__MyCustomMessage
 * )) before or use
 * ros2_bridge_support_pkg__msg__MyCustomMessage__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_ros2_bridge_support_pkg
bool
ros2_bridge_support_pkg__msg__MyCustomMessage__init(ros2_bridge_support_pkg__msg__MyCustomMessage * msg);

/// Finalize msg/MyCustomMessage message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ros2_bridge_support_pkg
void
ros2_bridge_support_pkg__msg__MyCustomMessage__fini(ros2_bridge_support_pkg__msg__MyCustomMessage * msg);

/// Create msg/MyCustomMessage message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * ros2_bridge_support_pkg__msg__MyCustomMessage__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ros2_bridge_support_pkg
ros2_bridge_support_pkg__msg__MyCustomMessage *
ros2_bridge_support_pkg__msg__MyCustomMessage__create();

/// Destroy msg/MyCustomMessage message.
/**
 * It calls
 * ros2_bridge_support_pkg__msg__MyCustomMessage__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ros2_bridge_support_pkg
void
ros2_bridge_support_pkg__msg__MyCustomMessage__destroy(ros2_bridge_support_pkg__msg__MyCustomMessage * msg);


/// Initialize array of msg/MyCustomMessage messages.
/**
 * It allocates the memory for the number of elements and calls
 * ros2_bridge_support_pkg__msg__MyCustomMessage__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_ros2_bridge_support_pkg
bool
ros2_bridge_support_pkg__msg__MyCustomMessage__Sequence__init(ros2_bridge_support_pkg__msg__MyCustomMessage__Sequence * array, size_t size);

/// Finalize array of msg/MyCustomMessage messages.
/**
 * It calls
 * ros2_bridge_support_pkg__msg__MyCustomMessage__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ros2_bridge_support_pkg
void
ros2_bridge_support_pkg__msg__MyCustomMessage__Sequence__fini(ros2_bridge_support_pkg__msg__MyCustomMessage__Sequence * array);

/// Create array of msg/MyCustomMessage messages.
/**
 * It allocates the memory for the array and calls
 * ros2_bridge_support_pkg__msg__MyCustomMessage__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ros2_bridge_support_pkg
ros2_bridge_support_pkg__msg__MyCustomMessage__Sequence *
ros2_bridge_support_pkg__msg__MyCustomMessage__Sequence__create(size_t size);

/// Destroy array of msg/MyCustomMessage messages.
/**
 * It calls
 * ros2_bridge_support_pkg__msg__MyCustomMessage__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ros2_bridge_support_pkg
void
ros2_bridge_support_pkg__msg__MyCustomMessage__Sequence__destroy(ros2_bridge_support_pkg__msg__MyCustomMessage__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // ROS2_BRIDGE_SUPPORT_PKG__MSG__DETAIL__MY_CUSTOM_MESSAGE__FUNCTIONS_H_
