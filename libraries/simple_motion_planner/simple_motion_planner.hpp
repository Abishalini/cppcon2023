#pragma once
 
#include <iostream>
#include "motion_planner_interface.hpp"

class SimpleMotionPlanner : public motion_planner::IMotionPlanner
{
public:
	SimpleMotionPlanner() = default;
	~SimpleMotionPlanner() = default;

	bool initialize() override
	{
		// Here is where MoveIt reads parameters and creates publishers/subscribers/services/actions
		return true;
	}
 
	std::vector<motion_planner::RobotState> plan(motion_planner::RobotState start, motion_planner::RobotState goal) override
	{
		// Insert a simple motion planner
		std::cout << "I am a planning motion simply\n";
		return std::vector<motion_planner::RobotState>{};
	}
};

// class factories

typedef SimpleMotionPlanner *create_t();
typedef void destroy_t(SimpleMotionPlanner *ptr);
