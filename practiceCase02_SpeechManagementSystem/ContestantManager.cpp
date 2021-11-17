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

void ContestantManager::addContestantInfo()
{
    system("cls");
    cout << "------------- �ݽ���������ϵͳv1.0 -------------\n"
        << "|                 ѡ����Ϣ����                 |\n"
        << "|[1] - ���ѡ����Ϣ                            |\n"
        << "|    (1) - �ֶ���Ӳ���ѡ����Ϣ                |\n"
        << "|    (2) - ���ļ��������ѡ����Ϣ              |\n"
        << "|    (3) - ������ɲ���ѡ����Ϣ                |\n"
        << "------------------------------------------------"
        << endl;

    int choise = -1;
    cout << "����������ѡ��" << endl;
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
    cout << "��������Ҫ��Ӳ���ѡ����Ϣ������";
    cin >> totalNum;
    for (int i = 0; i < totalNum; i++)
    {
        string tempStr;
        cout << "������� " << i + 1 << " ������ѡ�ֵ����������䣬��id(�ÿո�ָ����磺xxx xx xxxxx)" << endl;
        getline(cin, tempStr);
        vector<string> result = Utils::Utils::strSplit(tempStr, ' ');
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
        string tempStr;
        cout << "������� " << i + 1 << " ������ѡ�ֵ����������䣬��id(�ÿո�ָ����磺xxx xx xxxxx)" << endl;
        getline(cin, tempStr);
        vector<string> result = Utils::Utils::strSplit(tempStr, ' ');
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
}
