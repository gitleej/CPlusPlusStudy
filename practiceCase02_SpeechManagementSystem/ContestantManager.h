#pragma once
#ifndef _CONTESTANT_MANAGER_H_
#define _CONTESTANT_MANAGER_H_

#include "Utils.hpp"
#include "common.h"

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <map>
#include <iomanip>

using namespace std;
using std::right;
using std::left;
using std::setw;
using std::fixed;
using std::string;

class ContestantManager {
public:
    ContestantManager();
    ~ContestantManager();

    // ��ʾ�˵�
    void showMenu();

    // ��Ӳ���ѡ����Ϣ
    void addContestantInfo();

    // �ֶ���Ӳ���ѡ����Ϣ
    void addContestantInfoManually();

    // ���ļ����ز���ѡ����Ϣ
    void addContestantInfoFromFile();

    // ������ɲ���ѡ����Ϣ
    void addContestantInfoRandomly();

    // �鿴����ѡ����Ϣ
    void viewContestantInfo();

    // ɾ������ѡ����Ϣ
    void deletContestantInfo();

    // �޸�ѡ����Ϣ
    void modifyContestantInfo();

    // ����ѡ����Ϣ
    void saveContestantInfo();

    // ����ѡ����Ϣ
    void loadContestantInfo();

private:
    // ��������
    string makeName();
    // �������֤id
    map<string, int> makeId();
    // �ж�����
    bool isLeapYear(int year);
    // �������֤��
    vector<ContestantType>::iterator findContestantId(string id);
    // ��������
    vector<vector<ContestantType>::iterator> findContestantName(string name);

public:
    bool m_isSaveContestantInfo;           ///< �Ƿ��ѱ������ѡ����Ϣ

private:
    vector<ContestantType> m_contestants;  ///< ����ѡ����Ϣ
    int m_num;                             ///< ����ѡ������
};

#endif  // !_CONTESTANT_MANAGER_H_
