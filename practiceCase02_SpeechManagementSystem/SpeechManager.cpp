#include "SpeechManager.h"

SpeechManager::SpeechManager()
    : m_speechRule(new SpeechRule)
    , m_isSetRule(false)
    , m_contestantManager(new ContestantManager)
    , m_contestStartTimestamp("")
    , m_contestProcess(OTHERS)
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
}

void SpeechManager::showRules()
{
    if (m_isSetRule)
    {
        this->m_speechRule->showRules();
    }
    else
    {
        cout << "������δ���������������ȷ�����������" << endl;
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
        cout << "���������ѡ��";
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

void SpeechManager::exitSystem()
{
    exit(0);
    cout << "���˳�ϵͳ����ӭ�´�ʹ�á�" << endl;
}

void SpeechManager::showMainMenu()
{
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
        << "------------------------------------------------"
        << endl;
}

void SpeechManager::saveHistoryRecord() {
    string filepath = "./data/history_record.csv";

    ofstream ofs;
    ofs.open(filepath.c_str(), std::ios::out | std::ios::trunc);
    if (!ofs.is_open()) {
        cout << "�����󡿣��ļ������ڡ�" << filepath << endl;
        return;
    }

    for (auto it = this->m_historyRecord.begin(); it != this->m_historyRecord.end(); it++) {
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
            case 0:{
                this->m_historyRecord.insert(make_pair(tempStrs[0], FINALS));
                break;
            }
            case 1: {
                this->m_historyRecord.insert(make_pair(tempStrs[0], PUBLISHING_RULES));
                break;
            }
            case 2: {
                this->m_historyRecord.insert(make_pair(tempStrs[0], RECRUITING_CONTESTANTS));
                break;
            }
            case 3: {
                this->m_historyRecord.insert(make_pair(tempStrs[0], PRELIMINARY));
                break;
            }
            case 4: {
                this->m_historyRecord.insert(make_pair(tempStrs[0], REMATCH));
                break;
            }
            default: break;
        }
    }

    ifs.close();
}
