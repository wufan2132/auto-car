## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)
find_package(catkin REQUIRED COMPONENTS
  car_msgs
)


include_directories(
    include
  ../../../common
)

# 生成链接库
add_library(common_lib pid_controller.cc trajectory_analyzer.cc)

add_dependencies(common_lib car_msgs_gencpp)
