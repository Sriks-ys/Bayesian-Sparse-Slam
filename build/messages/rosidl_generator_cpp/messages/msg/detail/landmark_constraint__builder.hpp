// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from messages:msg/LandmarkConstraint.idl
// generated code does not contain a copyright notice

#ifndef MESSAGES__MSG__DETAIL__LANDMARK_CONSTRAINT__BUILDER_HPP_
#define MESSAGES__MSG__DETAIL__LANDMARK_CONSTRAINT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "messages/msg/detail/landmark_constraint__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace messages
{

namespace msg
{

namespace builder
{

class Init_LandmarkConstraint_covariance
{
public:
  explicit Init_LandmarkConstraint_covariance(::messages::msg::LandmarkConstraint & msg)
  : msg_(msg)
  {}
  ::messages::msg::LandmarkConstraint covariance(::messages::msg::LandmarkConstraint::_covariance_type arg)
  {
    msg_.covariance = std::move(arg);
    return std::move(msg_);
  }

private:
  ::messages::msg::LandmarkConstraint msg_;
};

class Init_LandmarkConstraint_alpha
{
public:
  explicit Init_LandmarkConstraint_alpha(::messages::msg::LandmarkConstraint & msg)
  : msg_(msg)
  {}
  Init_LandmarkConstraint_covariance alpha(::messages::msg::LandmarkConstraint::_alpha_type arg)
  {
    msg_.alpha = std::move(arg);
    return Init_LandmarkConstraint_covariance(msg_);
  }

private:
  ::messages::msg::LandmarkConstraint msg_;
};

class Init_LandmarkConstraint_rho
{
public:
  explicit Init_LandmarkConstraint_rho(::messages::msg::LandmarkConstraint & msg)
  : msg_(msg)
  {}
  Init_LandmarkConstraint_alpha rho(::messages::msg::LandmarkConstraint::_rho_type arg)
  {
    msg_.rho = std::move(arg);
    return Init_LandmarkConstraint_alpha(msg_);
  }

private:
  ::messages::msg::LandmarkConstraint msg_;
};

class Init_LandmarkConstraint_landmark_id
{
public:
  explicit Init_LandmarkConstraint_landmark_id(::messages::msg::LandmarkConstraint & msg)
  : msg_(msg)
  {}
  Init_LandmarkConstraint_rho landmark_id(::messages::msg::LandmarkConstraint::_landmark_id_type arg)
  {
    msg_.landmark_id = std::move(arg);
    return Init_LandmarkConstraint_rho(msg_);
  }

private:
  ::messages::msg::LandmarkConstraint msg_;
};

class Init_LandmarkConstraint_pose_id
{
public:
  explicit Init_LandmarkConstraint_pose_id(::messages::msg::LandmarkConstraint & msg)
  : msg_(msg)
  {}
  Init_LandmarkConstraint_landmark_id pose_id(::messages::msg::LandmarkConstraint::_pose_id_type arg)
  {
    msg_.pose_id = std::move(arg);
    return Init_LandmarkConstraint_landmark_id(msg_);
  }

private:
  ::messages::msg::LandmarkConstraint msg_;
};

class Init_LandmarkConstraint_header
{
public:
  Init_LandmarkConstraint_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LandmarkConstraint_pose_id header(::messages::msg::LandmarkConstraint::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_LandmarkConstraint_pose_id(msg_);
  }

private:
  ::messages::msg::LandmarkConstraint msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::messages::msg::LandmarkConstraint>()
{
  return messages::msg::builder::Init_LandmarkConstraint_header();
}

}  // namespace messages

#endif  // MESSAGES__MSG__DETAIL__LANDMARK_CONSTRAINT__BUILDER_HPP_
