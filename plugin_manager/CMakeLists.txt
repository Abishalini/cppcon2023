cmake_minimum_required(VERSION 3.22)
project(plugin_manager)

add_library(plugin_manager src/class_loader.cpp)

target_compile_features(plugin_manager PUBLIC cxx_std_17)
target_include_directories(
  plugin_manager PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

install(
  TARGETS plugin_manager
  EXPORT plugin_managerTargets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES
  DESTINATION include)
install(DIRECTORY include/ DESTINATION include)

install(
  EXPORT plugin_managerTargets
  FILE plugin_managerTargets.cmake
  NAMESPACE plugin_manager::
  DESTINATION lib/cmake/plugin_manager)

# Install
include(CMakePackageConfigHelpers)

# Guard for those whole include this package directly
if(NOT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  return()
endif()