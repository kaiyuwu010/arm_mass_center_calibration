// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from arm_calibration_interfaces:action/ServoJ.idl
// generated code does not contain a copyright notice

#ifndef ARM_CALIBRATION_INTERFACES__ACTION__DETAIL__SERVO_J__STRUCT_H_
#define ARM_CALIBRATION_INTERFACES__ACTION__DETAIL__SERVO_J__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'trajectory'
#include "trajectory_msgs/msg/detail/joint_trajectory__struct.h"

/// Struct defined in action/ServoJ in the package arm_calibration_interfaces.
typedef struct arm_calibration_interfaces__action__ServoJ_Goal
{
  trajectory_msgs__msg__JointTrajectory trajectory;
} arm_calibration_interfaces__action__ServoJ_Goal;

// Struct for a sequence of arm_calibration_interfaces__action__ServoJ_Goal.
typedef struct arm_calibration_interfaces__action__ServoJ_Goal__Sequence
{
  arm_calibration_interfaces__action__ServoJ_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} arm_calibration_interfaces__action__ServoJ_Goal__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in action/ServoJ in the package arm_calibration_interfaces.
typedef struct arm_calibration_interfaces__action__ServoJ_Result
{
  bool success;
  rosidl_runtime_c__String message;
} arm_calibration_interfaces__action__ServoJ_Result;

// Struct for a sequence of arm_calibration_interfaces__action__ServoJ_Result.
typedef struct arm_calibration_interfaces__action__ServoJ_Result__Sequence
{
  arm_calibration_interfaces__action__ServoJ_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} arm_calibration_interfaces__action__ServoJ_Result__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'commanded_positions'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in action/ServoJ in the package arm_calibration_interfaces.
typedef struct arm_calibration_interfaces__action__ServoJ_Feedback
{
  uint32_t current_point;
  double elapsed_seconds;
  /// 本周期传给底层servo_j的目标，单位为弧度。
  rosidl_runtime_c__double__Sequence commanded_positions;
} arm_calibration_interfaces__action__ServoJ_Feedback;

// Struct for a sequence of arm_calibration_interfaces__action__ServoJ_Feedback.
typedef struct arm_calibration_interfaces__action__ServoJ_Feedback__Sequence
{
  arm_calibration_interfaces__action__ServoJ_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} arm_calibration_interfaces__action__ServoJ_Feedback__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "arm_calibration_interfaces/action/detail/servo_j__struct.h"

/// Struct defined in action/ServoJ in the package arm_calibration_interfaces.
typedef struct arm_calibration_interfaces__action__ServoJ_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  arm_calibration_interfaces__action__ServoJ_Goal goal;
} arm_calibration_interfaces__action__ServoJ_SendGoal_Request;

// Struct for a sequence of arm_calibration_interfaces__action__ServoJ_SendGoal_Request.
typedef struct arm_calibration_interfaces__action__ServoJ_SendGoal_Request__Sequence
{
  arm_calibration_interfaces__action__ServoJ_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} arm_calibration_interfaces__action__ServoJ_SendGoal_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in action/ServoJ in the package arm_calibration_interfaces.
typedef struct arm_calibration_interfaces__action__ServoJ_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} arm_calibration_interfaces__action__ServoJ_SendGoal_Response;

// Struct for a sequence of arm_calibration_interfaces__action__ServoJ_SendGoal_Response.
typedef struct arm_calibration_interfaces__action__ServoJ_SendGoal_Response__Sequence
{
  arm_calibration_interfaces__action__ServoJ_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} arm_calibration_interfaces__action__ServoJ_SendGoal_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Struct defined in action/ServoJ in the package arm_calibration_interfaces.
typedef struct arm_calibration_interfaces__action__ServoJ_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} arm_calibration_interfaces__action__ServoJ_GetResult_Request;

// Struct for a sequence of arm_calibration_interfaces__action__ServoJ_GetResult_Request.
typedef struct arm_calibration_interfaces__action__ServoJ_GetResult_Request__Sequence
{
  arm_calibration_interfaces__action__ServoJ_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} arm_calibration_interfaces__action__ServoJ_GetResult_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "arm_calibration_interfaces/action/detail/servo_j__struct.h"

/// Struct defined in action/ServoJ in the package arm_calibration_interfaces.
typedef struct arm_calibration_interfaces__action__ServoJ_GetResult_Response
{
  int8_t status;
  arm_calibration_interfaces__action__ServoJ_Result result;
} arm_calibration_interfaces__action__ServoJ_GetResult_Response;

// Struct for a sequence of arm_calibration_interfaces__action__ServoJ_GetResult_Response.
typedef struct arm_calibration_interfaces__action__ServoJ_GetResult_Response__Sequence
{
  arm_calibration_interfaces__action__ServoJ_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} arm_calibration_interfaces__action__ServoJ_GetResult_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "arm_calibration_interfaces/action/detail/servo_j__struct.h"

/// Struct defined in action/ServoJ in the package arm_calibration_interfaces.
typedef struct arm_calibration_interfaces__action__ServoJ_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  arm_calibration_interfaces__action__ServoJ_Feedback feedback;
} arm_calibration_interfaces__action__ServoJ_FeedbackMessage;

// Struct for a sequence of arm_calibration_interfaces__action__ServoJ_FeedbackMessage.
typedef struct arm_calibration_interfaces__action__ServoJ_FeedbackMessage__Sequence
{
  arm_calibration_interfaces__action__ServoJ_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} arm_calibration_interfaces__action__ServoJ_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ARM_CALIBRATION_INTERFACES__ACTION__DETAIL__SERVO_J__STRUCT_H_
