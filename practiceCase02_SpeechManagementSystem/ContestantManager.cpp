#include "ContestantManager.h"

ContestantManager::ContestantManager()
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
        break;
    }
    case 2:
    {
        loadContestantInfoFromFile();
        break;
    }
    case 3:
    {
        break;
    }
    default:
        break;
    }

    system("pause");
}

void ContestantManager::loadContestantInfoFromFile()
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

    string line;
    while (getline(ifs, line))
    {
        cout << line << endl;
    }
}
