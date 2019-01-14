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
if(ENABLE_MPC)
  add_library(common_lib trajectory_analyzer.cc)
else()
  add_library(common_lib pid_controller.cc trajectory_analyzer.cc)
endif()

