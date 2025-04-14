// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from messages:msg/LandmarkLandmarkConstraintList.idl
// generated code does not contain a copyright notice

#ifndef MESSAGES__MSG__DETAIL__LANDMARK_LANDMARK_CONSTRAINT_LIST__BUILDER_HPP_
#define MESSAGES__MSG__DETAIL__LANDMARK_LANDMARK_CONSTRAINT_LIST__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "messages/msg/detail/landmark_landmark_constraint_list__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace messages
{

namespace msg
{

namespace builder
{

class Init_LandmarkLandmarkConstraintList_constraints
{
public:
  explicit Init_LandmarkLandmarkConstraintList_constraints(::messages::msg::LandmarkLandmarkConstraintList & msg)
  : msg_(msg)
  {}
  ::messages::msg::LandmarkLandmarkConstraintList constraints(::messages::msg::LandmarkLandmarkConstraintList::_constraints_type arg)
  {
    msg_.constraints = std::move(arg);
    return std::move(msg_);
  }

private:
  ::messages::msg::LandmarkLandmarkConstraintList msg_;
};

class Init_LandmarkLandmarkConstraintList_header
{
public:
  Init_LandmarkLandmarkConstraintList_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LandmarkLandmarkConstraintList_constraints header(::messages::msg::LandmarkLandmarkConstraintList::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_LandmarkLandmarkConstraintList_constraints(msg_);
  }

private:
  ::messages::msg::LandmarkLandmarkConstraintList msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::messages::msg::LandmarkLandmarkConstraintList>()
{
  return messages::msg::builder::Init_LandmarkLandmarkConstraintList_header();
}

}  // namespace messages

#endif  // MESSAGES__MSG__DETAIL__LANDMARK_LANDMARK_CONSTRAINT_LIST__BUILDER_HPP_
