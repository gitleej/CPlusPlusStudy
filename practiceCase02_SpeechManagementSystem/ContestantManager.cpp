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
    cout << "------------- �ݽ���������ϵͳv1.0 -------------\n"
        << "|                 ѡ����Ϣ����                 |\n"
        << "|[1] - ���ѡ����Ϣ                            |\n"
        << "|[2] - �鿴ѡ����Ϣ                            |\n"
        << "|[3] - ɾ��ѡ����Ϣ                            |\n"
        << "|[4] - �޸�ѡ����Ϣ                            |\n"
        << "|[5] - ����ѡ����Ϣ                            |\n"
        << "|[0] - �˳���ǰ�˵�                            |\n"
        << "------------------------------------------------"
        << endl;
}

//void ContestantManager::addContestantInfo()
//{
//    m_isSaveContestantInfo = false;
//    system("cls");
//    cout << "------------- �ݽ���������ϵͳv1.0 -------------\n"
//        << "|                 ѡ����Ϣ����                 |\n"
//        << "|[1] - ���ѡ����Ϣ                            |\n"
//        << "|    (1) - �ֶ���Ӳ���ѡ����Ϣ                |\n"
//        << "|    (2) - ���ļ��������ѡ����Ϣ              |\n"
//        << "|    (3) - ������ɲ���ѡ����Ϣ                |\n"
//        << "------------------------------------------------"
//        << endl;
//
//    int choise = -1;
//    cout << "����������ѡ��" << endl;
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
    cout << "------------- �ݽ���������ϵͳv1.0 -------------\n"
         << "|                 ѡ����Ϣ����                 |\n"
         << "|[1] - ���ѡ����Ϣ                            |\n"
         << "|    (1) - �ֶ���Ӳ���ѡ����Ϣ                |\n"
         << "|    (2) - ���ļ��������ѡ����Ϣ              |\n"
         << "|    (3) - ������ɲ���ѡ����Ϣ                |\n"
         << "------------------------------------------------" << endl;

    int choise = -1;
    cout << "����������ѡ��" << endl;
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
    cout << "��������Ҫ��Ӳ���ѡ����Ϣ������";
    cin >> totalNum;
    for (int i = 0; i < totalNum; i++)
    {
        string tempStr;
        cout << "������� " << i + 1 << " ������ѡ�ֵ����������䣬��id(�ö��ŷָ����磺xxx,xx,xxxxx)" << endl;
        getline(cin, tempStr);
        vector<string> result = Utils::Utils::strSplit(tempStr, ',');
        if (result.size() != 3)
        {
            cout << "�����󡿣������ʽ����ȷ����������ԡ�" << endl;
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

    cout << "����� " << totalNum << " ������ѡ����Ϣ��\n"
        << "���ݿ��й��� " << this->m_num << " ������ѡ����Ϣ��" << endl;
}

void ContestantManager::addContestantInfoFromFile()
{
    string filePath;
    cout << "�������ļ�·����";
    cin >> filePath;

    ifstream ifs;
    ifs.open(filePath.c_str(), std::ios::in);
    if (!ifs.is_open())
    {
        cout << "�ļ������ڣ�" << filePath << endl;
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

    cout << "����� " << totalNum << " ������ѡ����Ϣ��\n"
        << "���ݿ��й��� " << this->m_num << " ������ѡ����Ϣ��" << endl;
}

void ContestantManager::addContestantInfoRandomly()
{
    // �����������
    srand((unsigned int)time(NULL));

    int totalNum = 0;
    cout << "��������Ҫ��Ӳ���ѡ����Ϣ������";
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
    cout << "����� " << totalNum << " ������ѡ����Ϣ��\n"
         << "���ݿ��й��� " << this->m_num << " ������ѡ����Ϣ��" << endl;
}

void ContestantManager::viewContestantInfo() {
    system("cls");
    // ����Ƿ��Ѿ���ѡ��
    if (this->m_contestants.size() == 0) {
        cout << "�����桿����ǰ��û����ļ������ѡ�֣�������ļ����ѡ�֡�"
             << endl;
        system("pause");
        return;
    }
    
    cout << "------------- �ݽ���������ϵͳv1.0 -------------\n"
         << "|                 ѡ����Ϣ����                 |\n"
         << "|[2] - �鿴ѡ����Ϣ                            |\n"
         << "------------------------------------------------" << endl;
    for (auto it = this->m_contestants.begin(); it != this->m_contestants.end();
         it++) {
        int index = (int)(it - this->m_contestants.begin());
        if ((index + 1) % 10 == 0) {
            system("pause");
            system("cls");
            cout << "------------- �ݽ���������ϵͳv1.0 -------------\n"
                 << "|                 ѡ����Ϣ����                 |\n"
                 << "|[2] - �鿴ѡ����Ϣ                            |\n"
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
    // ����Ƿ��Ѿ���ѡ��
    if (this->m_contestants.size() == 0) {
        cout << "�����桿����ǰ��û����ļ������ѡ�֣�������ļ����ѡ�֡�"
             << endl;
        system("pause");
        return -1;
    }

    m_isSaveContestantInfo = false;
    system("cls");
    cout << "------------- �ݽ���������ϵͳv1.0 -------------\n"
         << "|                 ѡ����Ϣ����                 |\n"
         << "|[3] - ɾ��ѡ����Ϣ                            |\n"
         << "------------------------------------------------" << endl;
    getchar();
    string tempId;
    cout << "�������ɾ������ѡ�ֵ�id��(18λ)��";
    getline(cin, tempId);
    if (tempId.size() != 18) {
        cout << "�����󡿣�id��ʽ����ȷ�������ԣ�" << endl;
        system("pause");
        return -1;
    }
    vector<ContestantType>::iterator resultIter =
        this->findContestantId(tempId);
    if (resultIter != this->m_contestants.end()) {
        cout << "�����桿��ȷ��ɾ��idΪ��" << tempId << " �Ĳ���ѡ����Ϣ��(y/n)"
             << endl;
        char confirm = 'y';
        confirm = getchar();
        if (confirm == 'y') {
            cout << "�����ѡ���name:" << right << setw(20) << fixed
                 << resultIter->name << "\tage: " << resultIter->age
                 << "\tid: " << resultIter->id << " ��ɾ��" << endl;
            this->m_contestants.erase(resultIter);
            this->m_num--;
        } else {
            cout << "�����ѡ���ɾ����ȡ��" << endl;
        }
    } else {
        cout << "�����󡿣����޴�id: " << tempId << " ��Ӧ�Ĳ���ѡ����Ϣ"
             << endl;
    }

    system("pause");
    return (int)(this->m_contestants.size());
}

void ContestantManager::modifyContestantInfo() {
    // ����Ƿ��Ѿ���ѡ��
    if (this->m_contestants.size() == 0) {
        cout << "�����桿����ǰ��û����ļ������ѡ�֣�������ļ����ѡ�֡�"
             << endl;
        system("pause");
        return;
    }

    m_isSaveContestantInfo = false;
    system("cls");
    cout << "------------- �ݽ���������ϵͳv1.0 -------------\n"
         << "|                 ѡ����Ϣ����                 |\n"
         << "|[4] - �޸�ѡ����Ϣ                            |\n"
         << "------------------------------------------------" << endl;
    getchar();
    string tempStr;
    cout << "��������޸Ĳ���ѡ�ֵ�������id��";
    getline(cin, tempStr);
    // �ж������Ƿ�Ϊid�������idִ��
    if (tempStr.size() == 18 && isdigit(tempStr[0])) {      
        vector<ContestantType>::iterator retIter =
            this->findContestantId(tempStr);
        if (retIter == this->m_contestants.end()) {
            cout << "�����󡿣����޴�id: " << tempStr
                 << " ��Ӧ�Ĳ���ѡ����Ϣ�������ԡ�" << endl;
            system("pause");
            return;
        }
        cout << "�����ѡ������޸Ĳ���ѡ����Ϣ���£�\n"
             << "name:" << right << setw(20) << fixed << retIter->name
             << "\tage: " << retIter->age << "\tid: " << retIter->id << endl;
        while (true) {
            getchar();
            cout << "\n�������µĲ���ѡ�ֵ����������䣬��id("
                    "�ö��ŷָ����磺xxx,xx,xxxxx)"
                 << endl;
            getline(cin, tempStr);
            vector<string> result = Utils::Utils::strSplit(tempStr, ',');
            if (result.size() != 3) {
                cout << "�����󡿣������ʽ����ȷ����������ԡ�" << endl;
                continue;
            }

            retIter->name = result[0];
            retIter->age = stoi(result[1]);
            retIter->id = result[2];
            break;
        }
    } else {    // �������id����ִ�б���
        vector<vector<ContestantType>::iterator> retIters =
            this->findContestantName(tempStr);
        if (retIters.size() == 0) {
            cout << "�����󡿣����޴�����: " << tempStr
                 << " ��Ӧ�Ĳ���ѡ����Ϣ�������ԡ�" << endl;
            system("pause");
            return;
        }
        cout << "�����ѡ������ҵ�����ͬ������ѡ����Ϣ����ѡ���Ӧ��Ž����޸ģ�"
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
                cout << "�����󡿣�����������Ų�Ӧ����" << retIters.size()
                     << "��������ѡ����ţ�" << endl;
                continue;
            }
            break;
        }

        while (true) {
            getchar();
            cout << "\n�������µĲ���ѡ�ֵ����������䣬��id("
                    "�ö��ŷָ����磺xxx,xx,xxxxx)"
                 << endl;
            getline(cin, tempStr);
            vector<string> result = Utils::Utils::strSplit(tempStr, ',');
            if (result.size() != 3) {
                cout << "�����󡿣������ʽ����ȷ����������ԡ�" << endl;
                continue;
            }

            retIters[chooseContestant-1]->name = result[0];
            retIters[chooseContestant-1]->age = stoi(result[1]);
            retIters[chooseContestant-1]->id = result[2];
            break;
        }
    }

    cout << "�����ѡ�������ѡ����Ϣ�޸ĳɹ���" << endl;
    system("pause");
}

void ContestantManager::saveContestantInfo() {
    // ����Ƿ��Ѿ���ѡ��
    if (this->m_contestants.size() == 0) {
        cout << "�����桿����ǰ��û����ļ������ѡ�֣�������ļ����ѡ�֡�"
             << endl;
        system("pause");
        return;
    }
    string filePath = "./data/contestant_info/default.csv";

    ofstream ofs;
    ofs.open(filePath.c_str(), std::ios::out | std::ios::trunc);
    if (!ofs.is_open()) {
        cout << "�����󡿣��ļ������ڣ�" << filePath << endl;
        return;
    }

    for (auto it = this->m_contestants.begin(); it != this->m_contestants.end(); it++) {
        ofs << it->name << "," << it->age << "," << it->id << endl;
    }

    ofs.close();

    m_isSaveContestantInfo = true;
    cout << "�����ѡ�������ѡ����Ϣ����ɹ���" << endl;
    system("pause");
}

void ContestantManager::saveContestantInfo(const string &timestamp) {
    // ����Ƿ��Ѿ���ѡ��
    if (this->m_contestants.size() == 0) {
        cout << "�����桿����ǰ��û����ļ������ѡ�֣�������ļ����ѡ�֡�"
             << endl;
        system("pause");
        return;
    }

    string filePath = "./data/contestant_info/" + timestamp + ".csv";

    ofstream ofs;
    ofs.open(filePath.c_str(), std::ios::out | std::ios::trunc);
    if (!ofs.is_open()) {
        cout << "�����󡿣��ļ������ڣ�" << filePath << endl;
        return;
    }

    for (auto it = this->m_contestants.begin(); it != this->m_contestants.end();
         it++) {
        ofs << it->name << "," << it->age << "," << it->id << endl;
    }

    ofs.close();

    m_isSaveContestantInfo = true;
    cout << "�����ѡ�������ѡ����Ϣ����ɹ���" << endl;
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
    // id�洢����
    char id[24];
    // ��ȡ��ǰʱ��
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

    // ����
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

    // ����
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
