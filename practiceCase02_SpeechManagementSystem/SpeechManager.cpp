#include "SpeechManager.h"

SpeechManager::SpeechManager()
    : m_speechRule(new SpeechRule)
    , m_isSetRule(false)
    , m_contestantManager(new ContestantManager)
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

void SpeechManager::contestantMangement()
{
    m_contestantManager->loadContestantInfo();

    int choise = -1;
    while (true)
    {
        this->m_contestantManager->showMenu();
        cout << "���������ѡ��";
        cin >> choise;
        switch (choise)
        {
        case 1:
        {
            m_contestantManager->addContestantInfo();
            break;
        }
        case 2:
        {
            m_contestantManager->viewContestantInfo();
            break;
        }
        case 3:
        {
            m_contestantManager->deletContestantInfo();
            break;
        }
        case 4:
        {
            m_contestantManager->modifyContestantInfo();
            break;
        }
        case 5:
        {
            m_contestantManager->saveContestantInfo();
            break;
        }
        default:
            break;
        }

        if (choise == 0)
        {
            if (!m_contestantManager->m_isSaveContestantInfo) {
                getchar();
                cout << "�����桿���в���ѡ����Ϣ�Ķ�δ���棬��ȷ���Ƿ񱣴�(y/"
                        "n)��";
                char confime = getchar();
                if (confime == 'y') {
                    m_contestantManager->saveContestantInfo();
                } else {
                    cout << "�����ѡ������ԸĶ������ᱣ�棬��ֱ���˳���ǰ�˵�"
                         << endl;
                    system("pause");
                }
            }
            m_contestantManager->m_isSaveContestantInfo = true;
            break;
        }
    }
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
