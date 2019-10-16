
## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++14)

# 生成链接库
add_library(global_gflags
    global_gflags.cc)
# target_link_libraries(global_gflags
#      gflags)


