#pragma once
#ifndef _SPEECH_MANAGER_H_
#define _SPEECH_MANAGER_H_

#include "SpeechRule.h"
#include "ContestantManager.h"
#include "Utils.hpp"

#include <iostream>
#include <ctime>

using namespace std;

// 菜单级别
typedef enum _MENUTYPE_
{
    MAIN_MENU,      // 主菜单
}MenuType;

typedef enum _ContestProcessType_ {
    FINALS = 0,                 ///< 决赛
    PUBLISHING_RULES,           ///< 发布规则
    RECRUITING_CONTESTANTS,     ///< 招募选手
    PRELIMINARY,                ///< 初赛
    REMATCH,                    ///< 复赛
    OTHERS
}ContestProcessType;

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

    // 参赛选手管理
    void contestantMangement();

    // 退出系统
    void exitSystem();

private:
    void showMainMenu();
    // 保存历史记录
    void saveHistoryRecord();
    // 加载历史记录
    void loadHistoryRecode();

public:
    SpeechRule          *m_speechRule;                  // 比赛规则
    ContestantManager   *m_contestantManager;           // 选手信息管理
    string m_contestStartTimestamp;                     // 比赛开始时间
    ContestProcessType m_contestProcess;                // 比赛进度，1-发布规则，2-招募选手，3-初赛完成，4-复赛完成，0-比赛完成
    map<string, ContestProcessType> m_historyRecord;    // 历史记录

private:
    bool                m_isSetRule;            // 是否已设置规则
};

#endif // !_SPEECH_MANAGER_H_
