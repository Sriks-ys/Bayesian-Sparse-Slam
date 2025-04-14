// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from messages:msg/PoseNode.idl
// generated code does not contain a copyright notice

#ifndef MESSAGES__MSG__DETAIL__POSE_NODE__STRUCT_HPP_
#define MESSAGES__MSG__DETAIL__POSE_NODE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__messages__msg__PoseNode __attribute__((deprecated))
#else
# define DEPRECATED__messages__msg__PoseNode __declspec(deprecated)
#endif

namespace messages
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct PoseNode_
{
  using Type = PoseNode_<ContainerAllocator>;

  explicit PoseNode_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0l;
      this->x = 0.0f;
      this->y = 0.0f;
      this->theta = 0.0f;
      std::fill<typename std::array<float, 9>::iterator, float>(this->covariance.begin(), this->covariance.end(), 0.0f);
    }
  }

  explicit PoseNode_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : covariance(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0l;
      this->x = 0.0f;
      this->y = 0.0f;
      this->theta = 0.0f;
      std::fill<typename std::array<float, 9>::iterator, float>(this->covariance.begin(), this->covariance.end(), 0.0f);
    }
  }

  // field types and members
  using _id_type =
    int32_t;
  _id_type id;
  using _x_type =
    float;
  _x_type x;
  using _y_type =
    float;
  _y_type y;
  using _theta_type =
    float;
  _theta_type theta;
  using _covariance_type =
    std::array<float, 9>;
  _covariance_type covariance;

  // setters for named parameter idiom
  Type & set__id(
    const int32_t & _arg)
  {
    this->id = _arg;
    return *this;
  }
  Type & set__x(
    const float & _arg)
  {
    this->x = _arg;
    return *this;
  }
  Type & set__y(
    const float & _arg)
  {
    this->y = _arg;
    return *this;
  }
  Type & set__theta(
    const float & _arg)
  {
    this->theta = _arg;
    return *this;
  }
  Type & set__covariance(
    const std::array<float, 9> & _arg)
  {
    this->covariance = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    messages::msg::PoseNode_<ContainerAllocator> *;
  using ConstRawPtr =
    const messages::msg::PoseNode_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<messages::msg::PoseNode_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<messages::msg::PoseNode_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      messages::msg::PoseNode_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<messages::msg::PoseNode_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      messages::msg::PoseNode_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<messages::msg::PoseNode_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<messages::msg::PoseNode_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<messages::msg::PoseNode_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__messages__msg__PoseNode
    std::shared_ptr<messages::msg::PoseNode_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__messages__msg__PoseNode
    std::shared_ptr<messages::msg::PoseNode_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PoseNode_ & other) const
  {
    if (this->id != other.id) {
      return false;
    }
    if (this->x != other.x) {
      return false;
    }
    if (this->y != other.y) {
      return false;
    }
    if (this->theta != other.theta) {
      return false;
    }
    if (this->covariance != other.covariance) {
      return false;
    }
    return true;
  }
  bool operator!=(const PoseNode_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PoseNode_

// alias to use template instance with default allocator
using PoseNode =
  messages::msg::PoseNode_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace messages

#endif  // MESSAGES__MSG__DETAIL__POSE_NODE__STRUCT_HPP_
