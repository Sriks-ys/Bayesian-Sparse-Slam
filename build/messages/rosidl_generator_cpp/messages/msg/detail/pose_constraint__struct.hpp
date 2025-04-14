// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from messages:msg/PoseConstraint.idl
// generated code does not contain a copyright notice

#ifndef MESSAGES__MSG__DETAIL__POSE_CONSTRAINT__STRUCT_HPP_
#define MESSAGES__MSG__DETAIL__POSE_CONSTRAINT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__messages__msg__PoseConstraint __attribute__((deprecated))
#else
# define DEPRECATED__messages__msg__PoseConstraint __declspec(deprecated)
#endif

namespace messages
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct PoseConstraint_
{
  using Type = PoseConstraint_<ContainerAllocator>;

  explicit PoseConstraint_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->pose1_id = 0l;
      this->pose2_id = 0l;
      this->dx = 0.0f;
      this->dy = 0.0f;
      this->dtheta = 0.0f;
      std::fill<typename std::array<float, 9>::iterator, float>(this->covariance.begin(), this->covariance.end(), 0.0f);
    }
  }

  explicit PoseConstraint_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : covariance(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->pose1_id = 0l;
      this->pose2_id = 0l;
      this->dx = 0.0f;
      this->dy = 0.0f;
      this->dtheta = 0.0f;
      std::fill<typename std::array<float, 9>::iterator, float>(this->covariance.begin(), this->covariance.end(), 0.0f);
    }
  }

  // field types and members
  using _pose1_id_type =
    int32_t;
  _pose1_id_type pose1_id;
  using _pose2_id_type =
    int32_t;
  _pose2_id_type pose2_id;
  using _dx_type =
    float;
  _dx_type dx;
  using _dy_type =
    float;
  _dy_type dy;
  using _dtheta_type =
    float;
  _dtheta_type dtheta;
  using _covariance_type =
    std::array<float, 9>;
  _covariance_type covariance;

  // setters for named parameter idiom
  Type & set__pose1_id(
    const int32_t & _arg)
  {
    this->pose1_id = _arg;
    return *this;
  }
  Type & set__pose2_id(
    const int32_t & _arg)
  {
    this->pose2_id = _arg;
    return *this;
  }
  Type & set__dx(
    const float & _arg)
  {
    this->dx = _arg;
    return *this;
  }
  Type & set__dy(
    const float & _arg)
  {
    this->dy = _arg;
    return *this;
  }
  Type & set__dtheta(
    const float & _arg)
  {
    this->dtheta = _arg;
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
    messages::msg::PoseConstraint_<ContainerAllocator> *;
  using ConstRawPtr =
    const messages::msg::PoseConstraint_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<messages::msg::PoseConstraint_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<messages::msg::PoseConstraint_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      messages::msg::PoseConstraint_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<messages::msg::PoseConstraint_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      messages::msg::PoseConstraint_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<messages::msg::PoseConstraint_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<messages::msg::PoseConstraint_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<messages::msg::PoseConstraint_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__messages__msg__PoseConstraint
    std::shared_ptr<messages::msg::PoseConstraint_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__messages__msg__PoseConstraint
    std::shared_ptr<messages::msg::PoseConstraint_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PoseConstraint_ & other) const
  {
    if (this->pose1_id != other.pose1_id) {
      return false;
    }
    if (this->pose2_id != other.pose2_id) {
      return false;
    }
    if (this->dx != other.dx) {
      return false;
    }
    if (this->dy != other.dy) {
      return false;
    }
    if (this->dtheta != other.dtheta) {
      return false;
    }
    if (this->covariance != other.covariance) {
      return false;
    }
    return true;
  }
  bool operator!=(const PoseConstraint_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PoseConstraint_

// alias to use template instance with default allocator
using PoseConstraint =
  messages::msg::PoseConstraint_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace messages

#endif  // MESSAGES__MSG__DETAIL__POSE_CONSTRAINT__STRUCT_HPP_
