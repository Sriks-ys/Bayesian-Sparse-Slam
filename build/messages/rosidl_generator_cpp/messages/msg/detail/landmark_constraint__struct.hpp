// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from messages:msg/LandmarkConstraint.idl
// generated code does not contain a copyright notice

#ifndef MESSAGES__MSG__DETAIL__LANDMARK_CONSTRAINT__STRUCT_HPP_
#define MESSAGES__MSG__DETAIL__LANDMARK_CONSTRAINT__STRUCT_HPP_

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

#ifndef _WIN32
# define DEPRECATED__messages__msg__LandmarkConstraint __attribute__((deprecated))
#else
# define DEPRECATED__messages__msg__LandmarkConstraint __declspec(deprecated)
#endif

namespace messages
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LandmarkConstraint_
{
  using Type = LandmarkConstraint_<ContainerAllocator>;

  explicit LandmarkConstraint_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->pose_id = 0l;
      this->landmark_id = 0l;
      this->rho = 0.0f;
      this->alpha = 0.0f;
      std::fill<typename std::array<float, 4>::iterator, float>(this->covariance.begin(), this->covariance.end(), 0.0f);
    }
  }

  explicit LandmarkConstraint_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    covariance(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->pose_id = 0l;
      this->landmark_id = 0l;
      this->rho = 0.0f;
      this->alpha = 0.0f;
      std::fill<typename std::array<float, 4>::iterator, float>(this->covariance.begin(), this->covariance.end(), 0.0f);
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _pose_id_type =
    int32_t;
  _pose_id_type pose_id;
  using _landmark_id_type =
    int32_t;
  _landmark_id_type landmark_id;
  using _rho_type =
    float;
  _rho_type rho;
  using _alpha_type =
    float;
  _alpha_type alpha;
  using _covariance_type =
    std::array<float, 4>;
  _covariance_type covariance;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__pose_id(
    const int32_t & _arg)
  {
    this->pose_id = _arg;
    return *this;
  }
  Type & set__landmark_id(
    const int32_t & _arg)
  {
    this->landmark_id = _arg;
    return *this;
  }
  Type & set__rho(
    const float & _arg)
  {
    this->rho = _arg;
    return *this;
  }
  Type & set__alpha(
    const float & _arg)
  {
    this->alpha = _arg;
    return *this;
  }
  Type & set__covariance(
    const std::array<float, 4> & _arg)
  {
    this->covariance = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    messages::msg::LandmarkConstraint_<ContainerAllocator> *;
  using ConstRawPtr =
    const messages::msg::LandmarkConstraint_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<messages::msg::LandmarkConstraint_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<messages::msg::LandmarkConstraint_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      messages::msg::LandmarkConstraint_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<messages::msg::LandmarkConstraint_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      messages::msg::LandmarkConstraint_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<messages::msg::LandmarkConstraint_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<messages::msg::LandmarkConstraint_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<messages::msg::LandmarkConstraint_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__messages__msg__LandmarkConstraint
    std::shared_ptr<messages::msg::LandmarkConstraint_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__messages__msg__LandmarkConstraint
    std::shared_ptr<messages::msg::LandmarkConstraint_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LandmarkConstraint_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->pose_id != other.pose_id) {
      return false;
    }
    if (this->landmark_id != other.landmark_id) {
      return false;
    }
    if (this->rho != other.rho) {
      return false;
    }
    if (this->alpha != other.alpha) {
      return false;
    }
    if (this->covariance != other.covariance) {
      return false;
    }
    return true;
  }
  bool operator!=(const LandmarkConstraint_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LandmarkConstraint_

// alias to use template instance with default allocator
using LandmarkConstraint =
  messages::msg::LandmarkConstraint_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace messages

#endif  // MESSAGES__MSG__DETAIL__LANDMARK_CONSTRAINT__STRUCT_HPP_
