cmake_minimum_required(VERSION 3.22)
project(SimpleMotionPlanner VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

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

include_directories(
	../../API/MotionPlanner
)

add_library(simple_motion_planner SHARED
	../../API/MotionPlanner/motion_planner_interface
	simple_motion_planner.hpp
)
