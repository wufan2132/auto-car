## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)
find_package(catkin REQUIRED COMPONENTS
  car_msgs
)


include_directories(
    include
    ${CMAKE_SOURCE_DIR}/common
)

add_library(control_gflags 
control_gflags.cc)

add_library(trajectory_analyzer trajectory_analyzer.cc)


