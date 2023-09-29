#pragma once
#include <vector>
#include <string>

struct RobotState {
  std::vector<std::string> joint_names;
  std::vector<double> joint_values;
};

struct MotionPlannerParameters{
  std::string description;
};

class IMotionPlanner
{
public:
	virtual ~IMotionPlanner() = default;

	virtual std::vector<RobotState> plan(RobotState start, RobotState goal) = 0;
};
