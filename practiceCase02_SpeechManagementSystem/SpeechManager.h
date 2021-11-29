#pragma once
#ifndef _SPEECH_MANAGER_H_
#define _SPEECH_MANAGER_H_

#include "SpeechRule.h"
#include "ContestantManager.h"
#include "Utils.hpp"

#include <iostream>
#include <ctime>
#include <cstdio>

using namespace std;

// 菜单级别
typedef enum _MENUTYPE_
{
    MAIN_MENU,      // 主菜单
    CONTINUE_MENU,  // 继续比赛菜单
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

    // 显示历史记录
    void coutHistoryRecord(const vector<map<string, ContestProcessType>> &src);

    // 开始新的比赛
    void startNewContest();

    // 继续比赛
    void continueContest();

    // 发布比赛规则
    void publishRules();
    void publishRules(const string &timestamp);
    
    // 查看规则
    void showRules();

    // 参赛选手管理
    void contestantMangement();
    void contestantMangement(const string &timestamp);

    // 退出系统
    void exitSystem();

    // 清除历史记录
    void removeHistory();

private:
    // 显示主菜单
    void showMainMenu();
    // 显示是否继续比赛菜单
    void showContinueMenu();
    // 保存历史记录
    void saveHistoryRecord();
    // 加载历史记录
    void loadHistoryRecode();
    // 检查是否有历史记录存在
    void checkRecordExist(const string &timestamp,
                          const ContestProcessType &contestProcess);

public:
    SpeechRule          *m_speechRule;                      // 比赛规则
    ContestantManager   *m_contestantManager;               // 选手信息管理
    string m_contestStartTimestamp;                         // 比赛开始时间
    ContestProcessType m_contestProcess;                    // 比赛进度，1-发布规则，2-招募选手，3-初赛完成，4-复赛完成，0-比赛完成
    vector<map<string, ContestProcessType>> m_historyRecord;        // 历史记录
    vector<map<string, ContestProcessType>> m_unfinishedContests;   // 未完成的比赛

private:
    bool                m_isSetRule;            // 是否已设置规则
};

#endif // !_SPEECH_MANAGER_H_
