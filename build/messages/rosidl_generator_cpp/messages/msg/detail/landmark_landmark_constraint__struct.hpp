// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from messages:msg/LandmarkLandmarkConstraint.idl
// generated code does not contain a copyright notice

#ifndef MESSAGES__MSG__DETAIL__LANDMARK_LANDMARK_CONSTRAINT__STRUCT_HPP_
#define MESSAGES__MSG__DETAIL__LANDMARK_LANDMARK_CONSTRAINT__STRUCT_HPP_

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
# define DEPRECATED__messages__msg__LandmarkLandmarkConstraint __attribute__((deprecated))
#else
# define DEPRECATED__messages__msg__LandmarkLandmarkConstraint __declspec(deprecated)
#endif

namespace messages
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LandmarkLandmarkConstraint_
{
  using Type = LandmarkLandmarkConstraint_<ContainerAllocator>;

  explicit LandmarkLandmarkConstraint_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->landmark1_id = 0l;
      this->landmark2_id = 0l;
      this->dx = 0.0f;
      this->dy = 0.0f;
      std::fill<typename std::array<float, 4>::iterator, float>(this->covariance.begin(), this->covariance.end(), 0.0f);
    }
  }

  explicit LandmarkLandmarkConstraint_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    covariance(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->landmark1_id = 0l;
      this->landmark2_id = 0l;
      this->dx = 0.0f;
      this->dy = 0.0f;
      std::fill<typename std::array<float, 4>::iterator, float>(this->covariance.begin(), this->covariance.end(), 0.0f);
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _landmark1_id_type =
    int32_t;
  _landmark1_id_type landmark1_id;
  using _landmark2_id_type =
    int32_t;
  _landmark2_id_type landmark2_id;
  using _dx_type =
    float;
  _dx_type dx;
  using _dy_type =
    float;
  _dy_type dy;
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
  Type & set__landmark1_id(
    const int32_t & _arg)
  {
    this->landmark1_id = _arg;
    return *this;
  }
  Type & set__landmark2_id(
    const int32_t & _arg)
  {
    this->landmark2_id = _arg;
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
  Type & set__covariance(
    const std::array<float, 4> & _arg)
  {
    this->covariance = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    messages::msg::LandmarkLandmarkConstraint_<ContainerAllocator> *;
  using ConstRawPtr =
    const messages::msg::LandmarkLandmarkConstraint_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<messages::msg::LandmarkLandmarkConstraint_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<messages::msg::LandmarkLandmarkConstraint_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      messages::msg::LandmarkLandmarkConstraint_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<messages::msg::LandmarkLandmarkConstraint_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      messages::msg::LandmarkLandmarkConstraint_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<messages::msg::LandmarkLandmarkConstraint_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<messages::msg::LandmarkLandmarkConstraint_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<messages::msg::LandmarkLandmarkConstraint_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__messages__msg__LandmarkLandmarkConstraint
    std::shared_ptr<messages::msg::LandmarkLandmarkConstraint_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__messages__msg__LandmarkLandmarkConstraint
    std::shared_ptr<messages::msg::LandmarkLandmarkConstraint_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LandmarkLandmarkConstraint_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->landmark1_id != other.landmark1_id) {
      return false;
    }
    if (this->landmark2_id != other.landmark2_id) {
      return false;
    }
    if (this->dx != other.dx) {
      return false;
    }
    if (this->dy != other.dy) {
      return false;
    }
    if (this->covariance != other.covariance) {
      return false;
    }
    return true;
  }
  bool operator!=(const LandmarkLandmarkConstraint_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LandmarkLandmarkConstraint_

// alias to use template instance with default allocator
using LandmarkLandmarkConstraint =
  messages::msg::LandmarkLandmarkConstraint_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace messages

#endif  // MESSAGES__MSG__DETAIL__LANDMARK_LANDMARK_CONSTRAINT__STRUCT_HPP_
