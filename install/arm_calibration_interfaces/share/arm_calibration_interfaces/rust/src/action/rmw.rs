
#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "arm_calibration_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__arm_calibration_interfaces__action__ServoJ_Goal() -> *const std::ffi::c_void;
}

#[link(name = "arm_calibration_interfaces__rosidl_generator_c")]
extern "C" {
    fn arm_calibration_interfaces__action__ServoJ_Goal__init(msg: *mut ServoJ_Goal) -> bool;
    fn arm_calibration_interfaces__action__ServoJ_Goal__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ServoJ_Goal>, size: usize) -> bool;
    fn arm_calibration_interfaces__action__ServoJ_Goal__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ServoJ_Goal>);
    fn arm_calibration_interfaces__action__ServoJ_Goal__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ServoJ_Goal>, out_seq: *mut rosidl_runtime_rs::Sequence<ServoJ_Goal>) -> bool;
}

// Corresponds to arm_calibration_interfaces__action__ServoJ_Goal
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ServoJ_Goal {

    // This member is not documented.
    #[allow(missing_docs)]
    pub trajectory: trajectory_msgs::msg::rmw::JointTrajectory,

}



impl Default for ServoJ_Goal {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !arm_calibration_interfaces__action__ServoJ_Goal__init(&mut msg as *mut _) {
        panic!("Call to arm_calibration_interfaces__action__ServoJ_Goal__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ServoJ_Goal {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { arm_calibration_interfaces__action__ServoJ_Goal__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { arm_calibration_interfaces__action__ServoJ_Goal__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { arm_calibration_interfaces__action__ServoJ_Goal__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ServoJ_Goal {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ServoJ_Goal where Self: Sized {
  const TYPE_NAME: &'static str = "arm_calibration_interfaces/action/ServoJ_Goal";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__arm_calibration_interfaces__action__ServoJ_Goal() }
  }
}


#[link(name = "arm_calibration_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__arm_calibration_interfaces__action__ServoJ_Result() -> *const std::ffi::c_void;
}

#[link(name = "arm_calibration_interfaces__rosidl_generator_c")]
extern "C" {
    fn arm_calibration_interfaces__action__ServoJ_Result__init(msg: *mut ServoJ_Result) -> bool;
    fn arm_calibration_interfaces__action__ServoJ_Result__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ServoJ_Result>, size: usize) -> bool;
    fn arm_calibration_interfaces__action__ServoJ_Result__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ServoJ_Result>);
    fn arm_calibration_interfaces__action__ServoJ_Result__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ServoJ_Result>, out_seq: *mut rosidl_runtime_rs::Sequence<ServoJ_Result>) -> bool;
}

// Corresponds to arm_calibration_interfaces__action__ServoJ_Result
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ServoJ_Result {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}



impl Default for ServoJ_Result {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !arm_calibration_interfaces__action__ServoJ_Result__init(&mut msg as *mut _) {
        panic!("Call to arm_calibration_interfaces__action__ServoJ_Result__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ServoJ_Result {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { arm_calibration_interfaces__action__ServoJ_Result__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { arm_calibration_interfaces__action__ServoJ_Result__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { arm_calibration_interfaces__action__ServoJ_Result__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ServoJ_Result {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ServoJ_Result where Self: Sized {
  const TYPE_NAME: &'static str = "arm_calibration_interfaces/action/ServoJ_Result";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__arm_calibration_interfaces__action__ServoJ_Result() }
  }
}


#[link(name = "arm_calibration_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__arm_calibration_interfaces__action__ServoJ_Feedback() -> *const std::ffi::c_void;
}

#[link(name = "arm_calibration_interfaces__rosidl_generator_c")]
extern "C" {
    fn arm_calibration_interfaces__action__ServoJ_Feedback__init(msg: *mut ServoJ_Feedback) -> bool;
    fn arm_calibration_interfaces__action__ServoJ_Feedback__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ServoJ_Feedback>, size: usize) -> bool;
    fn arm_calibration_interfaces__action__ServoJ_Feedback__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ServoJ_Feedback>);
    fn arm_calibration_interfaces__action__ServoJ_Feedback__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ServoJ_Feedback>, out_seq: *mut rosidl_runtime_rs::Sequence<ServoJ_Feedback>) -> bool;
}

// Corresponds to arm_calibration_interfaces__action__ServoJ_Feedback
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ServoJ_Feedback {

    // This member is not documented.
    #[allow(missing_docs)]
    pub current_point: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub elapsed_seconds: f64,

    /// 本周期传给底层servo_j的目标，单位为弧度。
    pub commanded_positions: rosidl_runtime_rs::Sequence<f64>,

}



impl Default for ServoJ_Feedback {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !arm_calibration_interfaces__action__ServoJ_Feedback__init(&mut msg as *mut _) {
        panic!("Call to arm_calibration_interfaces__action__ServoJ_Feedback__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ServoJ_Feedback {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { arm_calibration_interfaces__action__ServoJ_Feedback__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { arm_calibration_interfaces__action__ServoJ_Feedback__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { arm_calibration_interfaces__action__ServoJ_Feedback__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ServoJ_Feedback {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ServoJ_Feedback where Self: Sized {
  const TYPE_NAME: &'static str = "arm_calibration_interfaces/action/ServoJ_Feedback";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__arm_calibration_interfaces__action__ServoJ_Feedback() }
  }
}


#[link(name = "arm_calibration_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__arm_calibration_interfaces__action__ServoJ_FeedbackMessage() -> *const std::ffi::c_void;
}

#[link(name = "arm_calibration_interfaces__rosidl_generator_c")]
extern "C" {
    fn arm_calibration_interfaces__action__ServoJ_FeedbackMessage__init(msg: *mut ServoJ_FeedbackMessage) -> bool;
    fn arm_calibration_interfaces__action__ServoJ_FeedbackMessage__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ServoJ_FeedbackMessage>, size: usize) -> bool;
    fn arm_calibration_interfaces__action__ServoJ_FeedbackMessage__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ServoJ_FeedbackMessage>);
    fn arm_calibration_interfaces__action__ServoJ_FeedbackMessage__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ServoJ_FeedbackMessage>, out_seq: *mut rosidl_runtime_rs::Sequence<ServoJ_FeedbackMessage>) -> bool;
}

// Corresponds to arm_calibration_interfaces__action__ServoJ_FeedbackMessage
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ServoJ_FeedbackMessage {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub feedback: super::super::action::rmw::ServoJ_Feedback,

}



impl Default for ServoJ_FeedbackMessage {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !arm_calibration_interfaces__action__ServoJ_FeedbackMessage__init(&mut msg as *mut _) {
        panic!("Call to arm_calibration_interfaces__action__ServoJ_FeedbackMessage__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ServoJ_FeedbackMessage {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { arm_calibration_interfaces__action__ServoJ_FeedbackMessage__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { arm_calibration_interfaces__action__ServoJ_FeedbackMessage__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { arm_calibration_interfaces__action__ServoJ_FeedbackMessage__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ServoJ_FeedbackMessage {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ServoJ_FeedbackMessage where Self: Sized {
  const TYPE_NAME: &'static str = "arm_calibration_interfaces/action/ServoJ_FeedbackMessage";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__arm_calibration_interfaces__action__ServoJ_FeedbackMessage() }
  }
}




#[link(name = "arm_calibration_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__arm_calibration_interfaces__action__ServoJ_SendGoal_Request() -> *const std::ffi::c_void;
}

#[link(name = "arm_calibration_interfaces__rosidl_generator_c")]
extern "C" {
    fn arm_calibration_interfaces__action__ServoJ_SendGoal_Request__init(msg: *mut ServoJ_SendGoal_Request) -> bool;
    fn arm_calibration_interfaces__action__ServoJ_SendGoal_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ServoJ_SendGoal_Request>, size: usize) -> bool;
    fn arm_calibration_interfaces__action__ServoJ_SendGoal_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ServoJ_SendGoal_Request>);
    fn arm_calibration_interfaces__action__ServoJ_SendGoal_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ServoJ_SendGoal_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<ServoJ_SendGoal_Request>) -> bool;
}

// Corresponds to arm_calibration_interfaces__action__ServoJ_SendGoal_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ServoJ_SendGoal_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub goal: super::super::action::rmw::ServoJ_Goal,

}



impl Default for ServoJ_SendGoal_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !arm_calibration_interfaces__action__ServoJ_SendGoal_Request__init(&mut msg as *mut _) {
        panic!("Call to arm_calibration_interfaces__action__ServoJ_SendGoal_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ServoJ_SendGoal_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { arm_calibration_interfaces__action__ServoJ_SendGoal_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { arm_calibration_interfaces__action__ServoJ_SendGoal_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { arm_calibration_interfaces__action__ServoJ_SendGoal_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ServoJ_SendGoal_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ServoJ_SendGoal_Request where Self: Sized {
  const TYPE_NAME: &'static str = "arm_calibration_interfaces/action/ServoJ_SendGoal_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__arm_calibration_interfaces__action__ServoJ_SendGoal_Request() }
  }
}


#[link(name = "arm_calibration_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__arm_calibration_interfaces__action__ServoJ_SendGoal_Response() -> *const std::ffi::c_void;
}

#[link(name = "arm_calibration_interfaces__rosidl_generator_c")]
extern "C" {
    fn arm_calibration_interfaces__action__ServoJ_SendGoal_Response__init(msg: *mut ServoJ_SendGoal_Response) -> bool;
    fn arm_calibration_interfaces__action__ServoJ_SendGoal_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ServoJ_SendGoal_Response>, size: usize) -> bool;
    fn arm_calibration_interfaces__action__ServoJ_SendGoal_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ServoJ_SendGoal_Response>);
    fn arm_calibration_interfaces__action__ServoJ_SendGoal_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ServoJ_SendGoal_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<ServoJ_SendGoal_Response>) -> bool;
}

// Corresponds to arm_calibration_interfaces__action__ServoJ_SendGoal_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ServoJ_SendGoal_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub accepted: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::rmw::Time,

}



impl Default for ServoJ_SendGoal_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !arm_calibration_interfaces__action__ServoJ_SendGoal_Response__init(&mut msg as *mut _) {
        panic!("Call to arm_calibration_interfaces__action__ServoJ_SendGoal_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ServoJ_SendGoal_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { arm_calibration_interfaces__action__ServoJ_SendGoal_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { arm_calibration_interfaces__action__ServoJ_SendGoal_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { arm_calibration_interfaces__action__ServoJ_SendGoal_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ServoJ_SendGoal_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ServoJ_SendGoal_Response where Self: Sized {
  const TYPE_NAME: &'static str = "arm_calibration_interfaces/action/ServoJ_SendGoal_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__arm_calibration_interfaces__action__ServoJ_SendGoal_Response() }
  }
}


#[link(name = "arm_calibration_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__arm_calibration_interfaces__action__ServoJ_GetResult_Request() -> *const std::ffi::c_void;
}

#[link(name = "arm_calibration_interfaces__rosidl_generator_c")]
extern "C" {
    fn arm_calibration_interfaces__action__ServoJ_GetResult_Request__init(msg: *mut ServoJ_GetResult_Request) -> bool;
    fn arm_calibration_interfaces__action__ServoJ_GetResult_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ServoJ_GetResult_Request>, size: usize) -> bool;
    fn arm_calibration_interfaces__action__ServoJ_GetResult_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ServoJ_GetResult_Request>);
    fn arm_calibration_interfaces__action__ServoJ_GetResult_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ServoJ_GetResult_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<ServoJ_GetResult_Request>) -> bool;
}

// Corresponds to arm_calibration_interfaces__action__ServoJ_GetResult_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ServoJ_GetResult_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,

}



impl Default for ServoJ_GetResult_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !arm_calibration_interfaces__action__ServoJ_GetResult_Request__init(&mut msg as *mut _) {
        panic!("Call to arm_calibration_interfaces__action__ServoJ_GetResult_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ServoJ_GetResult_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { arm_calibration_interfaces__action__ServoJ_GetResult_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { arm_calibration_interfaces__action__ServoJ_GetResult_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { arm_calibration_interfaces__action__ServoJ_GetResult_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ServoJ_GetResult_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ServoJ_GetResult_Request where Self: Sized {
  const TYPE_NAME: &'static str = "arm_calibration_interfaces/action/ServoJ_GetResult_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__arm_calibration_interfaces__action__ServoJ_GetResult_Request() }
  }
}


#[link(name = "arm_calibration_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__arm_calibration_interfaces__action__ServoJ_GetResult_Response() -> *const std::ffi::c_void;
}

#[link(name = "arm_calibration_interfaces__rosidl_generator_c")]
extern "C" {
    fn arm_calibration_interfaces__action__ServoJ_GetResult_Response__init(msg: *mut ServoJ_GetResult_Response) -> bool;
    fn arm_calibration_interfaces__action__ServoJ_GetResult_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ServoJ_GetResult_Response>, size: usize) -> bool;
    fn arm_calibration_interfaces__action__ServoJ_GetResult_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ServoJ_GetResult_Response>);
    fn arm_calibration_interfaces__action__ServoJ_GetResult_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ServoJ_GetResult_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<ServoJ_GetResult_Response>) -> bool;
}

// Corresponds to arm_calibration_interfaces__action__ServoJ_GetResult_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ServoJ_GetResult_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub status: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub result: super::super::action::rmw::ServoJ_Result,

}



impl Default for ServoJ_GetResult_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !arm_calibration_interfaces__action__ServoJ_GetResult_Response__init(&mut msg as *mut _) {
        panic!("Call to arm_calibration_interfaces__action__ServoJ_GetResult_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ServoJ_GetResult_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { arm_calibration_interfaces__action__ServoJ_GetResult_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { arm_calibration_interfaces__action__ServoJ_GetResult_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { arm_calibration_interfaces__action__ServoJ_GetResult_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ServoJ_GetResult_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ServoJ_GetResult_Response where Self: Sized {
  const TYPE_NAME: &'static str = "arm_calibration_interfaces/action/ServoJ_GetResult_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__arm_calibration_interfaces__action__ServoJ_GetResult_Response() }
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


