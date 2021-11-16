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

    // 显示菜单
    void showMenu();

    // 添加参赛选手信息
    void addContestantInfo();

    // 从文件加载参赛选手信息
    void loadContestantInfoFromFile();
};

#endif // !_CONTESTANT_MANAGER_H_

