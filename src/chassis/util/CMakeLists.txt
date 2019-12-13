## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++14)

include_directories(
    ${CMAKE_SOURCE_DIR}
)

add_library(usart 
usart.cc)
target_link_libraries(usart
  boost_system
)
# 生成单元测试
enable_testing()
find_package(GTest REQUIRED)

add_executable(usart_test 
usart_test.cc
)

target_link_libraries(usart_test
  PUBLIC 
  glog
  gflags
  yaml-cpp
)
target_link_libraries(usart_test 
   GTest::GTest 
   GTest::Main
   usart
)
add_test(autocar_test usart_test)