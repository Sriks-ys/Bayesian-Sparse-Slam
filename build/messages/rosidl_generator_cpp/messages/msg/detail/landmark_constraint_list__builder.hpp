// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from messages:msg/LandmarkConstraintList.idl
// generated code does not contain a copyright notice

#ifndef MESSAGES__MSG__DETAIL__LANDMARK_CONSTRAINT_LIST__BUILDER_HPP_
#define MESSAGES__MSG__DETAIL__LANDMARK_CONSTRAINT_LIST__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "messages/msg/detail/landmark_constraint_list__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace messages
{

namespace msg
{

namespace builder
{

class Init_LandmarkConstraintList_segments
{
public:
  explicit Init_LandmarkConstraintList_segments(::messages::msg::LandmarkConstraintList & msg)
  : msg_(msg)
  {}
  ::messages::msg::LandmarkConstraintList segments(::messages::msg::LandmarkConstraintList::_segments_type arg)
  {
    msg_.segments = std::move(arg);
    return std::move(msg_);
  }

private:
  ::messages::msg::LandmarkConstraintList msg_;
};

class Init_LandmarkConstraintList_header
{
public:
  Init_LandmarkConstraintList_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LandmarkConstraintList_segments header(::messages::msg::LandmarkConstraintList::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_LandmarkConstraintList_segments(msg_);
  }

private:
  ::messages::msg::LandmarkConstraintList msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::messages::msg::LandmarkConstraintList>()
{
  return messages::msg::builder::Init_LandmarkConstraintList_header();
}

}  // namespace messages

#endif  // MESSAGES__MSG__DETAIL__LANDMARK_CONSTRAINT_LIST__BUILDER_HPP_
