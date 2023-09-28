
#include <memory>
#include <motion_planner_interface.hpp>
#include <plugin_manager/class_loader.hpp>

class MotionPlan
{
public:
  std::vector<RobotState> createMotionPlan(RobotState start, RobotState goal)
  {
    const auto dll_path{""};
    // Load the correct planner. What should the parameter be. In ROS world, we send the package name and base class name
    // So we need something to find the path of .so and the interface name
    using LoaderType = ClassLoader<IMotionPlanner>;
    std::shared_ptr<LoaderType> loader = std::make_shared<LoaderType>();

    // In ROS world, we send the plugin name which is declared in XML file. Maybe we send in the derived class name?
    std::shared_ptr<IMotionPlanner> motion_planner = loader->createUniqueInstance("");

    // Call the plan function
    return motion_planner->plan(start, goal);
  }
};
