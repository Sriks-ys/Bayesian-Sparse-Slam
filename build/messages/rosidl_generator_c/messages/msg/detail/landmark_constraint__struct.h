// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from messages:msg/LandmarkConstraint.idl
// generated code does not contain a copyright notice

#ifndef MESSAGES__MSG__DETAIL__LANDMARK_CONSTRAINT__STRUCT_H_
#define MESSAGES__MSG__DETAIL__LANDMARK_CONSTRAINT__STRUCT_H_

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

/// Struct defined in msg/LandmarkConstraint in the package messages.
typedef struct messages__msg__LandmarkConstraint
{
  std_msgs__msg__Header header;
  /// ID of observing pose
  int32_t pose_id;
  /// ID of associated landmark
  int32_t landmark_id;
  /// Distance from origin
  float rho;
  /// Angle in radians
  float alpha;
  /// 2x2 Covariance matrix (row-major)
  float covariance[4];
} messages__msg__LandmarkConstraint;

// Struct for a sequence of messages__msg__LandmarkConstraint.
typedef struct messages__msg__LandmarkConstraint__Sequence
{
  messages__msg__LandmarkConstraint * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} messages__msg__LandmarkConstraint__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MESSAGES__MSG__DETAIL__LANDMARK_CONSTRAINT__STRUCT_H_
