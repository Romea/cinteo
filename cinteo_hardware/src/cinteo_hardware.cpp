// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


// ros2
#include "rclcpp/macros.hpp"
#include "rclcpp/rclcpp.hpp"

// romea
#include "romea_mobile_base_utils/ros2_control/info/hardware_info_common.hpp"

// local
#include "cinteo_hardware/cinteo_hardware.hpp"


namespace romea
{
namespace ros2
{

//-----------------------------------------------------------------------------
CinteoHardware::CinteoHardware()
: HardwareSystemInterface<HardwareInterface1FAS2RWD>("CinteoHardware"),
  // front_wheel_radius_(0),
  rear_wheel_radius_(0),
  // wheelbase_(0),
  // front_track_(0),
  front_steering_angle_measure_(0),
  rear_left_wheel_angular_speed_measure_(0),
  rear_right_wheel_angular_speed_measure_(0),
  front_steering_angle_command_(0),
  rear_left_wheel_angular_speed_command_(0),
  rear_right_wheel_angular_speed_command_(0)
{
}

//-----------------------------------------------------------------------------
CinteoHardware::~CinteoHardware()
{
  // force deactive when interface has not been deactivated by controller manager but by ctrl-c
  if (lifecycle_state_.id() == 3) {
    on_deactivate(lifecycle_state_);
  }
}


//-----------------------------------------------------------------------------
hardware_interface::return_type CinteoHardware::connect_()
{
  // RCLCPP_ERROR(rclcpp::get_logger("CinteoHardware"), "Init communication with robot");
  // To be implememented

  send_null_command_();
  return hardware_interface::return_type::OK;
}

//-----------------------------------------------------------------------------
hardware_interface::return_type CinteoHardware::disconnect_()
{
  // RCLCPP_ERROR(rclcpp::get_logger("CinteoHardware"), "Close communication with robot");
  // To be implememented

  send_null_command_();
  return hardware_interface::return_type::OK;
}

//-----------------------------------------------------------------------------
hardware_interface::return_type CinteoHardware::load_info_(
  const hardware_interface::HardwareInfo & hardware_info)
{
  try {
    // Get some info from ros2_control item of robot urdf file
    // wheelbase_ = get_parameter<double>(hardware_info, "wheelbase");
    // front_track_ = get_parameter<double>(hardware_info, "front_track");
    // front_wheel_radius_ = get_parameter<float>(hardware_info, "front_wheel_radius");
    // rear_wheel_radius_ = get_parameter<float>(hardware_info, "rear_wheel_radius");
    rear_wheel_radius_ = get_rear_wheel_radius(hardware_info);
    return hardware_interface::return_type::OK;
  } catch (std::runtime_error & e) {
    RCLCPP_FATAL_STREAM(rclcpp::get_logger("CinteoHardware"), e.what());
    return hardware_interface::return_type::ERROR;
  }
}

//-----------------------------------------------------------------------------
void CinteoHardware::send_command_()
{
  // To be implememented
  // Send command to robot
}

//-----------------------------------------------------------------------------
void CinteoHardware::send_null_command_()
{
  // To be implememented
  // Send null command to robot
}


//-----------------------------------------------------------------------------
#if ROS_DISTRO == ROS_GALACTIC
hardware_interface::return_type CinteoHardware::read()
#else
hardware_interface::return_type CinteoHardware::read(
  const rclcpp::Time & /*time*/,
  const rclcpp::Duration & /*period*/)
#endif
{
  // RCLCPP_ERROR(rclcpp::get_logger("CinteoHardware"), "Read data from robot ");
  // To be implememented
  // front_steering_angle_measure_ = ???
  // front_left_wheel_angular_speed_measure_ = ???
  // front_right_wheel_angular_speed_measure_ = ???


  try {
    set_hardware_state_();
    return hardware_interface::return_type::OK;
  } catch (std::runtime_error & e) {
    RCLCPP_FATAL_STREAM(rclcpp::get_logger("CinteoHardware"), e.what());
    return hardware_interface::return_type::ERROR;
  }
}


//-----------------------------------------------------------------------------
#if ROS_DISTRO == ROS_GALACTIC
hardware_interface::return_type CinteoHardware::write()
# else
hardware_interface::return_type CinteoHardware::write(
  const rclcpp::Time & /*time*/,
  const rclcpp::Duration & /*period*/)
#endif
{
  // RCLCPP_ERROR(rclcpp::get_logger("CinteoHardware"), "Send command to robot");
  get_hardware_command_();
  send_command_();

  return hardware_interface::return_type::OK;
}


//-----------------------------------------------------------------------------
void CinteoHardware::set_hardware_state_()
{
  core::HardwareState1FAS2RWD state;
  state.frontAxleSteeringAngle = front_steering_angle_measure_;
  state.rearLeftWheelSpinningMotion.velocity = rear_left_wheel_angular_speed_measure_;
  state.rearRightWheelSpinningMotion.velocity = rear_right_wheel_angular_speed_measure_;
  this->hardware_interface_->set_feedback(state);
}

//-----------------------------------------------------------------------------
void CinteoHardware::get_hardware_command_()
{
  core::HardwareCommand1FAS2RWD command = this->hardware_interface_->get_hardware_command();
  front_steering_angle_command_ = command.frontAxleSteeringAngle;
  rear_left_wheel_angular_speed_command_ = command.rearLeftWheelSpinningSetPoint;
  rear_right_wheel_angular_speed_command_ = command.rearRightWheelSpinningSetPoint;
}

}  // namespace ros2
}  // namespace romea


#include "pluginlib/class_list_macros.hpp"
PLUGINLIB_EXPORT_CLASS(romea::ros2::CinteoHardware, hardware_interface::SystemInterface)
