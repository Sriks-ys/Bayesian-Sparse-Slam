// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from messages:msg/LandmarkLandmarkConstraintList.idl
// generated code does not contain a copyright notice
#include "messages/msg/detail/landmark_landmark_constraint_list__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `constraints`
#include "messages/msg/detail/landmark_landmark_constraint__functions.h"

bool
messages__msg__LandmarkLandmarkConstraintList__init(messages__msg__LandmarkLandmarkConstraintList * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    messages__msg__LandmarkLandmarkConstraintList__fini(msg);
    return false;
  }
  // constraints
  if (!messages__msg__LandmarkLandmarkConstraint__Sequence__init(&msg->constraints, 0)) {
    messages__msg__LandmarkLandmarkConstraintList__fini(msg);
    return false;
  }
  return true;
}

void
messages__msg__LandmarkLandmarkConstraintList__fini(messages__msg__LandmarkLandmarkConstraintList * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // constraints
  messages__msg__LandmarkLandmarkConstraint__Sequence__fini(&msg->constraints);
}

bool
messages__msg__LandmarkLandmarkConstraintList__are_equal(const messages__msg__LandmarkLandmarkConstraintList * lhs, const messages__msg__LandmarkLandmarkConstraintList * rhs)
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
  // constraints
  if (!messages__msg__LandmarkLandmarkConstraint__Sequence__are_equal(
      &(lhs->constraints), &(rhs->constraints)))
  {
    return false;
  }
  return true;
}

bool
messages__msg__LandmarkLandmarkConstraintList__copy(
  const messages__msg__LandmarkLandmarkConstraintList * input,
  messages__msg__LandmarkLandmarkConstraintList * output)
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
  // constraints
  if (!messages__msg__LandmarkLandmarkConstraint__Sequence__copy(
      &(input->constraints), &(output->constraints)))
  {
    return false;
  }
  return true;
}

messages__msg__LandmarkLandmarkConstraintList *
messages__msg__LandmarkLandmarkConstraintList__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  messages__msg__LandmarkLandmarkConstraintList * msg = (messages__msg__LandmarkLandmarkConstraintList *)allocator.allocate(sizeof(messages__msg__LandmarkLandmarkConstraintList), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(messages__msg__LandmarkLandmarkConstraintList));
  bool success = messages__msg__LandmarkLandmarkConstraintList__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
messages__msg__LandmarkLandmarkConstraintList__destroy(messages__msg__LandmarkLandmarkConstraintList * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    messages__msg__LandmarkLandmarkConstraintList__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
messages__msg__LandmarkLandmarkConstraintList__Sequence__init(messages__msg__LandmarkLandmarkConstraintList__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  messages__msg__LandmarkLandmarkConstraintList * data = NULL;

  if (size) {
    data = (messages__msg__LandmarkLandmarkConstraintList *)allocator.zero_allocate(size, sizeof(messages__msg__LandmarkLandmarkConstraintList), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = messages__msg__LandmarkLandmarkConstraintList__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        messages__msg__LandmarkLandmarkConstraintList__fini(&data[i - 1]);
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
messages__msg__LandmarkLandmarkConstraintList__Sequence__fini(messages__msg__LandmarkLandmarkConstraintList__Sequence * array)
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
      messages__msg__LandmarkLandmarkConstraintList__fini(&array->data[i]);
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

messages__msg__LandmarkLandmarkConstraintList__Sequence *
messages__msg__LandmarkLandmarkConstraintList__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  messages__msg__LandmarkLandmarkConstraintList__Sequence * array = (messages__msg__LandmarkLandmarkConstraintList__Sequence *)allocator.allocate(sizeof(messages__msg__LandmarkLandmarkConstraintList__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = messages__msg__LandmarkLandmarkConstraintList__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
messages__msg__LandmarkLandmarkConstraintList__Sequence__destroy(messages__msg__LandmarkLandmarkConstraintList__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    messages__msg__LandmarkLandmarkConstraintList__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
messages__msg__LandmarkLandmarkConstraintList__Sequence__are_equal(const messages__msg__LandmarkLandmarkConstraintList__Sequence * lhs, const messages__msg__LandmarkLandmarkConstraintList__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!messages__msg__LandmarkLandmarkConstraintList__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
messages__msg__LandmarkLandmarkConstraintList__Sequence__copy(
  const messages__msg__LandmarkLandmarkConstraintList__Sequence * input,
  messages__msg__LandmarkLandmarkConstraintList__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(messages__msg__LandmarkLandmarkConstraintList);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    messages__msg__LandmarkLandmarkConstraintList * data =
      (messages__msg__LandmarkLandmarkConstraintList *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!messages__msg__LandmarkLandmarkConstraintList__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          messages__msg__LandmarkLandmarkConstraintList__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!messages__msg__LandmarkLandmarkConstraintList__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
