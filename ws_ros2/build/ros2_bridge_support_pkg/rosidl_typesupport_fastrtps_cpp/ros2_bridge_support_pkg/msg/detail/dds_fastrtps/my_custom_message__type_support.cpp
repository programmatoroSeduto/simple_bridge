// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from ros2_bridge_support_pkg:msg/MyCustomMessage.idl
// generated code does not contain a copyright notice
#include "ros2_bridge_support_pkg/msg/detail/my_custom_message__rosidl_typesupport_fastrtps_cpp.hpp"
#include "ros2_bridge_support_pkg/msg/detail/my_custom_message__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace ros2_bridge_support_pkg
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_ros2_bridge_support_pkg
cdr_serialize(
  const ros2_bridge_support_pkg::msg::MyCustomMessage & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: value_boolean
  cdr << (ros_message.value_boolean ? true : false);
  // Member: value_integer
  cdr << ros_message.value_integer;
  // Member: value_float
  cdr << ros_message.value_float;
  // Member: value_string
  cdr << ros_message.value_string;
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_ros2_bridge_support_pkg
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  ros2_bridge_support_pkg::msg::MyCustomMessage & ros_message)
{
  // Member: value_boolean
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.value_boolean = tmp ? true : false;
  }

  // Member: value_integer
  cdr >> ros_message.value_integer;

  // Member: value_float
  cdr >> ros_message.value_float;

  // Member: value_string
  cdr >> ros_message.value_string;

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_ros2_bridge_support_pkg
get_serialized_size(
  const ros2_bridge_support_pkg::msg::MyCustomMessage & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: value_boolean
  {
    size_t item_size = sizeof(ros_message.value_boolean);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: value_integer
  {
    size_t item_size = sizeof(ros_message.value_integer);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: value_float
  {
    size_t item_size = sizeof(ros_message.value_float);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: value_string
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message.value_string.size() + 1);

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_ros2_bridge_support_pkg
max_serialized_size_MyCustomMessage(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;


  // Member: value_boolean
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: value_integer
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: value_float
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: value_string
  {
    size_t array_size = 1;

    full_bounded = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  return current_alignment - initial_alignment;
}

static bool _MyCustomMessage__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const ros2_bridge_support_pkg::msg::MyCustomMessage *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _MyCustomMessage__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<ros2_bridge_support_pkg::msg::MyCustomMessage *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _MyCustomMessage__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const ros2_bridge_support_pkg::msg::MyCustomMessage *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _MyCustomMessage__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_MyCustomMessage(full_bounded, 0);
}

static message_type_support_callbacks_t _MyCustomMessage__callbacks = {
  "ros2_bridge_support_pkg::msg",
  "MyCustomMessage",
  _MyCustomMessage__cdr_serialize,
  _MyCustomMessage__cdr_deserialize,
  _MyCustomMessage__get_serialized_size,
  _MyCustomMessage__max_serialized_size
};

static rosidl_message_type_support_t _MyCustomMessage__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_MyCustomMessage__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace ros2_bridge_support_pkg

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_ros2_bridge_support_pkg
const rosidl_message_type_support_t *
get_message_type_support_handle<ros2_bridge_support_pkg::msg::MyCustomMessage>()
{
  return &ros2_bridge_support_pkg::msg::typesupport_fastrtps_cpp::_MyCustomMessage__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, ros2_bridge_support_pkg, msg, MyCustomMessage)() {
  return &ros2_bridge_support_pkg::msg::typesupport_fastrtps_cpp::_MyCustomMessage__handle;
}

#ifdef __cplusplus
}
#endif
