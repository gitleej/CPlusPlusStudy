#include "ContestantManager.h"

ContestantManager::ContestantManager()
{
}

ContestantManager::~ContestantManager()
{
}

void ContestantManager::showMenu()
{
    system("cls");
    cout << "------------- 演讲比赛管理系统v1.0 -------------\n"
        << "|                 选手信息管理                 |\n"
        << "|[1] - 添加选手信息                            |\n"
        << "|[2] - 查看选手信息                            |\n"
        << "|[3] - 删除选手信息                            |\n"
        << "|[4] - 修改选手信息                            |\n"
        << "|[5] - 保存选手信息                            |\n"
        << "|[0] - 退出当前菜单                            |\n"
        << "------------------------------------------------"
        << endl;
}

void ContestantManager::addContestantInfo()
{
    system("cls");
    cout << "------------- 演讲比赛管理系统v1.0 -------------\n"
        << "|                 选手信息管理                 |\n"
        << "|[1] - 添加选手信息                            |\n"
        << "|    (1) - 手动添加参赛选手信息                |\n"
        << "|    (2) - 从文件导入参赛选手信息              |\n"
        << "|    (3) - 随机生成参赛选手信息                |\n"
        << "------------------------------------------------"
        << endl;

    int choise = -1;
    cout << "请输入您的选择：" << endl;
    cin >> choise;
    switch (choise)
    {
    case 1:
    {
        break;
    }
    case 2:
    {
        loadContestantInfoFromFile();
        break;
    }
    case 3:
    {
        break;
    }
    default:
        break;
    }

    system("pause");
}

void ContestantManager::loadContestantInfoFromFile()
{
    string filePath;
    cout << "请输入文件路径：";
    cin >> filePath;

    ifstream ifs;
    ifs.open(filePath.c_str(), std::ios::in);
    if (!ifs.is_open())
    {
        cout << "文件不存在：" << filePath << endl;
        return;
    }

    string line;
    while (getline(ifs, line))
    {
        cout << line << endl;
    }
}
