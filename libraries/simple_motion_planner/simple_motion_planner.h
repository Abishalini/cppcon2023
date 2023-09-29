#pragma once
 
#include <iostream>
#include "plugin_api/motion_planner_interface.h"

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
		std::cout << "I am a planning motion simply\n";
		return std::vector<RobotState>{};
	}
};

// class factories

typedef SimpleMotionPlanner *create_t();
typedef void destroy_t(SimpleMotionPlanner *ptr);
