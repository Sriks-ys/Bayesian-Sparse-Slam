// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from messages:msg/LandmarkLandmarkConstraint.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "messages/msg/detail/landmark_landmark_constraint__rosidl_typesupport_introspection_c.h"
#include "messages/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "messages/msg/detail/landmark_landmark_constraint__functions.h"
#include "messages/msg/detail/landmark_landmark_constraint__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void messages__msg__LandmarkLandmarkConstraint__rosidl_typesupport_introspection_c__LandmarkLandmarkConstraint_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  messages__msg__LandmarkLandmarkConstraint__init(message_memory);
}

void messages__msg__LandmarkLandmarkConstraint__rosidl_typesupport_introspection_c__LandmarkLandmarkConstraint_fini_function(void * message_memory)
{
  messages__msg__LandmarkLandmarkConstraint__fini(message_memory);
}

size_t messages__msg__LandmarkLandmarkConstraint__rosidl_typesupport_introspection_c__size_function__LandmarkLandmarkConstraint__covariance(
  const void * untyped_member)
{
  (void)untyped_member;
  return 4;
}

const void * messages__msg__LandmarkLandmarkConstraint__rosidl_typesupport_introspection_c__get_const_function__LandmarkLandmarkConstraint__covariance(
  const void * untyped_member, size_t index)
{
  const float * member =
    (const float *)(untyped_member);
  return &member[index];
}

void * messages__msg__LandmarkLandmarkConstraint__rosidl_typesupport_introspection_c__get_function__LandmarkLandmarkConstraint__covariance(
  void * untyped_member, size_t index)
{
  float * member =
    (float *)(untyped_member);
  return &member[index];
}

void messages__msg__LandmarkLandmarkConstraint__rosidl_typesupport_introspection_c__fetch_function__LandmarkLandmarkConstraint__covariance(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    messages__msg__LandmarkLandmarkConstraint__rosidl_typesupport_introspection_c__get_const_function__LandmarkLandmarkConstraint__covariance(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void messages__msg__LandmarkLandmarkConstraint__rosidl_typesupport_introspection_c__assign_function__LandmarkLandmarkConstraint__covariance(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    messages__msg__LandmarkLandmarkConstraint__rosidl_typesupport_introspection_c__get_function__LandmarkLandmarkConstraint__covariance(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

static rosidl_typesupport_introspection_c__MessageMember messages__msg__LandmarkLandmarkConstraint__rosidl_typesupport_introspection_c__LandmarkLandmarkConstraint_message_member_array[6] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(messages__msg__LandmarkLandmarkConstraint, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "landmark1_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(messages__msg__LandmarkLandmarkConstraint, landmark1_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "landmark2_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(messages__msg__LandmarkLandmarkConstraint, landmark2_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "dx",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(messages__msg__LandmarkLandmarkConstraint, dx),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "dy",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(messages__msg__LandmarkLandmarkConstraint, dy),  // bytes offset in struct
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
    4,  // array size
    false,  // is upper bound
    offsetof(messages__msg__LandmarkLandmarkConstraint, covariance),  // bytes offset in struct
    NULL,  // default value
    messages__msg__LandmarkLandmarkConstraint__rosidl_typesupport_introspection_c__size_function__LandmarkLandmarkConstraint__covariance,  // size() function pointer
    messages__msg__LandmarkLandmarkConstraint__rosidl_typesupport_introspection_c__get_const_function__LandmarkLandmarkConstraint__covariance,  // get_const(index) function pointer
    messages__msg__LandmarkLandmarkConstraint__rosidl_typesupport_introspection_c__get_function__LandmarkLandmarkConstraint__covariance,  // get(index) function pointer
    messages__msg__LandmarkLandmarkConstraint__rosidl_typesupport_introspection_c__fetch_function__LandmarkLandmarkConstraint__covariance,  // fetch(index, &value) function pointer
    messages__msg__LandmarkLandmarkConstraint__rosidl_typesupport_introspection_c__assign_function__LandmarkLandmarkConstraint__covariance,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers messages__msg__LandmarkLandmarkConstraint__rosidl_typesupport_introspection_c__LandmarkLandmarkConstraint_message_members = {
  "messages__msg",  // message namespace
  "LandmarkLandmarkConstraint",  // message name
  6,  // number of fields
  sizeof(messages__msg__LandmarkLandmarkConstraint),
  messages__msg__LandmarkLandmarkConstraint__rosidl_typesupport_introspection_c__LandmarkLandmarkConstraint_message_member_array,  // message members
  messages__msg__LandmarkLandmarkConstraint__rosidl_typesupport_introspection_c__LandmarkLandmarkConstraint_init_function,  // function to initialize message memory (memory has to be allocated)
  messages__msg__LandmarkLandmarkConstraint__rosidl_typesupport_introspection_c__LandmarkLandmarkConstraint_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t messages__msg__LandmarkLandmarkConstraint__rosidl_typesupport_introspection_c__LandmarkLandmarkConstraint_message_type_support_handle = {
  0,
  &messages__msg__LandmarkLandmarkConstraint__rosidl_typesupport_introspection_c__LandmarkLandmarkConstraint_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_messages
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, messages, msg, LandmarkLandmarkConstraint)() {
  messages__msg__LandmarkLandmarkConstraint__rosidl_typesupport_introspection_c__LandmarkLandmarkConstraint_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  if (!messages__msg__LandmarkLandmarkConstraint__rosidl_typesupport_introspection_c__LandmarkLandmarkConstraint_message_type_support_handle.typesupport_identifier) {
    messages__msg__LandmarkLandmarkConstraint__rosidl_typesupport_introspection_c__LandmarkLandmarkConstraint_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &messages__msg__LandmarkLandmarkConstraint__rosidl_typesupport_introspection_c__LandmarkLandmarkConstraint_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
