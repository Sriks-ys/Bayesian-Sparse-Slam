// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from messages:msg/PoseConstraint.idl
// generated code does not contain a copyright notice

#ifndef MESSAGES__MSG__DETAIL__POSE_CONSTRAINT__STRUCT_H_
#define MESSAGES__MSG__DETAIL__POSE_CONSTRAINT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/PoseConstraint in the package messages.
typedef struct messages__msg__PoseConstraint
{
  /// ID of first pose
  int32_t pose1_id;
  /// ID of second pose
  int32_t pose2_id;
  /// Relative x displacement
  float dx;
  /// Relative y displacement
  float dy;
  /// Relative yaw displacement (radians)
  float dtheta;
  /// 3x3 Covariance matrix (row-major)
  float covariance[9];
} messages__msg__PoseConstraint;

// Struct for a sequence of messages__msg__PoseConstraint.
typedef struct messages__msg__PoseConstraint__Sequence
{
  messages__msg__PoseConstraint * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} messages__msg__PoseConstraint__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MESSAGES__MSG__DETAIL__POSE_CONSTRAINT__STRUCT_H_
