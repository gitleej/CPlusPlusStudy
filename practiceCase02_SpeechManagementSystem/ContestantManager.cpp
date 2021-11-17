#include "ContestantManager.h"

ContestantManager::ContestantManager(): 
    m_num(0)
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
        addContestantInfoManually();
        break;
    }
    case 2:
    {
        addContestantInfoFromFile();
        break;
    }
    case 3:
    {
        addContestantInfoRandomly();
        break;
    }
    default:
        break;
    }

    system("pause");
}

void ContestantManager::addContestantInfoManually()
{
    int totalNum = 0;
    cout << "请输入需要添加参赛选手信息数量：";
    cin >> totalNum;
    for (int i = 0; i < totalNum; i++)
    {
        string tempStr;
        cout << "请输入第 " << i + 1 << " 个参赛选手的姓名，年龄，和id(用空格分隔，如：xxx xx xxxxx)" << endl;
        getline(cin, tempStr);
        vector<string> result = Utils::Utils::strSplit(tempStr, ' ');
        if (result.size() != 3)
        {
            cout << "【错误】：输入格式不正确，请检查后重试。" << endl;
            i--;
            continue;
        }

        ContestantType tempContestant;
        tempContestant.name = result[0];
        tempContestant.age = std::stoi(result[1]);
        tempContestant.id = result[2];
        this->m_contestants.push_back(tempContestant);
        this->m_num++;
    }

    cout << "共添加 " << totalNum << " 个参赛选手信息。\n"
        << "数据库中共有 " << this->m_num << " 个参赛选手信息。" << endl;
}

void ContestantManager::addContestantInfoFromFile()
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

    int totalNum = 0;
    string line;
    while (getline(ifs, line))
    {
        vector<string> results = Utils::Utils::strSplit(line, ',');
        if (results.size() == 3)
        {
            ContestantType tempContestant;
            tempContestant.name = results[0];
            tempContestant.age = std::stoi(results[1]);
            tempContestant.id = results[2];
            this->m_contestants.push_back(tempContestant);
            totalNum++;
            this->m_num++;
        }
    }

    cout << "共添加 " << totalNum << " 个参赛选手信息。\n"
        << "数据库中共有 " << this->m_num << " 个参赛选手信息。" << endl;
}

void ContestantManager::addContestantInfoRandomly()
{
    // 设置随机种子
    srand((unsigned int)time(NULL));

    int totalNum = 0;
    cout << "请输入需要添加参赛选手信息数量：";
    cin >> totalNum;
    for (int i = 0; i < totalNum; i++)
    {
        string tempStr;
        cout << "请输入第 " << i + 1 << " 个参赛选手的姓名，年龄，和id(用空格分隔，如：xxx xx xxxxx)" << endl;
        getline(cin, tempStr);
        vector<string> result = Utils::Utils::strSplit(tempStr, ' ');
        if (result.size() != 3)
        {
            cout << "【错误】：输入格式不正确，请检查后重试。" << endl;
            i--;
            continue;
        }

        ContestantType tempContestant;
        tempContestant.name = result[0];
        tempContestant.age = std::stoi(result[1]);
        tempContestant.id = result[2];
        this->m_contestants.push_back(tempContestant);
        this->m_num++;
    }
}
