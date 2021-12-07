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
        AUDITION,       // ��ѡ
        SEMI_FINALS,    // ����
        FINALS          // ����
    }ProcessType;

    typedef enum _RULEERRORTYPE_
    {
        RULE_OK,                // ����ϸ�
        RULE_ZERO_NUMBER,       // С��0����
        RULE_TOTAL_LESS,        // ��������
        RULE_SF_CANT_AVG,       // ���������
        RULE_SF_LESS_FINAL,     // ������������3��
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
    // ������
    Rule::RuleErrorType checkRule(int level);
    // �����й�Լ��
    void getCommonDivisor(const int &src, map<int, int> &dst);

public:
    int m_auditionNum;      // ��ѡ����
    int m_semi_finalsNum;   // ��������
    int m_finalsNum;        // ��������

    int m_auditionGrpNum;   // ��ѡ������
    int m_auditionNextNum;  // ��ѡÿ���������

    int m_sfGrpNum;         // ������������
    int m_sfNextNum;        // ����ÿ���������
};

#endif // !_SPEECH_RULE_H_
