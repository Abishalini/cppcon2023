#include <memory>
#include <filesystem>
#include <expected>
#include <optional>
#include "plugin_api/motion_planner_interface.h"
#include "plugin_manager/class_loader.h"
#include "motion_plan_config.h"
#include "planner_manager/planner_manager.h"
#include "plugin_manager_errors.h"

std::expected<std::shared_ptr<IMotionPlanner>, core::ErrorCode> getDefaultMotionPlanner()
{
  // Ideally, we'd have another object handle getting this path.
  // For demonstrative purposes, we'll just hard code this for now
  const auto dll_path = std::filesystem::path{
    library_build_path() + "/simple_motion_planner/libsimple_motion_planner.so"};
  // Load the correct planner. What should the parameter be. In ROS world, we send the package name and base class name
  // So we need something to find the path of .so and the interface name
  ClassLoader<IMotionPlanner> loader;
  if(const auto maybe_error = loader.loadLibrary(dll_path.string()); maybe_error.has_value())
  {
    return std::unexpected(maybe_error.value());
  }
  return loader.GetInstance();
}

int main(){
  const auto start_state = RobotState();
  const auto goal_state = RobotState();
  if(const auto maybe_motion_planner = getDefaultMotionPlanner();
      maybe_motion_planner.has_value()){
    const auto planner_manager = PlannerManager(maybe_motion_planner.value());
    const auto motion_plan = planner_manager.createMotionPlan(start_state, goal_state);
  }
  else{
    std::cerr << "Error occured creating motion plan: " 
        << core::error_message(maybe_motion_planner.error()) << "\n";
  }
}
