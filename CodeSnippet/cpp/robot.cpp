#include "robot.h"

#include "robot_state_login.h"
#include "robot_state_type.h"

Robot::Robot(std::string account)
{
    _account = account;
}

void Robot::Init()
{
    InitStateTemplateMgr(RobotState_Login_Connecting);
}

void Robot::Update()
{
    UpdateState();
}

std::string Robot::GetAccount() const
{
    return _account;
}

void Robot::RegisterState()
{
    RegisterStateClass(RobotState_Login_Connecting, DynamicStateBind(RobotStateLoginConnecting));
    RegisterStateClass(RobotState_Login_Connected, DynamicStateBind(RobotStateLoginConnected));
    RegisterStateClass(RobotState_Login_Logined, DynamicStateBind(RobotStateLoginLogined));
}