#pragma once
#ifndef _CONTESTANT_MANAGER_H_
#define _CONTESTANT_MANAGER_H_

#include <iostream>
#include <string>
#include <fstream>

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

    // ���ļ����ز���ѡ����Ϣ
    void loadContestantInfoFromFile();
};

#endif // !_CONTESTANT_MANAGER_H_

