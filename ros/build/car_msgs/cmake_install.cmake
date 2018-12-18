# Install script for directory: /home/wf/my-code/auto-car/ros/src/car_msgs

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/car_msgs/msg" TYPE FILE FILES
    "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/chassis.msg"
    "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/localization.msg"
    "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/trajectory_point.msg"
    "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/trajectory.msg"
    "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/control_cmd.msg"
    "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/vehicle_state.msg"
    "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/lon_debug.msg"
    "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/lat_debug.msg"
    "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/mpc_debug.msg"
    "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/debug.msg"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/car_msgs/cmake" TYPE FILE FILES "/home/wf/my-code/auto-car/ros/build/car_msgs/catkin_generated/installspace/car_msgs-msg-paths.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/wf/my-code/auto-car/ros/devel/include/car_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/wf/my-code/auto-car/ros/devel/share/roseus/ros/car_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/wf/my-code/auto-car/ros/devel/share/common-lisp/ros/car_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gennodejs/ros" TYPE DIRECTORY FILES "/home/wf/my-code/auto-car/ros/devel/share/gennodejs/ros/car_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  execute_process(COMMAND "/usr/bin/python" -m compileall "/home/wf/my-code/auto-car/ros/devel/lib/python2.7/dist-packages/car_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/wf/my-code/auto-car/ros/devel/lib/python2.7/dist-packages/car_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/wf/my-code/auto-car/ros/build/car_msgs/catkin_generated/installspace/car_msgs.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/car_msgs/cmake" TYPE FILE FILES "/home/wf/my-code/auto-car/ros/build/car_msgs/catkin_generated/installspace/car_msgs-msg-extras.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/car_msgs/cmake" TYPE FILE FILES
    "/home/wf/my-code/auto-car/ros/build/car_msgs/catkin_generated/installspace/car_msgsConfig.cmake"
    "/home/wf/my-code/auto-car/ros/build/car_msgs/catkin_generated/installspace/car_msgsConfig-version.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/car_msgs" TYPE FILE FILES "/home/wf/my-code/auto-car/ros/src/car_msgs/package.xml")
endif()

