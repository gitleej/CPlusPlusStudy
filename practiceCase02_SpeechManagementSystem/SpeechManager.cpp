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

    // ��ʼ�±�������¼������ʼʱ���
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
        // ���ܲ˵�����
        cout << "����������ѡ��" << endl;
        cin >> choise;

        switch (choise) {
            case 1:  // [1] - ������������
            {
                publishRules(this->m_contestStartTimestamp);
                break;
            }
            case 2:  // [2] - �鿴��������
            {
                showRules();
                break;
            }
            case 3:  // [3] - ѡ����Ϣ����
            {
                contestantMangement(this->m_contestStartTimestamp);
                break;
            }
            case 4:  // [4] - ��ʼ�ݽ�����
            {
                startContest();
                break;
            }
            case 5:  // [5] - �鿴������¼
            {
                reviewHistory(this->m_contestStartTimestamp);
                break;
            }
            case 6:  // [6] - ��ձ�����¼
            {
                removeHistory(this->m_contestStartTimestamp);
                break;
            }
            case 0:  // [0] - �˳�    ϵͳ
            {
                // exitSystem();
                break;
            }
            default: {
                cout << "�����󡿣���������������ѡ��" << endl;
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
    cout << "��ѡ����Ҫ�������еı�����ţ�" << endl;
    int whichContest = 0;
    vector<pair<string, ContestProcessType>>::iterator iter =
        this->m_unfinishedContests.begin();
    cin >> whichContest;
    iter = (iter + whichContest - 1);
    
    // ʱ���
    this->m_contestStartTimestamp = iter->first;
    // ��������
    this->m_contestProcess = iter->second;
    // ��������
    switch (this->m_contestProcess) {
        case REMATCH: { // ���ظ������
            ;
        }
        case PRELIMINARY: { // ���س������
            ;
        }
        case RECRUITING_CONTESTANTS: { // �������в���ѡ������
            this->m_contestantManager->loadContestantInfo(
                this->m_contestStartTimestamp);
        }
        case PUBLISHING_RULES: { // ���ر�������
            this->m_speechRule->loadRule(this->m_contestStartTimestamp);
            break;
        }
        default: break;
    }
    showMainMenu();
}

void SpeechManager::publishRules() {
    if (this->m_isSetRule) {
        cout << "�����ѡ����ѷ������������ظ���������ǰ���鿴����" << endl;
        system("pause");
        return;
    }
    // ��ʼ�±�������¼������ʼʱ���
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
    // ����Ƿ������ʷ��¼�������ڼ���ӣ����ڼ��޸���ʷ��¼��״̬
    this->checkRecordExist(this->m_contestStartTimestamp,
                           this->m_contestProcess);
    // ������ʷ��¼����
    this->saveHistoryRecord();
}

void SpeechManager::publishRules(const string &timestamp) {
    if (this->m_isSetRule) {
        cout << "�����ѡ����ѷ������������ظ���������ǰ���鿴����" << endl;
        system("pause");
        return;
    }

    this->m_speechRule->setRule();
    this->m_speechRule->saveRule(timestamp);
    this->m_isSetRule = true;
    this->m_contestProcess = PUBLISHING_RULES;
    // ����Ƿ������ʷ��¼�������ڼ���ӣ����ڼ��޸���ʷ��¼��״̬
    this->checkRecordExist(timestamp, this->m_contestProcess);
    // ������ʷ��¼����
    this->saveHistoryRecord();
}

void SpeechManager::showRules() {
    if (m_isSetRule) {
        this->m_speechRule->showRules();
    } else {
        cout << "������δ���������������ȷ�����������" << endl;
    }
    system("pause");
}

void SpeechManager::contestantMangement() {
    m_contestantManager->loadContestantInfo();

    int choise = -1;
    while (true) {
        this->m_contestantManager->showMenu();
        cout << "���������ѡ��";
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

void SpeechManager::contestantMangement(const string &timestamp) {
    // ����Ƿ��ѷ�������δ���������ܽ���ѡ����ļ
    if (!this->m_isSetRule) {
        cout << "�����桿����δ���������޷����в���ѡ�ֽ��й������ȷ�������"
                "��"
             << endl;
        system("pause");
        return;
    }

    m_contestantManager->loadContestantInfo(timestamp);

    int choise = -1;
    while (true) {
        this->m_contestantManager->showMenu();
        cout << "���������ѡ��";
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
                cout << "�����桿���в���ѡ����Ϣ�Ķ�δ���棬��ȷ���Ƿ񱣴�(y/"
                        "n)��";
                char confime = getchar();
                if (confime == 'y') {
                    m_contestantManager->saveContestantInfo(timestamp);
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

    // ����Ƿ������ʷ��¼�������ڼ���ӣ����ڼ��޸���ʷ��¼��״̬
    this->checkRecordExist(timestamp, this->m_contestProcess);
    // ������ʷ��¼����
    this->saveHistoryRecord();
}

void SpeechManager::startContest() {
    // ���ݱ������̷ֱ���뵽��ͬ�ı����׶�
    switch (this->m_contestProcess) {
        case PUBLISHING_RULES: {
            cout << "�����桿����δ���в���ѡ����ļ�����ѡ�ֲ��㣬�޷���ʼ����"
                    "��"
                 << endl;
            break;
        }
        case RECRUITING_CONTESTANTS:{
            // ��ʼ����
            startPreliminary();
            cout << "�����ѡ����Ƿ�������б���(y/n)��" << endl;
            getchar();
            char confime = getchar();
            if ('n' == confime) {
                // ����״̬
                this->m_contestProcess = PRELIMINARY;
                // ����Ƿ������ʷ��¼�������ڼ���ӣ����ڼ��޸���ʷ��¼��״̬
                this->checkRecordExist(this->m_contestStartTimestamp,
                                       this->m_contestProcess);
                // ������ʷ��¼����
                this->saveHistoryRecord();
                break;
            }
        }
        case PRELIMINARY:{
            startRematch();
            cout << "�����ѡ����Ƿ�������б���(y/n)��" << endl;
            getchar();
            char confime = getchar();
            if ('n' == confime) {
                // ����״̬
                this->m_contestProcess = REMATCH;
                // ����Ƿ������ʷ��¼�������ڼ���ӣ����ڼ��޸���ʷ��¼��״̬
                this->checkRecordExist(this->m_contestStartTimestamp,
                                       this->m_contestProcess);
                // ������ʷ��¼����
                this->saveHistoryRecord();
                break;
            }
        }
        case REMATCH:{
            startFinals();
            // ����״̬
            this->m_contestProcess = FINALS;
            // ����Ƿ������ʷ��¼�������ڼ���ӣ����ڼ��޸���ʷ��¼��״̬
            this->checkRecordExist(this->m_contestStartTimestamp,
                                   this->m_contestProcess);
            // ������ʷ��¼����
            this->saveHistoryRecord();
            break;
        }
        case FINALS:{
            cout << "�����ѡ������α����ѽ������뿪ʼ�µı�����" << endl;
            break;
        }
        default: break;
    }

    system("pause");
}

void SpeechManager::exitSystem() {
    cout << "���˳�ϵͳ����ӭ�´�ʹ�á�" << endl;
    exit(0);
}

void SpeechManager::reviewHistory() {
    if (this->m_contestProcess == PUBLISHING_RULES ||
        this->m_contestProcess == RECRUITING_CONTESTANTS ||
        this->m_contestProcess == OTHERS) {
        cout << "�����ѡ���������δ��ʼ����û�б�����¼��" << endl;
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
        cout << "�����ѡ���������δ��ʼ����û�б�����¼��" << endl;
        system("pause");
        return;
    }

    // ���ر�����¼���
    loadContestResult(timestamp);

    // ѡ��鿴����
    int choise = 0;
    bool resultRange = true;
    cout << "�����ѡ�����ѡ���������(0-������1-������2-����)��" << endl;
    cin >> choise;
    cout << "�����ѡ�����ѡ���������鿴��Χ(0-����ѡ�ֽ����1-����ѡ�ֽ��)��"
         << endl;
    cin >> resultRange;
    switch (choise) {
        case 0:{// ��ʾ�����ɼ�
            showResultRecord(0, resultRange, this->m_resultRecord[0]);
            break;
        }
        case 1:{// ��ʾ�����ɼ�
            showResultRecord(1, resultRange, this->m_resultRecord[1]);
            break;
        }
        case 2:{// ��ʾ�����ɼ�
            showResultRecord(2, resultRange, this->m_resultRecord[2]);
            break;
        }
        default: break;
    }
}

void SpeechManager::removeHistory() {
    cout << "�����桿��ȷ��Ҫ���������ʷ��¼��(y/n)��" << endl;
    getchar();
    char choise = getchar();
    if ('y' != choise) {
        cout << "�����ѡ������������ʷ��¼������ȡ����" << endl;
        system("pause");
        return;
    }

    // ��ʷ��¼�ļ�·��
    string historyFilePath = "./data/history_record.csv";
    for (auto it = this->m_historyRecord.begin();
         it != this->m_historyRecord.end(); it++) {
        string filename = it->first;
        ContestProcessType contestProcess = it->second;
        // �����ļ�·��
        string ruleFilePath = "./data/rules/" + filename + ".csv";
        // ��������ļ�·��
        string contestResultFilePath =
            "./data/contest_result/" + filename + ".csv";
        // ����ѡ����Ϣ�ļ�·��
        string contestantInfoFilePath =
            "./data/contestant_info/" + filename + ".csv";

        // ����ֵ
        int ret = 0;
        // �����������
        ret = remove(ruleFilePath.c_str());
        if (0 != ret) {
            cout << "�����󡿣��ļ������ڣ�" << ruleFilePath << endl;
        }

        // �������ѡ��xinx
        if (contestProcess != PUBLISHING_RULES) {
            ret = remove(contestantInfoFilePath.c_str());
            if (0 != ret) {
                cout << "�����󡿣��ļ������ڣ�" << contestantInfoFilePath
                     << endl;
            }
        }
        
        // ����������
        if (contestProcess != RECRUITING_CONTESTANTS && contestProcess != PUBLISHING_RULES) {
            ret = remove(contestResultFilePath.c_str());
            if (0 != ret) {
                cout << "�����󡿣��ļ������ڣ�" << contestResultFilePath
                     << endl;
            }
        } 
    }

    ofstream ofs;
    ofs.open(historyFilePath.c_str(), std::ios::out | std::ios::trunc);
    if (!ofs.is_open()) {
        cout << "�����󡿣��ļ������ڣ�" << historyFilePath << endl;
    }
    ofs.close();

    this->m_historyRecord.clear();
    this->m_unfinishedContests.clear();

    cout << "�����ѡ���������ʷ��¼�ѳɹ������" << endl;

    system("pause");
}

void SpeechManager::removeHistory(const string &timestamp) {
    cout << "�����桿��ȷ��Ҫ�����ǰ������¼��(y/n)��" << endl;
    getchar();
    char choise = getchar();
    if ('y' != choise) {
        cout << "�����ѡ��������ǰ������¼������ȡ����" << endl;
        system("pause");
        return;
    }

    // �����ļ�·��
    string ruleFilePath = "./data/rules/" + timestamp + ".csv";
    // ��������ļ�·��
    string contestResultFilePath = "./data/contest_result/" + timestamp + ".csv";
    // ����ѡ����Ϣ�ļ�·��
    string contestantInfoFilePath =
        "./data/contestant_info/" + timestamp + ".csv";

    // ����ֵ
    int ret = 0;
    // �����������
    ret = remove(ruleFilePath.c_str());
    if (0 != ret) {
        cout << "�����󡿣��ļ������ڣ�" << ruleFilePath << endl;
    }

    // �������ѡ��xinx
    if (this->m_contestProcess != PUBLISHING_RULES) {
        ret = remove(contestantInfoFilePath.c_str());
        if (0 != ret) {
            cout << "�����󡿣��ļ������ڣ�" << contestantInfoFilePath << endl;
        }
    }

    // ����������
    if (this->m_contestProcess != RECRUITING_CONTESTANTS &&
        this->m_contestProcess != PUBLISHING_RULES) {
        ret = remove(contestResultFilePath.c_str());
        if (0 != ret) {
            cout << "�����󡿣��ļ������ڣ�" << contestResultFilePath << endl;
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

    cout << "�����ѡ�����ǰ������¼�ѳɹ������" << endl;

    system("pause");
}

void SpeechManager::showMainMenu() {
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
         << "------------------------------------------------" << endl;
}

void SpeechManager::showContinueMenu() {
    cout << "------------- �ݽ���������ϵͳv1.0 -------------\n"
         << "|                    ���˵�                    |\n"
         << "|[1] - ��ʼ�µı���                            |\n"
         << "|[2] - ����δ��ɵı���                        |\n"
         << "|[3] - �����ʷ��¼                            |\n"
         << "|[0] - �˳�    ϵͳ                            |\n"
         << "------------------------------------------------" << endl;
}

void SpeechManager::saveHistoryRecord() {
    string filepath = "./data/history_record.csv";

    ofstream ofs;
    ofs.open(filepath.c_str(), std::ios::out | std::ios::trunc);
    if (!ofs.is_open()) {
        cout << "�����󡿣��ļ������ڡ�" << filepath << endl;
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
        cout << "�����󡿣��ļ������ڡ�" << filepath << endl;
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
    // ����Ƿ������ʷ��¼�������ڼ���ӣ����ڼ��޸���ʷ��¼��״̬
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
    cout << "�����ѡ������ڽ��г���..." << endl;
    vector<ContestantType> contestants =
        this->m_contestantManager->getContestantsInfo();
    // ���������������Ԥ�ں�ѡ��������˳��ȡ
    vector<ContestantType> finalContestants(
        contestants.begin(),
        contestants.begin() + this->m_speechRule->m_auditionNum);
    // ����
    getGroup(0, finalContestants, this->m_contestantsGroup);
    // ����
    for (auto it = this->m_contestantsGroup.begin();
         it != this->m_contestantsGroup.end(); it++) {
        cout << "�����ѡ����� "
             << int(it - this->m_contestantsGroup.begin() + 1)
             << " �����ڽ��б���..." << endl;
        vector<ContestantType> groupResult = startGame(*it, 0);
        this->m_contestantsRematch.insert(this->m_contestantsRematch.end(),
                                          groupResult.begin(),
                                          groupResult.end());
        cout << "�����ѡ����� "
             << int(it - this->m_contestantsGroup.begin() + 1)
             << " �������ɡ�" << endl;
    }
    cout << "�����ѡ�������������" << endl;

    // ����������
    this->saveContestResult(0, m_contestantsGroup, m_contestantsRematch);
}

void SpeechManager::startRematch() {
    cout << "�����ѡ������ڽ��и���..." << endl;
    // ����
    getGroup(1, this->m_contestantsRematch, this->m_contestantsRematchGroup);
    // ����
    for (auto it = this->m_contestantsRematchGroup.begin(); it != this->m_contestantsRematchGroup.end(); it++) {
        cout << "�����ѡ����� "
             << int(it - this->m_contestantsRematchGroup.begin() + 1)
             << " �����ڽ��б���..." << endl;
        vector<ContestantType> groupResult = startGame(*it, 1);
        this->m_contestantsFinals.insert(this->m_contestantsFinals.end(),
                                          groupResult.begin(),
                                          groupResult.end());
        cout << "�����ѡ����� "
             << int(it - this->m_contestantsRematchGroup.begin() + 1)
             << " �������ɡ�" << endl;
    }

    cout << "�����ѡ�������������" << endl;
    // ����������
    this->saveContestResult(1, m_contestantsRematchGroup, m_contestantsFinals);
}

void SpeechManager::startFinals() {
    cout << "�����ѡ������ڽ��о���..." << endl;
    vector<ContestantType> finalsResult =
        startGame(this->m_contestantsFinals, 2);
    cout << "�����ѡ�������������" << endl;
    
    // ����������
    vector<vector<ContestantType>> finalsGroup;
    finalsGroup.push_back(m_contestantsFinals);
    this->saveContestResult(2, finalsGroup, finalsResult);
}

void SpeechManager::getGroup(int level, vector<ContestantType> &src, vector<vector<ContestantType>> &contestantsGroup) {
    cout << "�����ѡ������ڽ��б�������..." << endl;
    // �������
    auto rng = std::default_random_engine{};
    shuffle(src.begin(), src.end(), rng);

    // ����
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
    cout << "�����ѡ�������������ɡ�" << endl;
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

    // ������
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

    // ���ؽ�����Ա
    return finalResult;
}

float SpeechManager::judge() {
    deque<float> judgeScore(10, 0.f);
    for (auto it = judgeScore.begin(); it != judgeScore.end(); it++) {
        float score = (rand() % 41 + 60) / 10.f;
        *it = score;
    }
    // ����
    sort(judgeScore.begin(), judgeScore.end());
    // ȥ����߷ֺ���ͷ�
    judgeScore.pop_front();
    judgeScore.pop_back();
    // ��ƽ��ֵ
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

    // ����ļ��Ƿ����
    ifstream ifs(filepath.c_str());
    ofstream ofs;
    if (!ifs) {
        ofs.open(filepath.c_str(), std::ios::out | std::ios::trunc);
    } else {
        ofs.open(filepath.c_str(), std::ios::out | std::ios::app);
    }
    if (!ofs.is_open()) {
        cout << "�����󡿣��ļ������ڡ�" << filepath << endl;
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

    cout << "�����ѡ�����������ѱ��档" << endl;
    ofs.close();
}


// TODO:
void SpeechManager::loadContestResult(const string &timestamp) {
    string filepath = "./data/contest_result/" + timestamp + ".csv";

    ifstream ifs;
    ifs.open(filepath.c_str(), std::ios::in);
    if (!ifs.is_open()) {
        cout << "�����󡿣��ļ������ڡ�" << filepath << endl;
        return;
    }

    // ��ջ���
    this->m_resultRecord.clear();

    string line;
    int tempLevel = 0;
    int tempGroup = 0;
    vector<ContestantType> tempGroupVec;        // ͬ��ѡ��
    vector<ContestantType> tempGroupNextVec;    // ͬ�����ѡ��
    vector<pair<vector<ContestantType>, vector<ContestantType>>> tempLevelVec;  // ͬһ������ѡ��
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
                cout << "�� " << group << " �����ѡ�ֱ��������" << endl;
            } else {
                cout << "���������" << endl;
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
                cout << "�� " << group << " ����������" << endl;
                for (auto contestant = groupGotoNextData.begin();
                     contestant != groupGotoNextData.end(); contestant++) {
                    cout << "[" << right << setw(2) << fixed
                         << int(contestant - groupGotoNextData.begin()) + 1
                         << "/" << left << setw(2) << fixed
                         << groupGotoNextData.size() << "]: " << *contestant
                         << endl;
                }
            } else {
                cout << "���������" << endl;
                map<float, ContestantType, greater<float>> tempMap;
                for (auto  contestant = groupGotoNextData.begin(); contestant != groupGotoNextData.end(); contestant++) {
                    tempMap.insert(
                        make_pair(contestant->score.finalsScore, *contestant));
                }
                int count = 0;
                for (auto mapIter = tempMap.begin(); mapIter != tempMap.end(); mapIter++) {
                    if (count == 0) {
                        cout << "***�ھ�***\n" << mapIter->second << endl;
                    } else if(count == 1) {
                        cout << "**�Ǿ�**\n" << mapIter->second << endl;
                    } else {
                        cout << "*����*\n" << mapIter->second << endl;
                    }
                    count++;
                }
            }
            system("pause");
        }
    }
    
}
