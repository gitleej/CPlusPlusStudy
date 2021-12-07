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
    const vector<pair<string, ContestProcessType>> &src) {
    int index = 0;
    for (auto it = src.begin(); it != src.end(); it++) {
        index++;
        cout << "[" << right << setw(4) << fixed << index << "/" << left
             << setw(4) << fixed << src.size() << "]: " << it->first
             << "\t" << it->second << endl;
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
                reviewHistory(this->m_contestStartTimestamp);
                break;
            }
            case 6:  // [6] - 清空比赛记录
            {
                removeHistory(this->m_contestStartTimestamp);
                break;
            }
            case 0:  // [0] - 退出    系统
            {
                // exitSystem();
                break;
            }
            default: {
                cout << "【错误】：输入有误，请重新选择！" << endl;
                system("pause");
                break;
            }
        }
        if (choise == 0) {
            if (this->m_unfinishedContests.size() == 0) {
                exitSystem();
            } else {
                break;
            }
        }
    }
}

void SpeechManager::continueContest() {
    coutHistoryRecord(m_unfinishedContests);
    cout << "请选择需要继续进行的比赛序号：" << endl;
    int whichContest = 0;
    vector<pair<string, ContestProcessType>>::iterator iter =
        this->m_unfinishedContests.begin();
    cin >> whichContest;
    iter = (iter + whichContest - 1);
    
    // 时间戳
    this->m_contestStartTimestamp = iter->first;
    // 比赛进度
    this->m_contestProcess = iter->second;
    // 加载数据
    switch (this->m_contestProcess) {
        case REMATCH: { // 加载复赛结果
            ;
        }
        case PRELIMINARY: { // 加载初赛结果
            ;
        }
        case RECRUITING_CONTESTANTS: { // 加载所有参赛选手数据
            this->m_contestantManager->loadContestantInfo(
                this->m_contestStartTimestamp);
        }
        case PUBLISHING_RULES: { // 加载比赛规则
            this->m_speechRule->loadRule(this->m_contestStartTimestamp);
            break;
        }
        default: break;
    }
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

void SpeechManager::reviewHistory() {
    if (this->m_contestProcess == PUBLISHING_RULES ||
        this->m_contestProcess == RECRUITING_CONTESTANTS ||
        this->m_contestProcess == OTHERS) {
        cout << "【提醒】：比赛尚未开始，还没有比赛记录。" << endl;
        system("pause");
        return;
    }

    loadContestResult(this->m_contestStartTimestamp);
    switch (this->m_contestProcess) {
        default: break;
    }
}

void SpeechManager::reviewHistory(const string &timestamp) {
    if (this->m_contestProcess == PUBLISHING_RULES ||
        this->m_contestProcess == RECRUITING_CONTESTANTS ||
        this->m_contestProcess == OTHERS) {
        cout << "【提醒】：比赛尚未开始，还没有比赛记录。" << endl;
        system("pause");
        return;
    }

    // 加载比赛记录结果
    loadContestResult(timestamp);

    // 选择查看级别
    int choise = 0;
    bool resultRange = true;
    cout << "【提醒】：请选择比赛级别(0-初赛，1-复赛，2-决赛)：" << endl;
    cin >> choise;
    cout << "【提醒】：请选择比赛结果查看范围(0-晋级选手结果，1-所有选手结果)："
         << endl;
    cin >> resultRange;
    switch (choise) {
        case 0:{// 显示初赛成绩
            showResultRecord(0, resultRange, this->m_resultRecord[0]);
            break;
        }
        case 1:{// 显示复赛成绩
            showResultRecord(1, resultRange, this->m_resultRecord[1]);
            break;
        }
        case 2:{// 显示决赛成绩
            showResultRecord(2, resultRange, this->m_resultRecord[2]);
            break;
        }
        default: break;
    }
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
        string filename = it->first;
        ContestProcessType contestProcess = it->second;
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

void SpeechManager::removeHistory(const string &timestamp) {
    cout << "【警告】：确认要清除当前比赛记录？(y/n)：" << endl;
    getchar();
    char choise = getchar();
    if ('y' != choise) {
        cout << "【提醒】：清除当前比赛记录操作已取消。" << endl;
        system("pause");
        return;
    }

    // 规则文件路径
    string ruleFilePath = "./data/rules/" + timestamp + ".csv";
    // 比赛结果文件路径
    string contestResultFilePath = "./data/contest_result/" + timestamp + ".csv";
    // 参赛选手信息文件路径
    string contestantInfoFilePath =
        "./data/contestant_info/" + timestamp + ".csv";

    // 返回值
    int ret = 0;
    // 清除比赛规则
    ret = remove(ruleFilePath.c_str());
    if (0 != ret) {
        cout << "【错误】：文件不存在！" << ruleFilePath << endl;
    }

    // 清除参赛选手xinx
    if (this->m_contestProcess != PUBLISHING_RULES) {
        ret = remove(contestantInfoFilePath.c_str());
        if (0 != ret) {
            cout << "【错误】：文件不存在！" << contestantInfoFilePath << endl;
        }
    }

    // 清除比赛结果
    if (this->m_contestProcess != RECRUITING_CONTESTANTS &&
        this->m_contestProcess != PUBLISHING_RULES) {
        ret = remove(contestResultFilePath.c_str());
        if (0 != ret) {
            cout << "【错误】：文件不存在！" << contestResultFilePath << endl;
        }
    }

    // this->m_historyRecord.erase(timestamp);
    for (auto it = this->m_historyRecord.begin(); it != this->m_historyRecord.end(); it++) {
        if (it->first == timestamp) {
            this->m_historyRecord.erase(it);
            break;
        }
    }
    // this->m_unfinishedContests.erase(timestamp);
    for (auto it = this->m_unfinishedContests.begin(); it != this->m_unfinishedContests.end(); it++) {
        if (it->first == timestamp) {
            this->m_unfinishedContests.erase(it);
            break;
        }
    }
    this->m_contestProcess = OTHERS;
    this->m_isSetRule = false;
    this->m_contestStartTimestamp.clear();
    this->m_contestantsFinals.clear();
    this->m_contestantsGroup.clear();
    this->m_contestantsRematch.clear();
    this->m_contestantsRematchGroup.clear();
    saveHistoryRecord();

    cout << "【提醒】：当前比赛记录已成功清除。" << endl;

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
        ofs << it->first << "," << it->second << endl;
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
                // this->m_historyRecord.insert(make_pair(tempStrs[0], FINALS));
                this->m_historyRecord.push_back(make_pair(tempStrs[0], FINALS));
                break;
            }
            case 1: {
                /*this->m_historyRecord.insert(
                    make_pair(tempStrs[0], PUBLISHING_RULES));
                this->m_unfinishedContests.insert(
                    make_pair(tempStrs[0], PUBLISHING_RULES));*/
                this->m_historyRecord.push_back(
                    make_pair(tempStrs[0], PUBLISHING_RULES));
                this->m_unfinishedContests.push_back(
                    make_pair(tempStrs[0], PUBLISHING_RULES));
                break;
            }
            case 2: {
                /*this->m_historyRecord.insert(
                    make_pair(tempStrs[0], RECRUITING_CONTESTANTS));
                this->m_unfinishedContests.insert(
                    make_pair(tempStrs[0], RECRUITING_CONTESTANTS));*/
                this->m_historyRecord.push_back(
                    make_pair(tempStrs[0], RECRUITING_CONTESTANTS));
                this->m_unfinishedContests.push_back(
                    make_pair(tempStrs[0], RECRUITING_CONTESTANTS));
                break;
            }
            case 3: {
                /*this->m_historyRecord.insert(
                    make_pair(tempStrs[0], PRELIMINARY));
                this->m_unfinishedContests.insert(
                    make_pair(tempStrs[0], PRELIMINARY));*/
                this->m_historyRecord.push_back(
                    make_pair(tempStrs[0], PRELIMINARY));
                this->m_unfinishedContests.push_back(
                    make_pair(tempStrs[0], PRELIMINARY));
                break;
            }
            case 4: {
                map<string, ContestProcessType> tempMap;
                tempMap.insert(make_pair(tempStrs[0], REMATCH));
                /*this->m_historyRecord.insert(make_pair(tempStrs[0], REMATCH));
                this->m_unfinishedContests.insert(
                    make_pair(tempStrs[0], REMATCH));*/
                this->m_historyRecord.push_back(make_pair(tempStrs[0], REMATCH));
                this->m_unfinishedContests.push_back(
                    make_pair(tempStrs[0], REMATCH));
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
        if (it->first == timestamp) {
            it->second = contestProcess;
            break;
        }
    }
    if (it == this->m_historyRecord.end()) {
        this->m_historyRecord.push_back(make_pair(timestamp, contestProcess));
    }

    auto unfinishedIter = this->m_unfinishedContests.begin();
    for (; unfinishedIter != this->m_unfinishedContests.end(); unfinishedIter++) {
        if ((unfinishedIter->first == timestamp) &&
            (contestProcess != FINALS)) {
            unfinishedIter->second = contestProcess;
            break;
        } else if ((unfinishedIter->first == timestamp) &&
                   (contestProcess == FINALS)) {
            this->m_unfinishedContests.erase(unfinishedIter);
        }
    }
    if (unfinishedIter == this->m_unfinishedContests.end() && contestProcess != FINALS) {
        this->m_unfinishedContests.push_back(
            make_pair(timestamp, contestProcess));
    }

    //this->m_historyRecord[timestamp] = contestProcess;
    //// this->m_historyRecord.insert(make_pair(timestamp, contestProcess));
    //if (contestProcess != FINALS) {
    //    this->m_unfinishedContests[timestamp] = contestProcess;
    //    // this->m_unfinishedContests.insert(make_pair(timestamp, contestProcess));
    //} else {
    //    this->m_unfinishedContests.erase(timestamp);
    //}
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
    getGroup(0, finalContestants, this->m_contestantsGroup);
    // 比赛
    for (auto it = this->m_contestantsGroup.begin();
         it != this->m_contestantsGroup.end(); it++) {
        cout << "【提醒】：第 "
             << int(it - this->m_contestantsGroup.begin() + 1)
             << " 组正在进行比赛..." << endl;
        vector<ContestantType> groupResult = startGame(*it, 0);
        this->m_contestantsRematch.insert(this->m_contestantsRematch.end(),
                                          groupResult.begin(),
                                          groupResult.end());
        cout << "【提醒】：第 "
             << int(it - this->m_contestantsGroup.begin() + 1)
             << " 组比赛完成。" << endl;
    }
    cout << "【提醒】：初赛结束。" << endl;

    // 保存比赛结果
    this->saveContestResult(0, m_contestantsGroup, m_contestantsRematch);
}

void SpeechManager::startRematch() {
    cout << "【提醒】：正在进行复赛..." << endl;
    // 分组
    getGroup(1, this->m_contestantsRematch, this->m_contestantsRematchGroup);
    // 比赛
    for (auto it = this->m_contestantsRematchGroup.begin(); it != this->m_contestantsRematchGroup.end(); it++) {
        cout << "【提醒】：第 "
             << int(it - this->m_contestantsRematchGroup.begin() + 1)
             << " 组正在进行比赛..." << endl;
        vector<ContestantType> groupResult = startGame(*it, 1);
        this->m_contestantsFinals.insert(this->m_contestantsFinals.end(),
                                          groupResult.begin(),
                                          groupResult.end());
        cout << "【提醒】：第 "
             << int(it - this->m_contestantsRematchGroup.begin() + 1)
             << " 组比赛完成。" << endl;
    }

    cout << "【提醒】：复赛结束。" << endl;
    // 保存比赛结果
    this->saveContestResult(1, m_contestantsRematchGroup, m_contestantsFinals);
}

void SpeechManager::startFinals() {
    cout << "【提醒】：正在进行决赛..." << endl;
    vector<ContestantType> finalsResult =
        startGame(this->m_contestantsFinals, 2);
    cout << "【提醒】：决赛结束。" << endl;
    
    // 保存比赛结果
    vector<vector<ContestantType>> finalsGroup;
    finalsGroup.push_back(m_contestantsFinals);
    this->saveContestResult(2, finalsGroup, finalsResult);
}

void SpeechManager::getGroup(int level, vector<ContestantType> &src, vector<vector<ContestantType>> &contestantsGroup) {
    cout << "【提醒】：正在进行比赛分组..." << endl;
    // 随机打乱
    auto rng = std::default_random_engine{};
    shuffle(src.begin(), src.end(), rng);

    // 分组
    vector<ContestantType> tempMap;
    for (auto it = src.begin(); it != src.end(); it++) {
        int index = (int)(it - src.begin());
        if (level == 0) {
            it->score = {0.f, 0.f, 0.f};
            if (index % (this->m_speechRule->m_auditionNum / this->m_speechRule->m_auditionGrpNum) == 0 &&
                tempMap.size() != 0) {
                contestantsGroup.push_back(tempMap);
                tempMap.clear();
            }
        } else if (level == 1) {
            if (index % (this->m_speechRule->m_semi_finalsNum / this->m_speechRule->m_sfGrpNum) == 0 &&
                tempMap.size() != 0) {
                contestantsGroup.push_back(tempMap);
                tempMap.clear();
            }
        }
        
        tempMap.push_back(*it);
    }
    contestantsGroup.push_back(tempMap);
    cout << "【提醒】：比赛分组完成。" << endl;
}

vector<ContestantType> SpeechManager::startGame(vector<ContestantType> &src, int level) {
    map<float, ContestantType, greater<float>> groupResult;
    for (auto it = src.begin(); it != src.end(); it++) {
        float score = judge();
        if (level == 0) {
            it->score.preliminaryScore = score;
        } else if (level == 1) {
            it->score.rematchScore = score;
        } else {
            it->score.finalsScore = score;
        }
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

void SpeechManager::saveContestResult(
    const int level,
    const vector<vector<ContestantType>> &groupedContestants,
    const vector<ContestantType> &nextContestants) {
    string filepath =
        "./data/contest_result/" + this->m_contestStartTimestamp + ".csv";

    // 检查文件是否存在
    ifstream ifs(filepath.c_str());
    ofstream ofs;
    if (!ifs) {
        ofs.open(filepath.c_str(), std::ios::out | std::ios::trunc);
    } else {
        ofs.open(filepath.c_str(), std::ios::out | std::ios::app);
    }
    if (!ofs.is_open()) {
        cout << "【错误】：文件不存在。" << filepath << endl;
        return;
    }

    for (auto it = groupedContestants.begin(); it != groupedContestants.end(); it++) {
        int groupNum = (int)(it - groupedContestants.begin());
        for (auto contestant = (*it).begin(); contestant != (*it).end(); contestant++) {
            vector<ContestantType>::const_iterator iterRet = find(
                nextContestants.begin(), nextContestants.end(), *contestant);
            bool gotoNext = false;
            if (iterRet != nextContestants.end()) {
                gotoNext = true;
            }
            ofs << level << "," 
                << groupNum << "," 
                << contestant->name << ","
                << contestant->age << "," 
                << contestant->id << ","
                << contestant->score.preliminaryScore << ","
                << contestant->score.rematchScore << ","
                << contestant->score.finalsScore << ","
                << gotoNext << endl;
        }
    }

    cout << "【提醒】：比赛结果已保存。" << endl;
    ofs.close();
}


// TODO:
void SpeechManager::loadContestResult(const string &timestamp) {
    string filepath = "./data/contest_result/" + timestamp + ".csv";

    ifstream ifs;
    ifs.open(filepath.c_str(), std::ios::in);
    if (!ifs.is_open()) {
        cout << "【错误】：文件不存在。" << filepath << endl;
        return;
    }

    // 清空缓存
    this->m_resultRecord.clear();

    string line;
    int tempLevel = 0;
    int tempGroup = 0;
    vector<ContestantType> tempGroupVec;        // 同组选手
    vector<ContestantType> tempGroupNextVec;    // 同组晋级选手
    vector<pair<vector<ContestantType>, vector<ContestantType>>> tempLevelVec;  // 同一场比赛选手
    vector<vector<pair<vector<ContestantType>, vector<ContestantType>>>>
        resultRecord;
    while (getline(ifs, line)) {
        vector<string> splitResult = Utils::Utils::strSplit(line, ',');
        int level = stoi(splitResult[0]);
        int group = stoi(splitResult[1]);
        ContestantType contestant;
        contestant.name = splitResult[2];
        contestant.age = stoi(splitResult[3]);
        contestant.id = splitResult[4];
        contestant.score.preliminaryScore = stof(splitResult[5]);
        contestant.score.rematchScore = stof(splitResult[6]);
        contestant.score.finalsScore = stof(splitResult[7]);
        bool gotoNext = stoi(splitResult[8]);

        if (tempGroup != group) {
            tempLevelVec.push_back(make_pair(tempGroupVec, tempGroupNextVec));
            tempGroup = group;
            tempGroupVec.clear();
            tempGroupNextVec.clear();
        }

        if (tempLevel != level) {
            resultRecord.push_back(tempLevelVec);
            tempLevel = level;
            tempLevelVec.clear();
        }

        tempGroupVec.push_back(contestant);
        if (gotoNext) {
            tempGroupNextVec.push_back(contestant);
        }
    }
    tempLevelVec.push_back(make_pair(tempGroupVec, tempGroupNextVec));
    resultRecord.push_back(tempLevelVec);
    this->m_resultRecord = resultRecord;

    ifs.close();
}

void SpeechManager::showResultRecord(int level, bool isAll,
    const vector<pair<vector<ContestantType>, vector<ContestantType>>> &src) {
    if (isAll) {
        for (auto it = src.begin(); it != src.end(); it++) {
            vector<ContestantType> groupData = it->first;
            int group = int(it - src.begin()) + 1;
            if (level != 2) {
                cout << "第 " << group << " 组参赛选手比赛结果：" << endl;
            } else {
                cout << "决赛结果：" << endl;
            }
            
            for (auto contestant = groupData.begin(); contestant != groupData.end(); contestant++) {
                cout << "[" << right << setw(2) << fixed
                     << int(contestant - groupData.begin()) + 1 << "/" << left
                     << setw(2) << fixed << groupData.size()
                     << "]: " << *contestant << endl;
            }
            system("pause");
        }
    } else {
        for (auto it = src.begin(); it != src.end(); it++) {
            vector<ContestantType> groupGotoNextData = it->second;
            int group = int(it - src.begin()) + 1;
            if (level != 2) {
                cout << "第 " << group << " 组晋级结果：" << endl;
                for (auto contestant = groupGotoNextData.begin();
                     contestant != groupGotoNextData.end(); contestant++) {
                    cout << "[" << right << setw(2) << fixed
                         << int(contestant - groupGotoNextData.begin()) + 1
                         << "/" << left << setw(2) << fixed
                         << groupGotoNextData.size() << "]: " << *contestant
                         << endl;
                }
            } else {
                cout << "决赛结果：" << endl;
                map<float, ContestantType, greater<float>> tempMap;
                for (auto  contestant = groupGotoNextData.begin(); contestant != groupGotoNextData.end(); contestant++) {
                    tempMap.insert(
                        make_pair(contestant->score.finalsScore, *contestant));
                }
                int count = 0;
                for (auto mapIter = tempMap.begin(); mapIter != tempMap.end(); mapIter++) {
                    if (count == 0) {
                        cout << "***冠军***\n" << mapIter->second << endl;
                    } else if(count == 1) {
                        cout << "**亚军**\n" << mapIter->second << endl;
                    } else {
                        cout << "*季军*\n" << mapIter->second << endl;
                    }
                    count++;
                }
            }
            system("pause");
        }
    }
    
}
