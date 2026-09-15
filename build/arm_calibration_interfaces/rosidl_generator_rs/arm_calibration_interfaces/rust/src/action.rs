
#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to arm_calibration_interfaces__action__ServoJ_Goal

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ServoJ_Goal {

    // This member is not documented.
    #[allow(missing_docs)]
    pub trajectory: trajectory_msgs::msg::JointTrajectory,

}



impl Default for ServoJ_Goal {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ServoJ_Goal::default())
  }
}

impl rosidl_runtime_rs::Message for ServoJ_Goal {
  type RmwMsg = super::action::rmw::ServoJ_Goal;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        trajectory: trajectory_msgs::msg::JointTrajectory::into_rmw_message(std::borrow::Cow::Owned(msg.trajectory)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        trajectory: trajectory_msgs::msg::JointTrajectory::into_rmw_message(std::borrow::Cow::Borrowed(&msg.trajectory)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      trajectory: trajectory_msgs::msg::JointTrajectory::from_rmw_message(msg.trajectory),
    }
  }
}


// Corresponds to arm_calibration_interfaces__action__ServoJ_Result

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ServoJ_Result {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: std::string::String,

}



impl Default for ServoJ_Result {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ServoJ_Result::default())
  }
}

impl rosidl_runtime_rs::Message for ServoJ_Result {
  type RmwMsg = super::action::rmw::ServoJ_Result;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        message: msg.message.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
        message: msg.message.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      message: msg.message.to_string(),
    }
  }
}


// Corresponds to arm_calibration_interfaces__action__ServoJ_Feedback

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ServoJ_Feedback {

    // This member is not documented.
    #[allow(missing_docs)]
    pub current_point: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub elapsed_seconds: f64,

    /// 本周期传给底层servo_j的目标，单位为弧度。
    pub commanded_positions: Vec<f64>,

}



impl Default for ServoJ_Feedback {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ServoJ_Feedback::default())
  }
}

impl rosidl_runtime_rs::Message for ServoJ_Feedback {
  type RmwMsg = super::action::rmw::ServoJ_Feedback;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        current_point: msg.current_point,
        elapsed_seconds: msg.elapsed_seconds,
        commanded_positions: msg.commanded_positions.into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      current_point: msg.current_point,
      elapsed_seconds: msg.elapsed_seconds,
        commanded_positions: msg.commanded_positions.as_slice().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      current_point: msg.current_point,
      elapsed_seconds: msg.elapsed_seconds,
      commanded_positions: msg.commanded_positions
          .into_iter()
          .collect(),
    }
  }
}


// Corresponds to arm_calibration_interfaces__action__ServoJ_FeedbackMessage

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ServoJ_FeedbackMessage {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub feedback: super::action::ServoJ_Feedback,

}



impl Default for ServoJ_FeedbackMessage {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ServoJ_FeedbackMessage::default())
  }
}

impl rosidl_runtime_rs::Message for ServoJ_FeedbackMessage {
  type RmwMsg = super::action::rmw::ServoJ_FeedbackMessage;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Owned(msg.goal_id)).into_owned(),
        feedback: super::action::ServoJ_Feedback::into_rmw_message(std::borrow::Cow::Owned(msg.feedback)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal_id)).into_owned(),
        feedback: super::action::ServoJ_Feedback::into_rmw_message(std::borrow::Cow::Borrowed(&msg.feedback)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      goal_id: unique_identifier_msgs::msg::UUID::from_rmw_message(msg.goal_id),
      feedback: super::action::ServoJ_Feedback::from_rmw_message(msg.feedback),
    }
  }
}






// Corresponds to arm_calibration_interfaces__action__ServoJ_SendGoal_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ServoJ_SendGoal_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub goal: super::action::ServoJ_Goal,

}



impl Default for ServoJ_SendGoal_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ServoJ_SendGoal_Request::default())
  }
}

impl rosidl_runtime_rs::Message for ServoJ_SendGoal_Request {
  type RmwMsg = super::action::rmw::ServoJ_SendGoal_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Owned(msg.goal_id)).into_owned(),
        goal: super::action::ServoJ_Goal::into_rmw_message(std::borrow::Cow::Owned(msg.goal)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal_id)).into_owned(),
        goal: super::action::ServoJ_Goal::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      goal_id: unique_identifier_msgs::msg::UUID::from_rmw_message(msg.goal_id),
      goal: super::action::ServoJ_Goal::from_rmw_message(msg.goal),
    }
  }
}


// Corresponds to arm_calibration_interfaces__action__ServoJ_SendGoal_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ServoJ_SendGoal_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub accepted: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::Time,

}



impl Default for ServoJ_SendGoal_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ServoJ_SendGoal_Response::default())
  }
}

impl rosidl_runtime_rs::Message for ServoJ_SendGoal_Response {
  type RmwMsg = super::action::rmw::ServoJ_SendGoal_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        accepted: msg.accepted,
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Owned(msg.stamp)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      accepted: msg.accepted,
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Borrowed(&msg.stamp)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      accepted: msg.accepted,
      stamp: builtin_interfaces::msg::Time::from_rmw_message(msg.stamp),
    }
  }
}


// Corresponds to arm_calibration_interfaces__action__ServoJ_GetResult_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ServoJ_GetResult_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::UUID,

}



impl Default for ServoJ_GetResult_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ServoJ_GetResult_Request::default())
  }
}

impl rosidl_runtime_rs::Message for ServoJ_GetResult_Request {
  type RmwMsg = super::action::rmw::ServoJ_GetResult_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Owned(msg.goal_id)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal_id)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      goal_id: unique_identifier_msgs::msg::UUID::from_rmw_message(msg.goal_id),
    }
  }
}


// Corresponds to arm_calibration_interfaces__action__ServoJ_GetResult_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ServoJ_GetResult_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub status: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub result: super::action::ServoJ_Result,

}



impl Default for ServoJ_GetResult_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ServoJ_GetResult_Response::default())
  }
}

impl rosidl_runtime_rs::Message for ServoJ_GetResult_Response {
  type RmwMsg = super::action::rmw::ServoJ_GetResult_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        status: msg.status,
        result: super::action::ServoJ_Result::into_rmw_message(std::borrow::Cow::Owned(msg.result)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      status: msg.status,
        result: super::action::ServoJ_Result::into_rmw_message(std::borrow::Cow::Borrowed(&msg.result)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      status: msg.status,
      result: super::action::ServoJ_Result::from_rmw_message(msg.result),
    }
  }
}






#[link(name = "arm_calibration_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__arm_calibration_interfaces__action__ServoJ_SendGoal() -> *const std::ffi::c_void;
}

// Corresponds to arm_calibration_interfaces__action__ServoJ_SendGoal
#[allow(missing_docs, non_camel_case_types)]
pub struct ServoJ_SendGoal;

impl rosidl_runtime_rs::Service for ServoJ_SendGoal {
    type Request = ServoJ_SendGoal_Request;
    type Response = ServoJ_SendGoal_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__arm_calibration_interfaces__action__ServoJ_SendGoal() }
    }
}




#[link(name = "arm_calibration_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__arm_calibration_interfaces__action__ServoJ_GetResult() -> *const std::ffi::c_void;
}

// Corresponds to arm_calibration_interfaces__action__ServoJ_GetResult
#[allow(missing_docs, non_camel_case_types)]
pub struct ServoJ_GetResult;

impl rosidl_runtime_rs::Service for ServoJ_GetResult {
    type Request = ServoJ_GetResult_Request;
    type Response = ServoJ_GetResult_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__arm_calibration_interfaces__action__ServoJ_GetResult() }
    }
}






#[link(name = "arm_calibration_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_action_type_support_handle__arm_calibration_interfaces__action__ServoJ() -> *const std::ffi::c_void;
}

// Corresponds to arm_calibration_interfaces__action__ServoJ
#[allow(missing_docs, non_camel_case_types)]
pub struct ServoJ;

impl rosidl_runtime_rs::Action for ServoJ {
  // --- Associated types for client library users ---
  /// The goal message defined in the action definition.
  type Goal = ServoJ_Goal;

  /// The result message defined in the action definition.
  type Result = ServoJ_Result;

  /// The feedback message defined in the action definition.
  type Feedback = ServoJ_Feedback;

  // --- Associated types for client library implementation ---
  /// The feedback message with generic fields which wraps the feedback message.
  type FeedbackMessage = super::action::ServoJ_FeedbackMessage;

  /// The send_goal service using a wrapped version of the goal message as a request.
  type SendGoalService = super::action::ServoJ_SendGoal;

  /// The generic service to cancel a goal.
  type CancelGoalService = action_msgs::srv::rmw::CancelGoal;

  /// The get_result service using a wrapped version of the result message as a response.
  type GetResultService = super::action::ServoJ_GetResult;

  // --- Methods for client library implementation ---
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_action_type_support_handle__arm_calibration_interfaces__action__ServoJ() }
  }

  fn create_goal_request(
    goal_id: &[u8; 16],
    goal: super::action::rmw::ServoJ_Goal,
  ) -> super::action::rmw::ServoJ_SendGoal_Request {
   super::action::rmw::ServoJ_SendGoal_Request {
      goal_id: unique_identifier_msgs::msg::rmw::UUID { uuid: *goal_id },
      goal,
    }
  }

  fn split_goal_request(
    request: super::action::rmw::ServoJ_SendGoal_Request,
  ) -> (
    [u8; 16],
   super::action::rmw::ServoJ_Goal,
  ) {
    (request.goal_id.uuid, request.goal)
  }

  fn create_goal_response(
    accepted: bool,
    stamp: (i32, u32),
  ) -> super::action::rmw::ServoJ_SendGoal_Response {
   super::action::rmw::ServoJ_SendGoal_Response {
      accepted,
      stamp: builtin_interfaces::msg::rmw::Time {
        sec: stamp.0,
        nanosec: stamp.1,
      },
    }
  }

  fn get_goal_response_accepted(
    response: &super::action::rmw::ServoJ_SendGoal_Response,
  ) -> bool {
    response.accepted
  }

  fn get_goal_response_stamp(
    response: &super::action::rmw::ServoJ_SendGoal_Response,
  ) -> (i32, u32) {
    (response.stamp.sec, response.stamp.nanosec)
  }

  fn create_feedback_message(
    goal_id: &[u8; 16],
    feedback: super::action::rmw::ServoJ_Feedback,
  ) -> super::action::rmw::ServoJ_FeedbackMessage {
    let mut message = super::action::rmw::ServoJ_FeedbackMessage::default();
    message.goal_id.uuid = *goal_id;
    message.feedback = feedback;
    message
  }

  fn split_feedback_message(
    feedback: super::action::rmw::ServoJ_FeedbackMessage,
  ) -> (
    [u8; 16],
   super::action::rmw::ServoJ_Feedback,
  ) {
    (feedback.goal_id.uuid, feedback.feedback)
  }

  fn create_result_request(
    goal_id: &[u8; 16],
  ) -> super::action::rmw::ServoJ_GetResult_Request {
   super::action::rmw::ServoJ_GetResult_Request {
      goal_id: unique_identifier_msgs::msg::rmw::UUID { uuid: *goal_id },
    }
  }

  fn get_result_request_uuid(
    request: &super::action::rmw::ServoJ_GetResult_Request,
  ) -> &[u8; 16] {
    &request.goal_id.uuid
  }

  fn create_result_response(
    status: i8,
    result: super::action::rmw::ServoJ_Result,
  ) -> super::action::rmw::ServoJ_GetResult_Response {
   super::action::rmw::ServoJ_GetResult_Response {
      status,
      result,
    }
  }

  fn split_result_response(
    response: super::action::rmw::ServoJ_GetResult_Response
  ) -> (
    i8,
   super::action::rmw::ServoJ_Result,
  ) {
    (response.status, response.result)
  }
}


