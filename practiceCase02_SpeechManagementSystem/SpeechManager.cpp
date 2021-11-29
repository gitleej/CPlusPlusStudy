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
                break;
            }
            case 6:  // [6] - ��ձ�����¼
            {
                break;
            }
            case 0:  // [0] - �˳�    ϵͳ
            {
                exitSystem();
                break;
            }
            default: {
                cout << "�����󡿣���������������ѡ��" << endl;
                system("pause");
                break;
            }
        }
    }
}

void SpeechManager::continueContest() {
    coutHistoryRecord(this->m_historyRecord);
    cout << "��ѡ����Ҫ�������еı�����ţ�" << endl;
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
        string filename = it->begin()->first;
        ContestProcessType contestProcess = it->begin()->second;
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
        ofs << it->begin()->first << "," << it->begin()->second << endl;
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
    // ����Ƿ������ʷ��¼�������ڼ���ӣ����ڼ��޸���ʷ��¼��״̬
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
    cout << "�����ѡ������ڽ��г���..." << endl;
    vector<ContestantType> contestants =
        this->m_contestantManager->getContestantsInfo();
    // ���������������Ԥ�ں�ѡ��������˳��ȡ
    vector<ContestantType> finalContestants(
        contestants.begin(),
        contestants.begin() + this->m_speechRule->m_auditionNum);
    // ����
    getGroup(finalContestants);
    // ����
    for (auto it = this->m_contestantsGroup.begin();
         it != this->m_contestantsGroup.end(); it++) {
        cout << "�����ѡ����� "
             << int(it - this->m_contestantsGroup.begin() + 1)
             << " �����ڽ��б���..." << endl;
        vector<ContestantType> groupResult = startGame(*it, 0);
        this->m_contestantsRematch.insert(this->m_contestantsRematch.end,
                                          groupResult.begin(),
                                          groupResult.end());
        cout << "�����ѡ����� "
             << int(it - this->m_contestantsGroup.begin() + 1)
             << " �������ɡ�" << endl;
    }
    cout << "�����ѡ�������������" << endl;
}

void SpeechManager::startRematch() {
    cout << "�����ѡ������ڽ��и���..." << endl;
}

void SpeechManager::startFinals() {
    cout << "�����ѡ������ڽ��о���..." << endl;
}

void SpeechManager::getGroup(vector<ContestantType> &src) {
    cout << "�����ѡ������ڽ��б�������..." << endl;
    // �������
    auto rng = std::default_random_engine{};
    shuffle(src.begin(), src.end(), rng);

    // ����
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
    cout << "�����ѡ�������������ɡ�" << endl;
}

vector<ContestantType> SpeechManager::startGame(vector<ContestantType> &src, int level) {
    map<float, ContestantType, greater<float>> groupResult;
    for (auto it = src.begin(); it != src.end(); it++) {
        float score = judge();
        it->score.preliminaryScore = score;
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
