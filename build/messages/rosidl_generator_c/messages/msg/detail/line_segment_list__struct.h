// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from messages:msg/LineSegmentList.idl
// generated code does not contain a copyright notice

#ifndef MESSAGES__MSG__DETAIL__LINE_SEGMENT_LIST__STRUCT_H_
#define MESSAGES__MSG__DETAIL__LINE_SEGMENT_LIST__STRUCT_H_

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
#include "messages/msg/detail/line_segment__struct.h"

/// Struct defined in msg/LineSegmentList in the package messages.
typedef struct messages__msg__LineSegmentList
{
  std_msgs__msg__Header header;
  /// Array of line segments
  messages__msg__LineSegment__Sequence segments;
} messages__msg__LineSegmentList;

// Struct for a sequence of messages__msg__LineSegmentList.
typedef struct messages__msg__LineSegmentList__Sequence
{
  messages__msg__LineSegmentList * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} messages__msg__LineSegmentList__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MESSAGES__MSG__DETAIL__LINE_SEGMENT_LIST__STRUCT_H_
