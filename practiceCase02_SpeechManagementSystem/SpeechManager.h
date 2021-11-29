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
    void coutHistoryRecord(const vector<map<string, ContestProcessType>> &src);

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

    // �˳�ϵͳ
    void exitSystem();

    // �����ʷ��¼
    void removeHistory();

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

public:
    SpeechRule          *m_speechRule;                      // ��������
    ContestantManager   *m_contestantManager;               // ѡ����Ϣ����
    string m_contestStartTimestamp;                         // ������ʼʱ��
    ContestProcessType m_contestProcess;                    // �������ȣ�1-��������2-��ļѡ�֣�3-������ɣ�4-������ɣ�0-�������
    vector<map<string, ContestProcessType>> m_historyRecord;        // ��ʷ��¼
    vector<map<string, ContestProcessType>> m_unfinishedContests;   // δ��ɵı���

private:
    bool                m_isSetRule;            // �Ƿ������ù���
};

#endif // !_SPEECH_MANAGER_H_
