
#include <memory>
#include <filesystem>
#include "motion_planner_interface.hpp"
#include "class_loader.hpp"


namespace{
  std::vector<motion_planner::RobotState> createMotionPlan(motion_planner::RobotState start, motion_planner::RobotState goal)
  {
    // Ideally, we'd have another object handle getting this path.
    // For demonstrative purposes, we'll just hard code this for now
    const auto dll_path = std::filesystem::path{"/home/abaker/Documents/cppcon2023/build/libsimple_motion_planner.so"};
    // Load the correct planner. What should the parameter be. In ROS world, we send the package name and base class name
    // So we need something to find the path of .so and the interface name
    using LoaderType = plugin_manager::ClassLoader<motion_planner::IMotionPlanner>;
    std::shared_ptr<LoaderType> loader = std::make_shared<LoaderType>(dll_path);

    // In ROS world, we send the plugin name which is declared in XML file. Maybe we send in the derived class name?
    std::shared_ptr<motion_planner::IMotionPlanner> motion_planner = loader->GetInstance();

    // Call the plan function
    return motion_planner->plan(start, goal);
  }
}

int main(){
  auto start_state = motion_planner::RobotState();
  auto goal_state = motion_planner::RobotState();
  auto motion_plan = createMotionPlan(start_state, goal_state);
}