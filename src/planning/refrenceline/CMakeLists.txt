
# 生成链接库
add_library(refrenceline_provider refrenceline_provider.cc)
target_link_libraries(refrenceline_provider
   file_tool
   frame
   map
   replay
)

enable_testing()
find_package(GTest REQUIRED)
   add_executable(refrenceline_provider_test 
   refrenceline_provider_test.cc
)
target_link_libraries(refrenceline_provider_test
  PUBLIC 
  glog
  gflags
  yaml-cpp
)
target_link_libraries(refrenceline_provider_test 
   GTest::GTest 
   GTest::Main
   refrenceline_provider
)
add_test(autocar_test refrenceline_provider_test)
