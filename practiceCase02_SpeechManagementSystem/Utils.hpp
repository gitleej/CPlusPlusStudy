#pragma once
#ifndef _UILTS_H_
#define _UILTS_H_

#include "common.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

namespace Utils
{
    template<typename T>
    void printData(T & data)
    {
        cout << data << " ";
    }

    class Utils
    {
    public:
        static vector<string> strSplit(const string &src, const char pattern);
        static void printContestantInfo(const ContestantType& contestant);
    };

};

#endif // !_UILTS_H_

