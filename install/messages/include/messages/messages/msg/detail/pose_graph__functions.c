// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from messages:msg/PoseGraph.idl
// generated code does not contain a copyright notice
#include "messages/msg/detail/pose_graph__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `nodes`
#include "messages/msg/detail/pose_node__functions.h"
// Member `pose_constraints`
#include "messages/msg/detail/pose_constraint__functions.h"
// Member `landmark_constraints`
#include "messages/msg/detail/landmark_constraint__functions.h"

bool
messages__msg__PoseGraph__init(messages__msg__PoseGraph * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    messages__msg__PoseGraph__fini(msg);
    return false;
  }
  // nodes
  if (!messages__msg__PoseNode__Sequence__init(&msg->nodes, 0)) {
    messages__msg__PoseGraph__fini(msg);
    return false;
  }
  // pose_constraints
  if (!messages__msg__PoseConstraint__Sequence__init(&msg->pose_constraints, 0)) {
    messages__msg__PoseGraph__fini(msg);
    return false;
  }
  // landmark_constraints
  if (!messages__msg__LandmarkConstraint__Sequence__init(&msg->landmark_constraints, 0)) {
    messages__msg__PoseGraph__fini(msg);
    return false;
  }
  return true;
}

void
messages__msg__PoseGraph__fini(messages__msg__PoseGraph * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // nodes
  messages__msg__PoseNode__Sequence__fini(&msg->nodes);
  // pose_constraints
  messages__msg__PoseConstraint__Sequence__fini(&msg->pose_constraints);
  // landmark_constraints
  messages__msg__LandmarkConstraint__Sequence__fini(&msg->landmark_constraints);
}

bool
messages__msg__PoseGraph__are_equal(const messages__msg__PoseGraph * lhs, const messages__msg__PoseGraph * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // nodes
  if (!messages__msg__PoseNode__Sequence__are_equal(
      &(lhs->nodes), &(rhs->nodes)))
  {
    return false;
  }
  // pose_constraints
  if (!messages__msg__PoseConstraint__Sequence__are_equal(
      &(lhs->pose_constraints), &(rhs->pose_constraints)))
  {
    return false;
  }
  // landmark_constraints
  if (!messages__msg__LandmarkConstraint__Sequence__are_equal(
      &(lhs->landmark_constraints), &(rhs->landmark_constraints)))
  {
    return false;
  }
  return true;
}

bool
messages__msg__PoseGraph__copy(
  const messages__msg__PoseGraph * input,
  messages__msg__PoseGraph * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // nodes
  if (!messages__msg__PoseNode__Sequence__copy(
      &(input->nodes), &(output->nodes)))
  {
    return false;
  }
  // pose_constraints
  if (!messages__msg__PoseConstraint__Sequence__copy(
      &(input->pose_constraints), &(output->pose_constraints)))
  {
    return false;
  }
  // landmark_constraints
  if (!messages__msg__LandmarkConstraint__Sequence__copy(
      &(input->landmark_constraints), &(output->landmark_constraints)))
  {
    return false;
  }
  return true;
}

messages__msg__PoseGraph *
messages__msg__PoseGraph__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  messages__msg__PoseGraph * msg = (messages__msg__PoseGraph *)allocator.allocate(sizeof(messages__msg__PoseGraph), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(messages__msg__PoseGraph));
  bool success = messages__msg__PoseGraph__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
messages__msg__PoseGraph__destroy(messages__msg__PoseGraph * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    messages__msg__PoseGraph__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
messages__msg__PoseGraph__Sequence__init(messages__msg__PoseGraph__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  messages__msg__PoseGraph * data = NULL;

  if (size) {
    data = (messages__msg__PoseGraph *)allocator.zero_allocate(size, sizeof(messages__msg__PoseGraph), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = messages__msg__PoseGraph__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        messages__msg__PoseGraph__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
messages__msg__PoseGraph__Sequence__fini(messages__msg__PoseGraph__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      messages__msg__PoseGraph__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

messages__msg__PoseGraph__Sequence *
messages__msg__PoseGraph__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  messages__msg__PoseGraph__Sequence * array = (messages__msg__PoseGraph__Sequence *)allocator.allocate(sizeof(messages__msg__PoseGraph__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = messages__msg__PoseGraph__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
messages__msg__PoseGraph__Sequence__destroy(messages__msg__PoseGraph__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    messages__msg__PoseGraph__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
messages__msg__PoseGraph__Sequence__are_equal(const messages__msg__PoseGraph__Sequence * lhs, const messages__msg__PoseGraph__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!messages__msg__PoseGraph__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
messages__msg__PoseGraph__Sequence__copy(
  const messages__msg__PoseGraph__Sequence * input,
  messages__msg__PoseGraph__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(messages__msg__PoseGraph);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    messages__msg__PoseGraph * data =
      (messages__msg__PoseGraph *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!messages__msg__PoseGraph__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          messages__msg__PoseGraph__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!messages__msg__PoseGraph__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
