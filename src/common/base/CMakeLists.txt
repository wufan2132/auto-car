
## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

# 添加下一级目录
add_subdirectory(app)
add_subdirectory(global_gflags)
add_subdirectory(file_tool)

