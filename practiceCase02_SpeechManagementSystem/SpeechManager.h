#pragma once
#ifndef _SPEECH_MANAGER_H_
#define _SPEECH_MANAGER_H_

#include "SpeechRule.h"
#include "ContestantManager.h"
#include "Utils.hpp"

#include <iostream>
#include <ctime>

using namespace std;

// �˵�����
typedef enum _MENUTYPE_
{
    MAIN_MENU,      // ���˵�
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

    // ������������
    void publishRules();
    
    // �鿴����
    void showRules();

    // ����ѡ�ֹ���
    void contestantMangement();

    // �˳�ϵͳ
    void exitSystem();

private:
    void showMainMenu();
    // ������ʷ��¼
    void saveHistoryRecord();
    // ������ʷ��¼
    void loadHistoryRecode();

public:
    SpeechRule          *m_speechRule;                  // ��������
    ContestantManager   *m_contestantManager;           // ѡ����Ϣ����
    string m_contestStartTimestamp;                     // ������ʼʱ��
    ContestProcessType m_contestProcess;                // �������ȣ�1-��������2-��ļѡ�֣�3-������ɣ�4-������ɣ�0-�������
    map<string, ContestProcessType> m_historyRecord;    // ��ʷ��¼

private:
    bool                m_isSetRule;            // �Ƿ������ù���
};

#endif // !_SPEECH_MANAGER_H_
