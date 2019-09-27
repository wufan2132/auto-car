
## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

# 生成链接库
add_library(qp_solver
    active_set_qp_solver.cc
    qp_solver.cc
    qp_solver_gflags.cc)
    
target_link_libraries(qp_solver gflags)
target_link_libraries(qp_solver qpOASES)