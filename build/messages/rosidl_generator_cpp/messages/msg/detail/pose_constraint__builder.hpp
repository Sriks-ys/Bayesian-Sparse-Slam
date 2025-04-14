// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from messages:msg/PoseConstraint.idl
// generated code does not contain a copyright notice

#ifndef MESSAGES__MSG__DETAIL__POSE_CONSTRAINT__BUILDER_HPP_
#define MESSAGES__MSG__DETAIL__POSE_CONSTRAINT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "messages/msg/detail/pose_constraint__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace messages
{

namespace msg
{

namespace builder
{

class Init_PoseConstraint_covariance
{
public:
  explicit Init_PoseConstraint_covariance(::messages::msg::PoseConstraint & msg)
  : msg_(msg)
  {}
  ::messages::msg::PoseConstraint covariance(::messages::msg::PoseConstraint::_covariance_type arg)
  {
    msg_.covariance = std::move(arg);
    return std::move(msg_);
  }

private:
  ::messages::msg::PoseConstraint msg_;
};

class Init_PoseConstraint_dtheta
{
public:
  explicit Init_PoseConstraint_dtheta(::messages::msg::PoseConstraint & msg)
  : msg_(msg)
  {}
  Init_PoseConstraint_covariance dtheta(::messages::msg::PoseConstraint::_dtheta_type arg)
  {
    msg_.dtheta = std::move(arg);
    return Init_PoseConstraint_covariance(msg_);
  }

private:
  ::messages::msg::PoseConstraint msg_;
};

class Init_PoseConstraint_dy
{
public:
  explicit Init_PoseConstraint_dy(::messages::msg::PoseConstraint & msg)
  : msg_(msg)
  {}
  Init_PoseConstraint_dtheta dy(::messages::msg::PoseConstraint::_dy_type arg)
  {
    msg_.dy = std::move(arg);
    return Init_PoseConstraint_dtheta(msg_);
  }

private:
  ::messages::msg::PoseConstraint msg_;
};

class Init_PoseConstraint_dx
{
public:
  explicit Init_PoseConstraint_dx(::messages::msg::PoseConstraint & msg)
  : msg_(msg)
  {}
  Init_PoseConstraint_dy dx(::messages::msg::PoseConstraint::_dx_type arg)
  {
    msg_.dx = std::move(arg);
    return Init_PoseConstraint_dy(msg_);
  }

private:
  ::messages::msg::PoseConstraint msg_;
};

class Init_PoseConstraint_pose2_id
{
public:
  explicit Init_PoseConstraint_pose2_id(::messages::msg::PoseConstraint & msg)
  : msg_(msg)
  {}
  Init_PoseConstraint_dx pose2_id(::messages::msg::PoseConstraint::_pose2_id_type arg)
  {
    msg_.pose2_id = std::move(arg);
    return Init_PoseConstraint_dx(msg_);
  }

private:
  ::messages::msg::PoseConstraint msg_;
};

class Init_PoseConstraint_pose1_id
{
public:
  Init_PoseConstraint_pose1_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PoseConstraint_pose2_id pose1_id(::messages::msg::PoseConstraint::_pose1_id_type arg)
  {
    msg_.pose1_id = std::move(arg);
    return Init_PoseConstraint_pose2_id(msg_);
  }

private:
  ::messages::msg::PoseConstraint msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::messages::msg::PoseConstraint>()
{
  return messages::msg::builder::Init_PoseConstraint_pose1_id();
}

}  // namespace messages

#endif  // MESSAGES__MSG__DETAIL__POSE_CONSTRAINT__BUILDER_HPP_
