// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from messages:msg/LineSegmentList.idl
// generated code does not contain a copyright notice

#ifndef MESSAGES__MSG__DETAIL__LINE_SEGMENT_LIST__BUILDER_HPP_
#define MESSAGES__MSG__DETAIL__LINE_SEGMENT_LIST__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "messages/msg/detail/line_segment_list__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace messages
{

namespace msg
{

namespace builder
{

class Init_LineSegmentList_segments
{
public:
  explicit Init_LineSegmentList_segments(::messages::msg::LineSegmentList & msg)
  : msg_(msg)
  {}
  ::messages::msg::LineSegmentList segments(::messages::msg::LineSegmentList::_segments_type arg)
  {
    msg_.segments = std::move(arg);
    return std::move(msg_);
  }

private:
  ::messages::msg::LineSegmentList msg_;
};

class Init_LineSegmentList_header
{
public:
  Init_LineSegmentList_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LineSegmentList_segments header(::messages::msg::LineSegmentList::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_LineSegmentList_segments(msg_);
  }

private:
  ::messages::msg::LineSegmentList msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::messages::msg::LineSegmentList>()
{
  return messages::msg::builder::Init_LineSegmentList_header();
}

}  // namespace messages

#endif  // MESSAGES__MSG__DETAIL__LINE_SEGMENT_LIST__BUILDER_HPP_
