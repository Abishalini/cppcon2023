#pragma once
#include <vector>
#include <string>

struct RobotState {
  std::vector<std::string> joint_names;
  std::vector<double> joint_values;
};

class IMotionPlanner
{
public:
	virtual ~IMotionPlanner() = default;
  virtual bool initialize() = 0;
	virtual std::vector<RobotState> plan(RobotState start, RobotState goal) = 0;
};
