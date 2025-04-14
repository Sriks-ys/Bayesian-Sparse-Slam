// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from messages:msg/PoseGraph.idl
// generated code does not contain a copyright notice

#ifndef MESSAGES__MSG__DETAIL__POSE_GRAPH__BUILDER_HPP_
#define MESSAGES__MSG__DETAIL__POSE_GRAPH__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "messages/msg/detail/pose_graph__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace messages
{

namespace msg
{

namespace builder
{

class Init_PoseGraph_landmark_constraints
{
public:
  explicit Init_PoseGraph_landmark_constraints(::messages::msg::PoseGraph & msg)
  : msg_(msg)
  {}
  ::messages::msg::PoseGraph landmark_constraints(::messages::msg::PoseGraph::_landmark_constraints_type arg)
  {
    msg_.landmark_constraints = std::move(arg);
    return std::move(msg_);
  }

private:
  ::messages::msg::PoseGraph msg_;
};

class Init_PoseGraph_pose_constraints
{
public:
  explicit Init_PoseGraph_pose_constraints(::messages::msg::PoseGraph & msg)
  : msg_(msg)
  {}
  Init_PoseGraph_landmark_constraints pose_constraints(::messages::msg::PoseGraph::_pose_constraints_type arg)
  {
    msg_.pose_constraints = std::move(arg);
    return Init_PoseGraph_landmark_constraints(msg_);
  }

private:
  ::messages::msg::PoseGraph msg_;
};

class Init_PoseGraph_nodes
{
public:
  explicit Init_PoseGraph_nodes(::messages::msg::PoseGraph & msg)
  : msg_(msg)
  {}
  Init_PoseGraph_pose_constraints nodes(::messages::msg::PoseGraph::_nodes_type arg)
  {
    msg_.nodes = std::move(arg);
    return Init_PoseGraph_pose_constraints(msg_);
  }

private:
  ::messages::msg::PoseGraph msg_;
};

class Init_PoseGraph_header
{
public:
  Init_PoseGraph_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PoseGraph_nodes header(::messages::msg::PoseGraph::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_PoseGraph_nodes(msg_);
  }

private:
  ::messages::msg::PoseGraph msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::messages::msg::PoseGraph>()
{
  return messages::msg::builder::Init_PoseGraph_header();
}

}  // namespace messages

#endif  // MESSAGES__MSG__DETAIL__POSE_GRAPH__BUILDER_HPP_
