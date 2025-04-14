// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from messages:msg/LandmarkConstraint.idl
// generated code does not contain a copyright notice

#ifndef MESSAGES__MSG__DETAIL__LANDMARK_CONSTRAINT__TRAITS_HPP_
#define MESSAGES__MSG__DETAIL__LANDMARK_CONSTRAINT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "messages/msg/detail/landmark_constraint__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace messages
{

namespace msg
{

inline void to_flow_style_yaml(
  const LandmarkConstraint & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: pose_id
  {
    out << "pose_id: ";
    rosidl_generator_traits::value_to_yaml(msg.pose_id, out);
    out << ", ";
  }

  // member: landmark_id
  {
    out << "landmark_id: ";
    rosidl_generator_traits::value_to_yaml(msg.landmark_id, out);
    out << ", ";
  }

  // member: rho
  {
    out << "rho: ";
    rosidl_generator_traits::value_to_yaml(msg.rho, out);
    out << ", ";
  }

  // member: alpha
  {
    out << "alpha: ";
    rosidl_generator_traits::value_to_yaml(msg.alpha, out);
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
  const LandmarkConstraint & msg,
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

  // member: pose_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pose_id: ";
    rosidl_generator_traits::value_to_yaml(msg.pose_id, out);
    out << "\n";
  }

  // member: landmark_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "landmark_id: ";
    rosidl_generator_traits::value_to_yaml(msg.landmark_id, out);
    out << "\n";
  }

  // member: rho
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "rho: ";
    rosidl_generator_traits::value_to_yaml(msg.rho, out);
    out << "\n";
  }

  // member: alpha
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "alpha: ";
    rosidl_generator_traits::value_to_yaml(msg.alpha, out);
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

inline std::string to_yaml(const LandmarkConstraint & msg, bool use_flow_style = false)
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
  const messages::msg::LandmarkConstraint & msg,
  std::ostream & out, size_t indentation = 0)
{
  messages::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use messages::msg::to_yaml() instead")]]
inline std::string to_yaml(const messages::msg::LandmarkConstraint & msg)
{
  return messages::msg::to_yaml(msg);
}

template<>
inline const char * data_type<messages::msg::LandmarkConstraint>()
{
  return "messages::msg::LandmarkConstraint";
}

template<>
inline const char * name<messages::msg::LandmarkConstraint>()
{
  return "messages/msg/LandmarkConstraint";
}

template<>
struct has_fixed_size<messages::msg::LandmarkConstraint>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<messages::msg::LandmarkConstraint>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<messages::msg::LandmarkConstraint>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MESSAGES__MSG__DETAIL__LANDMARK_CONSTRAINT__TRAITS_HPP_
