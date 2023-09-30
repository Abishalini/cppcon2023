#include <memory>
#include <filesystem>
#include "plugin_api/motion_planner_interface.h"
#include "plugin_manager/class_loader.h"
#include "motion_plan_config.h"
#include "planner_manager/planner_manager.h"

std::shared_ptr<IMotionPlanner> getDefaultMotionPlanner()
{
  // Ideally, we'd have another object handle getting this path.
  // For demonstrative purposes, we'll just hard code this for now
  const auto dll_path = std::filesystem::path{
    library_build_path() + "/simple_motion_planner/libsimple_motion_planner.so"};
  // Load the correct planner. What should the parameter be. In ROS world, we send the package name and base class name
  // So we need something to find the path of .so and the interface name
  auto loader = ClassLoader<IMotionPlanner>(dll_path.string());

  // In ROS world, we send the plugin name which is declared in XML file. Maybe we send in the derived class name?
  return loader.GetInstance();
}

int main(){
  const auto start_state = RobotState();
  const auto goal_state = RobotState();
  const auto motion_planner = getDefaultMotionPlanner();
  const auto planner_manager = PlannerManager(motion_planner);
  const auto motion_plan = planner_manager.createMotionPlan(start_state, goal_state);
}
