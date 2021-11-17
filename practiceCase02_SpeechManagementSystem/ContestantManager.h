#pragma once
#ifndef _CONTESTANT_MANAGER_H_
#define _CONTESTANT_MANAGER_H_

#include "Utils.hpp"
#include "common.h"

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

class ContestantManager
{
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

private:
    string makeName();
    string makeId();

private:
    vector<ContestantType>          m_contestants;          ///< ����ѡ����Ϣ
    int                             m_num;                  ///< ����ѡ������
};

#endif // !_CONTESTANT_MANAGER_H_

