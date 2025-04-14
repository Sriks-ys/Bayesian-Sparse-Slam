// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from messages:msg/PoseGraph.idl
// generated code does not contain a copyright notice

#ifndef MESSAGES__MSG__DETAIL__POSE_GRAPH__STRUCT_HPP_
#define MESSAGES__MSG__DETAIL__POSE_GRAPH__STRUCT_HPP_

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
// Member 'nodes'
#include "messages/msg/detail/pose_node__struct.hpp"
// Member 'pose_constraints'
#include "messages/msg/detail/pose_constraint__struct.hpp"
// Member 'landmark_constraints'
#include "messages/msg/detail/landmark_constraint__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__messages__msg__PoseGraph __attribute__((deprecated))
#else
# define DEPRECATED__messages__msg__PoseGraph __declspec(deprecated)
#endif

namespace messages
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct PoseGraph_
{
  using Type = PoseGraph_<ContainerAllocator>;

  explicit PoseGraph_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    (void)_init;
  }

  explicit PoseGraph_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _nodes_type =
    std::vector<messages::msg::PoseNode_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<messages::msg::PoseNode_<ContainerAllocator>>>;
  _nodes_type nodes;
  using _pose_constraints_type =
    std::vector<messages::msg::PoseConstraint_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<messages::msg::PoseConstraint_<ContainerAllocator>>>;
  _pose_constraints_type pose_constraints;
  using _landmark_constraints_type =
    std::vector<messages::msg::LandmarkConstraint_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<messages::msg::LandmarkConstraint_<ContainerAllocator>>>;
  _landmark_constraints_type landmark_constraints;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__nodes(
    const std::vector<messages::msg::PoseNode_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<messages::msg::PoseNode_<ContainerAllocator>>> & _arg)
  {
    this->nodes = _arg;
    return *this;
  }
  Type & set__pose_constraints(
    const std::vector<messages::msg::PoseConstraint_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<messages::msg::PoseConstraint_<ContainerAllocator>>> & _arg)
  {
    this->pose_constraints = _arg;
    return *this;
  }
  Type & set__landmark_constraints(
    const std::vector<messages::msg::LandmarkConstraint_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<messages::msg::LandmarkConstraint_<ContainerAllocator>>> & _arg)
  {
    this->landmark_constraints = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    messages::msg::PoseGraph_<ContainerAllocator> *;
  using ConstRawPtr =
    const messages::msg::PoseGraph_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<messages::msg::PoseGraph_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<messages::msg::PoseGraph_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      messages::msg::PoseGraph_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<messages::msg::PoseGraph_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      messages::msg::PoseGraph_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<messages::msg::PoseGraph_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<messages::msg::PoseGraph_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<messages::msg::PoseGraph_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__messages__msg__PoseGraph
    std::shared_ptr<messages::msg::PoseGraph_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__messages__msg__PoseGraph
    std::shared_ptr<messages::msg::PoseGraph_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PoseGraph_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->nodes != other.nodes) {
      return false;
    }
    if (this->pose_constraints != other.pose_constraints) {
      return false;
    }
    if (this->landmark_constraints != other.landmark_constraints) {
      return false;
    }
    return true;
  }
  bool operator!=(const PoseGraph_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PoseGraph_

// alias to use template instance with default allocator
using PoseGraph =
  messages::msg::PoseGraph_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace messages

#endif  // MESSAGES__MSG__DETAIL__POSE_GRAPH__STRUCT_HPP_
