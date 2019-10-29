
find_package(catkin REQUIRED COMPONENTS
  roscpp
  car_msgs
)
# 生成链接库
add_library(tool 
    interpolating.cc 
    Fitting.cpp
    )
add_dependencies(tool
    car_msgs_gencpp
)   


add_library(interpolating_refrenceline
  interpolating_refrenceline.cc
)
target_link_libraries(interpolating_refrenceline
    tool
)  