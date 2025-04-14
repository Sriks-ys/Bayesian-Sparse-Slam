// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from messages:msg/LandmarkConstraintList.idl
// generated code does not contain a copyright notice

#ifndef MESSAGES__MSG__DETAIL__LANDMARK_CONSTRAINT_LIST__STRUCT_HPP_
#define MESSAGES__MSG__DETAIL__LANDMARK_CONSTRAINT_LIST__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"
// Member 'segments'
#include "messages/msg/detail/landmark_constraint__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__messages__msg__LandmarkConstraintList __attribute__((deprecated))
#else
# define DEPRECATED__messages__msg__LandmarkConstraintList __declspec(deprecated)
#endif

namespace messages
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LandmarkConstraintList_
{
  using Type = LandmarkConstraintList_<ContainerAllocator>;

  explicit LandmarkConstraintList_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    (void)_init;
  }

  explicit LandmarkConstraintList_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _segments_type =
    std::vector<messages::msg::LandmarkConstraint_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<messages::msg::LandmarkConstraint_<ContainerAllocator>>>;
  _segments_type segments;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__segments(
    const std::vector<messages::msg::LandmarkConstraint_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<messages::msg::LandmarkConstraint_<ContainerAllocator>>> & _arg)
  {
    this->segments = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    messages::msg::LandmarkConstraintList_<ContainerAllocator> *;
  using ConstRawPtr =
    const messages::msg::LandmarkConstraintList_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<messages::msg::LandmarkConstraintList_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<messages::msg::LandmarkConstraintList_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      messages::msg::LandmarkConstraintList_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<messages::msg::LandmarkConstraintList_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      messages::msg::LandmarkConstraintList_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<messages::msg::LandmarkConstraintList_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<messages::msg::LandmarkConstraintList_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<messages::msg::LandmarkConstraintList_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__messages__msg__LandmarkConstraintList
    std::shared_ptr<messages::msg::LandmarkConstraintList_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__messages__msg__LandmarkConstraintList
    std::shared_ptr<messages::msg::LandmarkConstraintList_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LandmarkConstraintList_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->segments != other.segments) {
      return false;
    }
    return true;
  }
  bool operator!=(const LandmarkConstraintList_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LandmarkConstraintList_

// alias to use template instance with default allocator
using LandmarkConstraintList =
  messages::msg::LandmarkConstraintList_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace messages

#endif  // MESSAGES__MSG__DETAIL__LANDMARK_CONSTRAINT_LIST__STRUCT_HPP_
