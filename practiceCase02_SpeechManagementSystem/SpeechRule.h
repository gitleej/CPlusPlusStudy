#pragma once
#ifndef _SPEECH_RULE_H_
#define _SPEECH_RULE_H_

#include "Utils.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>

using namespace std;

namespace Rule 
{
    typedef enum _PROCESSTYPE_
    {
        AUDITION,       // 海选
        SEMI_FINALS,    // 复赛
        FINALS          // 决赛
    }ProcessType;

    typedef enum _RULEERRORTYPE_
    {
        RULE_OK,                // 规则合格
        RULE_ZERO_NUMBER,       // 小于0的数
        RULE_TOTAL_LESS,        // 总数不足
        RULE_SF_CANT_AVG,       // 半决赛分组
        RULE_SF_LESS_FINAL,     // 决赛人数少于3人
    }RuleErrorType;
};

class SpeechRule
{
public:
    SpeechRule();
    ~SpeechRule();

    void setRule();

    void showRules();

    void saveRule(string filename);

    void loadRule(string filename);

private:
    // 检查规则
    Rule::RuleErrorType checkRule(int level);
    // 求所有公约数
    void getCommonDivisor(const int &src, map<int, int> &dst);

public:
    int m_auditionNum;      // 海选人数
    int m_semi_finalsNum;   // 复赛人数
    int m_finalsNum;        // 决赛人数

    int m_auditionGrpNum;   // 海选分组数
    int m_auditionNextNum;  // 海选每组晋级人数

    int m_sfGrpNum;         // 复赛分组数量
    int m_sfNextNum;        // 复赛每组晋级人数
};

#endif // !_SPEECH_RULE_H_
