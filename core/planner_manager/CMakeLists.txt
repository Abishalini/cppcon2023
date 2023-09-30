cmake_minimum_required(VERSION 3.16)
project(planner_manager VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

add_library(planner_manager
	planner_manager.h
  planner_manager.cpp
)

target_link_libraries(planner_manager PUBLIC
  plugin_api
)

target_include_directories(
  planner_manager PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

install(
  TARGETS planner_manager
  EXPORT planner_managerTargets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include)
