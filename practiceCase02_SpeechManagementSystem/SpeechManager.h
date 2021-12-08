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

// �˵�����
typedef enum _MENUTYPE_
{
    MAIN_MENU,      // ���˵�
    CONTINUE_MENU,  // ���������˵�
}MenuType;

typedef enum _ContestProcessType_ {
    FINALS = 0,                 ///< ����
    PUBLISHING_RULES,           ///< ��������
    RECRUITING_CONTESTANTS,     ///< ��ļѡ��
    PRELIMINARY,                ///< ����
    REMATCH,                    ///< ����
    OTHERS
}ContestProcessType;

class SpeechManager
{
public:
    SpeechManager();
    ~SpeechManager();

    // ��ʾ�˵�
    void showMenu(MenuType menuType);

    // ��ʾ��ʷ��¼
    void coutHistoryRecord(const vector<pair<string, ContestProcessType>> &src);

    // ��ʼ�µı���
    void startNewContest();

    // ��������
    void continueContest();

    // ������������
    void publishRules();
    void publishRules(const string &timestamp);
    
    // �鿴����
    void showRules();

    // ����ѡ�ֹ���
    void contestantMangement();
    void contestantMangement(const string &timestamp);

    // ��ʼ���б���
    void startContest();

    // �˳�ϵͳ
    void exitSystem();

    // �鿴������¼
    void reviewAllHistory();
    void reviewHistory(const string &timestamp);

    // �����ʷ��¼
    void removeHistory();
    void removeHistory(const string &timestamp);

private:
    // ��ʾ���˵�
    void showMainMenu();
    // ��ʾ�Ƿ���������˵�
    void showContinueMenu();
    // ������ʷ��¼
    void saveHistoryRecord();
    // ������ʷ��¼
    void loadHistoryRecode();
    // ����Ƿ�����ʷ��¼����
    void checkRecordExist(const string &timestamp,
                          const ContestProcessType &contestProcess);
    // ��ʼ���г���
    void startPreliminary();
    // ��ʼ���и���
    void startRematch();
    // ��ʼ���о���
    void startFinals();
    // ����
    void getGroup(int level,
                  vector<ContestantType> &src,
                  vector<vector<ContestantType>> &contestantsGroup);
    // ����
    vector<ContestantType> startGame(
        vector<ContestantType> &src,
        int level);  // level 0,1,2->����������������
    // ���
    float judge();
    // ����������
    void saveContestResult(
        const int level,
        const vector<vector<ContestantType>> &groupedContestants,
        const vector<ContestantType> &nextContestants);
    // ���ر������
    void loadContestResult(const string &timestamp);
    // ��ʾ��¼���
    void showResultRecord(
        int level,
        bool isAll,
        const vector<pair<vector<ContestantType>, vector<ContestantType>>>
            &src);

public:
    SpeechRule          *m_speechRule;                      // ��������
    ContestantManager   *m_contestantManager;               // ѡ����Ϣ����
    string m_contestStartTimestamp;                         // ������ʼʱ��
    ContestProcessType m_contestProcess;                    // �������ȣ�1-��������2-��ļѡ�֣�3-������ɣ�4-������ɣ�0-�������
    // map<string, ContestProcessType> m_historyRecord;        // ��ʷ��¼
    vector<pair<string, ContestProcessType>> m_historyRecord;
    // map<string, ContestProcessType> m_unfinishedContests;   // δ��ɵı���
    vector<pair<string, ContestProcessType>> m_unfinishedContests;
    vector<vector<ContestantType>> m_contestantsGroup;              // ����ѡ�ַ���
    vector<vector<ContestantType>> m_contestantsRematchGroup;       // ����ѡ�ַ���
    vector<ContestantType> m_contestantsRematch;                    // ����ѡ��
    vector<ContestantType> m_contestantsFinals;                     // ����ѡ��
    
    // vector<vector<ContestantType>> m_resultRecord;                  // ��ʷ��¼
    vector<vector<pair<vector<ContestantType>, vector<ContestantType>>>>
        m_resultRecord;

private:
    bool                m_isSetRule;            // �Ƿ������ù���
};

#endif // !_SPEECH_MANAGER_H_
