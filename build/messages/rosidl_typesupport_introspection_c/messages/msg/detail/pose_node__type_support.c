// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from messages:msg/PoseNode.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "messages/msg/detail/pose_node__rosidl_typesupport_introspection_c.h"
#include "messages/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "messages/msg/detail/pose_node__functions.h"
#include "messages/msg/detail/pose_node__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void messages__msg__PoseNode__rosidl_typesupport_introspection_c__PoseNode_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  messages__msg__PoseNode__init(message_memory);
}

void messages__msg__PoseNode__rosidl_typesupport_introspection_c__PoseNode_fini_function(void * message_memory)
{
  messages__msg__PoseNode__fini(message_memory);
}

size_t messages__msg__PoseNode__rosidl_typesupport_introspection_c__size_function__PoseNode__covariance(
  const void * untyped_member)
{
  (void)untyped_member;
  return 9;
}

const void * messages__msg__PoseNode__rosidl_typesupport_introspection_c__get_const_function__PoseNode__covariance(
  const void * untyped_member, size_t index)
{
  const float * member =
    (const float *)(untyped_member);
  return &member[index];
}

void * messages__msg__PoseNode__rosidl_typesupport_introspection_c__get_function__PoseNode__covariance(
  void * untyped_member, size_t index)
{
  float * member =
    (float *)(untyped_member);
  return &member[index];
}

void messages__msg__PoseNode__rosidl_typesupport_introspection_c__fetch_function__PoseNode__covariance(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    messages__msg__PoseNode__rosidl_typesupport_introspection_c__get_const_function__PoseNode__covariance(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void messages__msg__PoseNode__rosidl_typesupport_introspection_c__assign_function__PoseNode__covariance(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    messages__msg__PoseNode__rosidl_typesupport_introspection_c__get_function__PoseNode__covariance(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

static rosidl_typesupport_introspection_c__MessageMember messages__msg__PoseNode__rosidl_typesupport_introspection_c__PoseNode_message_member_array[5] = {
  {
    "id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(messages__msg__PoseNode, id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "x",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(messages__msg__PoseNode, x),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "y",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(messages__msg__PoseNode, y),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "theta",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(messages__msg__PoseNode, theta),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "covariance",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    9,  // array size
    false,  // is upper bound
    offsetof(messages__msg__PoseNode, covariance),  // bytes offset in struct
    NULL,  // default value
    messages__msg__PoseNode__rosidl_typesupport_introspection_c__size_function__PoseNode__covariance,  // size() function pointer
    messages__msg__PoseNode__rosidl_typesupport_introspection_c__get_const_function__PoseNode__covariance,  // get_const(index) function pointer
    messages__msg__PoseNode__rosidl_typesupport_introspection_c__get_function__PoseNode__covariance,  // get(index) function pointer
    messages__msg__PoseNode__rosidl_typesupport_introspection_c__fetch_function__PoseNode__covariance,  // fetch(index, &value) function pointer
    messages__msg__PoseNode__rosidl_typesupport_introspection_c__assign_function__PoseNode__covariance,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers messages__msg__PoseNode__rosidl_typesupport_introspection_c__PoseNode_message_members = {
  "messages__msg",  // message namespace
  "PoseNode",  // message name
  5,  // number of fields
  sizeof(messages__msg__PoseNode),
  messages__msg__PoseNode__rosidl_typesupport_introspection_c__PoseNode_message_member_array,  // message members
  messages__msg__PoseNode__rosidl_typesupport_introspection_c__PoseNode_init_function,  // function to initialize message memory (memory has to be allocated)
  messages__msg__PoseNode__rosidl_typesupport_introspection_c__PoseNode_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t messages__msg__PoseNode__rosidl_typesupport_introspection_c__PoseNode_message_type_support_handle = {
  0,
  &messages__msg__PoseNode__rosidl_typesupport_introspection_c__PoseNode_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_messages
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, messages, msg, PoseNode)() {
  if (!messages__msg__PoseNode__rosidl_typesupport_introspection_c__PoseNode_message_type_support_handle.typesupport_identifier) {
    messages__msg__PoseNode__rosidl_typesupport_introspection_c__PoseNode_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &messages__msg__PoseNode__rosidl_typesupport_introspection_c__PoseNode_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
