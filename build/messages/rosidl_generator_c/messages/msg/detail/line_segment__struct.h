// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from messages:msg/LineSegment.idl
// generated code does not contain a copyright notice

#ifndef MESSAGES__MSG__DETAIL__LINE_SEGMENT__STRUCT_H_
#define MESSAGES__MSG__DETAIL__LINE_SEGMENT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'start'
// Member 'end'
#include "geometry_msgs/msg/detail/point__struct.h"

/// Struct defined in msg/LineSegment in the package messages.
typedef struct messages__msg__LineSegment
{
  /// Distance from origin
  float rho;
  /// Angle in radians
  float alpha;
  /// 2x2 Covariance matrix (row-major)
  float covariance[4];
  /// Start point of the line
  geometry_msgs__msg__Point start;
  /// End point of the line
  geometry_msgs__msg__Point end;
} messages__msg__LineSegment;

// Struct for a sequence of messages__msg__LineSegment.
typedef struct messages__msg__LineSegment__Sequence
{
  messages__msg__LineSegment * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} messages__msg__LineSegment__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MESSAGES__MSG__DETAIL__LINE_SEGMENT__STRUCT_H_
