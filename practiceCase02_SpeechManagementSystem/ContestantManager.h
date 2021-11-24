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

    // 查看参赛选手信息
    void viewContestantInfo();

    // 删除参赛选手信息
    void deletContestantInfo();

    // 修改选手信息
    void modifyContestantInfo();

    // 保存选手信息
    void saveContestantInfo();

    // 加载选手信息
    void loadContestantInfo();

private:
    // 生成姓名
    string makeName();
    // 生成身份证id
    map<string, int> makeId();
    // 判断闰年
    bool isLeapYear(int year);
    // 查找身份证号
    vector<ContestantType>::iterator findContestantId(string id);
    // 查找姓名
    vector<vector<ContestantType>::iterator> findContestantName(string name);

public:
    bool m_isSaveContestantInfo;           ///< 是否已保存参赛选手信息

private:
    vector<ContestantType> m_contestants;  ///< 参赛选手信息
    int m_num;                             ///< 参赛选手人数
};

#endif  // !_CONTESTANT_MANAGER_H_
