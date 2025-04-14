// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from messages:msg/PoseNode.idl
// generated code does not contain a copyright notice
#include "messages/msg/detail/pose_node__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
messages__msg__PoseNode__init(messages__msg__PoseNode * msg)
{
  if (!msg) {
    return false;
  }
  // id
  // x
  // y
  // theta
  // covariance
  return true;
}

void
messages__msg__PoseNode__fini(messages__msg__PoseNode * msg)
{
  if (!msg) {
    return;
  }
  // id
  // x
  // y
  // theta
  // covariance
}

bool
messages__msg__PoseNode__are_equal(const messages__msg__PoseNode * lhs, const messages__msg__PoseNode * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // id
  if (lhs->id != rhs->id) {
    return false;
  }
  // x
  if (lhs->x != rhs->x) {
    return false;
  }
  // y
  if (lhs->y != rhs->y) {
    return false;
  }
  // theta
  if (lhs->theta != rhs->theta) {
    return false;
  }
  // covariance
  for (size_t i = 0; i < 9; ++i) {
    if (lhs->covariance[i] != rhs->covariance[i]) {
      return false;
    }
  }
  return true;
}

bool
messages__msg__PoseNode__copy(
  const messages__msg__PoseNode * input,
  messages__msg__PoseNode * output)
{
  if (!input || !output) {
    return false;
  }
  // id
  output->id = input->id;
  // x
  output->x = input->x;
  // y
  output->y = input->y;
  // theta
  output->theta = input->theta;
  // covariance
  for (size_t i = 0; i < 9; ++i) {
    output->covariance[i] = input->covariance[i];
  }
  return true;
}

messages__msg__PoseNode *
messages__msg__PoseNode__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  messages__msg__PoseNode * msg = (messages__msg__PoseNode *)allocator.allocate(sizeof(messages__msg__PoseNode), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(messages__msg__PoseNode));
  bool success = messages__msg__PoseNode__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
messages__msg__PoseNode__destroy(messages__msg__PoseNode * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    messages__msg__PoseNode__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
messages__msg__PoseNode__Sequence__init(messages__msg__PoseNode__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  messages__msg__PoseNode * data = NULL;

  if (size) {
    data = (messages__msg__PoseNode *)allocator.zero_allocate(size, sizeof(messages__msg__PoseNode), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = messages__msg__PoseNode__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        messages__msg__PoseNode__fini(&data[i - 1]);
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
messages__msg__PoseNode__Sequence__fini(messages__msg__PoseNode__Sequence * array)
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
      messages__msg__PoseNode__fini(&array->data[i]);
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

messages__msg__PoseNode__Sequence *
messages__msg__PoseNode__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  messages__msg__PoseNode__Sequence * array = (messages__msg__PoseNode__Sequence *)allocator.allocate(sizeof(messages__msg__PoseNode__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = messages__msg__PoseNode__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
messages__msg__PoseNode__Sequence__destroy(messages__msg__PoseNode__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    messages__msg__PoseNode__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
messages__msg__PoseNode__Sequence__are_equal(const messages__msg__PoseNode__Sequence * lhs, const messages__msg__PoseNode__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!messages__msg__PoseNode__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
messages__msg__PoseNode__Sequence__copy(
  const messages__msg__PoseNode__Sequence * input,
  messages__msg__PoseNode__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(messages__msg__PoseNode);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    messages__msg__PoseNode * data =
      (messages__msg__PoseNode *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!messages__msg__PoseNode__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          messages__msg__PoseNode__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!messages__msg__PoseNode__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
