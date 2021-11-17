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

    // 显示菜单
    void showMenu();

    // 添加参赛选手信息
    void addContestantInfo();

    // 手动添加参赛选手信息
    void addContestantInfoManually();

    // 从文件加载参赛选手信息
    void addContestantInfoFromFile();

    // 随机生成参赛选手信息
    void addContestantInfoRandomly();

private:
    string makeName();
    string makeId();

private:
    vector<ContestantType>          m_contestants;          ///< 参赛选手信息
    int                             m_num;                  ///< 参赛选手人数
};

#endif // !_CONTESTANT_MANAGER_H_

