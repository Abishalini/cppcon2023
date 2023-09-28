cmake_minimum_required(VERSION 3.22)
project(MyPluginManager VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

### Output directory ###
set(CMAKE_OUTPUT_DIR ${CMAKE_SOURCE_DIR}/Core/build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIR})

include_directories(
	core/plugin_manager
	API/
)

add_executable(MyPluginManager
	${DLLOADER_SRC}
	Core/
)

target_link_libraries( ${CMAKE_DL_LIBS})

# set_property( DIRECTORY PROPERTY VS_STARTUP_PROJECT Greet-Core)

add_subdirectory(libraries/simple_motion_planner)
