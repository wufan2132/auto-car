
## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++14)

# 生成链接库
add_library(qp_solver
    active_set_qp_solver.cc
    qp_solver.cc
    qp_solver_gflags.cc)

target_link_libraries(qp_solver qpOASES)

enable_testing()
find_package(GTest REQUIRED)

add_executable(active_set_qp_solver_test 
active_set_qp_solver_test.cc
)

target_link_libraries(active_set_qp_solver_test
  PUBLIC 
  glog
  gflags
  yaml-cpp
)
target_link_libraries(active_set_qp_solver_test 
   GTest::GTest 
   GTest::Main
   qp_solver
)
add_test(autocar_test active_set_qp_solver_test)