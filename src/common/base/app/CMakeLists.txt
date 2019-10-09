
# ## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

# ##
# find_package(catkin REQUIRED COMPONENTS
#   roscpp
#   rospy
# )

# include_directories(
#   ${PROJECT_SOURCE_DIR}
#    ${catkin_INCLUDE_DIRS}
# )

# add_subdirectory(qp_solver)


# # 生成链接库
# add_library(mpc_math
#     mpc_solver.cc
#     linear_interpolation.cc 
#     search.cc
#     math_utils.cc)
# target_link_libraries(mpc_math
#      qp_solver)


