// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from messages:msg/PoseNode.idl
// generated code does not contain a copyright notice

#ifndef MESSAGES__MSG__DETAIL__POSE_NODE__BUILDER_HPP_
#define MESSAGES__MSG__DETAIL__POSE_NODE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "messages/msg/detail/pose_node__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace messages
{

namespace msg
{

namespace builder
{

class Init_PoseNode_covariance
{
public:
  explicit Init_PoseNode_covariance(::messages::msg::PoseNode & msg)
  : msg_(msg)
  {}
  ::messages::msg::PoseNode covariance(::messages::msg::PoseNode::_covariance_type arg)
  {
    msg_.covariance = std::move(arg);
    return std::move(msg_);
  }

private:
  ::messages::msg::PoseNode msg_;
};

class Init_PoseNode_theta
{
public:
  explicit Init_PoseNode_theta(::messages::msg::PoseNode & msg)
  : msg_(msg)
  {}
  Init_PoseNode_covariance theta(::messages::msg::PoseNode::_theta_type arg)
  {
    msg_.theta = std::move(arg);
    return Init_PoseNode_covariance(msg_);
  }

private:
  ::messages::msg::PoseNode msg_;
};

class Init_PoseNode_y
{
public:
  explicit Init_PoseNode_y(::messages::msg::PoseNode & msg)
  : msg_(msg)
  {}
  Init_PoseNode_theta y(::messages::msg::PoseNode::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_PoseNode_theta(msg_);
  }

private:
  ::messages::msg::PoseNode msg_;
};

class Init_PoseNode_x
{
public:
  explicit Init_PoseNode_x(::messages::msg::PoseNode & msg)
  : msg_(msg)
  {}
  Init_PoseNode_y x(::messages::msg::PoseNode::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_PoseNode_y(msg_);
  }

private:
  ::messages::msg::PoseNode msg_;
};

class Init_PoseNode_id
{
public:
  Init_PoseNode_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PoseNode_x id(::messages::msg::PoseNode::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_PoseNode_x(msg_);
  }

private:
  ::messages::msg::PoseNode msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::messages::msg::PoseNode>()
{
  return messages::msg::builder::Init_PoseNode_id();
}

}  // namespace messages

#endif  // MESSAGES__MSG__DETAIL__POSE_NODE__BUILDER_HPP_
