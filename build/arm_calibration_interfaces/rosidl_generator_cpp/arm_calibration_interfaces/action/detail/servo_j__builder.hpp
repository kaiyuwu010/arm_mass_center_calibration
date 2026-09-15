// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from arm_calibration_interfaces:action/ServoJ.idl
// generated code does not contain a copyright notice

#ifndef ARM_CALIBRATION_INTERFACES__ACTION__DETAIL__SERVO_J__BUILDER_HPP_
#define ARM_CALIBRATION_INTERFACES__ACTION__DETAIL__SERVO_J__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "arm_calibration_interfaces/action/detail/servo_j__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace arm_calibration_interfaces
{

namespace action
{

namespace builder
{

class Init_ServoJ_Goal_trajectory
{
public:
  Init_ServoJ_Goal_trajectory()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::arm_calibration_interfaces::action::ServoJ_Goal trajectory(::arm_calibration_interfaces::action::ServoJ_Goal::_trajectory_type arg)
  {
    msg_.trajectory = std::move(arg);
    return std::move(msg_);
  }

private:
  ::arm_calibration_interfaces::action::ServoJ_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::arm_calibration_interfaces::action::ServoJ_Goal>()
{
  return arm_calibration_interfaces::action::builder::Init_ServoJ_Goal_trajectory();
}

}  // namespace arm_calibration_interfaces


namespace arm_calibration_interfaces
{

namespace action
{

namespace builder
{

class Init_ServoJ_Result_message
{
public:
  explicit Init_ServoJ_Result_message(::arm_calibration_interfaces::action::ServoJ_Result & msg)
  : msg_(msg)
  {}
  ::arm_calibration_interfaces::action::ServoJ_Result message(::arm_calibration_interfaces::action::ServoJ_Result::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::arm_calibration_interfaces::action::ServoJ_Result msg_;
};

class Init_ServoJ_Result_success
{
public:
  Init_ServoJ_Result_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ServoJ_Result_message success(::arm_calibration_interfaces::action::ServoJ_Result::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_ServoJ_Result_message(msg_);
  }

private:
  ::arm_calibration_interfaces::action::ServoJ_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::arm_calibration_interfaces::action::ServoJ_Result>()
{
  return arm_calibration_interfaces::action::builder::Init_ServoJ_Result_success();
}

}  // namespace arm_calibration_interfaces


namespace arm_calibration_interfaces
{

namespace action
{

namespace builder
{

class Init_ServoJ_Feedback_commanded_positions
{
public:
  explicit Init_ServoJ_Feedback_commanded_positions(::arm_calibration_interfaces::action::ServoJ_Feedback & msg)
  : msg_(msg)
  {}
  ::arm_calibration_interfaces::action::ServoJ_Feedback commanded_positions(::arm_calibration_interfaces::action::ServoJ_Feedback::_commanded_positions_type arg)
  {
    msg_.commanded_positions = std::move(arg);
    return std::move(msg_);
  }

private:
  ::arm_calibration_interfaces::action::ServoJ_Feedback msg_;
};

class Init_ServoJ_Feedback_elapsed_seconds
{
public:
  explicit Init_ServoJ_Feedback_elapsed_seconds(::arm_calibration_interfaces::action::ServoJ_Feedback & msg)
  : msg_(msg)
  {}
  Init_ServoJ_Feedback_commanded_positions elapsed_seconds(::arm_calibration_interfaces::action::ServoJ_Feedback::_elapsed_seconds_type arg)
  {
    msg_.elapsed_seconds = std::move(arg);
    return Init_ServoJ_Feedback_commanded_positions(msg_);
  }

private:
  ::arm_calibration_interfaces::action::ServoJ_Feedback msg_;
};

class Init_ServoJ_Feedback_current_point
{
public:
  Init_ServoJ_Feedback_current_point()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ServoJ_Feedback_elapsed_seconds current_point(::arm_calibration_interfaces::action::ServoJ_Feedback::_current_point_type arg)
  {
    msg_.current_point = std::move(arg);
    return Init_ServoJ_Feedback_elapsed_seconds(msg_);
  }

private:
  ::arm_calibration_interfaces::action::ServoJ_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::arm_calibration_interfaces::action::ServoJ_Feedback>()
{
  return arm_calibration_interfaces::action::builder::Init_ServoJ_Feedback_current_point();
}

}  // namespace arm_calibration_interfaces


namespace arm_calibration_interfaces
{

namespace action
{

namespace builder
{

class Init_ServoJ_SendGoal_Request_goal
{
public:
  explicit Init_ServoJ_SendGoal_Request_goal(::arm_calibration_interfaces::action::ServoJ_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::arm_calibration_interfaces::action::ServoJ_SendGoal_Request goal(::arm_calibration_interfaces::action::ServoJ_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::arm_calibration_interfaces::action::ServoJ_SendGoal_Request msg_;
};

class Init_ServoJ_SendGoal_Request_goal_id
{
public:
  Init_ServoJ_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ServoJ_SendGoal_Request_goal goal_id(::arm_calibration_interfaces::action::ServoJ_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_ServoJ_SendGoal_Request_goal(msg_);
  }

private:
  ::arm_calibration_interfaces::action::ServoJ_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::arm_calibration_interfaces::action::ServoJ_SendGoal_Request>()
{
  return arm_calibration_interfaces::action::builder::Init_ServoJ_SendGoal_Request_goal_id();
}

}  // namespace arm_calibration_interfaces


namespace arm_calibration_interfaces
{

namespace action
{

namespace builder
{

class Init_ServoJ_SendGoal_Response_stamp
{
public:
  explicit Init_ServoJ_SendGoal_Response_stamp(::arm_calibration_interfaces::action::ServoJ_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::arm_calibration_interfaces::action::ServoJ_SendGoal_Response stamp(::arm_calibration_interfaces::action::ServoJ_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::arm_calibration_interfaces::action::ServoJ_SendGoal_Response msg_;
};

class Init_ServoJ_SendGoal_Response_accepted
{
public:
  Init_ServoJ_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ServoJ_SendGoal_Response_stamp accepted(::arm_calibration_interfaces::action::ServoJ_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_ServoJ_SendGoal_Response_stamp(msg_);
  }

private:
  ::arm_calibration_interfaces::action::ServoJ_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::arm_calibration_interfaces::action::ServoJ_SendGoal_Response>()
{
  return arm_calibration_interfaces::action::builder::Init_ServoJ_SendGoal_Response_accepted();
}

}  // namespace arm_calibration_interfaces


namespace arm_calibration_interfaces
{

namespace action
{

namespace builder
{

class Init_ServoJ_GetResult_Request_goal_id
{
public:
  Init_ServoJ_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::arm_calibration_interfaces::action::ServoJ_GetResult_Request goal_id(::arm_calibration_interfaces::action::ServoJ_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::arm_calibration_interfaces::action::ServoJ_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::arm_calibration_interfaces::action::ServoJ_GetResult_Request>()
{
  return arm_calibration_interfaces::action::builder::Init_ServoJ_GetResult_Request_goal_id();
}

}  // namespace arm_calibration_interfaces


namespace arm_calibration_interfaces
{

namespace action
{

namespace builder
{

class Init_ServoJ_GetResult_Response_result
{
public:
  explicit Init_ServoJ_GetResult_Response_result(::arm_calibration_interfaces::action::ServoJ_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::arm_calibration_interfaces::action::ServoJ_GetResult_Response result(::arm_calibration_interfaces::action::ServoJ_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::arm_calibration_interfaces::action::ServoJ_GetResult_Response msg_;
};

class Init_ServoJ_GetResult_Response_status
{
public:
  Init_ServoJ_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ServoJ_GetResult_Response_result status(::arm_calibration_interfaces::action::ServoJ_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_ServoJ_GetResult_Response_result(msg_);
  }

private:
  ::arm_calibration_interfaces::action::ServoJ_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::arm_calibration_interfaces::action::ServoJ_GetResult_Response>()
{
  return arm_calibration_interfaces::action::builder::Init_ServoJ_GetResult_Response_status();
}

}  // namespace arm_calibration_interfaces


namespace arm_calibration_interfaces
{

namespace action
{

namespace builder
{

class Init_ServoJ_FeedbackMessage_feedback
{
public:
  explicit Init_ServoJ_FeedbackMessage_feedback(::arm_calibration_interfaces::action::ServoJ_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::arm_calibration_interfaces::action::ServoJ_FeedbackMessage feedback(::arm_calibration_interfaces::action::ServoJ_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::arm_calibration_interfaces::action::ServoJ_FeedbackMessage msg_;
};

class Init_ServoJ_FeedbackMessage_goal_id
{
public:
  Init_ServoJ_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ServoJ_FeedbackMessage_feedback goal_id(::arm_calibration_interfaces::action::ServoJ_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_ServoJ_FeedbackMessage_feedback(msg_);
  }

private:
  ::arm_calibration_interfaces::action::ServoJ_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::arm_calibration_interfaces::action::ServoJ_FeedbackMessage>()
{
  return arm_calibration_interfaces::action::builder::Init_ServoJ_FeedbackMessage_goal_id();
}

}  // namespace arm_calibration_interfaces

#endif  // ARM_CALIBRATION_INTERFACES__ACTION__DETAIL__SERVO_J__BUILDER_HPP_
