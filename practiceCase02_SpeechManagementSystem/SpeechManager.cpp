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
        cout << "错误！尚未发布比赛规则！请先发布比赛规则。" << endl;
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
        cout << "请输入你的选择：";
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
                cout << "【警告】：有参赛选手信息改动未保存，请确认是否保存(y/"
                        "n)：";
                char confime = getchar();
                if (confime == 'y') {
                    m_contestantManager->saveContestantInfo();
                } else {
                    cout << "【提醒】：所以改动均不会保存，将直接退出当前菜单"
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
    cout << "已退出系统，欢迎下次使用。" << endl;
}

void SpeechManager::showMainMenu()
{
    system("cls");
    cout << "------------- 演讲比赛管理系统v1.0 -------------\n"
        << "|                    主菜单                    |\n"
        << "|[1] - 发布比赛规则                            |\n"
        << "|[2] - 查看比赛规则                            |\n"
        << "|[3] - 选手信息管理                            |\n"
        << "|[4] - 开始演讲比赛                            |\n"
        << "|[5] - 查看比赛记录                            |\n"
        << "|[6] - 清空比赛记录                            |\n"
        << "|[0] - 退出    系统                            |\n"
        << "------------------------------------------------"
        << endl;
}
