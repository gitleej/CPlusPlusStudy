#include "SpeechManager.h"

SpeechManager::SpeechManager()
    : m_speechRule(new SpeechRule),
      m_isSetRule(false),
      m_contestantManager(new ContestantManager),
      m_contestStartTimestamp(""),
      m_contestProcess(OTHERS) {
    this->loadHistoryRecode();
}

SpeechManager::~SpeechManager() {}

void SpeechManager::showMenu(MenuType menuType) {
    switch (menuType) {
        case MAIN_MENU: {
            showMainMenu();
            break;
        }
        case CONTINUE_MENU: {
            showContinueMenu();
        }
        default: break;
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

    // 开始新比赛，记录比赛开始时间戳
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char timestamp[24];

    sprintf(timestamp, "%04d%02d%02d%02d%02d%02d", 1900 + ltm->tm_year,
            1 + ltm->tm_mon, ltm->tm_mday, ltm->tm_hour, ltm->tm_min,
            ltm->tm_sec);
    this->m_contestStartTimestamp = timestamp;

    while (true) {
        showMainMenu();
        int choise = -1;
        // 接受菜单参数
        cout << "请输入您的选择：" << endl;
        cin >> choise;

        switch (choise) {
            case 1:  // [1] - 发布比赛规则
            {
                publishRules(this->m_contestStartTimestamp);
                break;
            }
            case 2:  // [2] - 查看比赛规则
            {
                showRules();
                break;
            }
            case 3:  // [3] - 选手信息管理
            {
                contestantMangement(this->m_contestStartTimestamp);
                break;
            }
            case 4:  // [4] - 开始演讲比赛
            {
                startContest();
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

void SpeechManager::publishRules(const string &timestamp) {
    if (this->m_isSetRule) {
        cout << "【提醒】：已发布规则，无需重复发布，请前往查看规则。" << endl;
        system("pause");
        return;
    }

    this->m_speechRule->setRule();
    this->m_speechRule->saveRule(timestamp);
    this->m_isSetRule = true;
    this->m_contestProcess = PUBLISHING_RULES;
    // 检查是否存在历史记录，不存在即添加，存在即修改历史记录的状态
    this->checkRecordExist(timestamp, this->m_contestProcess);
    // 保存历史记录进度
    this->saveHistoryRecord();
}

void SpeechManager::showRules() {
    if (m_isSetRule) {
        this->m_speechRule->showRules();
    } else {
        cout << "错误！尚未发布比赛规则！请先发布比赛规则。" << endl;
    }
    system("pause");
}

void SpeechManager::contestantMangement() {
    m_contestantManager->loadContestantInfo();

    int choise = -1;
    while (true) {
        this->m_contestantManager->showMenu();
        cout << "请输入你的选择：";
        cin >> choise;
        switch (choise) {
            case 1: {
                m_contestantManager->addContestantInfo();
                break;
            }
            case 2: {
                m_contestantManager->viewContestantInfo();
                break;
            }
            case 3: {
                m_contestantManager->deletContestantInfo();
                break;
            }
            case 4: {
                m_contestantManager->modifyContestantInfo();
                break;
            }
            case 5: {
                m_contestantManager->saveContestantInfo();
                break;
            }
            default: break;
        }

        if (choise == 0) {
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

void SpeechManager::contestantMangement(const string &timestamp) {
    // 检查是否已发布规则，未发布规则不能进行选手招募
    if (!this->m_isSetRule) {
        cout << "【警告】：尚未发布规则，无法进行参赛选手进行管理，请先发布规则"
                "。"
             << endl;
        system("pause");
        return;
    }

    m_contestantManager->loadContestantInfo(timestamp);

    int choise = -1;
    while (true) {
        this->m_contestantManager->showMenu();
        cout << "请输入你的选择：";
        cin >> choise;
        switch (choise) {
            case 1: {
                int totalNum = m_contestantManager->addContestantInfo();
                if (totalNum >= this->m_speechRule->m_auditionNum) {
                    this->m_contestProcess = RECRUITING_CONTESTANTS;
                }
                break;
            }
            case 2: {
                m_contestantManager->viewContestantInfo();
                break;
            }
            case 3: {
                int totalNum = m_contestantManager->deletContestantInfo();
                if (totalNum >= this->m_speechRule->m_auditionNum) {
                    this->m_contestProcess = RECRUITING_CONTESTANTS;
                } else {
                    this->m_contestProcess = PUBLISHING_RULES;
                }
                break;
            }
            case 4: {
                m_contestantManager->modifyContestantInfo();
                break;
            }
            case 5: {
                m_contestantManager->saveContestantInfo(timestamp);
                break;
            }
            default: break;
        }

        if (choise == 0) {
            if (!m_contestantManager->m_isSaveContestantInfo) {
                getchar();
                cout << "【警告】：有参赛选手信息改动未保存，请确认是否保存(y/"
                        "n)：";
                char confime = getchar();
                if (confime == 'y') {
                    m_contestantManager->saveContestantInfo(timestamp);
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

    // 检查是否存在历史记录，不存在即添加，存在即修改历史记录的状态
    this->checkRecordExist(timestamp, this->m_contestProcess);
    // 保存历史记录进度
    this->saveHistoryRecord();
}

void SpeechManager::startContest() {
    // 根据比赛进程分别进入到不同的比赛阶段
    switch (this->m_contestProcess) {
        case PUBLISHING_RULES: {
            cout << "【警告】：尚未进行参赛选手招募或参赛选手不足，无法开始比赛"
                    "！"
                 << endl;
            break;
        }
        case RECRUITING_CONTESTANTS:{
            // 开始初赛
            startPreliminary();
            cout << "【提醒】：是否继续进行比赛(y/n)：" << endl;
            getchar();
            char confime = getchar();
            if ('n' == confime) {
                // 更新状态
                this->m_contestProcess = PRELIMINARY;
                // 检查是否存在历史记录，不存在即添加，存在即修改历史记录的状态
                this->checkRecordExist(this->m_contestStartTimestamp,
                                       this->m_contestProcess);
                // 保存历史记录进度
                this->saveHistoryRecord();
                break;
            }
        }
        case PRELIMINARY:{
            startRematch();
            cout << "【提醒】：是否继续进行比赛(y/n)：" << endl;
            getchar();
            char confime = getchar();
            if ('n' == confime) {
                // 更新状态
                this->m_contestProcess = REMATCH;
                // 检查是否存在历史记录，不存在即添加，存在即修改历史记录的状态
                this->checkRecordExist(this->m_contestStartTimestamp,
                                       this->m_contestProcess);
                // 保存历史记录进度
                this->saveHistoryRecord();
                break;
            }
        }
        case REMATCH:{
            startFinals();
            // 更新状态
            this->m_contestProcess = FINALS;
            // 检查是否存在历史记录，不存在即添加，存在即修改历史记录的状态
            this->checkRecordExist(this->m_contestStartTimestamp,
                                   this->m_contestProcess);
            // 保存历史记录进度
            this->saveHistoryRecord();
            break;
        }
        case FINALS:{
            cout << "【提醒】：本次比赛已结束，请开始新的比赛。" << endl;
            break;
        }
        default: break;
    }

    system("pause");
}

void SpeechManager::exitSystem() {
    cout << "已退出系统，欢迎下次使用。" << endl;
    exit(0);
}

void SpeechManager::removeHistory() {
    cout << "【警告】：确认要清除所有历史记录？(y/n)：" << endl;
    getchar();
    char choise = getchar();
    if ('y' != choise) {
        cout << "【提醒】：清除所有历史记录操作已取消。" << endl;
        system("pause");
        return;
    }

    // 历史记录文件路径
    string historyFilePath = "./data/history_record.csv";
    for (auto it = this->m_historyRecord.begin();
         it != this->m_historyRecord.end(); it++) {
        string filename = it->begin()->first;
        ContestProcessType contestProcess = it->begin()->second;
        // 规则文件路径
        string ruleFilePath = "./data/rules/" + filename + ".csv";
        // 比赛结果文件路径
        string contestResultFilePath =
            "./data/contest_result/" + filename + ".csv";
        // 参赛选手信息文件路径
        string contestantInfoFilePath =
            "./data/contestant_info/" + filename + ".csv";

        // 返回值
        int ret = 0;
        // 清除比赛规则
        ret = remove(ruleFilePath.c_str());
        if (0 != ret) {
            cout << "【错误】：文件不存在！" << ruleFilePath << endl;
        }

        // 清除参赛选手xinx
        if (contestProcess != PUBLISHING_RULES) {
            ret = remove(contestantInfoFilePath.c_str());
            if (0 != ret) {
                cout << "【错误】：文件不存在！" << contestantInfoFilePath
                     << endl;
            }
        }
        
        // 清除比赛结果
        if (contestProcess != RECRUITING_CONTESTANTS && contestProcess != PUBLISHING_RULES) {
            ret = remove(contestResultFilePath.c_str());
            if (0 != ret) {
                cout << "【错误】：文件不存在！" << contestResultFilePath
                     << endl;
            }
        } 
    }

    ofstream ofs;
    ofs.open(historyFilePath.c_str(), std::ios::out | std::ios::trunc);
    if (!ofs.is_open()) {
        cout << "【错误】：文件不存在！" << historyFilePath << endl;
    }
    ofs.close();

    this->m_historyRecord.clear();
    this->m_unfinishedContests.clear();

    cout << "【提醒】：所有历史记录已成功清除。" << endl;

    system("pause");
}

void SpeechManager::showMainMenu() {
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
         << "------------------------------------------------" << endl;
}

void SpeechManager::showContinueMenu() {
    cout << "------------- 演讲比赛管理系统v1.0 -------------\n"
         << "|                    主菜单                    |\n"
         << "|[1] - 开始新的比赛                            |\n"
         << "|[2] - 继续未完成的比赛                        |\n"
         << "|[3] - 清除历史记录                            |\n"
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

    for (auto it = this->m_historyRecord.begin();
         it != this->m_historyRecord.end(); it++) {
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
            case 0: {
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

void SpeechManager::checkRecordExist(const string &timestamp,
                                     const ContestProcessType &contestProcess) {
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

void SpeechManager::startPreliminary() {
    cout << "【提醒】：正在进行初赛..." << endl;
    vector<ContestantType> contestants =
        this->m_contestantManager->getContestantsInfo();
    // 如果报名人数超过预期海选人数，则按顺序取
    vector<ContestantType> finalContestants(
        contestants.begin(),
        contestants.begin() + this->m_speechRule->m_auditionNum);
    // 分组
    getGroup(finalContestants);
    // 比赛
    for (auto it = this->m_contestantsGroup.begin();
         it != this->m_contestantsGroup.end(); it++) {
        cout << "【提醒】：第 "
             << int(it - this->m_contestantsGroup.begin() + 1)
             << " 组正在进行比赛..." << endl;
        vector<ContestantType> groupResult = startGame(*it, 0);
        this->m_contestantsRematch.insert(this->m_contestantsRematch.end,
                                          groupResult.begin(),
                                          groupResult.end());
        cout << "【提醒】：第 "
             << int(it - this->m_contestantsGroup.begin() + 1)
             << " 组比赛完成。" << endl;
    }
    cout << "【提醒】：初赛结束。" << endl;
}

void SpeechManager::startRematch() {
    cout << "【提醒】：正在进行复赛..." << endl;
}

void SpeechManager::startFinals() {
    cout << "【提醒】：正在进行决赛..." << endl;
}

void SpeechManager::getGroup(vector<ContestantType> &src) {
    cout << "【提醒】：正在进行比赛分组..." << endl;
    // 随机打乱
    auto rng = std::default_random_engine{};
    shuffle(src.begin(), src.end(), rng);

    // 分组
    vector<ContestantType> tempMap;
    for (auto it = src.begin(); it != src.end(); it++) {
        int index = (int)(it - src.begin());
        if (index % this->m_speechRule->m_auditionGrpNum == 0 && tempMap.size() != 0) {
            this->m_contestantsGroup.push_back(tempMap);
            tempMap.clear();
        }
        it->score = {0.f, 0.f, 0.f};
        tempMap.push_back(*it);
    }
    this->m_contestantsGroup.push_back(tempMap);
    cout << "【提醒】：比赛分组完成。" << endl;
}

vector<ContestantType> SpeechManager::startGame(vector<ContestantType> &src, int level) {
    map<float, ContestantType, greater<float>> groupResult;
    for (auto it = src.begin(); it != src.end(); it++) {
        float score = judge();
        it->score.preliminaryScore = score;
        groupResult.insert(make_pair(score, *it));
    }

    // 处理结果
    vector<ContestantType> finalResult;
    int count = 0;
    for (auto it = groupResult.begin(); it != groupResult.end(); it++) {
        if (level == 0) {
            if (count == this->m_speechRule->m_auditionNextNum) {
                break;
            }
            finalResult.push_back(it->second);
            count++;
        }
        else if (level == 1) {
            if (count == this->m_speechRule->m_sfNextNum) {
                break;
            }
            finalResult.push_back(it->second);
            count++;
        } 
        else if (level == 2) {
            if (count == 3) {
                break;
            }
            finalResult.push_back(it->second);
            count++;
        }
    }
    

    // 返回晋级人员
    return finalResult;
}

float SpeechManager::judge() {
    deque<float> judgeScore(10, 0.f);
    for (auto it = judgeScore.begin(); it != judgeScore.end(); it++) {
        float score = (rand() % 41 + 60) / 10.f;
        *it = score;
    }
    // 排序
    sort(judgeScore.begin(), judgeScore.end());
    // 去除最高分和最低分
    judgeScore.pop_front();
    judgeScore.pop_back();
    // 求平均值
    float sum = 0.f;
    for (auto dit = judgeScore.begin(); dit != judgeScore.end(); dit++) {
        sum += (*dit);
    }
    
    float finalScore = float(sum / judgeScore.size());
    return finalScore;
}
