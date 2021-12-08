#pragma once
#ifndef _SPEECH_MANAGER_H_
#define _SPEECH_MANAGER_H_

#include "SpeechRule.h"
#include "ContestantManager.h"
#include "Utils.hpp"

#include <iostream>
#include <ctime>
#include <cstdio>
#include <algorithm>
#include <random>
#include <deque>

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
    void coutHistoryRecord(const vector<pair<string, ContestProcessType>> &src);

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

    // 开始进行比赛
    void startContest();

    // 退出系统
    void exitSystem();

    // 查看比赛记录
    void reviewAllHistory();
    void reviewHistory(const string &timestamp);

    // 清除历史记录
    void removeHistory();
    void removeHistory(const string &timestamp);

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
    // 开始进行初赛
    void startPreliminary();
    // 开始进行复赛
    void startRematch();
    // 开始进行决赛
    void startFinals();
    // 分组
    void getGroup(int level,
                  vector<ContestantType> &src,
                  vector<vector<ContestantType>> &contestantsGroup);
    // 比赛
    vector<ContestantType> startGame(
        vector<ContestantType> &src,
        int level);  // level 0,1,2->初赛、复赛、决赛
    // 打分
    float judge();
    // 保存比赛结果
    void saveContestResult(
        const int level,
        const vector<vector<ContestantType>> &groupedContestants,
        const vector<ContestantType> &nextContestants);
    // 加载比赛结果
    void loadContestResult(const string &timestamp);
    // 显示记录结果
    void showResultRecord(
        int level,
        bool isAll,
        const vector<pair<vector<ContestantType>, vector<ContestantType>>>
            &src);

public:
    SpeechRule          *m_speechRule;                      // 比赛规则
    ContestantManager   *m_contestantManager;               // 选手信息管理
    string m_contestStartTimestamp;                         // 比赛开始时间
    ContestProcessType m_contestProcess;                    // 比赛进度，1-发布规则，2-招募选手，3-初赛完成，4-复赛完成，0-比赛完成
    // map<string, ContestProcessType> m_historyRecord;        // 历史记录
    vector<pair<string, ContestProcessType>> m_historyRecord;
    // map<string, ContestProcessType> m_unfinishedContests;   // 未完成的比赛
    vector<pair<string, ContestProcessType>> m_unfinishedContests;
    vector<vector<ContestantType>> m_contestantsGroup;              // 初赛选手分组
    vector<vector<ContestantType>> m_contestantsRematchGroup;       // 复赛选手分组
    vector<ContestantType> m_contestantsRematch;                    // 复赛选手
    vector<ContestantType> m_contestantsFinals;                     // 决赛选手
    
    // vector<vector<ContestantType>> m_resultRecord;                  // 历史记录
    vector<vector<pair<vector<ContestantType>, vector<ContestantType>>>>
        m_resultRecord;

private:
    bool                m_isSetRule;            // 是否已设置规则
};

#endif // !_SPEECH_MANAGER_H_
