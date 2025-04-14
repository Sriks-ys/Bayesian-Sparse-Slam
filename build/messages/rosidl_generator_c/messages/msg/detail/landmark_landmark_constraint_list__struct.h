// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from messages:msg/LandmarkLandmarkConstraintList.idl
// generated code does not contain a copyright notice

#ifndef MESSAGES__MSG__DETAIL__LANDMARK_LANDMARK_CONSTRAINT_LIST__STRUCT_H_
#define MESSAGES__MSG__DETAIL__LANDMARK_LANDMARK_CONSTRAINT_LIST__STRUCT_H_

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
// Member 'constraints'
#include "messages/msg/detail/landmark_landmark_constraint__struct.h"

/// Struct defined in msg/LandmarkLandmarkConstraintList in the package messages.
typedef struct messages__msg__LandmarkLandmarkConstraintList
{
  std_msgs__msg__Header header;
  messages__msg__LandmarkLandmarkConstraint__Sequence constraints;
} messages__msg__LandmarkLandmarkConstraintList;

// Struct for a sequence of messages__msg__LandmarkLandmarkConstraintList.
typedef struct messages__msg__LandmarkLandmarkConstraintList__Sequence
{
  messages__msg__LandmarkLandmarkConstraintList * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} messages__msg__LandmarkLandmarkConstraintList__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MESSAGES__MSG__DETAIL__LANDMARK_LANDMARK_CONSTRAINT_LIST__STRUCT_H_
