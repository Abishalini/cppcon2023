cmake_minimum_required(VERSION 3.22)
project(CppConPluginExample)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(API)
add_subdirectory(plugin_manager)
add_subdirectory(libraries/simple_motion_planner)

add_executable(CppConPluginExample 
	core/motion_plan.cpp
)

# link DL libraries
target_link_libraries(CppConPluginExample 
  ${CMAKE_DL_LIBS}
  plugin_api
  plugin_manager
)
