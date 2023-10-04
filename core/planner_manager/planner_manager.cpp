#include <memory>
#include "plugin_api/motion_planner_interface.h"
#include "planner_manager.h"

PlannerManager::PlannerManager(std::shared_ptr<IMotionPlanner> motion_planner)
: motion_planner_{motion_planner} {}

std::vector<RobotState>
PlannerManager::createMotionPlan(const RobotState& start, const RobotState& goal) const
{
  // In practice, the manager would be doing other things like getting sensor
  // data, updating maps to give to the planner, etc.
  // Call the plan function
  return motion_planner_->plan(start, goal);
}
