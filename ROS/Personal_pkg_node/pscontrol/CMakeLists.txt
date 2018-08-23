cmake_minimum_required(VERSION 2.8.3)
project(pscontrol)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  joy
)

include_directories(
  include ${catkin_INCLUDE_DIRS}
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(pscontrol
  src/pscontrol.cpp
)
add_dependencies(pscontrol ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(pscontrol
  ${catkin_LIBRARIES}
)