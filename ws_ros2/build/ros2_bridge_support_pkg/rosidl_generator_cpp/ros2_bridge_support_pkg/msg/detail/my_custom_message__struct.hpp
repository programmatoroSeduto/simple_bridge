// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from ros2_bridge_support_pkg:msg/MyCustomMessage.idl
// generated code does not contain a copyright notice

#ifndef ROS2_BRIDGE_SUPPORT_PKG__MSG__DETAIL__MY_CUSTOM_MESSAGE__STRUCT_HPP_
#define ROS2_BRIDGE_SUPPORT_PKG__MSG__DETAIL__MY_CUSTOM_MESSAGE__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__ros2_bridge_support_pkg__msg__MyCustomMessage __attribute__((deprecated))
#else
# define DEPRECATED__ros2_bridge_support_pkg__msg__MyCustomMessage __declspec(deprecated)
#endif

namespace ros2_bridge_support_pkg
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct MyCustomMessage_
{
  using Type = MyCustomMessage_<ContainerAllocator>;

  explicit MyCustomMessage_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->value_boolean = false;
      this->value_integer = 0l;
      this->value_float = 0.0f;
      this->value_string = "";
    }
  }

  explicit MyCustomMessage_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : value_string(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->value_boolean = false;
      this->value_integer = 0l;
      this->value_float = 0.0f;
      this->value_string = "";
    }
  }

  // field types and members
  using _value_boolean_type =
    bool;
  _value_boolean_type value_boolean;
  using _value_integer_type =
    int32_t;
  _value_integer_type value_integer;
  using _value_float_type =
    float;
  _value_float_type value_float;
  using _value_string_type =
    std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>;
  _value_string_type value_string;

  // setters for named parameter idiom
  Type & set__value_boolean(
    const bool & _arg)
  {
    this->value_boolean = _arg;
    return *this;
  }
  Type & set__value_integer(
    const int32_t & _arg)
  {
    this->value_integer = _arg;
    return *this;
  }
  Type & set__value_float(
    const float & _arg)
  {
    this->value_float = _arg;
    return *this;
  }
  Type & set__value_string(
    const std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other> & _arg)
  {
    this->value_string = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    ros2_bridge_support_pkg::msg::MyCustomMessage_<ContainerAllocator> *;
  using ConstRawPtr =
    const ros2_bridge_support_pkg::msg::MyCustomMessage_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<ros2_bridge_support_pkg::msg::MyCustomMessage_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<ros2_bridge_support_pkg::msg::MyCustomMessage_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      ros2_bridge_support_pkg::msg::MyCustomMessage_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<ros2_bridge_support_pkg::msg::MyCustomMessage_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      ros2_bridge_support_pkg::msg::MyCustomMessage_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<ros2_bridge_support_pkg::msg::MyCustomMessage_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<ros2_bridge_support_pkg::msg::MyCustomMessage_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<ros2_bridge_support_pkg::msg::MyCustomMessage_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__ros2_bridge_support_pkg__msg__MyCustomMessage
    std::shared_ptr<ros2_bridge_support_pkg::msg::MyCustomMessage_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__ros2_bridge_support_pkg__msg__MyCustomMessage
    std::shared_ptr<ros2_bridge_support_pkg::msg::MyCustomMessage_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MyCustomMessage_ & other) const
  {
    if (this->value_boolean != other.value_boolean) {
      return false;
    }
    if (this->value_integer != other.value_integer) {
      return false;
    }
    if (this->value_float != other.value_float) {
      return false;
    }
    if (this->value_string != other.value_string) {
      return false;
    }
    return true;
  }
  bool operator!=(const MyCustomMessage_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MyCustomMessage_

// alias to use template instance with default allocator
using MyCustomMessage =
  ros2_bridge_support_pkg::msg::MyCustomMessage_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace ros2_bridge_support_pkg

#endif  // ROS2_BRIDGE_SUPPORT_PKG__MSG__DETAIL__MY_CUSTOM_MESSAGE__STRUCT_HPP_
