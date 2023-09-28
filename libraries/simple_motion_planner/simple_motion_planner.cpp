#include "simple_motion_planner.hpp"

#if defined(__linux__) || defined(__APPLE__)
extern "C" {
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