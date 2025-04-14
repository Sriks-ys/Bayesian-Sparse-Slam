// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from messages:msg/LandmarkConstraintList.idl
// generated code does not contain a copyright notice

#ifndef MESSAGES__MSG__DETAIL__LANDMARK_CONSTRAINT_LIST__TRAITS_HPP_
#define MESSAGES__MSG__DETAIL__LANDMARK_CONSTRAINT_LIST__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "messages/msg/detail/landmark_constraint_list__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'segments'
#include "messages/msg/detail/landmark_constraint__traits.hpp"

namespace messages
{

namespace msg
{

inline void to_flow_style_yaml(
  const LandmarkConstraintList & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: segments
  {
    if (msg.segments.size() == 0) {
      out << "segments: []";
    } else {
      out << "segments: [";
      size_t pending_items = msg.segments.size();
      for (auto item : msg.segments) {
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
  const LandmarkConstraintList & msg,
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

  // member: segments
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.segments.size() == 0) {
      out << "segments: []\n";
    } else {
      out << "segments:\n";
      for (auto item : msg.segments) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LandmarkConstraintList & msg, bool use_flow_style = false)
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
  const messages::msg::LandmarkConstraintList & msg,
  std::ostream & out, size_t indentation = 0)
{
  messages::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use messages::msg::to_yaml() instead")]]
inline std::string to_yaml(const messages::msg::LandmarkConstraintList & msg)
{
  return messages::msg::to_yaml(msg);
}

template<>
inline const char * data_type<messages::msg::LandmarkConstraintList>()
{
  return "messages::msg::LandmarkConstraintList";
}

template<>
inline const char * name<messages::msg::LandmarkConstraintList>()
{
  return "messages/msg/LandmarkConstraintList";
}

template<>
struct has_fixed_size<messages::msg::LandmarkConstraintList>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<messages::msg::LandmarkConstraintList>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<messages::msg::LandmarkConstraintList>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MESSAGES__MSG__DETAIL__LANDMARK_CONSTRAINT_LIST__TRAITS_HPP_
