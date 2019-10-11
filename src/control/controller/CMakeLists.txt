
## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

FIND_LIBRARY(YAML_CPP_LIBRARIES yaml-cpp)
include_directories(
  ${CMAKE_SOURCE_DIR}
)

# 生成链接库
if(ENABLE_MPC)
  add_library(mpc_controller 
              mpc_controller.cc
              )
  target_link_libraries(mpc_controller mpc_math)
  message(STATUS "Use mpc_math")
else()
  add_library(pid_controller 
              lon_controller.cc 
              lat_controller.cc 
              pid_controller.cc
              )    
  target_link_libraries(pid_controller 
  math
  trajectory_analyzer
  )
  message(STATUS "Use math")
endif()