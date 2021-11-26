#include "SpeechManager.h"

SpeechManager::SpeechManager()
    : m_speechRule(new SpeechRule)
    , m_isSetRule(false)
    , m_contestantManager(new ContestantManager)
    , m_contestStartTimestamp("")
    , m_contestProcess(OTHERS)
{
    this->loadHistoryRecode();
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
    case CONTINUE_MENU: {
        showContinueMenu();
    }
    default:
        break;
    }
}

void SpeechManager::coutHistoryRecord(
    const vector<map<string, ContestProcessType>> &src) {
    for (auto it = src.begin(); it != src.end(); it++) {
        int index = (int)(it - src.begin());
        cout << "[" << right << setw(4) << fixed << index + 1 << "/" << left
             << setw(4) << fixed << src.size() << "]: " << it->begin()->first
             << "\t" << it->begin()->second << endl;
    }
}

void SpeechManager::startNewContest() {
    m_speechRule = new SpeechRule;
    m_isSetRule = false;
    m_contestantManager = new ContestantManager;
    m_contestStartTimestamp = "";
    m_contestProcess = OTHERS;
    while (true) {
        showMainMenu();
        int choise = -1;
        // 接受菜单参数
        cout << "请输入您的选择：" << endl;
        cin >> choise;

        switch (choise) {
            case 1:  // [1] - 发布比赛规则
            {
                publishRules();
                break;
            }
            case 2:  // [2] - 查看比赛规则
            {
                showRules();
                break;
            }
            case 3:  // [3] - 选手信息管理
            {
                contestantMangement();
                break;
            }
            case 4:  // [4] - 开始演讲比赛
            {
                break;
            }
            case 5:  // [5] - 查看比赛记录
            {
                break;
            }
            case 6:  // [6] - 清空比赛记录
            {
                break;
            }
            case 0:  // [0] - 退出    系统
            {
                exitSystem();
                break;
            }
            default: {
                cout << "【错误】：输入有误，请重新选择！" << endl;
                system("pause");
                break;
            }
        }
    }
}

void SpeechManager::continueContest() {
    coutHistoryRecord(this->m_historyRecord);
    cout << "请选择需要继续进行的比赛序号：" << endl;
    showMainMenu();
}

void SpeechManager::publishRules() {
    if (this->m_isSetRule) {
        cout << "【提醒】：已发布规则，无需重复发布，请前往查看规则。" << endl;
        system("pause");
        return;
    }
    // 开始新比赛，记录比赛开始时间戳
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char timestamp[24];

    sprintf(timestamp, "%04d%02d%02d%02d%02d%02d", 1900 + ltm->tm_year,
            1 + ltm->tm_mon, ltm->tm_mday, ltm->tm_hour, ltm->tm_min,
            ltm->tm_sec);
    this->m_contestStartTimestamp = timestamp;

    this->m_speechRule->setRule();
    this->m_speechRule->saveRule(timestamp);
    this->m_isSetRule = true;
    this->m_contestProcess = PUBLISHING_RULES;
    // 检查是否存在历史记录，不存在即添加，存在即修改历史记录的状态
    this->checkRecordExist(this->m_contestStartTimestamp,
                           this->m_contestProcess);
    // 保存历史记录进度
    this->saveHistoryRecord();
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
    cout << "已退出系统，欢迎下次使用。" << endl;
    exit(0);
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

void SpeechManager::showContinueMenu() {
    cout << "------------- 演讲比赛管理系统v1.0 -------------\n"
         << "|                    主菜单                    |\n"
         << "|[1] - 开始新的比赛                            |\n"
         << "|[2] - 继续未完成的比赛                        |\n"
         << "|[0] - 退出    系统                            |\n"
         << "------------------------------------------------" << endl;
}

void SpeechManager::saveHistoryRecord() {
    string filepath = "./data/history_record.csv";

    ofstream ofs;
    ofs.open(filepath.c_str(), std::ios::out | std::ios::trunc);
    if (!ofs.is_open()) {
        cout << "【错误】：文件不存在。" << filepath << endl;
        return;
    }

    for (auto it = this->m_historyRecord.begin(); it != this->m_historyRecord.end(); it++) {
        ofs << it->begin()->first << "," << it->begin()->second << endl;
    }
    
    ofs.close();
}

void SpeechManager::loadHistoryRecode() {
    string filepath = "./data/history_record.csv";

    ifstream ifs;
    ifs.open(filepath.c_str(), std::ios::in);
    if (!ifs.is_open()) {
        cout << "【错误】：文件不存在。" << filepath << endl;
        return;
    }

    this->m_historyRecord.clear();
    string line;
    while (getline(ifs, line)) {
        vector<string> tempStrs = Utils::Utils::strSplit(line, ',');
        switch (stoi(tempStrs[1])) {
            case 0:{
                map<string, ContestProcessType> tempMap;
                tempMap.insert(make_pair(tempStrs[0], FINALS));
                this->m_historyRecord.push_back(tempMap);
                break;
            }
            case 1: {
                map<string, ContestProcessType> tempMap;
                tempMap.insert(make_pair(tempStrs[0], PUBLISHING_RULES));
                this->m_historyRecord.push_back(tempMap);
                this->m_unfinishedContests.push_back(tempMap);
                break;
            }
            case 2: {
                map<string, ContestProcessType> tempMap;
                tempMap.insert(make_pair(tempStrs[0], RECRUITING_CONTESTANTS));
                this->m_historyRecord.push_back(tempMap);
                this->m_unfinishedContests.push_back(tempMap);
                break;
            }
            case 3: {
                map<string, ContestProcessType> tempMap;
                tempMap.insert(make_pair(tempStrs[0], PRELIMINARY));
                this->m_historyRecord.push_back(tempMap);
                this->m_unfinishedContests.push_back(tempMap);
                break;
            }
            case 4: {
                map<string, ContestProcessType> tempMap;
                tempMap.insert(make_pair(tempStrs[0], REMATCH));
                this->m_historyRecord.push_back(tempMap);
                this->m_unfinishedContests.push_back(tempMap);
                break;
            }
            default: break;
        }
    }

    ifs.close();
}

void SpeechManager::checkRecordExist(const string &timestamp, const ContestProcessType &contestProcess) {
    // 检查是否存在历史记录，不存在即添加，存在即修改历史记录的状态
    auto it = this->m_historyRecord.begin();
    for (; it != this->m_historyRecord.end(); it++) {
        if (it->begin()->first == timestamp) {
            (*it)[timestamp] = contestProcess;
            break;
        }
    }
    if (it == this->m_historyRecord.end()) {
        map<string, ContestProcessType> tempMap;
        tempMap.insert(make_pair(timestamp, contestProcess));
        this->m_historyRecord.push_back(tempMap);
    }
}
