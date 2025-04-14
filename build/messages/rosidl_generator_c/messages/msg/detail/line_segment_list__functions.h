// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from messages:msg/LineSegmentList.idl
// generated code does not contain a copyright notice

#ifndef MESSAGES__MSG__DETAIL__LINE_SEGMENT_LIST__FUNCTIONS_H_
#define MESSAGES__MSG__DETAIL__LINE_SEGMENT_LIST__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "messages/msg/rosidl_generator_c__visibility_control.h"

#include "messages/msg/detail/line_segment_list__struct.h"

/// Initialize msg/LineSegmentList message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * messages__msg__LineSegmentList
 * )) before or use
 * messages__msg__LineSegmentList__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_messages
bool
messages__msg__LineSegmentList__init(messages__msg__LineSegmentList * msg);

/// Finalize msg/LineSegmentList message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_messages
void
messages__msg__LineSegmentList__fini(messages__msg__LineSegmentList * msg);

/// Create msg/LineSegmentList message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * messages__msg__LineSegmentList__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_messages
messages__msg__LineSegmentList *
messages__msg__LineSegmentList__create();

/// Destroy msg/LineSegmentList message.
/**
 * It calls
 * messages__msg__LineSegmentList__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_messages
void
messages__msg__LineSegmentList__destroy(messages__msg__LineSegmentList * msg);

/// Check for msg/LineSegmentList message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_messages
bool
messages__msg__LineSegmentList__are_equal(const messages__msg__LineSegmentList * lhs, const messages__msg__LineSegmentList * rhs);

/// Copy a msg/LineSegmentList message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_messages
bool
messages__msg__LineSegmentList__copy(
  const messages__msg__LineSegmentList * input,
  messages__msg__LineSegmentList * output);

/// Initialize array of msg/LineSegmentList messages.
/**
 * It allocates the memory for the number of elements and calls
 * messages__msg__LineSegmentList__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_messages
bool
messages__msg__LineSegmentList__Sequence__init(messages__msg__LineSegmentList__Sequence * array, size_t size);

/// Finalize array of msg/LineSegmentList messages.
/**
 * It calls
 * messages__msg__LineSegmentList__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_messages
void
messages__msg__LineSegmentList__Sequence__fini(messages__msg__LineSegmentList__Sequence * array);

/// Create array of msg/LineSegmentList messages.
/**
 * It allocates the memory for the array and calls
 * messages__msg__LineSegmentList__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_messages
messages__msg__LineSegmentList__Sequence *
messages__msg__LineSegmentList__Sequence__create(size_t size);

/// Destroy array of msg/LineSegmentList messages.
/**
 * It calls
 * messages__msg__LineSegmentList__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_messages
void
messages__msg__LineSegmentList__Sequence__destroy(messages__msg__LineSegmentList__Sequence * array);

/// Check for msg/LineSegmentList message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_messages
bool
messages__msg__LineSegmentList__Sequence__are_equal(const messages__msg__LineSegmentList__Sequence * lhs, const messages__msg__LineSegmentList__Sequence * rhs);

/// Copy an array of msg/LineSegmentList messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_messages
bool
messages__msg__LineSegmentList__Sequence__copy(
  const messages__msg__LineSegmentList__Sequence * input,
  messages__msg__LineSegmentList__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // MESSAGES__MSG__DETAIL__LINE_SEGMENT_LIST__FUNCTIONS_H_
