cmake_minimum_required(VERSION 3.16)
project(plugin_api)

set(HEADERS include/plugin_api/motion_planner_interface.h)

add_library(plugin_api INTERFACE include/plugin_api/motion_planner_interface.h)

target_compile_features(plugin_api INTERFACE cxx_std_17)
target_include_directories(
  plugin_api INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

install(
  TARGETS plugin_api
  EXPORT plugin_apiTargets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include)
install(DIRECTORY include/ DESTINATION include)

install(
  EXPORT plugin_apiTargets
  FILE plugin_apiTargets.cmake
  NAMESPACE plugin_api::
  DESTINATION lib/cmake/plugin_api)
