// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from messages:msg/LandmarkLandmarkConstraintList.idl
// generated code does not contain a copyright notice

#ifndef MESSAGES__MSG__DETAIL__LANDMARK_LANDMARK_CONSTRAINT_LIST__TRAITS_HPP_
#define MESSAGES__MSG__DETAIL__LANDMARK_LANDMARK_CONSTRAINT_LIST__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "messages/msg/detail/landmark_landmark_constraint_list__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'constraints'
#include "messages/msg/detail/landmark_landmark_constraint__traits.hpp"

namespace messages
{

namespace msg
{

inline void to_flow_style_yaml(
  const LandmarkLandmarkConstraintList & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: constraints
  {
    if (msg.constraints.size() == 0) {
      out << "constraints: []";
    } else {
      out << "constraints: [";
      size_t pending_items = msg.constraints.size();
      for (auto item : msg.constraints) {
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
  const LandmarkLandmarkConstraintList & msg,
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

  // member: constraints
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.constraints.size() == 0) {
      out << "constraints: []\n";
    } else {
      out << "constraints:\n";
      for (auto item : msg.constraints) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LandmarkLandmarkConstraintList & msg, bool use_flow_style = false)
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
  const messages::msg::LandmarkLandmarkConstraintList & msg,
  std::ostream & out, size_t indentation = 0)
{
  messages::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use messages::msg::to_yaml() instead")]]
inline std::string to_yaml(const messages::msg::LandmarkLandmarkConstraintList & msg)
{
  return messages::msg::to_yaml(msg);
}

template<>
inline const char * data_type<messages::msg::LandmarkLandmarkConstraintList>()
{
  return "messages::msg::LandmarkLandmarkConstraintList";
}

template<>
inline const char * name<messages::msg::LandmarkLandmarkConstraintList>()
{
  return "messages/msg/LandmarkLandmarkConstraintList";
}

template<>
struct has_fixed_size<messages::msg::LandmarkLandmarkConstraintList>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<messages::msg::LandmarkLandmarkConstraintList>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<messages::msg::LandmarkLandmarkConstraintList>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MESSAGES__MSG__DETAIL__LANDMARK_LANDMARK_CONSTRAINT_LIST__TRAITS_HPP_
