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

#if defined(__linux__) || defined(__APPLE__)
extern "C"
{
	SimpleMotionPlanner *allocator()
	{
		return new SimpleMotionPlanner();
	}

	void deleter(SimpleMotionPlanner *ptr)
	{
		delete ptr;
	}
}
#endif

#ifdef WIN32
extern "C"
{
	__declspec (dllexport) SimpleMotionPlanner *allocator()
	{
		return new SimpleMotionPlanner();
	}

	__declspec (dllexport) void deleter(SimpleMotionPlanner *ptr)
	{
		delete ptr;
	}
}
#endif

// extern "C" IMotionPlanner* createInstance() { return new SimpleMotionPlanner; }
// extern "C" void deleteInstance(IMotionPlanner* motion_planner) { delete motion_planner; }
