// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from messages:msg/PoseGraph.idl
// generated code does not contain a copyright notice

#ifndef MESSAGES__MSG__DETAIL__POSE_GRAPH__TRAITS_HPP_
#define MESSAGES__MSG__DETAIL__POSE_GRAPH__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "messages/msg/detail/pose_graph__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'nodes'
#include "messages/msg/detail/pose_node__traits.hpp"
// Member 'pose_constraints'
#include "messages/msg/detail/pose_constraint__traits.hpp"
// Member 'landmark_constraints'
#include "messages/msg/detail/landmark_constraint__traits.hpp"

namespace messages
{

namespace msg
{

inline void to_flow_style_yaml(
  const PoseGraph & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: nodes
  {
    if (msg.nodes.size() == 0) {
      out << "nodes: []";
    } else {
      out << "nodes: [";
      size_t pending_items = msg.nodes.size();
      for (auto item : msg.nodes) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: pose_constraints
  {
    if (msg.pose_constraints.size() == 0) {
      out << "pose_constraints: []";
    } else {
      out << "pose_constraints: [";
      size_t pending_items = msg.pose_constraints.size();
      for (auto item : msg.pose_constraints) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: landmark_constraints
  {
    if (msg.landmark_constraints.size() == 0) {
      out << "landmark_constraints: []";
    } else {
      out << "landmark_constraints: [";
      size_t pending_items = msg.landmark_constraints.size();
      for (auto item : msg.landmark_constraints) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const PoseGraph & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: nodes
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.nodes.size() == 0) {
      out << "nodes: []\n";
    } else {
      out << "nodes:\n";
      for (auto item : msg.nodes) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: pose_constraints
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.pose_constraints.size() == 0) {
      out << "pose_constraints: []\n";
    } else {
      out << "pose_constraints:\n";
      for (auto item : msg.pose_constraints) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: landmark_constraints
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.landmark_constraints.size() == 0) {
      out << "landmark_constraints: []\n";
    } else {
      out << "landmark_constraints:\n";
      for (auto item : msg.landmark_constraints) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const PoseGraph & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace messages

namespace rosidl_generator_traits
{

[[deprecated("use messages::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const messages::msg::PoseGraph & msg,
  std::ostream & out, size_t indentation = 0)
{
  messages::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use messages::msg::to_yaml() instead")]]
inline std::string to_yaml(const messages::msg::PoseGraph & msg)
{
  return messages::msg::to_yaml(msg);
}

template<>
inline const char * data_type<messages::msg::PoseGraph>()
{
  return "messages::msg::PoseGraph";
}

template<>
inline const char * name<messages::msg::PoseGraph>()
{
  return "messages/msg/PoseGraph";
}

template<>
struct has_fixed_size<messages::msg::PoseGraph>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<messages::msg::PoseGraph>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<messages::msg::PoseGraph>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MESSAGES__MSG__DETAIL__POSE_GRAPH__TRAITS_HPP_
