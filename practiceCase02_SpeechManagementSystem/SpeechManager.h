#pragma once
#ifndef _SPEECH_MANAGER_H_
#define _SPEECH_MANAGER_H_

#include "SpeechRule.h"
#include "ContestantManager.h"

#include <iostream>

using namespace std;

// 菜单级别
typedef enum _MENUTYPE_
{
    MAIN_MENU,      // 主菜单
}MenuType;

class SpeechManager
{
public:
    SpeechManager();
    ~SpeechManager();

    // 显示菜单
    void showMenu(MenuType menuType);

    // 发布比赛规则
    void publishRules();
    
    // 查看规则
    void showRules();

    void contestantMangement();

    // 退出系统
    void exitSystem();

private:
    void showMainMenu();

public:
    SpeechRule          *m_speechRule;          // 比赛规则
    ContestantManager   *m_contestantManager;   // 选手信息管理

private:
    bool                m_isSetRule;            // 是否已设置规则
};

#endif // !_SPEECH_MANAGER_H_
