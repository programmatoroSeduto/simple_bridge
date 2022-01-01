// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from ros2_bridge_support_pkg:msg/MyCustomMessage.idl
// generated code does not contain a copyright notice

#ifndef ROS2_BRIDGE_SUPPORT_PKG__MSG__DETAIL__MY_CUSTOM_MESSAGE__TRAITS_HPP_
#define ROS2_BRIDGE_SUPPORT_PKG__MSG__DETAIL__MY_CUSTOM_MESSAGE__TRAITS_HPP_

#include "ros2_bridge_support_pkg/msg/detail/my_custom_message__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<ros2_bridge_support_pkg::msg::MyCustomMessage>()
{
  return "ros2_bridge_support_pkg::msg::MyCustomMessage";
}

template<>
inline const char * name<ros2_bridge_support_pkg::msg::MyCustomMessage>()
{
  return "ros2_bridge_support_pkg/msg/MyCustomMessage";
}

template<>
struct has_fixed_size<ros2_bridge_support_pkg::msg::MyCustomMessage>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<ros2_bridge_support_pkg::msg::MyCustomMessage>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<ros2_bridge_support_pkg::msg::MyCustomMessage>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ROS2_BRIDGE_SUPPORT_PKG__MSG__DETAIL__MY_CUSTOM_MESSAGE__TRAITS_HPP_
