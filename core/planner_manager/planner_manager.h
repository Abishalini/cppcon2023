#include <memory>
#include "plugin_api/motion_planner_interface.h"

struct PlannerManager {
  /**
   * @brief Coordinates motion planning with other services needed for planning context
   * @param motion_planner The motion planner to use
   */
  PlannerManager(std::shared_ptr<IMotionPlanner> motion_planner);

  /**
   * @brief Creates a motion plan from start to goal
   * @param start state
   * @param goal state
   * @return The motion plan
   */
  std::vector<RobotState> createMotionPlan(const RobotState& start, const RobotState& goal) const;

 private:
  std::shared_ptr<IMotionPlanner> motion_planner_;
};
