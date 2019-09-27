
## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)
include_directories(
  ./qp_solver
)
add_subdirectory(./qp_solver)
# 生成链接库
# if(ENABLE_MPC)
    add_library(mpc_math
        mpc_solver.cc
        linear_interpolation.cc 
        search.cc
        math_utils.cc)

    target_link_libraries(mpc_math qp_solver)
# else()
    add_library(math
        linear_quadratic_regulator.cc 
        linear_interpolation.cc 
        search.cc
        math_utils.cc)
# endif()