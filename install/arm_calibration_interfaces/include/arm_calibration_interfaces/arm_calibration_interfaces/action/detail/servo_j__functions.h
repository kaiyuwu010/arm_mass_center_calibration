// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from arm_calibration_interfaces:action/ServoJ.idl
// generated code does not contain a copyright notice

#ifndef ARM_CALIBRATION_INTERFACES__ACTION__DETAIL__SERVO_J__FUNCTIONS_H_
#define ARM_CALIBRATION_INTERFACES__ACTION__DETAIL__SERVO_J__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "arm_calibration_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "arm_calibration_interfaces/action/detail/servo_j__struct.h"

/// Initialize action/ServoJ message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * arm_calibration_interfaces__action__ServoJ_Goal
 * )) before or use
 * arm_calibration_interfaces__action__ServoJ_Goal__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_Goal__init(arm_calibration_interfaces__action__ServoJ_Goal * msg);

/// Finalize action/ServoJ message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
void
arm_calibration_interfaces__action__ServoJ_Goal__fini(arm_calibration_interfaces__action__ServoJ_Goal * msg);

/// Create action/ServoJ message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * arm_calibration_interfaces__action__ServoJ_Goal__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
arm_calibration_interfaces__action__ServoJ_Goal *
arm_calibration_interfaces__action__ServoJ_Goal__create();

/// Destroy action/ServoJ message.
/**
 * It calls
 * arm_calibration_interfaces__action__ServoJ_Goal__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
void
arm_calibration_interfaces__action__ServoJ_Goal__destroy(arm_calibration_interfaces__action__ServoJ_Goal * msg);

/// Check for action/ServoJ message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_Goal__are_equal(const arm_calibration_interfaces__action__ServoJ_Goal * lhs, const arm_calibration_interfaces__action__ServoJ_Goal * rhs);

/// Copy a action/ServoJ message.
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
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_Goal__copy(
  const arm_calibration_interfaces__action__ServoJ_Goal * input,
  arm_calibration_interfaces__action__ServoJ_Goal * output);

/// Initialize array of action/ServoJ messages.
/**
 * It allocates the memory for the number of elements and calls
 * arm_calibration_interfaces__action__ServoJ_Goal__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_Goal__Sequence__init(arm_calibration_interfaces__action__ServoJ_Goal__Sequence * array, size_t size);

/// Finalize array of action/ServoJ messages.
/**
 * It calls
 * arm_calibration_interfaces__action__ServoJ_Goal__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
void
arm_calibration_interfaces__action__ServoJ_Goal__Sequence__fini(arm_calibration_interfaces__action__ServoJ_Goal__Sequence * array);

/// Create array of action/ServoJ messages.
/**
 * It allocates the memory for the array and calls
 * arm_calibration_interfaces__action__ServoJ_Goal__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
arm_calibration_interfaces__action__ServoJ_Goal__Sequence *
arm_calibration_interfaces__action__ServoJ_Goal__Sequence__create(size_t size);

/// Destroy array of action/ServoJ messages.
/**
 * It calls
 * arm_calibration_interfaces__action__ServoJ_Goal__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
void
arm_calibration_interfaces__action__ServoJ_Goal__Sequence__destroy(arm_calibration_interfaces__action__ServoJ_Goal__Sequence * array);

/// Check for action/ServoJ message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_Goal__Sequence__are_equal(const arm_calibration_interfaces__action__ServoJ_Goal__Sequence * lhs, const arm_calibration_interfaces__action__ServoJ_Goal__Sequence * rhs);

/// Copy an array of action/ServoJ messages.
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
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_Goal__Sequence__copy(
  const arm_calibration_interfaces__action__ServoJ_Goal__Sequence * input,
  arm_calibration_interfaces__action__ServoJ_Goal__Sequence * output);

/// Initialize action/ServoJ message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * arm_calibration_interfaces__action__ServoJ_Result
 * )) before or use
 * arm_calibration_interfaces__action__ServoJ_Result__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_Result__init(arm_calibration_interfaces__action__ServoJ_Result * msg);

/// Finalize action/ServoJ message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
void
arm_calibration_interfaces__action__ServoJ_Result__fini(arm_calibration_interfaces__action__ServoJ_Result * msg);

/// Create action/ServoJ message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * arm_calibration_interfaces__action__ServoJ_Result__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
arm_calibration_interfaces__action__ServoJ_Result *
arm_calibration_interfaces__action__ServoJ_Result__create();

/// Destroy action/ServoJ message.
/**
 * It calls
 * arm_calibration_interfaces__action__ServoJ_Result__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
void
arm_calibration_interfaces__action__ServoJ_Result__destroy(arm_calibration_interfaces__action__ServoJ_Result * msg);

/// Check for action/ServoJ message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_Result__are_equal(const arm_calibration_interfaces__action__ServoJ_Result * lhs, const arm_calibration_interfaces__action__ServoJ_Result * rhs);

/// Copy a action/ServoJ message.
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
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_Result__copy(
  const arm_calibration_interfaces__action__ServoJ_Result * input,
  arm_calibration_interfaces__action__ServoJ_Result * output);

/// Initialize array of action/ServoJ messages.
/**
 * It allocates the memory for the number of elements and calls
 * arm_calibration_interfaces__action__ServoJ_Result__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_Result__Sequence__init(arm_calibration_interfaces__action__ServoJ_Result__Sequence * array, size_t size);

/// Finalize array of action/ServoJ messages.
/**
 * It calls
 * arm_calibration_interfaces__action__ServoJ_Result__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
void
arm_calibration_interfaces__action__ServoJ_Result__Sequence__fini(arm_calibration_interfaces__action__ServoJ_Result__Sequence * array);

/// Create array of action/ServoJ messages.
/**
 * It allocates the memory for the array and calls
 * arm_calibration_interfaces__action__ServoJ_Result__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
arm_calibration_interfaces__action__ServoJ_Result__Sequence *
arm_calibration_interfaces__action__ServoJ_Result__Sequence__create(size_t size);

/// Destroy array of action/ServoJ messages.
/**
 * It calls
 * arm_calibration_interfaces__action__ServoJ_Result__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
void
arm_calibration_interfaces__action__ServoJ_Result__Sequence__destroy(arm_calibration_interfaces__action__ServoJ_Result__Sequence * array);

/// Check for action/ServoJ message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_Result__Sequence__are_equal(const arm_calibration_interfaces__action__ServoJ_Result__Sequence * lhs, const arm_calibration_interfaces__action__ServoJ_Result__Sequence * rhs);

/// Copy an array of action/ServoJ messages.
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
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_Result__Sequence__copy(
  const arm_calibration_interfaces__action__ServoJ_Result__Sequence * input,
  arm_calibration_interfaces__action__ServoJ_Result__Sequence * output);

/// Initialize action/ServoJ message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * arm_calibration_interfaces__action__ServoJ_Feedback
 * )) before or use
 * arm_calibration_interfaces__action__ServoJ_Feedback__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_Feedback__init(arm_calibration_interfaces__action__ServoJ_Feedback * msg);

/// Finalize action/ServoJ message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
void
arm_calibration_interfaces__action__ServoJ_Feedback__fini(arm_calibration_interfaces__action__ServoJ_Feedback * msg);

/// Create action/ServoJ message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * arm_calibration_interfaces__action__ServoJ_Feedback__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
arm_calibration_interfaces__action__ServoJ_Feedback *
arm_calibration_interfaces__action__ServoJ_Feedback__create();

/// Destroy action/ServoJ message.
/**
 * It calls
 * arm_calibration_interfaces__action__ServoJ_Feedback__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
void
arm_calibration_interfaces__action__ServoJ_Feedback__destroy(arm_calibration_interfaces__action__ServoJ_Feedback * msg);

/// Check for action/ServoJ message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_Feedback__are_equal(const arm_calibration_interfaces__action__ServoJ_Feedback * lhs, const arm_calibration_interfaces__action__ServoJ_Feedback * rhs);

/// Copy a action/ServoJ message.
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
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_Feedback__copy(
  const arm_calibration_interfaces__action__ServoJ_Feedback * input,
  arm_calibration_interfaces__action__ServoJ_Feedback * output);

/// Initialize array of action/ServoJ messages.
/**
 * It allocates the memory for the number of elements and calls
 * arm_calibration_interfaces__action__ServoJ_Feedback__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_Feedback__Sequence__init(arm_calibration_interfaces__action__ServoJ_Feedback__Sequence * array, size_t size);

/// Finalize array of action/ServoJ messages.
/**
 * It calls
 * arm_calibration_interfaces__action__ServoJ_Feedback__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
void
arm_calibration_interfaces__action__ServoJ_Feedback__Sequence__fini(arm_calibration_interfaces__action__ServoJ_Feedback__Sequence * array);

/// Create array of action/ServoJ messages.
/**
 * It allocates the memory for the array and calls
 * arm_calibration_interfaces__action__ServoJ_Feedback__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
arm_calibration_interfaces__action__ServoJ_Feedback__Sequence *
arm_calibration_interfaces__action__ServoJ_Feedback__Sequence__create(size_t size);

/// Destroy array of action/ServoJ messages.
/**
 * It calls
 * arm_calibration_interfaces__action__ServoJ_Feedback__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
void
arm_calibration_interfaces__action__ServoJ_Feedback__Sequence__destroy(arm_calibration_interfaces__action__ServoJ_Feedback__Sequence * array);

/// Check for action/ServoJ message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_Feedback__Sequence__are_equal(const arm_calibration_interfaces__action__ServoJ_Feedback__Sequence * lhs, const arm_calibration_interfaces__action__ServoJ_Feedback__Sequence * rhs);

/// Copy an array of action/ServoJ messages.
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
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_Feedback__Sequence__copy(
  const arm_calibration_interfaces__action__ServoJ_Feedback__Sequence * input,
  arm_calibration_interfaces__action__ServoJ_Feedback__Sequence * output);

/// Initialize action/ServoJ message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * arm_calibration_interfaces__action__ServoJ_SendGoal_Request
 * )) before or use
 * arm_calibration_interfaces__action__ServoJ_SendGoal_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_SendGoal_Request__init(arm_calibration_interfaces__action__ServoJ_SendGoal_Request * msg);

/// Finalize action/ServoJ message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
void
arm_calibration_interfaces__action__ServoJ_SendGoal_Request__fini(arm_calibration_interfaces__action__ServoJ_SendGoal_Request * msg);

/// Create action/ServoJ message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * arm_calibration_interfaces__action__ServoJ_SendGoal_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
arm_calibration_interfaces__action__ServoJ_SendGoal_Request *
arm_calibration_interfaces__action__ServoJ_SendGoal_Request__create();

/// Destroy action/ServoJ message.
/**
 * It calls
 * arm_calibration_interfaces__action__ServoJ_SendGoal_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
void
arm_calibration_interfaces__action__ServoJ_SendGoal_Request__destroy(arm_calibration_interfaces__action__ServoJ_SendGoal_Request * msg);

/// Check for action/ServoJ message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_SendGoal_Request__are_equal(const arm_calibration_interfaces__action__ServoJ_SendGoal_Request * lhs, const arm_calibration_interfaces__action__ServoJ_SendGoal_Request * rhs);

/// Copy a action/ServoJ message.
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
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_SendGoal_Request__copy(
  const arm_calibration_interfaces__action__ServoJ_SendGoal_Request * input,
  arm_calibration_interfaces__action__ServoJ_SendGoal_Request * output);

/// Initialize array of action/ServoJ messages.
/**
 * It allocates the memory for the number of elements and calls
 * arm_calibration_interfaces__action__ServoJ_SendGoal_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_SendGoal_Request__Sequence__init(arm_calibration_interfaces__action__ServoJ_SendGoal_Request__Sequence * array, size_t size);

/// Finalize array of action/ServoJ messages.
/**
 * It calls
 * arm_calibration_interfaces__action__ServoJ_SendGoal_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
void
arm_calibration_interfaces__action__ServoJ_SendGoal_Request__Sequence__fini(arm_calibration_interfaces__action__ServoJ_SendGoal_Request__Sequence * array);

/// Create array of action/ServoJ messages.
/**
 * It allocates the memory for the array and calls
 * arm_calibration_interfaces__action__ServoJ_SendGoal_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
arm_calibration_interfaces__action__ServoJ_SendGoal_Request__Sequence *
arm_calibration_interfaces__action__ServoJ_SendGoal_Request__Sequence__create(size_t size);

/// Destroy array of action/ServoJ messages.
/**
 * It calls
 * arm_calibration_interfaces__action__ServoJ_SendGoal_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
void
arm_calibration_interfaces__action__ServoJ_SendGoal_Request__Sequence__destroy(arm_calibration_interfaces__action__ServoJ_SendGoal_Request__Sequence * array);

/// Check for action/ServoJ message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_SendGoal_Request__Sequence__are_equal(const arm_calibration_interfaces__action__ServoJ_SendGoal_Request__Sequence * lhs, const arm_calibration_interfaces__action__ServoJ_SendGoal_Request__Sequence * rhs);

/// Copy an array of action/ServoJ messages.
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
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_SendGoal_Request__Sequence__copy(
  const arm_calibration_interfaces__action__ServoJ_SendGoal_Request__Sequence * input,
  arm_calibration_interfaces__action__ServoJ_SendGoal_Request__Sequence * output);

/// Initialize action/ServoJ message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * arm_calibration_interfaces__action__ServoJ_SendGoal_Response
 * )) before or use
 * arm_calibration_interfaces__action__ServoJ_SendGoal_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_SendGoal_Response__init(arm_calibration_interfaces__action__ServoJ_SendGoal_Response * msg);

/// Finalize action/ServoJ message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
void
arm_calibration_interfaces__action__ServoJ_SendGoal_Response__fini(arm_calibration_interfaces__action__ServoJ_SendGoal_Response * msg);

/// Create action/ServoJ message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * arm_calibration_interfaces__action__ServoJ_SendGoal_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
arm_calibration_interfaces__action__ServoJ_SendGoal_Response *
arm_calibration_interfaces__action__ServoJ_SendGoal_Response__create();

/// Destroy action/ServoJ message.
/**
 * It calls
 * arm_calibration_interfaces__action__ServoJ_SendGoal_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
void
arm_calibration_interfaces__action__ServoJ_SendGoal_Response__destroy(arm_calibration_interfaces__action__ServoJ_SendGoal_Response * msg);

/// Check for action/ServoJ message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_SendGoal_Response__are_equal(const arm_calibration_interfaces__action__ServoJ_SendGoal_Response * lhs, const arm_calibration_interfaces__action__ServoJ_SendGoal_Response * rhs);

/// Copy a action/ServoJ message.
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
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_SendGoal_Response__copy(
  const arm_calibration_interfaces__action__ServoJ_SendGoal_Response * input,
  arm_calibration_interfaces__action__ServoJ_SendGoal_Response * output);

/// Initialize array of action/ServoJ messages.
/**
 * It allocates the memory for the number of elements and calls
 * arm_calibration_interfaces__action__ServoJ_SendGoal_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_SendGoal_Response__Sequence__init(arm_calibration_interfaces__action__ServoJ_SendGoal_Response__Sequence * array, size_t size);

/// Finalize array of action/ServoJ messages.
/**
 * It calls
 * arm_calibration_interfaces__action__ServoJ_SendGoal_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
void
arm_calibration_interfaces__action__ServoJ_SendGoal_Response__Sequence__fini(arm_calibration_interfaces__action__ServoJ_SendGoal_Response__Sequence * array);

/// Create array of action/ServoJ messages.
/**
 * It allocates the memory for the array and calls
 * arm_calibration_interfaces__action__ServoJ_SendGoal_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
arm_calibration_interfaces__action__ServoJ_SendGoal_Response__Sequence *
arm_calibration_interfaces__action__ServoJ_SendGoal_Response__Sequence__create(size_t size);

/// Destroy array of action/ServoJ messages.
/**
 * It calls
 * arm_calibration_interfaces__action__ServoJ_SendGoal_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
void
arm_calibration_interfaces__action__ServoJ_SendGoal_Response__Sequence__destroy(arm_calibration_interfaces__action__ServoJ_SendGoal_Response__Sequence * array);

/// Check for action/ServoJ message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_SendGoal_Response__Sequence__are_equal(const arm_calibration_interfaces__action__ServoJ_SendGoal_Response__Sequence * lhs, const arm_calibration_interfaces__action__ServoJ_SendGoal_Response__Sequence * rhs);

/// Copy an array of action/ServoJ messages.
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
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_SendGoal_Response__Sequence__copy(
  const arm_calibration_interfaces__action__ServoJ_SendGoal_Response__Sequence * input,
  arm_calibration_interfaces__action__ServoJ_SendGoal_Response__Sequence * output);

/// Initialize action/ServoJ message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * arm_calibration_interfaces__action__ServoJ_GetResult_Request
 * )) before or use
 * arm_calibration_interfaces__action__ServoJ_GetResult_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_GetResult_Request__init(arm_calibration_interfaces__action__ServoJ_GetResult_Request * msg);

/// Finalize action/ServoJ message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
void
arm_calibration_interfaces__action__ServoJ_GetResult_Request__fini(arm_calibration_interfaces__action__ServoJ_GetResult_Request * msg);

/// Create action/ServoJ message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * arm_calibration_interfaces__action__ServoJ_GetResult_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
arm_calibration_interfaces__action__ServoJ_GetResult_Request *
arm_calibration_interfaces__action__ServoJ_GetResult_Request__create();

/// Destroy action/ServoJ message.
/**
 * It calls
 * arm_calibration_interfaces__action__ServoJ_GetResult_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
void
arm_calibration_interfaces__action__ServoJ_GetResult_Request__destroy(arm_calibration_interfaces__action__ServoJ_GetResult_Request * msg);

/// Check for action/ServoJ message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_GetResult_Request__are_equal(const arm_calibration_interfaces__action__ServoJ_GetResult_Request * lhs, const arm_calibration_interfaces__action__ServoJ_GetResult_Request * rhs);

/// Copy a action/ServoJ message.
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
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_GetResult_Request__copy(
  const arm_calibration_interfaces__action__ServoJ_GetResult_Request * input,
  arm_calibration_interfaces__action__ServoJ_GetResult_Request * output);

/// Initialize array of action/ServoJ messages.
/**
 * It allocates the memory for the number of elements and calls
 * arm_calibration_interfaces__action__ServoJ_GetResult_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_GetResult_Request__Sequence__init(arm_calibration_interfaces__action__ServoJ_GetResult_Request__Sequence * array, size_t size);

/// Finalize array of action/ServoJ messages.
/**
 * It calls
 * arm_calibration_interfaces__action__ServoJ_GetResult_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
void
arm_calibration_interfaces__action__ServoJ_GetResult_Request__Sequence__fini(arm_calibration_interfaces__action__ServoJ_GetResult_Request__Sequence * array);

/// Create array of action/ServoJ messages.
/**
 * It allocates the memory for the array and calls
 * arm_calibration_interfaces__action__ServoJ_GetResult_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
arm_calibration_interfaces__action__ServoJ_GetResult_Request__Sequence *
arm_calibration_interfaces__action__ServoJ_GetResult_Request__Sequence__create(size_t size);

/// Destroy array of action/ServoJ messages.
/**
 * It calls
 * arm_calibration_interfaces__action__ServoJ_GetResult_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
void
arm_calibration_interfaces__action__ServoJ_GetResult_Request__Sequence__destroy(arm_calibration_interfaces__action__ServoJ_GetResult_Request__Sequence * array);

/// Check for action/ServoJ message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_GetResult_Request__Sequence__are_equal(const arm_calibration_interfaces__action__ServoJ_GetResult_Request__Sequence * lhs, const arm_calibration_interfaces__action__ServoJ_GetResult_Request__Sequence * rhs);

/// Copy an array of action/ServoJ messages.
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
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_GetResult_Request__Sequence__copy(
  const arm_calibration_interfaces__action__ServoJ_GetResult_Request__Sequence * input,
  arm_calibration_interfaces__action__ServoJ_GetResult_Request__Sequence * output);

/// Initialize action/ServoJ message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * arm_calibration_interfaces__action__ServoJ_GetResult_Response
 * )) before or use
 * arm_calibration_interfaces__action__ServoJ_GetResult_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_GetResult_Response__init(arm_calibration_interfaces__action__ServoJ_GetResult_Response * msg);

/// Finalize action/ServoJ message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
void
arm_calibration_interfaces__action__ServoJ_GetResult_Response__fini(arm_calibration_interfaces__action__ServoJ_GetResult_Response * msg);

/// Create action/ServoJ message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * arm_calibration_interfaces__action__ServoJ_GetResult_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
arm_calibration_interfaces__action__ServoJ_GetResult_Response *
arm_calibration_interfaces__action__ServoJ_GetResult_Response__create();

/// Destroy action/ServoJ message.
/**
 * It calls
 * arm_calibration_interfaces__action__ServoJ_GetResult_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
void
arm_calibration_interfaces__action__ServoJ_GetResult_Response__destroy(arm_calibration_interfaces__action__ServoJ_GetResult_Response * msg);

/// Check for action/ServoJ message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_GetResult_Response__are_equal(const arm_calibration_interfaces__action__ServoJ_GetResult_Response * lhs, const arm_calibration_interfaces__action__ServoJ_GetResult_Response * rhs);

/// Copy a action/ServoJ message.
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
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_GetResult_Response__copy(
  const arm_calibration_interfaces__action__ServoJ_GetResult_Response * input,
  arm_calibration_interfaces__action__ServoJ_GetResult_Response * output);

/// Initialize array of action/ServoJ messages.
/**
 * It allocates the memory for the number of elements and calls
 * arm_calibration_interfaces__action__ServoJ_GetResult_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_GetResult_Response__Sequence__init(arm_calibration_interfaces__action__ServoJ_GetResult_Response__Sequence * array, size_t size);

/// Finalize array of action/ServoJ messages.
/**
 * It calls
 * arm_calibration_interfaces__action__ServoJ_GetResult_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
void
arm_calibration_interfaces__action__ServoJ_GetResult_Response__Sequence__fini(arm_calibration_interfaces__action__ServoJ_GetResult_Response__Sequence * array);

/// Create array of action/ServoJ messages.
/**
 * It allocates the memory for the array and calls
 * arm_calibration_interfaces__action__ServoJ_GetResult_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
arm_calibration_interfaces__action__ServoJ_GetResult_Response__Sequence *
arm_calibration_interfaces__action__ServoJ_GetResult_Response__Sequence__create(size_t size);

/// Destroy array of action/ServoJ messages.
/**
 * It calls
 * arm_calibration_interfaces__action__ServoJ_GetResult_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
void
arm_calibration_interfaces__action__ServoJ_GetResult_Response__Sequence__destroy(arm_calibration_interfaces__action__ServoJ_GetResult_Response__Sequence * array);

/// Check for action/ServoJ message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_GetResult_Response__Sequence__are_equal(const arm_calibration_interfaces__action__ServoJ_GetResult_Response__Sequence * lhs, const arm_calibration_interfaces__action__ServoJ_GetResult_Response__Sequence * rhs);

/// Copy an array of action/ServoJ messages.
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
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_GetResult_Response__Sequence__copy(
  const arm_calibration_interfaces__action__ServoJ_GetResult_Response__Sequence * input,
  arm_calibration_interfaces__action__ServoJ_GetResult_Response__Sequence * output);

/// Initialize action/ServoJ message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * arm_calibration_interfaces__action__ServoJ_FeedbackMessage
 * )) before or use
 * arm_calibration_interfaces__action__ServoJ_FeedbackMessage__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_FeedbackMessage__init(arm_calibration_interfaces__action__ServoJ_FeedbackMessage * msg);

/// Finalize action/ServoJ message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
void
arm_calibration_interfaces__action__ServoJ_FeedbackMessage__fini(arm_calibration_interfaces__action__ServoJ_FeedbackMessage * msg);

/// Create action/ServoJ message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * arm_calibration_interfaces__action__ServoJ_FeedbackMessage__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
arm_calibration_interfaces__action__ServoJ_FeedbackMessage *
arm_calibration_interfaces__action__ServoJ_FeedbackMessage__create();

/// Destroy action/ServoJ message.
/**
 * It calls
 * arm_calibration_interfaces__action__ServoJ_FeedbackMessage__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
void
arm_calibration_interfaces__action__ServoJ_FeedbackMessage__destroy(arm_calibration_interfaces__action__ServoJ_FeedbackMessage * msg);

/// Check for action/ServoJ message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_FeedbackMessage__are_equal(const arm_calibration_interfaces__action__ServoJ_FeedbackMessage * lhs, const arm_calibration_interfaces__action__ServoJ_FeedbackMessage * rhs);

/// Copy a action/ServoJ message.
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
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_FeedbackMessage__copy(
  const arm_calibration_interfaces__action__ServoJ_FeedbackMessage * input,
  arm_calibration_interfaces__action__ServoJ_FeedbackMessage * output);

/// Initialize array of action/ServoJ messages.
/**
 * It allocates the memory for the number of elements and calls
 * arm_calibration_interfaces__action__ServoJ_FeedbackMessage__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_FeedbackMessage__Sequence__init(arm_calibration_interfaces__action__ServoJ_FeedbackMessage__Sequence * array, size_t size);

/// Finalize array of action/ServoJ messages.
/**
 * It calls
 * arm_calibration_interfaces__action__ServoJ_FeedbackMessage__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
void
arm_calibration_interfaces__action__ServoJ_FeedbackMessage__Sequence__fini(arm_calibration_interfaces__action__ServoJ_FeedbackMessage__Sequence * array);

/// Create array of action/ServoJ messages.
/**
 * It allocates the memory for the array and calls
 * arm_calibration_interfaces__action__ServoJ_FeedbackMessage__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
arm_calibration_interfaces__action__ServoJ_FeedbackMessage__Sequence *
arm_calibration_interfaces__action__ServoJ_FeedbackMessage__Sequence__create(size_t size);

/// Destroy array of action/ServoJ messages.
/**
 * It calls
 * arm_calibration_interfaces__action__ServoJ_FeedbackMessage__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
void
arm_calibration_interfaces__action__ServoJ_FeedbackMessage__Sequence__destroy(arm_calibration_interfaces__action__ServoJ_FeedbackMessage__Sequence * array);

/// Check for action/ServoJ message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_FeedbackMessage__Sequence__are_equal(const arm_calibration_interfaces__action__ServoJ_FeedbackMessage__Sequence * lhs, const arm_calibration_interfaces__action__ServoJ_FeedbackMessage__Sequence * rhs);

/// Copy an array of action/ServoJ messages.
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
ROSIDL_GENERATOR_C_PUBLIC_arm_calibration_interfaces
bool
arm_calibration_interfaces__action__ServoJ_FeedbackMessage__Sequence__copy(
  const arm_calibration_interfaces__action__ServoJ_FeedbackMessage__Sequence * input,
  arm_calibration_interfaces__action__ServoJ_FeedbackMessage__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // ARM_CALIBRATION_INTERFACES__ACTION__DETAIL__SERVO_J__FUNCTIONS_H_
