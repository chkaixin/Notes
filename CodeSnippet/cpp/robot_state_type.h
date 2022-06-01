#pragma once

enum RobotStateType
{
    RobotState_Login_Connecting,	// 正在链接 Login
    RobotState_Login_Connected,	    // 链接成功
    RobotState_Login_Logined,       // 登录成功
    
    RobotState_Game_Connecting,	    // 正在链接 Game
    RobotState_Game_Connected,	    // 链接成功
    RobotState_Game_Logined,        // 登录成功
};