// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from messages:msg/PoseConstraint.idl
// generated code does not contain a copyright notice

#ifndef MESSAGES__MSG__DETAIL__POSE_CONSTRAINT__TRAITS_HPP_
#define MESSAGES__MSG__DETAIL__POSE_CONSTRAINT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "messages/msg/detail/pose_constraint__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace messages
{

namespace msg
{

inline void to_flow_style_yaml(
  const PoseConstraint & msg,
  std::ostream & out)
{
  out << "{";
  // member: pose1_id
  {
    out << "pose1_id: ";
    rosidl_generator_traits::value_to_yaml(msg.pose1_id, out);
    out << ", ";
  }

  // member: pose2_id
  {
    out << "pose2_id: ";
    rosidl_generator_traits::value_to_yaml(msg.pose2_id, out);
    out << ", ";
  }

  // member: dx
  {
    out << "dx: ";
    rosidl_generator_traits::value_to_yaml(msg.dx, out);
    out << ", ";
  }

  // member: dy
  {
    out << "dy: ";
    rosidl_generator_traits::value_to_yaml(msg.dy, out);
    out << ", ";
  }

  // member: dtheta
  {
    out << "dtheta: ";
    rosidl_generator_traits::value_to_yaml(msg.dtheta, out);
    out << ", ";
  }

  // member: covariance
  {
    if (msg.covariance.size() == 0) {
      out << "covariance: []";
    } else {
      out << "covariance: [";
      size_t pending_items = msg.covariance.size();
      for (auto item : msg.covariance) {
        rosidl_generator_traits::value_to_yaml(item, out);
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
  const PoseConstraint & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: pose1_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pose1_id: ";
    rosidl_generator_traits::value_to_yaml(msg.pose1_id, out);
    out << "\n";
  }

  // member: pose2_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pose2_id: ";
    rosidl_generator_traits::value_to_yaml(msg.pose2_id, out);
    out << "\n";
  }

  // member: dx
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "dx: ";
    rosidl_generator_traits::value_to_yaml(msg.dx, out);
    out << "\n";
  }

  // member: dy
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "dy: ";
    rosidl_generator_traits::value_to_yaml(msg.dy, out);
    out << "\n";
  }

  // member: dtheta
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "dtheta: ";
    rosidl_generator_traits::value_to_yaml(msg.dtheta, out);
    out << "\n";
  }

  // member: covariance
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.covariance.size() == 0) {
      out << "covariance: []\n";
    } else {
      out << "covariance:\n";
      for (auto item : msg.covariance) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const PoseConstraint & msg, bool use_flow_style = false)
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
  const messages::msg::PoseConstraint & msg,
  std::ostream & out, size_t indentation = 0)
{
  messages::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use messages::msg::to_yaml() instead")]]
inline std::string to_yaml(const messages::msg::PoseConstraint & msg)
{
  return messages::msg::to_yaml(msg);
}

template<>
inline const char * data_type<messages::msg::PoseConstraint>()
{
  return "messages::msg::PoseConstraint";
}

template<>
inline const char * name<messages::msg::PoseConstraint>()
{
  return "messages/msg/PoseConstraint";
}

template<>
struct has_fixed_size<messages::msg::PoseConstraint>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<messages::msg::PoseConstraint>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<messages::msg::PoseConstraint>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MESSAGES__MSG__DETAIL__POSE_CONSTRAINT__TRAITS_HPP_
