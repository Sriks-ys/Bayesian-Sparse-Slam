// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from messages:msg/LandmarkLandmarkConstraintList.idl
// generated code does not contain a copyright notice

#ifndef MESSAGES__MSG__DETAIL__LANDMARK_LANDMARK_CONSTRAINT_LIST__STRUCT_HPP_
#define MESSAGES__MSG__DETAIL__LANDMARK_LANDMARK_CONSTRAINT_LIST__STRUCT_HPP_

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
// Member 'constraints'
#include "messages/msg/detail/landmark_landmark_constraint__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__messages__msg__LandmarkLandmarkConstraintList __attribute__((deprecated))
#else
# define DEPRECATED__messages__msg__LandmarkLandmarkConstraintList __declspec(deprecated)
#endif

namespace messages
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LandmarkLandmarkConstraintList_
{
  using Type = LandmarkLandmarkConstraintList_<ContainerAllocator>;

  explicit LandmarkLandmarkConstraintList_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    (void)_init;
  }

  explicit LandmarkLandmarkConstraintList_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _constraints_type =
    std::vector<messages::msg::LandmarkLandmarkConstraint_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<messages::msg::LandmarkLandmarkConstraint_<ContainerAllocator>>>;
  _constraints_type constraints;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__constraints(
    const std::vector<messages::msg::LandmarkLandmarkConstraint_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<messages::msg::LandmarkLandmarkConstraint_<ContainerAllocator>>> & _arg)
  {
    this->constraints = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    messages::msg::LandmarkLandmarkConstraintList_<ContainerAllocator> *;
  using ConstRawPtr =
    const messages::msg::LandmarkLandmarkConstraintList_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<messages::msg::LandmarkLandmarkConstraintList_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<messages::msg::LandmarkLandmarkConstraintList_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      messages::msg::LandmarkLandmarkConstraintList_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<messages::msg::LandmarkLandmarkConstraintList_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      messages::msg::LandmarkLandmarkConstraintList_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<messages::msg::LandmarkLandmarkConstraintList_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<messages::msg::LandmarkLandmarkConstraintList_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<messages::msg::LandmarkLandmarkConstraintList_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__messages__msg__LandmarkLandmarkConstraintList
    std::shared_ptr<messages::msg::LandmarkLandmarkConstraintList_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__messages__msg__LandmarkLandmarkConstraintList
    std::shared_ptr<messages::msg::LandmarkLandmarkConstraintList_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LandmarkLandmarkConstraintList_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->constraints != other.constraints) {
      return false;
    }
    return true;
  }
  bool operator!=(const LandmarkLandmarkConstraintList_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LandmarkLandmarkConstraintList_

// alias to use template instance with default allocator
using LandmarkLandmarkConstraintList =
  messages::msg::LandmarkLandmarkConstraintList_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace messages

#endif  // MESSAGES__MSG__DETAIL__LANDMARK_LANDMARK_CONSTRAINT_LIST__STRUCT_HPP_
