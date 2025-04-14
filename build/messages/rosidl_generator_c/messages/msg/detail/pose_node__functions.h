// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from messages:msg/PoseNode.idl
// generated code does not contain a copyright notice

#ifndef MESSAGES__MSG__DETAIL__POSE_NODE__FUNCTIONS_H_
#define MESSAGES__MSG__DETAIL__POSE_NODE__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "messages/msg/rosidl_generator_c__visibility_control.h"

#include "messages/msg/detail/pose_node__struct.h"

/// Initialize msg/PoseNode message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * messages__msg__PoseNode
 * )) before or use
 * messages__msg__PoseNode__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_messages
bool
messages__msg__PoseNode__init(messages__msg__PoseNode * msg);

/// Finalize msg/PoseNode message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_messages
void
messages__msg__PoseNode__fini(messages__msg__PoseNode * msg);

/// Create msg/PoseNode message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * messages__msg__PoseNode__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_messages
messages__msg__PoseNode *
messages__msg__PoseNode__create();

/// Destroy msg/PoseNode message.
/**
 * It calls
 * messages__msg__PoseNode__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_messages
void
messages__msg__PoseNode__destroy(messages__msg__PoseNode * msg);

/// Check for msg/PoseNode message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_messages
bool
messages__msg__PoseNode__are_equal(const messages__msg__PoseNode * lhs, const messages__msg__PoseNode * rhs);

/// Copy a msg/PoseNode message.
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
messages__msg__PoseNode__copy(
  const messages__msg__PoseNode * input,
  messages__msg__PoseNode * output);

/// Initialize array of msg/PoseNode messages.
/**
 * It allocates the memory for the number of elements and calls
 * messages__msg__PoseNode__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_messages
bool
messages__msg__PoseNode__Sequence__init(messages__msg__PoseNode__Sequence * array, size_t size);

/// Finalize array of msg/PoseNode messages.
/**
 * It calls
 * messages__msg__PoseNode__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_messages
void
messages__msg__PoseNode__Sequence__fini(messages__msg__PoseNode__Sequence * array);

/// Create array of msg/PoseNode messages.
/**
 * It allocates the memory for the array and calls
 * messages__msg__PoseNode__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_messages
messages__msg__PoseNode__Sequence *
messages__msg__PoseNode__Sequence__create(size_t size);

/// Destroy array of msg/PoseNode messages.
/**
 * It calls
 * messages__msg__PoseNode__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_messages
void
messages__msg__PoseNode__Sequence__destroy(messages__msg__PoseNode__Sequence * array);

/// Check for msg/PoseNode message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_messages
bool
messages__msg__PoseNode__Sequence__are_equal(const messages__msg__PoseNode__Sequence * lhs, const messages__msg__PoseNode__Sequence * rhs);

/// Copy an array of msg/PoseNode messages.
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
messages__msg__PoseNode__Sequence__copy(
  const messages__msg__PoseNode__Sequence * input,
  messages__msg__PoseNode__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // MESSAGES__MSG__DETAIL__POSE_NODE__FUNCTIONS_H_
