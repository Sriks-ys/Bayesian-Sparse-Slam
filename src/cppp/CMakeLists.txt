cmake_minimum_required(VERSION 3.8)
project(cppp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()
if(POLICY CMP0074)
  cmake_policy(SET CMP0074 NEW)
endif()

set(GTSAM_DIR "$ENV{HOME}/externals/gtsam/install")
set(GTSAM_INCLUDE_DIR "$ENV{HOME}/externals/gtsam/install/include")
set(GTSAM_LIBRARY_DIR "$ENV{HOME}/externals/gtsam/install/lib")

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(visualization_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(messages REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)


find_package(pcl_conversions REQUIRED)
find_package(PCL REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(tf2_sensor_msgs REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)
find_package(TBB REQUIRED)


add_executable(PreprocessNode src/PreprocessNode.cpp)
add_executable(IncrementalLineFittingNode src/IncrementalLineFittingNode.cpp)
add_executable(HoughLineFittingNode src/HoughLineFittingNode.cpp)
add_executable(RansacLineExtractionNode src/RansacLineExtractionNode.cpp)
add_executable(ScanAccumulator src/ScanAccumulator.cpp)
add_executable(LandmarkTransformermapNode src/LandmarkTransformermapNode.cpp)
add_executable(LandmarkGraphNode src/LandmarkGraphNode.cpp)
add_executable(LandmarkTransformerNode src/LandmarkTransformerNode.cpp)
add_executable(ScanTransformer src/ScanTransformer.cpp)
add_executable(PoseGraphOptimizer src/PoseGraphOptimizer.cpp)

set(GTSAM_LIBRARIES "${GTSAM_LIBRARY_DIR}/libgtsam.so")
find_library(GTSAM_LIBRARIES NAMES gtsam PATHS ${GTSAM_LIBRARY_DIR})


# Include directories
include_directories(${PCL_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${GTSAM_INCLUDE_DIR})

link_directories(${GTSAM_LIBRARY_DIR})


target_link_libraries(RansacLineExtractionNode ${PCL_LIBRARIES})
target_link_libraries(IncrementalLineFittingNode ${PCL_LIBRARIES})
target_link_libraries(HoughLineFittingNode ${PCL_LIBRARIES})
target_link_libraries(ScanAccumulator ${PCL_LIBRARIES})
target_link_libraries(PoseGraphOptimizer 
              ${GTSAM_LIBRARIES}
              TBB::tbb)



ament_target_dependencies(LandmarkGraphNode
  rclcpp
  messages
  Eigen3
)

ament_target_dependencies(PreprocessNode
  rclcpp
  sensor_msgs
)

ament_target_dependencies(ScanAccumulator
  rclcpp 
  sensor_msgs 
  nav_msgs
  pcl_conversions
  visualization_msgs
  PCL 
  tf2
  tf2_ros
  tf2_geometry_msgs
  Eigen3
)

ament_target_dependencies(RansacLineExtractionNode
  rclcpp
  sensor_msgs
  geometry_msgs
  nav_msgs
  pcl_conversions
  PCL 
  messages
  Eigen3
)

ament_target_dependencies(LandmarkTransformerNode
  rclcpp
  geometry_msgs
  nav_msgs
  tf2_ros
  tf2
  Eigen3
  messages
  tf2_geometry_msgs
)


ament_target_dependencies(IncrementalLineFittingNode
  rclcpp
  sensor_msgs
  geometry_msgs
  nav_msgs
  pcl_conversions
  PCL 
  messages
  Eigen3
)

ament_target_dependencies(HoughLineFittingNode
  rclcpp
  sensor_msgs
  geometry_msgs
  nav_msgs
  pcl_conversions
  PCL 
  messages
  OpenCV
)

ament_target_dependencies(LandmarkTransformermapNode
  rclcpp
  geometry_msgs
  nav_msgs
  tf2_ros
  tf2
  Eigen3
  messages
  tf2_geometry_msgs
)

ament_target_dependencies(ScanTransformer
  rclcpp
  sensor_msgs
  tf2_ros
  tf2_sensor_msgs
)

ament_target_dependencies(PoseGraphOptimizer
  rclcpp
  geometry_msgs
  messages
  Eigen3
)

install(TARGETS 
  LandmarkTransformerNode
  DESTINATION lib/${PROJECT_NAME}
)

install(TARGETS 
  ScanAccumulator 
  DESTINATION lib/${PROJECT_NAME}
)

install(TARGETS
  PreprocessNode 
  DESTINATION lib/${PROJECT_NAME}  
)

install(TARGETS 
  LandmarkGraphNode
  DESTINATION lib/${PROJECT_NAME}
)

install(TARGETS 
  IncrementalLineFittingNode
  DESTINATION lib/${PROJECT_NAME}
)

install(TARGETS 
  LandmarkTransformermapNode
  DESTINATION lib/${PROJECT_NAME}
)

install(TARGETS 
  HoughLineFittingNode
  DESTINATION lib/${PROJECT_NAME}
)

install(TARGETS
  RansacLineExtractionNode
  DESTINATION lib/${PROJECT_NAME}
)

install(TARGETS
  ScanTransformer
  DESTINATION lib/${PROJECT_NAME}
)

install(TARGETS 
  PoseGraphOptimizer
  DESTINATION lib/${PROJECT_NAME}
)
ament_package()
