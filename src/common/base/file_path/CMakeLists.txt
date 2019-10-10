
## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

include_directories(
  ${CMAKE_SOURCE_DIR}
)

# 生成链接库
add_library(file_path
    file_path.cc)
target_link_libraries(file_path
     global_gflags)


