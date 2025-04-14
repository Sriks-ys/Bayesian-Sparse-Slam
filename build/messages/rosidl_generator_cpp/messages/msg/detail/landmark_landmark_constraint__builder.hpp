// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from messages:msg/LandmarkLandmarkConstraint.idl
// generated code does not contain a copyright notice

#ifndef MESSAGES__MSG__DETAIL__LANDMARK_LANDMARK_CONSTRAINT__BUILDER_HPP_
#define MESSAGES__MSG__DETAIL__LANDMARK_LANDMARK_CONSTRAINT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "messages/msg/detail/landmark_landmark_constraint__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace messages
{

namespace msg
{

namespace builder
{

class Init_LandmarkLandmarkConstraint_covariance
{
public:
  explicit Init_LandmarkLandmarkConstraint_covariance(::messages::msg::LandmarkLandmarkConstraint & msg)
  : msg_(msg)
  {}
  ::messages::msg::LandmarkLandmarkConstraint covariance(::messages::msg::LandmarkLandmarkConstraint::_covariance_type arg)
  {
    msg_.covariance = std::move(arg);
    return std::move(msg_);
  }

private:
  ::messages::msg::LandmarkLandmarkConstraint msg_;
};

class Init_LandmarkLandmarkConstraint_dy
{
public:
  explicit Init_LandmarkLandmarkConstraint_dy(::messages::msg::LandmarkLandmarkConstraint & msg)
  : msg_(msg)
  {}
  Init_LandmarkLandmarkConstraint_covariance dy(::messages::msg::LandmarkLandmarkConstraint::_dy_type arg)
  {
    msg_.dy = std::move(arg);
    return Init_LandmarkLandmarkConstraint_covariance(msg_);
  }

private:
  ::messages::msg::LandmarkLandmarkConstraint msg_;
};

class Init_LandmarkLandmarkConstraint_dx
{
public:
  explicit Init_LandmarkLandmarkConstraint_dx(::messages::msg::LandmarkLandmarkConstraint & msg)
  : msg_(msg)
  {}
  Init_LandmarkLandmarkConstraint_dy dx(::messages::msg::LandmarkLandmarkConstraint::_dx_type arg)
  {
    msg_.dx = std::move(arg);
    return Init_LandmarkLandmarkConstraint_dy(msg_);
  }

private:
  ::messages::msg::LandmarkLandmarkConstraint msg_;
};

class Init_LandmarkLandmarkConstraint_landmark2_id
{
public:
  explicit Init_LandmarkLandmarkConstraint_landmark2_id(::messages::msg::LandmarkLandmarkConstraint & msg)
  : msg_(msg)
  {}
  Init_LandmarkLandmarkConstraint_dx landmark2_id(::messages::msg::LandmarkLandmarkConstraint::_landmark2_id_type arg)
  {
    msg_.landmark2_id = std::move(arg);
    return Init_LandmarkLandmarkConstraint_dx(msg_);
  }

private:
  ::messages::msg::LandmarkLandmarkConstraint msg_;
};

class Init_LandmarkLandmarkConstraint_landmark1_id
{
public:
  explicit Init_LandmarkLandmarkConstraint_landmark1_id(::messages::msg::LandmarkLandmarkConstraint & msg)
  : msg_(msg)
  {}
  Init_LandmarkLandmarkConstraint_landmark2_id landmark1_id(::messages::msg::LandmarkLandmarkConstraint::_landmark1_id_type arg)
  {
    msg_.landmark1_id = std::move(arg);
    return Init_LandmarkLandmarkConstraint_landmark2_id(msg_);
  }

private:
  ::messages::msg::LandmarkLandmarkConstraint msg_;
};

class Init_LandmarkLandmarkConstraint_header
{
public:
  Init_LandmarkLandmarkConstraint_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LandmarkLandmarkConstraint_landmark1_id header(::messages::msg::LandmarkLandmarkConstraint::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_LandmarkLandmarkConstraint_landmark1_id(msg_);
  }

private:
  ::messages::msg::LandmarkLandmarkConstraint msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::messages::msg::LandmarkLandmarkConstraint>()
{
  return messages::msg::builder::Init_LandmarkLandmarkConstraint_header();
}

}  // namespace messages

#endif  // MESSAGES__MSG__DETAIL__LANDMARK_LANDMARK_CONSTRAINT__BUILDER_HPP_
