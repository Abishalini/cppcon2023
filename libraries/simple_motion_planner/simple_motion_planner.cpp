#include "simple_motion_planner.h"

#if defined(__linux__) || defined(__APPLE__)
extern "C" 
{
	SimpleMotionPlanner *create()
	{
		return new SimpleMotionPlanner();
	}

	void destroy(SimpleMotionPlanner *ptr)
	{
		delete ptr;
	}
}
#elif _WIN32
extern "C"
{
	__declspec (dllexport) SimpleMotionPlanner *create()
	{
		return new SimpleMotionPlanner();
	}

	__declspec (dllexport) void destroy(SimpleMotionPlanner *ptr)
	{
		delete ptr;
	}
}
#endif

bool SimpleMotionPlanner::initialize()
{
	// Here is where MoveIt reads parameters and creates publishers/subscribers/services/actions
	return true;
}

std::vector<RobotState> SimpleMotionPlanner::plan(RobotState start, RobotState goal)
{
	// Insert a simple motion planner
	std::cout << "I am planning motion simply\n";
	return std::vector<RobotState>{};
}
