
find_package(catkin REQUIRED COMPONENTS
  roscpp
  car_msgs
)
# 生成链接库
add_library(tool 
    Interpolating.cpp 
    Fitting.cpp
    )
add_dependencies(tool
    car_msgs_gencpp
)   