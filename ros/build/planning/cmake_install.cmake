# Install script for directory: /home/wf/my-code/auto-car/ros/src/planning

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/wf/my-code/auto-car/ros/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/wf/my-code/auto-car/ros/build/planning/catkin_generated/installspace/planning.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/planning/cmake" TYPE FILE FILES
    "/home/wf/my-code/auto-car/ros/build/planning/catkin_generated/installspace/planningConfig.cmake"
    "/home/wf/my-code/auto-car/ros/build/planning/catkin_generated/installspace/planningConfig-version.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/planning" TYPE FILE FILES "/home/wf/my-code/auto-car/ros/src/planning/package.xml")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/wf/my-code/auto-car/ros/build/planning/src/planning/cmake_install.cmake")
  include("/home/wf/my-code/auto-car/ros/build/planning/src/optimizer/cmake_install.cmake")
  include("/home/wf/my-code/auto-car/ros/build/planning/src/replay/cmake_install.cmake")
  include("/home/wf/my-code/auto-car/ros/build/planning/src/tool/cmake_install.cmake")
  include("/home/wf/my-code/auto-car/ros/build/planning/src/model/cmake_install.cmake")
  include("/home/wf/my-code/auto-car/ros/build/planning/src/trajectory/cmake_install.cmake")
  include("/home/wf/my-code/auto-car/ros/build/planning/src/sampler/cmake_install.cmake")
  include("/home/wf/my-code/auto-car/ros/build/planning/src/apollo_tool/cmake_install.cmake")

endif()

