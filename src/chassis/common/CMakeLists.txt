## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++14)

include_directories(
    ${CMAKE_SOURCE_DIR}
)

add_library(chassis_gflags 
chassis_gflags.cc)


