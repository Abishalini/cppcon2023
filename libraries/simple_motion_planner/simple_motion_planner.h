#pragma once
 
#include <iostream>
#include "plugin_api/motion_planner_interface.h"

class SimpleMotionPlanner : public IMotionPlanner
{
public:
	SimpleMotionPlanner() = default;
	~SimpleMotionPlanner() = default;
 
	std::vector<RobotState> plan(RobotState start, RobotState goal) override;
};
