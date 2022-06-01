#include "robot_state_login.h"
#include "robot.h"

void RobotStateLoginConnecting::OnEnterState()
{
}

RobotStateType RobotStateLoginConnecting::OnUpdate()
{
    return GetState();
}

void RobotStateLoginConnected::OnEnterState()
{
}