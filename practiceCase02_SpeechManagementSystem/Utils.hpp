#pragma once
#ifndef _UILTS_H_
#define _UILTS_H_

#include <iostream>

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
    };
};

#endif // !_UILTS_H_

