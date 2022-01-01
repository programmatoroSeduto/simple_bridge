// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from ros2_bridge_support_pkg:msg/MyCustomMessage.idl
// generated code does not contain a copyright notice
#include "ros2_bridge_support_pkg/msg/detail/my_custom_message__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "ros2_bridge_support_pkg/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "ros2_bridge_support_pkg/msg/detail/my_custom_message__struct.h"
#include "ros2_bridge_support_pkg/msg/detail/my_custom_message__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "rosidl_runtime_c/string.h"  // value_string
#include "rosidl_runtime_c/string_functions.h"  // value_string

// forward declare type support functions


using _MyCustomMessage__ros_msg_type = ros2_bridge_support_pkg__msg__MyCustomMessage;

static bool _MyCustomMessage__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _MyCustomMessage__ros_msg_type * ros_message = static_cast<const _MyCustomMessage__ros_msg_type *>(untyped_ros_message);
  // Field name: value_boolean
  {
    cdr << (ros_message->value_boolean ? true : false);
  }

  // Field name: value_integer
  {
    cdr << ros_message->value_integer;
  }

  // Field name: value_float
  {
    cdr << ros_message->value_float;
  }

  // Field name: value_string
  {
    const rosidl_runtime_c__String * str = &ros_message->value_string;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  return true;
}

static bool _MyCustomMessage__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _MyCustomMessage__ros_msg_type * ros_message = static_cast<_MyCustomMessage__ros_msg_type *>(untyped_ros_message);
  // Field name: value_boolean
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->value_boolean = tmp ? true : false;
  }

  // Field name: value_integer
  {
    cdr >> ros_message->value_integer;
  }

  // Field name: value_float
  {
    cdr >> ros_message->value_float;
  }

  // Field name: value_string
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->value_string.data) {
      rosidl_runtime_c__String__init(&ros_message->value_string);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->value_string,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'value_string'\n");
      return false;
    }
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_ros2_bridge_support_pkg
size_t get_serialized_size_ros2_bridge_support_pkg__msg__MyCustomMessage(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _MyCustomMessage__ros_msg_type * ros_message = static_cast<const _MyCustomMessage__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name value_boolean
  {
    size_t item_size = sizeof(ros_message->value_boolean);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name value_integer
  {
    size_t item_size = sizeof(ros_message->value_integer);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name value_float
  {
    size_t item_size = sizeof(ros_message->value_float);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name value_string
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->value_string.size + 1);

  return current_alignment - initial_alignment;
}

static uint32_t _MyCustomMessage__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_ros2_bridge_support_pkg__msg__MyCustomMessage(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_ros2_bridge_support_pkg
size_t max_serialized_size_ros2_bridge_support_pkg__msg__MyCustomMessage(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;

  // member: value_boolean
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: value_integer
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: value_float
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: value_string
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

static size_t _MyCustomMessage__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_ros2_bridge_support_pkg__msg__MyCustomMessage(
    full_bounded, 0);
}


static message_type_support_callbacks_t __callbacks_MyCustomMessage = {
  "ros2_bridge_support_pkg::msg",
  "MyCustomMessage",
  _MyCustomMessage__cdr_serialize,
  _MyCustomMessage__cdr_deserialize,
  _MyCustomMessage__get_serialized_size,
  _MyCustomMessage__max_serialized_size
};

static rosidl_message_type_support_t _MyCustomMessage__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_MyCustomMessage,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, ros2_bridge_support_pkg, msg, MyCustomMessage)() {
  return &_MyCustomMessage__type_support;
}

#if defined(__cplusplus)
}
#endif
