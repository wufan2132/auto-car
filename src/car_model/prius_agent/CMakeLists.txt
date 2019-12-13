cmake_minimum_required(VERSION 2.8.12)

find_package(catkin REQUIRED)

install(DIRECTORY meshes DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
