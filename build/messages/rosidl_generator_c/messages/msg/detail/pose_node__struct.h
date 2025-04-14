// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from messages:msg/PoseNode.idl
// generated code does not contain a copyright notice

#ifndef MESSAGES__MSG__DETAIL__POSE_NODE__STRUCT_H_
#define MESSAGES__MSG__DETAIL__POSE_NODE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/PoseNode in the package messages.
typedef struct messages__msg__PoseNode
{
  /// Unique pose ID
  int32_t id;
  /// X position in meters
  float x;
  /// Y position in meters
  float y;
  /// Orientation (radians)
  float theta;
  /// 3x3 Covariance matrix (row-major)
  float covariance[9];
} messages__msg__PoseNode;

// Struct for a sequence of messages__msg__PoseNode.
typedef struct messages__msg__PoseNode__Sequence
{
  messages__msg__PoseNode * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} messages__msg__PoseNode__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MESSAGES__MSG__DETAIL__POSE_NODE__STRUCT_H_
