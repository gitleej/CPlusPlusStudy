#pragma once
#ifndef _STAFF_H_
#define _STAFF_H_

#include <iostream>
#include <string>

using namespace std;

class Staff
{
public:
    Staff(string name, int salary);
    ~Staff();

    friend ostream& operator<<(ostream& output, const Staff& staff);

    string m_name;  // ÐÕÃû
    int m_salary;   // Ð½Ë®
};

#endif // !_STAFF_H_
