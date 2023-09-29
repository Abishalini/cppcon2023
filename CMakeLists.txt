cmake_minimum_required(VERSION 3.16)
project(plugin_cpp)

set(CMAKE_CXX_STANDARD 17)

set(LIBRARY_BUILD_PATH ${CMAKE_CURRENT_BINARY_DIR}/libraries)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/core/include/motion_plan_config.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/core/include/motion_plan_config.h)

add_subdirectory(API)
add_subdirectory(libraries/simple_motion_planner)

add_executable(plugin_cpp 
	core/motion_plan.cpp
)

# link DL libraries
target_link_libraries(plugin_cpp 
  ${CMAKE_DL_LIBS}
  plugin_api
  simple_motion_planner
)

target_include_directories(
  plugin_cpp PUBLIC 
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/core/plugin_manager/>
  $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/core/include/>
  $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/libraries/>
  $<INSTALL_INTERFACE:include>)

install(
  TARGETS plugin_cpp
  EXPORT plugin_cppTargets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include)

install(
  EXPORT plugin_cppTargets
  FILE plugin_cppTargets.cmake
  NAMESPACE plugin_cpp::
  DESTINATION lib/cmake/plugin_cpp)

# Install
include(CMakePackageConfigHelpers)
