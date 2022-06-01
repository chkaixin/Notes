#include "robot_state.h"
#include "robot.h"

RobotStateType RobotState::Update()
{
    return OnUpdate();
}

void RobotState::EnterState()
{
    OnEnterState();
}

void RobotState::LeaveState()
{
    OnLeaveState();
}