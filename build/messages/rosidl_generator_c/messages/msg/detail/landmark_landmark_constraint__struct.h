// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from messages:msg/LandmarkLandmarkConstraint.idl
// generated code does not contain a copyright notice

#ifndef MESSAGES__MSG__DETAIL__LANDMARK_LANDMARK_CONSTRAINT__STRUCT_H_
#define MESSAGES__MSG__DETAIL__LANDMARK_LANDMARK_CONSTRAINT__STRUCT_H_

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

/// Struct defined in msg/LandmarkLandmarkConstraint in the package messages.
typedef struct messages__msg__LandmarkLandmarkConstraint
{
  std_msgs__msg__Header header;
  int32_t landmark1_id;
  int32_t landmark2_id;
  float dx;
  float dy;
  /// 2x2 row-major covariance matrix
  float covariance[4];
} messages__msg__LandmarkLandmarkConstraint;

// Struct for a sequence of messages__msg__LandmarkLandmarkConstraint.
typedef struct messages__msg__LandmarkLandmarkConstraint__Sequence
{
  messages__msg__LandmarkLandmarkConstraint * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} messages__msg__LandmarkLandmarkConstraint__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MESSAGES__MSG__DETAIL__LANDMARK_LANDMARK_CONSTRAINT__STRUCT_H_
