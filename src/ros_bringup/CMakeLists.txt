cmake_minimum_required(VERSION 3.8)
project(ros_bringup)


# find dependencies
find_package(ament_cmake REQUIRED)
find_package(robot_description REQUIRED)
find_package(ros_gazebo REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
install(
  DIRECTORY
    launch/
  DESTINATION share/${PROJECT_NAME}/launch
)
install(
  DIRECTORY
    config/
  DESTINATION share/${PROJECT_NAME}/config
)
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
