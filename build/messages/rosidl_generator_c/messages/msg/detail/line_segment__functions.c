// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from messages:msg/LineSegment.idl
// generated code does not contain a copyright notice
#include "messages/msg/detail/line_segment__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `start`
// Member `end`
#include "geometry_msgs/msg/detail/point__functions.h"

bool
messages__msg__LineSegment__init(messages__msg__LineSegment * msg)
{
  if (!msg) {
    return false;
  }
  // rho
  // alpha
  // covariance
  // start
  if (!geometry_msgs__msg__Point__init(&msg->start)) {
    messages__msg__LineSegment__fini(msg);
    return false;
  }
  // end
  if (!geometry_msgs__msg__Point__init(&msg->end)) {
    messages__msg__LineSegment__fini(msg);
    return false;
  }
  return true;
}

void
messages__msg__LineSegment__fini(messages__msg__LineSegment * msg)
{
  if (!msg) {
    return;
  }
  // rho
  // alpha
  // covariance
  // start
  geometry_msgs__msg__Point__fini(&msg->start);
  // end
  geometry_msgs__msg__Point__fini(&msg->end);
}

bool
messages__msg__LineSegment__are_equal(const messages__msg__LineSegment * lhs, const messages__msg__LineSegment * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // rho
  if (lhs->rho != rhs->rho) {
    return false;
  }
  // alpha
  if (lhs->alpha != rhs->alpha) {
    return false;
  }
  // covariance
  for (size_t i = 0; i < 4; ++i) {
    if (lhs->covariance[i] != rhs->covariance[i]) {
      return false;
    }
  }
  // start
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->start), &(rhs->start)))
  {
    return false;
  }
  // end
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->end), &(rhs->end)))
  {
    return false;
  }
  return true;
}

bool
messages__msg__LineSegment__copy(
  const messages__msg__LineSegment * input,
  messages__msg__LineSegment * output)
{
  if (!input || !output) {
    return false;
  }
  // rho
  output->rho = input->rho;
  // alpha
  output->alpha = input->alpha;
  // covariance
  for (size_t i = 0; i < 4; ++i) {
    output->covariance[i] = input->covariance[i];
  }
  // start
  if (!geometry_msgs__msg__Point__copy(
      &(input->start), &(output->start)))
  {
    return false;
  }
  // end
  if (!geometry_msgs__msg__Point__copy(
      &(input->end), &(output->end)))
  {
    return false;
  }
  return true;
}

messages__msg__LineSegment *
messages__msg__LineSegment__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  messages__msg__LineSegment * msg = (messages__msg__LineSegment *)allocator.allocate(sizeof(messages__msg__LineSegment), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(messages__msg__LineSegment));
  bool success = messages__msg__LineSegment__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
messages__msg__LineSegment__destroy(messages__msg__LineSegment * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    messages__msg__LineSegment__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
messages__msg__LineSegment__Sequence__init(messages__msg__LineSegment__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  messages__msg__LineSegment * data = NULL;

  if (size) {
    data = (messages__msg__LineSegment *)allocator.zero_allocate(size, sizeof(messages__msg__LineSegment), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = messages__msg__LineSegment__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        messages__msg__LineSegment__fini(&data[i - 1]);
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
messages__msg__LineSegment__Sequence__fini(messages__msg__LineSegment__Sequence * array)
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
      messages__msg__LineSegment__fini(&array->data[i]);
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

messages__msg__LineSegment__Sequence *
messages__msg__LineSegment__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  messages__msg__LineSegment__Sequence * array = (messages__msg__LineSegment__Sequence *)allocator.allocate(sizeof(messages__msg__LineSegment__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = messages__msg__LineSegment__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
messages__msg__LineSegment__Sequence__destroy(messages__msg__LineSegment__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    messages__msg__LineSegment__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
messages__msg__LineSegment__Sequence__are_equal(const messages__msg__LineSegment__Sequence * lhs, const messages__msg__LineSegment__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!messages__msg__LineSegment__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
messages__msg__LineSegment__Sequence__copy(
  const messages__msg__LineSegment__Sequence * input,
  messages__msg__LineSegment__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(messages__msg__LineSegment);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    messages__msg__LineSegment * data =
      (messages__msg__LineSegment *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!messages__msg__LineSegment__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          messages__msg__LineSegment__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!messages__msg__LineSegment__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
