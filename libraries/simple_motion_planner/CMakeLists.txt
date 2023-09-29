cmake_minimum_required(VERSION 3.16)
project(simple_motion_planner VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

add_library(simple_motion_planner SHARED
	simple_motion_planner.h
  simple_motion_planner.cpp
)

target_link_libraries(simple_motion_planner PUBLIC
  plugin_api
)

target_include_directories(
  simple_motion_planner PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

install(
  TARGETS simple_motion_planner
  EXPORT simple_motion_plannerTargets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include)

install(
  EXPORT simple_motion_plannerTargets
  FILE simple_motion_plannerTargets.cmake
  NAMESPACE simple_motion_planner
  DESTINATION lib/cmake/simple_motion_planner)

# Install
include(CMakePackageConfigHelpers)

install(FILES cmake/simple_motion_plannerConfig.cmake DESTINATION lib/cmake/simple_motion_planner)