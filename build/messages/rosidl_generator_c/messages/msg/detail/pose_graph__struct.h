// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from messages:msg/PoseGraph.idl
// generated code does not contain a copyright notice

#ifndef MESSAGES__MSG__DETAIL__POSE_GRAPH__STRUCT_H_
#define MESSAGES__MSG__DETAIL__POSE_GRAPH__STRUCT_H_

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
// Member 'nodes'
#include "messages/msg/detail/pose_node__struct.h"
// Member 'pose_constraints'
#include "messages/msg/detail/pose_constraint__struct.h"
// Member 'landmark_constraints'
#include "messages/msg/detail/landmark_constraint__struct.h"

/// Struct defined in msg/PoseGraph in the package messages.
typedef struct messages__msg__PoseGraph
{
  std_msgs__msg__Header header;
  /// List of all poses
  messages__msg__PoseNode__Sequence nodes;
  /// List of pose-pose edges
  messages__msg__PoseConstraint__Sequence pose_constraints;
  /// List of pose-landmark edges
  messages__msg__LandmarkConstraint__Sequence landmark_constraints;
} messages__msg__PoseGraph;

// Struct for a sequence of messages__msg__PoseGraph.
typedef struct messages__msg__PoseGraph__Sequence
{
  messages__msg__PoseGraph * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} messages__msg__PoseGraph__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MESSAGES__MSG__DETAIL__POSE_GRAPH__STRUCT_H_
