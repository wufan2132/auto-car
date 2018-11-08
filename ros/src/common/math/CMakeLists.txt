
## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

# 生成链接库
add_library(math
    linear_quadratic_regulator.cc 
    linear_interpolation.cc 
    search.cc
    math_utils.cc)
