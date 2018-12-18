# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "car_msgs: 10 messages, 0 services")

set(MSG_I_FLAGS "-Icar_msgs:/home/wf/my-code/auto-car/ros/src/car_msgs/msg;-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/kinetic/share/geometry_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(car_msgs_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/vehicle_state.msg" NAME_WE)
add_custom_target(_car_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "car_msgs" "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/vehicle_state.msg" "std_msgs/Header"
)

get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/debug.msg" NAME_WE)
add_custom_target(_car_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "car_msgs" "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/debug.msg" "car_msgs/mpc_debug:car_msgs/lon_debug:std_msgs/Header:car_msgs/lat_debug"
)

get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/chassis.msg" NAME_WE)
add_custom_target(_car_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "car_msgs" "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/chassis.msg" "std_msgs/Header:geometry_msgs/Vector3"
)

get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/localization.msg" NAME_WE)
add_custom_target(_car_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "car_msgs" "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/localization.msg" "geometry_msgs/Vector3:std_msgs/Header:geometry_msgs/Point"
)

get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/lon_debug.msg" NAME_WE)
add_custom_target(_car_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "car_msgs" "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/lon_debug.msg" "std_msgs/Header"
)

get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/trajectory.msg" NAME_WE)
add_custom_target(_car_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "car_msgs" "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/trajectory.msg" "car_msgs/trajectory_point:std_msgs/Header"
)

get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/trajectory_point.msg" NAME_WE)
add_custom_target(_car_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "car_msgs" "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/trajectory_point.msg" "std_msgs/Header"
)

get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/mpc_debug.msg" NAME_WE)
add_custom_target(_car_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "car_msgs" "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/mpc_debug.msg" "std_msgs/Header"
)

get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/lat_debug.msg" NAME_WE)
add_custom_target(_car_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "car_msgs" "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/lat_debug.msg" "std_msgs/Header"
)

get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/control_cmd.msg" NAME_WE)
add_custom_target(_car_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "car_msgs" "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/control_cmd.msg" "std_msgs/Header"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/vehicle_state.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/car_msgs
)
_generate_msg_cpp(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/debug.msg"
  "${MSG_I_FLAGS}"
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/mpc_debug.msg;/home/wf/my-code/auto-car/ros/src/car_msgs/msg/lon_debug.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/home/wf/my-code/auto-car/ros/src/car_msgs/msg/lat_debug.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/car_msgs
)
_generate_msg_cpp(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/chassis.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/car_msgs
)
_generate_msg_cpp(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/mpc_debug.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/car_msgs
)
_generate_msg_cpp(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/lon_debug.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/car_msgs
)
_generate_msg_cpp(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/trajectory.msg"
  "${MSG_I_FLAGS}"
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/trajectory_point.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/car_msgs
)
_generate_msg_cpp(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/trajectory_point.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/car_msgs
)
_generate_msg_cpp(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/localization.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/car_msgs
)
_generate_msg_cpp(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/lat_debug.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/car_msgs
)
_generate_msg_cpp(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/control_cmd.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/car_msgs
)

### Generating Services

### Generating Module File
_generate_module_cpp(car_msgs
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/car_msgs
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(car_msgs_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(car_msgs_generate_messages car_msgs_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/vehicle_state.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_cpp _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/debug.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_cpp _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/chassis.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_cpp _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/localization.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_cpp _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/lon_debug.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_cpp _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/trajectory.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_cpp _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/trajectory_point.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_cpp _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/mpc_debug.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_cpp _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/lat_debug.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_cpp _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/control_cmd.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_cpp _car_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(car_msgs_gencpp)
add_dependencies(car_msgs_gencpp car_msgs_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS car_msgs_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/vehicle_state.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/car_msgs
)
_generate_msg_eus(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/debug.msg"
  "${MSG_I_FLAGS}"
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/mpc_debug.msg;/home/wf/my-code/auto-car/ros/src/car_msgs/msg/lon_debug.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/home/wf/my-code/auto-car/ros/src/car_msgs/msg/lat_debug.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/car_msgs
)
_generate_msg_eus(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/chassis.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/car_msgs
)
_generate_msg_eus(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/mpc_debug.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/car_msgs
)
_generate_msg_eus(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/lon_debug.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/car_msgs
)
_generate_msg_eus(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/trajectory.msg"
  "${MSG_I_FLAGS}"
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/trajectory_point.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/car_msgs
)
_generate_msg_eus(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/trajectory_point.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/car_msgs
)
_generate_msg_eus(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/localization.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/car_msgs
)
_generate_msg_eus(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/lat_debug.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/car_msgs
)
_generate_msg_eus(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/control_cmd.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/car_msgs
)

### Generating Services

### Generating Module File
_generate_module_eus(car_msgs
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/car_msgs
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(car_msgs_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(car_msgs_generate_messages car_msgs_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/vehicle_state.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_eus _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/debug.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_eus _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/chassis.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_eus _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/localization.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_eus _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/lon_debug.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_eus _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/trajectory.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_eus _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/trajectory_point.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_eus _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/mpc_debug.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_eus _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/lat_debug.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_eus _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/control_cmd.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_eus _car_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(car_msgs_geneus)
add_dependencies(car_msgs_geneus car_msgs_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS car_msgs_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/vehicle_state.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/car_msgs
)
_generate_msg_lisp(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/debug.msg"
  "${MSG_I_FLAGS}"
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/mpc_debug.msg;/home/wf/my-code/auto-car/ros/src/car_msgs/msg/lon_debug.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/home/wf/my-code/auto-car/ros/src/car_msgs/msg/lat_debug.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/car_msgs
)
_generate_msg_lisp(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/chassis.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/car_msgs
)
_generate_msg_lisp(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/mpc_debug.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/car_msgs
)
_generate_msg_lisp(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/lon_debug.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/car_msgs
)
_generate_msg_lisp(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/trajectory.msg"
  "${MSG_I_FLAGS}"
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/trajectory_point.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/car_msgs
)
_generate_msg_lisp(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/trajectory_point.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/car_msgs
)
_generate_msg_lisp(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/localization.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/car_msgs
)
_generate_msg_lisp(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/lat_debug.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/car_msgs
)
_generate_msg_lisp(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/control_cmd.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/car_msgs
)

### Generating Services

### Generating Module File
_generate_module_lisp(car_msgs
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/car_msgs
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(car_msgs_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(car_msgs_generate_messages car_msgs_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/vehicle_state.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_lisp _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/debug.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_lisp _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/chassis.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_lisp _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/localization.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_lisp _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/lon_debug.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_lisp _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/trajectory.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_lisp _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/trajectory_point.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_lisp _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/mpc_debug.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_lisp _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/lat_debug.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_lisp _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/control_cmd.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_lisp _car_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(car_msgs_genlisp)
add_dependencies(car_msgs_genlisp car_msgs_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS car_msgs_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/vehicle_state.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/car_msgs
)
_generate_msg_nodejs(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/debug.msg"
  "${MSG_I_FLAGS}"
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/mpc_debug.msg;/home/wf/my-code/auto-car/ros/src/car_msgs/msg/lon_debug.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/home/wf/my-code/auto-car/ros/src/car_msgs/msg/lat_debug.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/car_msgs
)
_generate_msg_nodejs(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/chassis.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/car_msgs
)
_generate_msg_nodejs(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/mpc_debug.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/car_msgs
)
_generate_msg_nodejs(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/lon_debug.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/car_msgs
)
_generate_msg_nodejs(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/trajectory.msg"
  "${MSG_I_FLAGS}"
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/trajectory_point.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/car_msgs
)
_generate_msg_nodejs(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/trajectory_point.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/car_msgs
)
_generate_msg_nodejs(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/localization.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/car_msgs
)
_generate_msg_nodejs(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/lat_debug.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/car_msgs
)
_generate_msg_nodejs(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/control_cmd.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/car_msgs
)

### Generating Services

### Generating Module File
_generate_module_nodejs(car_msgs
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/car_msgs
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(car_msgs_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(car_msgs_generate_messages car_msgs_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/vehicle_state.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_nodejs _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/debug.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_nodejs _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/chassis.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_nodejs _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/localization.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_nodejs _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/lon_debug.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_nodejs _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/trajectory.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_nodejs _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/trajectory_point.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_nodejs _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/mpc_debug.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_nodejs _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/lat_debug.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_nodejs _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/control_cmd.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_nodejs _car_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(car_msgs_gennodejs)
add_dependencies(car_msgs_gennodejs car_msgs_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS car_msgs_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/vehicle_state.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/car_msgs
)
_generate_msg_py(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/debug.msg"
  "${MSG_I_FLAGS}"
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/mpc_debug.msg;/home/wf/my-code/auto-car/ros/src/car_msgs/msg/lon_debug.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/home/wf/my-code/auto-car/ros/src/car_msgs/msg/lat_debug.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/car_msgs
)
_generate_msg_py(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/chassis.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/car_msgs
)
_generate_msg_py(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/mpc_debug.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/car_msgs
)
_generate_msg_py(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/lon_debug.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/car_msgs
)
_generate_msg_py(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/trajectory.msg"
  "${MSG_I_FLAGS}"
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/trajectory_point.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/car_msgs
)
_generate_msg_py(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/trajectory_point.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/car_msgs
)
_generate_msg_py(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/localization.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/car_msgs
)
_generate_msg_py(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/lat_debug.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/car_msgs
)
_generate_msg_py(car_msgs
  "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/control_cmd.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/car_msgs
)

### Generating Services

### Generating Module File
_generate_module_py(car_msgs
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/car_msgs
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(car_msgs_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(car_msgs_generate_messages car_msgs_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/vehicle_state.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_py _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/debug.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_py _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/chassis.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_py _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/localization.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_py _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/lon_debug.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_py _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/trajectory.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_py _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/trajectory_point.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_py _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/mpc_debug.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_py _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/lat_debug.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_py _car_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/wf/my-code/auto-car/ros/src/car_msgs/msg/control_cmd.msg" NAME_WE)
add_dependencies(car_msgs_generate_messages_py _car_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(car_msgs_genpy)
add_dependencies(car_msgs_genpy car_msgs_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS car_msgs_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/car_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/car_msgs
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(car_msgs_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(car_msgs_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/car_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/car_msgs
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(car_msgs_generate_messages_eus std_msgs_generate_messages_eus)
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(car_msgs_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/car_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/car_msgs
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(car_msgs_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(car_msgs_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/car_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/car_msgs
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(car_msgs_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(car_msgs_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/car_msgs)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/car_msgs\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/car_msgs
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(car_msgs_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(car_msgs_generate_messages_py geometry_msgs_generate_messages_py)
endif()
