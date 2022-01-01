// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from ros2_bridge_support_pkg:msg/MyCustomMessage.idl
// generated code does not contain a copyright notice
#include "ros2_bridge_support_pkg/msg/detail/my_custom_message__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


// Include directives for member types
// Member `value_string`
#include "rosidl_runtime_c/string_functions.h"

bool
ros2_bridge_support_pkg__msg__MyCustomMessage__init(ros2_bridge_support_pkg__msg__MyCustomMessage * msg)
{
  if (!msg) {
    return false;
  }
  // value_boolean
  // value_integer
  // value_float
  // value_string
  if (!rosidl_runtime_c__String__init(&msg->value_string)) {
    ros2_bridge_support_pkg__msg__MyCustomMessage__fini(msg);
    return false;
  }
  return true;
}

void
ros2_bridge_support_pkg__msg__MyCustomMessage__fini(ros2_bridge_support_pkg__msg__MyCustomMessage * msg)
{
  if (!msg) {
    return;
  }
  // value_boolean
  // value_integer
  // value_float
  // value_string
  rosidl_runtime_c__String__fini(&msg->value_string);
}

ros2_bridge_support_pkg__msg__MyCustomMessage *
ros2_bridge_support_pkg__msg__MyCustomMessage__create()
{
  ros2_bridge_support_pkg__msg__MyCustomMessage * msg = (ros2_bridge_support_pkg__msg__MyCustomMessage *)malloc(sizeof(ros2_bridge_support_pkg__msg__MyCustomMessage));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(ros2_bridge_support_pkg__msg__MyCustomMessage));
  bool success = ros2_bridge_support_pkg__msg__MyCustomMessage__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
ros2_bridge_support_pkg__msg__MyCustomMessage__destroy(ros2_bridge_support_pkg__msg__MyCustomMessage * msg)
{
  if (msg) {
    ros2_bridge_support_pkg__msg__MyCustomMessage__fini(msg);
  }
  free(msg);
}


bool
ros2_bridge_support_pkg__msg__MyCustomMessage__Sequence__init(ros2_bridge_support_pkg__msg__MyCustomMessage__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  ros2_bridge_support_pkg__msg__MyCustomMessage * data = NULL;
  if (size) {
    data = (ros2_bridge_support_pkg__msg__MyCustomMessage *)calloc(size, sizeof(ros2_bridge_support_pkg__msg__MyCustomMessage));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = ros2_bridge_support_pkg__msg__MyCustomMessage__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        ros2_bridge_support_pkg__msg__MyCustomMessage__fini(&data[i - 1]);
      }
      free(data);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
ros2_bridge_support_pkg__msg__MyCustomMessage__Sequence__fini(ros2_bridge_support_pkg__msg__MyCustomMessage__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      ros2_bridge_support_pkg__msg__MyCustomMessage__fini(&array->data[i]);
    }
    free(array->data);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

ros2_bridge_support_pkg__msg__MyCustomMessage__Sequence *
ros2_bridge_support_pkg__msg__MyCustomMessage__Sequence__create(size_t size)
{
  ros2_bridge_support_pkg__msg__MyCustomMessage__Sequence * array = (ros2_bridge_support_pkg__msg__MyCustomMessage__Sequence *)malloc(sizeof(ros2_bridge_support_pkg__msg__MyCustomMessage__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = ros2_bridge_support_pkg__msg__MyCustomMessage__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
ros2_bridge_support_pkg__msg__MyCustomMessage__Sequence__destroy(ros2_bridge_support_pkg__msg__MyCustomMessage__Sequence * array)
{
  if (array) {
    ros2_bridge_support_pkg__msg__MyCustomMessage__Sequence__fini(array);
  }
  free(array);
}
