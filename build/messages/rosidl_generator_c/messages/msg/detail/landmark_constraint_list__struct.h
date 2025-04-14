// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from messages:msg/LandmarkConstraintList.idl
// generated code does not contain a copyright notice

#ifndef MESSAGES__MSG__DETAIL__LANDMARK_CONSTRAINT_LIST__STRUCT_H_
#define MESSAGES__MSG__DETAIL__LANDMARK_CONSTRAINT_LIST__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'segments'
#include "messages/msg/detail/landmark_constraint__struct.h"

/// Struct defined in msg/LandmarkConstraintList in the package messages.
typedef struct messages__msg__LandmarkConstraintList
{
  std_msgs__msg__Header header;
  /// Array of line segments
  messages__msg__LandmarkConstraint__Sequence segments;
} messages__msg__LandmarkConstraintList;

// Struct for a sequence of messages__msg__LandmarkConstraintList.
typedef struct messages__msg__LandmarkConstraintList__Sequence
{
  messages__msg__LandmarkConstraintList * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} messages__msg__LandmarkConstraintList__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MESSAGES__MSG__DETAIL__LANDMARK_CONSTRAINT_LIST__STRUCT_H_
