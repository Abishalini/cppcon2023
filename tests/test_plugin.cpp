#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>

#include "planner_manager.h"
#include "plugin_api/motion_planner_interface.h"

using ::testing::Return;

// Define equality operator for RobotState to test paths
bool operator==(const RobotState& lhs, const RobotState& rhs) {
  return lhs.joint_names == rhs.joint_names && lhs.joint_values == rhs.joint_values;
}

// Mock motion planner so expections can be set
struct MockMotionPlanner : public IMotionPlanner {
  MOCK_METHOD(std::vector<RobotState>, plan, (RobotState, RobotState), (override));
};

TEST(PlannerManager, CallPlanner) {
  // GIVEN a planner manager with a motion planner
  const auto planner = std::make_shared<MockMotionPlanner>();
  // THEN it should call the planner once
  EXPECT_CALL(*planner, plan).Times(1);
  const auto manager = PlannerManager{planner};

  // WHEN it is asked to plan from start to goal
  const auto start_state = RobotState();
  const auto goal_state = RobotState();
  const auto motion_plan = manager.createMotionPlan(start_state, goal_state);
}

TEST(PlannerManager, GetPath) {
  // GIVEN a planner manager with a motion planner that returns a path
  const auto start_state = RobotState();
  const auto goal_state = RobotState();
  const auto planner = std::make_shared<MockMotionPlanner>();
  ON_CALL(*planner, plan).WillByDefault(Return(std::vector<RobotState>{start_state, goal_state}));
  const auto manager = PlannerManager{planner};

  // WHEN it is asked to plan from start to goal
  const auto motion_plan = manager.createMotionPlan(start_state, goal_state);

  // THEN it should return the expected path
  const auto expected = std::vector<RobotState>{start_state, goal_state};
  EXPECT_EQ(motion_plan, expected);
}
