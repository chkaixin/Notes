#pragma once
#include <string>

#include "state_template.h"
#include "robot_state_type.h"

#include "robot_state.h"

class Robot : public StateTemplateMgr<RobotStateType, RobotState, Robot>
{
public:
    explicit Robot(std::string account);
    void Init();
    void Update();

    std::string GetAccount() const;

protected:
    void RegisterState() override;

private:
    std::string _account;
};