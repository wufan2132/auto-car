## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++14)

include_directories(
    ${CMAKE_SOURCE_DIR}
)

add_library(gazebo_client 
gazebo_client.cc)

add_library(usart 
usart.cc)
