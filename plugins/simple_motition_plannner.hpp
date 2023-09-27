#pragma once
 
#include <iostream>
#include "motion_planner_interface.hpp"
 
class SimpleMotionPlanner : public IMotionPlanner
{
public:
	SimpleMotionPlanner() = default;
	~SimpleMotionPlanner() = default;

	bool initialize() override
	{
		// Here is where MoveIt reads parameters and creates publishers/subscribers/services/actions
		return true;
	}
 
	std::vector<RobotState> plan(RobotState start, RobotState goal) override
	{
		// Insert a simple motion planner
		return std::vector<RobotState>{};
	}
};

extern "C" IMotionPlanner* createInstance() { return new SimpleMotionPlanner; }
extern "C" void deleteInstance(IMotionPlanner* motion_planner) { delete motion_planner; }
