#include "SpeechManager.h"

SpeechManager::SpeechManager()
    : m_speechRule(new SpeechRule)
    , m_isSetRule(false)
{
}

SpeechManager::~SpeechManager()
{
}

void SpeechManager::showMenu(MenuType menuType)
{
    switch (menuType)
    {
    case MAIN_MENU:
    {
        showMainMenu();
        break;
    }
    default:
        break;
    }
}

void SpeechManager::publishRules()
{
    this->m_speechRule->setRule();
    this->m_speechRule->saveRule();
    this->m_isSetRule = true;
}

void SpeechManager::showRules()
{
    if (m_isSetRule)
    {
        this->m_speechRule->showRules();
    }
    else
    {
        cout << "������δ���������������ȷ�����������" << endl;
    }
    system("pause");
}

void SpeechManager::exitSystem()
{
    exit(0);
    cout << "���˳�ϵͳ����ӭ�´�ʹ�á�" << endl;
}

void SpeechManager::showMainMenu()
{
    system("cls");
    cout << "------------- �ݽ���������ϵͳv1.0 -------------\n"
        << "|                    ���˵�                    |\n"
        << "|[1] - ������������                            |\n"
        << "|[2] - �鿴��������                            |\n"
        << "|[3] - ѡ����Ϣ����                            |\n"
        << "|[4] - ��ʼ�ݽ�����                            |\n"
        << "|[5] - �鿴������¼                            |\n"
        << "|[6] - ��ձ�����¼                            |\n"
        << "|[0] - �˳�    ϵͳ                            |\n"
        << "------------------------------------------------"
        << endl;
}
