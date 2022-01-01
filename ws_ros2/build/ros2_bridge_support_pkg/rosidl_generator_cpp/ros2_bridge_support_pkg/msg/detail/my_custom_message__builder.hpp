// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from ros2_bridge_support_pkg:msg/MyCustomMessage.idl
// generated code does not contain a copyright notice

#ifndef ROS2_BRIDGE_SUPPORT_PKG__MSG__DETAIL__MY_CUSTOM_MESSAGE__BUILDER_HPP_
#define ROS2_BRIDGE_SUPPORT_PKG__MSG__DETAIL__MY_CUSTOM_MESSAGE__BUILDER_HPP_

#include "ros2_bridge_support_pkg/msg/detail/my_custom_message__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace ros2_bridge_support_pkg
{

namespace msg
{

namespace builder
{

class Init_MyCustomMessage_value_string
{
public:
  explicit Init_MyCustomMessage_value_string(::ros2_bridge_support_pkg::msg::MyCustomMessage & msg)
  : msg_(msg)
  {}
  ::ros2_bridge_support_pkg::msg::MyCustomMessage value_string(::ros2_bridge_support_pkg::msg::MyCustomMessage::_value_string_type arg)
  {
    msg_.value_string = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ros2_bridge_support_pkg::msg::MyCustomMessage msg_;
};

class Init_MyCustomMessage_value_float
{
public:
  explicit Init_MyCustomMessage_value_float(::ros2_bridge_support_pkg::msg::MyCustomMessage & msg)
  : msg_(msg)
  {}
  Init_MyCustomMessage_value_string value_float(::ros2_bridge_support_pkg::msg::MyCustomMessage::_value_float_type arg)
  {
    msg_.value_float = std::move(arg);
    return Init_MyCustomMessage_value_string(msg_);
  }

private:
  ::ros2_bridge_support_pkg::msg::MyCustomMessage msg_;
};

class Init_MyCustomMessage_value_integer
{
public:
  explicit Init_MyCustomMessage_value_integer(::ros2_bridge_support_pkg::msg::MyCustomMessage & msg)
  : msg_(msg)
  {}
  Init_MyCustomMessage_value_float value_integer(::ros2_bridge_support_pkg::msg::MyCustomMessage::_value_integer_type arg)
  {
    msg_.value_integer = std::move(arg);
    return Init_MyCustomMessage_value_float(msg_);
  }

private:
  ::ros2_bridge_support_pkg::msg::MyCustomMessage msg_;
};

class Init_MyCustomMessage_value_boolean
{
public:
  Init_MyCustomMessage_value_boolean()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MyCustomMessage_value_integer value_boolean(::ros2_bridge_support_pkg::msg::MyCustomMessage::_value_boolean_type arg)
  {
    msg_.value_boolean = std::move(arg);
    return Init_MyCustomMessage_value_integer(msg_);
  }

private:
  ::ros2_bridge_support_pkg::msg::MyCustomMessage msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::ros2_bridge_support_pkg::msg::MyCustomMessage>()
{
  return ros2_bridge_support_pkg::msg::builder::Init_MyCustomMessage_value_boolean();
}

}  // namespace ros2_bridge_support_pkg

#endif  // ROS2_BRIDGE_SUPPORT_PKG__MSG__DETAIL__MY_CUSTOM_MESSAGE__BUILDER_HPP_
