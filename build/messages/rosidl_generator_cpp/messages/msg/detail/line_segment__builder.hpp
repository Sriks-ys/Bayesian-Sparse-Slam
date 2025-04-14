// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from messages:msg/LineSegment.idl
// generated code does not contain a copyright notice

#ifndef MESSAGES__MSG__DETAIL__LINE_SEGMENT__BUILDER_HPP_
#define MESSAGES__MSG__DETAIL__LINE_SEGMENT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "messages/msg/detail/line_segment__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace messages
{

namespace msg
{

namespace builder
{

class Init_LineSegment_end
{
public:
  explicit Init_LineSegment_end(::messages::msg::LineSegment & msg)
  : msg_(msg)
  {}
  ::messages::msg::LineSegment end(::messages::msg::LineSegment::_end_type arg)
  {
    msg_.end = std::move(arg);
    return std::move(msg_);
  }

private:
  ::messages::msg::LineSegment msg_;
};

class Init_LineSegment_start
{
public:
  explicit Init_LineSegment_start(::messages::msg::LineSegment & msg)
  : msg_(msg)
  {}
  Init_LineSegment_end start(::messages::msg::LineSegment::_start_type arg)
  {
    msg_.start = std::move(arg);
    return Init_LineSegment_end(msg_);
  }

private:
  ::messages::msg::LineSegment msg_;
};

class Init_LineSegment_covariance
{
public:
  explicit Init_LineSegment_covariance(::messages::msg::LineSegment & msg)
  : msg_(msg)
  {}
  Init_LineSegment_start covariance(::messages::msg::LineSegment::_covariance_type arg)
  {
    msg_.covariance = std::move(arg);
    return Init_LineSegment_start(msg_);
  }

private:
  ::messages::msg::LineSegment msg_;
};

class Init_LineSegment_alpha
{
public:
  explicit Init_LineSegment_alpha(::messages::msg::LineSegment & msg)
  : msg_(msg)
  {}
  Init_LineSegment_covariance alpha(::messages::msg::LineSegment::_alpha_type arg)
  {
    msg_.alpha = std::move(arg);
    return Init_LineSegment_covariance(msg_);
  }

private:
  ::messages::msg::LineSegment msg_;
};

class Init_LineSegment_rho
{
public:
  Init_LineSegment_rho()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LineSegment_alpha rho(::messages::msg::LineSegment::_rho_type arg)
  {
    msg_.rho = std::move(arg);
    return Init_LineSegment_alpha(msg_);
  }

private:
  ::messages::msg::LineSegment msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::messages::msg::LineSegment>()
{
  return messages::msg::builder::Init_LineSegment_rho();
}

}  // namespace messages

#endif  // MESSAGES__MSG__DETAIL__LINE_SEGMENT__BUILDER_HPP_
