#include "ContestantManager.h"

ContestantManager::ContestantManager()
    : m_num(0), m_contestants(0), m_isSaveContestantInfo(true) {
    // loadContestantInfo();
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

//void ContestantManager::addContestantInfo()
//{
//    m_isSaveContestantInfo = false;
//    system("cls");
//    cout << "------------- 演讲比赛管理系统v1.0 -------------\n"
//        << "|                 选手信息管理                 |\n"
//        << "|[1] - 添加选手信息                            |\n"
//        << "|    (1) - 手动添加参赛选手信息                |\n"
//        << "|    (2) - 从文件导入参赛选手信息              |\n"
//        << "|    (3) - 随机生成参赛选手信息                |\n"
//        << "------------------------------------------------"
//        << endl;
//
//    int choise = -1;
//    cout << "请输入您的选择：" << endl;
//    cin >> choise;
//    switch (choise)
//    {
//    case 1:
//    {
//        addContestantInfoManually();
//        break;
//    }
//    case 2:
//    {
//        addContestantInfoFromFile();
//        break;
//    }
//    case 3:
//    {
//        addContestantInfoRandomly();
//        break;
//    }
//    default:
//        break;
//    }
//
//    system("pause");
//}

int ContestantManager::addContestantInfo() {
    m_isSaveContestantInfo = false;
    system("cls");
    cout << "------------- 演讲比赛管理系统v1.0 -------------\n"
         << "|                 选手信息管理                 |\n"
         << "|[1] - 添加选手信息                            |\n"
         << "|    (1) - 手动添加参赛选手信息                |\n"
         << "|    (2) - 从文件导入参赛选手信息              |\n"
         << "|    (3) - 随机生成参赛选手信息                |\n"
         << "------------------------------------------------" << endl;

    int choise = -1;
    cout << "请输入您的选择：" << endl;
    cin >> choise;
    switch (choise) {
        case 1: {
            addContestantInfoManually();
            break;
        }
        case 2: {
            addContestantInfoFromFile();
            break;
        }
        case 3: {
            addContestantInfoRandomly();
            break;
        }
        default: break;
    }

    system("pause");
    return (int)(this->m_contestants.size());
}

void ContestantManager::addContestantInfoManually()
{
    int totalNum = 0;
    cout << "请输入需要添加参赛选手信息数量：";
    cin >> totalNum;
    for (int i = 0; i < totalNum; i++)
    {
        string tempStr;
        cout << "请输入第 " << i + 1 << " 个参赛选手的姓名，年龄，和id(用逗号分隔，如：xxx,xx,xxxxx)" << endl;
        getline(cin, tempStr);
        vector<string> result = Utils::Utils::strSplit(tempStr, ',');
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
        string name = makeName();
        map<string, int> result = makeId();
        int age = result.begin()->second;
        if (age < 18) {
            i--;
            continue;
        }
        string id = result.begin()->first;
        // cout << name << "\t" << age << "\t" << id << endl;
        
        ContestantType tempContestant;
        tempContestant.name = name;
        tempContestant.age = age;
        tempContestant.id = id;
        this->m_contestants.push_back(tempContestant);
        this->m_num++;
    }
    cout << "共添加 " << totalNum << " 个参赛选手信息。\n"
         << "数据库中共有 " << this->m_num << " 个参赛选手信息。" << endl;
}

void ContestantManager::viewContestantInfo() {
    system("cls");
    // 检查是否已经有选手
    if (this->m_contestants.size() == 0) {
        cout << "【警告】：当前还没有招募到参赛选手，请先招募参赛选手。"
             << endl;
        system("pause");
        return;
    }
    
    cout << "------------- 演讲比赛管理系统v1.0 -------------\n"
         << "|                 选手信息管理                 |\n"
         << "|[2] - 查看选手信息                            |\n"
         << "------------------------------------------------" << endl;
    for (auto it = this->m_contestants.begin(); it != this->m_contestants.end();
         it++) {
        int index = (int)(it - this->m_contestants.begin());
        if ((index + 1) % 10 == 0) {
            system("pause");
            system("cls");
            cout << "------------- 演讲比赛管理系统v1.0 -------------\n"
                 << "|                 选手信息管理                 |\n"
                 << "|[2] - 查看选手信息                            |\n"
                 << "------------------------------------------------" << endl;
        }
        cout << "[" << right << setw(4) << fixed << index + 1 << "/ " << left
             << setw(4) << fixed << this->m_num << "]: "
             << "name: " << right << setw(20) << fixed << it->name
             << "\tage: " << it->age << "\tid: " << it->id << endl;
    }

    system("pause");
}

int ContestantManager::deletContestantInfo() {
    // 检查是否已经有选手
    if (this->m_contestants.size() == 0) {
        cout << "【警告】：当前还没有招募到参赛选手，请先招募参赛选手。"
             << endl;
        system("pause");
        return -1;
    }

    m_isSaveContestantInfo = false;
    system("cls");
    cout << "------------- 演讲比赛管理系统v1.0 -------------\n"
         << "|                 选手信息管理                 |\n"
         << "|[3] - 删除选手信息                            |\n"
         << "------------------------------------------------" << endl;
    getchar();
    string tempId;
    cout << "请输入待删除参赛选手的id号(18位)：";
    getline(cin, tempId);
    if (tempId.size() != 18) {
        cout << "【错误】：id格式不正确，请重试！" << endl;
        system("pause");
        return -1;
    }
    vector<ContestantType>::iterator resultIter =
        this->findContestantId(tempId);
    if (resultIter != this->m_contestants.end()) {
        cout << "【警告】：确认删除id为：" << tempId << " 的参赛选手信息？(y/n)"
             << endl;
        char confirm = 'y';
        confirm = getchar();
        if (confirm == 'y') {
            cout << "【提醒】：name:" << right << setw(20) << fixed
                 << resultIter->name << "\tage: " << resultIter->age
                 << "\tid: " << resultIter->id << " 已删除" << endl;
            this->m_contestants.erase(resultIter);
            this->m_num--;
        } else {
            cout << "【提醒】：删除已取消" << endl;
        }
    } else {
        cout << "【错误】：查无此id: " << tempId << " 对应的参赛选手信息"
             << endl;
    }

    system("pause");
    return (int)(this->m_contestants.size());
}

void ContestantManager::modifyContestantInfo() {
    // 检查是否已经有选手
    if (this->m_contestants.size() == 0) {
        cout << "【警告】：当前还没有招募到参赛选手，请先招募参赛选手。"
             << endl;
        system("pause");
        return;
    }

    m_isSaveContestantInfo = false;
    system("cls");
    cout << "------------- 演讲比赛管理系统v1.0 -------------\n"
         << "|                 选手信息管理                 |\n"
         << "|[4] - 修改选手信息                            |\n"
         << "------------------------------------------------" << endl;
    getchar();
    string tempStr;
    cout << "请输入待修改参赛选手的姓名或id：";
    getline(cin, tempStr);
    // 判断输入是否为id，如果是id执行
    if (tempStr.size() == 18 && isdigit(tempStr[0])) {      
        vector<ContestantType>::iterator retIter =
            this->findContestantId(tempStr);
        if (retIter == this->m_contestants.end()) {
            cout << "【错误】：查无此id: " << tempStr
                 << " 对应的参赛选手信息，请重试。" << endl;
            system("pause");
            return;
        }
        cout << "【提醒】：待修改参赛选手信息如下：\n"
             << "name:" << right << setw(20) << fixed << retIter->name
             << "\tage: " << retIter->age << "\tid: " << retIter->id << endl;
        while (true) {
            getchar();
            cout << "\n请输入新的参赛选手的姓名，年龄，和id("
                    "用逗号分隔，如：xxx,xx,xxxxx)"
                 << endl;
            getline(cin, tempStr);
            vector<string> result = Utils::Utils::strSplit(tempStr, ',');
            if (result.size() != 3) {
                cout << "【错误】：输入格式不正确，请检查后重试。" << endl;
                continue;
            }

            retIter->name = result[0];
            retIter->age = stoi(result[1]);
            retIter->id = result[2];
            break;
        }
    } else {    // 如果不是id，则执行本段
        vector<vector<ContestantType>::iterator> retIters =
            this->findContestantName(tempStr);
        if (retIters.size() == 0) {
            cout << "【错误】：查无此姓名: " << tempStr
                 << " 对应的参赛选手信息，请重试。" << endl;
            system("pause");
            return;
        }
        cout << "【提醒】：查找到如下同名参赛选手信息，请选择对应序号进行修改："
             << endl;
        for (auto it = retIters.begin(); it != retIters.end(); it++) {
            int index = (int)(it - retIters.begin());
            cout << "[" << right << setw(4) << fixed << index + 1 << "/ "
                 << left << setw(4) << fixed << this->m_num << "]: "
                 << "name: " << right << setw(20) << fixed << (*it)->name
                 << "\tage: " << (*it)->age << "\tid: " << (*it)->id << endl;
        }
        int chooseContestant;
        while (true) {
            cin >> chooseContestant;
            if (chooseContestant > retIters.size()) {
                cout << "【错误】：输入有误，序号不应大于" << retIters.size()
                     << "，请重新选择序号：" << endl;
                continue;
            }
            break;
        }

        while (true) {
            getchar();
            cout << "\n请输入新的参赛选手的姓名，年龄，和id("
                    "用逗号分隔，如：xxx,xx,xxxxx)"
                 << endl;
            getline(cin, tempStr);
            vector<string> result = Utils::Utils::strSplit(tempStr, ',');
            if (result.size() != 3) {
                cout << "【错误】：输入格式不正确，请检查后重试。" << endl;
                continue;
            }

            retIters[chooseContestant-1]->name = result[0];
            retIters[chooseContestant-1]->age = stoi(result[1]);
            retIters[chooseContestant-1]->id = result[2];
            break;
        }
    }

    cout << "【提醒】：参赛选手信息修改成功！" << endl;
    system("pause");
}

void ContestantManager::saveContestantInfo() {
    // 检查是否已经有选手
    if (this->m_contestants.size() == 0) {
        cout << "【警告】：当前还没有招募到参赛选手，请先招募参赛选手。"
             << endl;
        system("pause");
        return;
    }
    string filePath = "./data/contestant_info/default.csv";

    ofstream ofs;
    ofs.open(filePath.c_str(), std::ios::out | std::ios::trunc);
    if (!ofs.is_open()) {
        cout << "【错误】：文件不存在：" << filePath << endl;
        return;
    }

    for (auto it = this->m_contestants.begin(); it != this->m_contestants.end(); it++) {
        ofs << it->name << "," << it->age << "," << it->id << endl;
    }

    ofs.close();

    m_isSaveContestantInfo = true;
    cout << "【提醒】：参赛选手信息保存成功。" << endl;
    system("pause");
}

void ContestantManager::saveContestantInfo(const string &timestamp) {
    // 检查是否已经有选手
    if (this->m_contestants.size() == 0) {
        cout << "【警告】：当前还没有招募到参赛选手，请先招募参赛选手。"
             << endl;
        system("pause");
        return;
    }

    string filePath = "./data/contestant_info/" + timestamp + ".csv";

    ofstream ofs;
    ofs.open(filePath.c_str(), std::ios::out | std::ios::trunc);
    if (!ofs.is_open()) {
        cout << "【错误】：文件不存在：" << filePath << endl;
        return;
    }

    for (auto it = this->m_contestants.begin(); it != this->m_contestants.end();
         it++) {
        ofs << it->name << "," << it->age << "," << it->id << endl;
    }

    ofs.close();

    m_isSaveContestantInfo = true;
    cout << "【提醒】：参赛选手信息保存成功。" << endl;
    system("pause");
}

string ContestantManager::makeName() {
    int nameLength = rand() % 2 + 1;

    string lastName = LastNames[rand() % 16];

    string firstName;
    if (nameLength == 1) {
        firstName = MiddleNames[rand() % 16];
    } else {
        string temp1 = MiddleNames[rand() % 16];
        string temp2 = FirstNames[rand() % 16];
        firstName = temp1 + temp2;
    }

    return firstName + " " + lastName;
}

map<string, int> ContestantManager::makeId() {
    // id存储缓存
    char id[24];
    // 获取当前时间
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int currentYear = ltm->tm_year + 1900;

    string idArea = AreaIds[rand() % 3465];
    int idYear = rand() % 51 + 1970;
    int idMonth = rand() % 12 + 1;
    int idDay = 0;
    int idEnd = rand() % 1000;
    int idLast = rand() % 11;
    int age = currentYear - idYear;
    
    if (idMonth == 2) {
        if (isLeapYear(idYear)) {
            idDay = rand() % 29 + 1;
        } else {
            idDay = rand() % 28 + 1;
        }
    } else if (idMonth == 1 || idMonth == 3 || idMonth == 5 || idMonth == 7 ||
               idMonth == 8 || idMonth == 10 || idMonth == 12) {
        idDay = rand() % 31 + 1;
    } else {
        idDay = rand() % 30 + 1;
    }
    
    if (idLast != 10) {
        sprintf(id, "%s%04d%02d%02d%03d%d", idArea.c_str(), idYear, idMonth,
                idDay, idEnd, idLast);
    } else {
        sprintf(id, "%s%04d%02d%02d%03d%c", idArea.c_str(), idYear, idMonth,
                idDay, idEnd, 'x');
    }   

    map<string, int> result;
    result.insert(make_pair(string(id), age));
    return result;
}

bool ContestantManager::isLeapYear(int year) {
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        return true;
    } else {
        return false;
    }
}

vector<ContestantType>::iterator ContestantManager::findContestantId(
    string id) {
    for (auto it = this->m_contestants.begin(); it != this->m_contestants.end(); it++) {
        if (it->id == id) {
            return it;
        }
    }

    return this->m_contestants.end();
}

vector<vector<ContestantType>::iterator> ContestantManager::findContestantName(
    string name) {
    vector<vector<ContestantType>::iterator> results;
    for (auto it = this->m_contestants.begin(); it != this->m_contestants.end(); it++) {
        if (it->name == name) {
            results.push_back(it);
        }
    }

    return results;
}

void ContestantManager::loadContestantInfo() {
    m_isSaveContestantInfo = true;
    string filePath = "./data/contestant_info/default.csv";

    ifstream ifs;
    ifs.open(filePath.c_str(), std::ios::in);
    if (!ifs.is_open()) {
        this->m_contestants.clear();
        this->m_num = 0;
        return;
    }

    // 重置
    this->m_contestants.clear();
    this->m_num = 0;

    string line;
    while (getline(ifs, line)) {
        vector<string> results = Utils::Utils::strSplit(line, ',');
        if (results.size() == 3) {
            ContestantType tempContestant;
            tempContestant.name = results[0];
            tempContestant.age = std::stoi(results[1]);
            tempContestant.id = results[2];
            this->m_contestants.push_back(tempContestant);
            this->m_num++;
        }
    }
}

void ContestantManager::loadContestantInfo(const string &timestamp) {
    m_isSaveContestantInfo = true;
    string filePath = "./data/contestant_info/" + timestamp +".csv";

    ifstream ifs;
    ifs.open(filePath.c_str(), std::ios::in);
    if (!ifs.is_open()) {
        this->m_contestants.clear();
        this->m_num = 0;
        return;
    }

    // 重置
    this->m_contestants.clear();
    this->m_num = 0;

    string line;
    while (getline(ifs, line)) {
        vector<string> results = Utils::Utils::strSplit(line, ',');
        if (results.size() == 3) {
            ContestantType tempContestant;
            tempContestant.name = results[0];
            tempContestant.age = std::stoi(results[1]);
            tempContestant.id = results[2];
            this->m_contestants.push_back(tempContestant);
            this->m_num++;
        }
    }
}

vector<ContestantType> ContestantManager::getContestantsInfo() {
    return this->m_contestants;
}
