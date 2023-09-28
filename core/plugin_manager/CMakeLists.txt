cmake_minimum_required(VERSION 3.22)
project(plugin_manager VERSION 0.1.0 LANGUAGES CXX)

if(CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)")
  add_compile_options(
    -Werror
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wconversion
    -Wsign-conversion)
endif()

set(PROJECT_INCLUDE_DIR include/plugin_manager)

add_library(plugin_manager 
  ${PROJECT_INCLUDE_DIR}/class_loader.hpp
  ${PROJECT_INCLUDE_DIR}/meta_object.hpp
  ${PROJECT_INCLUDE_DIR}/shared_library_loader.hpp)
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

install(FILES cmake/plugin_managerConfig.cmake DESTINATION lib/cmake/plugin_manager)
