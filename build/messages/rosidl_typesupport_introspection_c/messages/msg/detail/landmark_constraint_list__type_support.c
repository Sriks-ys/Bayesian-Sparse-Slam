// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from messages:msg/LandmarkConstraintList.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "messages/msg/detail/landmark_constraint_list__rosidl_typesupport_introspection_c.h"
#include "messages/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "messages/msg/detail/landmark_constraint_list__functions.h"
#include "messages/msg/detail/landmark_constraint_list__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `segments`
#include "messages/msg/landmark_constraint.h"
// Member `segments`
#include "messages/msg/detail/landmark_constraint__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void messages__msg__LandmarkConstraintList__rosidl_typesupport_introspection_c__LandmarkConstraintList_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  messages__msg__LandmarkConstraintList__init(message_memory);
}

void messages__msg__LandmarkConstraintList__rosidl_typesupport_introspection_c__LandmarkConstraintList_fini_function(void * message_memory)
{
  messages__msg__LandmarkConstraintList__fini(message_memory);
}

size_t messages__msg__LandmarkConstraintList__rosidl_typesupport_introspection_c__size_function__LandmarkConstraintList__segments(
  const void * untyped_member)
{
  const messages__msg__LandmarkConstraint__Sequence * member =
    (const messages__msg__LandmarkConstraint__Sequence *)(untyped_member);
  return member->size;
}

const void * messages__msg__LandmarkConstraintList__rosidl_typesupport_introspection_c__get_const_function__LandmarkConstraintList__segments(
  const void * untyped_member, size_t index)
{
  const messages__msg__LandmarkConstraint__Sequence * member =
    (const messages__msg__LandmarkConstraint__Sequence *)(untyped_member);
  return &member->data[index];
}

void * messages__msg__LandmarkConstraintList__rosidl_typesupport_introspection_c__get_function__LandmarkConstraintList__segments(
  void * untyped_member, size_t index)
{
  messages__msg__LandmarkConstraint__Sequence * member =
    (messages__msg__LandmarkConstraint__Sequence *)(untyped_member);
  return &member->data[index];
}

void messages__msg__LandmarkConstraintList__rosidl_typesupport_introspection_c__fetch_function__LandmarkConstraintList__segments(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const messages__msg__LandmarkConstraint * item =
    ((const messages__msg__LandmarkConstraint *)
    messages__msg__LandmarkConstraintList__rosidl_typesupport_introspection_c__get_const_function__LandmarkConstraintList__segments(untyped_member, index));
  messages__msg__LandmarkConstraint * value =
    (messages__msg__LandmarkConstraint *)(untyped_value);
  *value = *item;
}

void messages__msg__LandmarkConstraintList__rosidl_typesupport_introspection_c__assign_function__LandmarkConstraintList__segments(
  void * untyped_member, size_t index, const void * untyped_value)
{
  messages__msg__LandmarkConstraint * item =
    ((messages__msg__LandmarkConstraint *)
    messages__msg__LandmarkConstraintList__rosidl_typesupport_introspection_c__get_function__LandmarkConstraintList__segments(untyped_member, index));
  const messages__msg__LandmarkConstraint * value =
    (const messages__msg__LandmarkConstraint *)(untyped_value);
  *item = *value;
}

bool messages__msg__LandmarkConstraintList__rosidl_typesupport_introspection_c__resize_function__LandmarkConstraintList__segments(
  void * untyped_member, size_t size)
{
  messages__msg__LandmarkConstraint__Sequence * member =
    (messages__msg__LandmarkConstraint__Sequence *)(untyped_member);
  messages__msg__LandmarkConstraint__Sequence__fini(member);
  return messages__msg__LandmarkConstraint__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember messages__msg__LandmarkConstraintList__rosidl_typesupport_introspection_c__LandmarkConstraintList_message_member_array[2] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(messages__msg__LandmarkConstraintList, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "segments",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(messages__msg__LandmarkConstraintList, segments),  // bytes offset in struct
    NULL,  // default value
    messages__msg__LandmarkConstraintList__rosidl_typesupport_introspection_c__size_function__LandmarkConstraintList__segments,  // size() function pointer
    messages__msg__LandmarkConstraintList__rosidl_typesupport_introspection_c__get_const_function__LandmarkConstraintList__segments,  // get_const(index) function pointer
    messages__msg__LandmarkConstraintList__rosidl_typesupport_introspection_c__get_function__LandmarkConstraintList__segments,  // get(index) function pointer
    messages__msg__LandmarkConstraintList__rosidl_typesupport_introspection_c__fetch_function__LandmarkConstraintList__segments,  // fetch(index, &value) function pointer
    messages__msg__LandmarkConstraintList__rosidl_typesupport_introspection_c__assign_function__LandmarkConstraintList__segments,  // assign(index, value) function pointer
    messages__msg__LandmarkConstraintList__rosidl_typesupport_introspection_c__resize_function__LandmarkConstraintList__segments  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers messages__msg__LandmarkConstraintList__rosidl_typesupport_introspection_c__LandmarkConstraintList_message_members = {
  "messages__msg",  // message namespace
  "LandmarkConstraintList",  // message name
  2,  // number of fields
  sizeof(messages__msg__LandmarkConstraintList),
  messages__msg__LandmarkConstraintList__rosidl_typesupport_introspection_c__LandmarkConstraintList_message_member_array,  // message members
  messages__msg__LandmarkConstraintList__rosidl_typesupport_introspection_c__LandmarkConstraintList_init_function,  // function to initialize message memory (memory has to be allocated)
  messages__msg__LandmarkConstraintList__rosidl_typesupport_introspection_c__LandmarkConstraintList_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t messages__msg__LandmarkConstraintList__rosidl_typesupport_introspection_c__LandmarkConstraintList_message_type_support_handle = {
  0,
  &messages__msg__LandmarkConstraintList__rosidl_typesupport_introspection_c__LandmarkConstraintList_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_messages
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, messages, msg, LandmarkConstraintList)() {
  messages__msg__LandmarkConstraintList__rosidl_typesupport_introspection_c__LandmarkConstraintList_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  messages__msg__LandmarkConstraintList__rosidl_typesupport_introspection_c__LandmarkConstraintList_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, messages, msg, LandmarkConstraint)();
  if (!messages__msg__LandmarkConstraintList__rosidl_typesupport_introspection_c__LandmarkConstraintList_message_type_support_handle.typesupport_identifier) {
    messages__msg__LandmarkConstraintList__rosidl_typesupport_introspection_c__LandmarkConstraintList_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &messages__msg__LandmarkConstraintList__rosidl_typesupport_introspection_c__LandmarkConstraintList_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
