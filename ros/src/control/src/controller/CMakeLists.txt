
## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

FIND_LIBRARY(YAML_CPP_LIBRARIES yaml-cpp)
include_directories(
  ../../../common
)
add_subdirectory(../../../common/math math.out)
# 生成链接库
if(ENABLE_MPC)
  add_library(control 
              control.cc 
              mpc_controller.cc
              )
  target_link_libraries(control mpc_math)
  message(STATUS "Use mpc_math")
else()
  add_library(control 
              control.cc 
              lon_controller.cc 
              lat_controller.cc 
              )    
  target_link_libraries(control math)
  message(STATUS "Use math")
endif()

target_link_libraries(control common_lib)
target_link_libraries(control ${YAML_CPP_LIBRARIES})