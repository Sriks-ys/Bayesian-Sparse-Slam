// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from messages:msg/LineSegment.idl
// generated code does not contain a copyright notice

#ifndef MESSAGES__MSG__DETAIL__LINE_SEGMENT__STRUCT_HPP_
#define MESSAGES__MSG__DETAIL__LINE_SEGMENT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'start'
// Member 'end'
#include "geometry_msgs/msg/detail/point__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__messages__msg__LineSegment __attribute__((deprecated))
#else
# define DEPRECATED__messages__msg__LineSegment __declspec(deprecated)
#endif

namespace messages
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LineSegment_
{
  using Type = LineSegment_<ContainerAllocator>;

  explicit LineSegment_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : start(_init),
    end(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->rho = 0.0f;
      this->alpha = 0.0f;
      std::fill<typename std::array<float, 4>::iterator, float>(this->covariance.begin(), this->covariance.end(), 0.0f);
    }
  }

  explicit LineSegment_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : covariance(_alloc),
    start(_alloc, _init),
    end(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->rho = 0.0f;
      this->alpha = 0.0f;
      std::fill<typename std::array<float, 4>::iterator, float>(this->covariance.begin(), this->covariance.end(), 0.0f);
    }
  }

  // field types and members
  using _rho_type =
    float;
  _rho_type rho;
  using _alpha_type =
    float;
  _alpha_type alpha;
  using _covariance_type =
    std::array<float, 4>;
  _covariance_type covariance;
  using _start_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _start_type start;
  using _end_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _end_type end;

  // setters for named parameter idiom
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
  Type & set__start(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->start = _arg;
    return *this;
  }
  Type & set__end(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->end = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    messages::msg::LineSegment_<ContainerAllocator> *;
  using ConstRawPtr =
    const messages::msg::LineSegment_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<messages::msg::LineSegment_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<messages::msg::LineSegment_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      messages::msg::LineSegment_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<messages::msg::LineSegment_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      messages::msg::LineSegment_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<messages::msg::LineSegment_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<messages::msg::LineSegment_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<messages::msg::LineSegment_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__messages__msg__LineSegment
    std::shared_ptr<messages::msg::LineSegment_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__messages__msg__LineSegment
    std::shared_ptr<messages::msg::LineSegment_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LineSegment_ & other) const
  {
    if (this->rho != other.rho) {
      return false;
    }
    if (this->alpha != other.alpha) {
      return false;
    }
    if (this->covariance != other.covariance) {
      return false;
    }
    if (this->start != other.start) {
      return false;
    }
    if (this->end != other.end) {
      return false;
    }
    return true;
  }
  bool operator!=(const LineSegment_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LineSegment_

// alias to use template instance with default allocator
using LineSegment =
  messages::msg::LineSegment_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace messages

#endif  // MESSAGES__MSG__DETAIL__LINE_SEGMENT__STRUCT_HPP_
