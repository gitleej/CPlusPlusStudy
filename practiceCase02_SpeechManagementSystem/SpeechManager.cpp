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
        cout << "错误！尚未发布比赛规则！请先发布比赛规则。" << endl;
    }
    system("pause");
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
