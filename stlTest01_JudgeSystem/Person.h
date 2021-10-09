#pragma once
#ifndef _PERSON_H_
#define _PERSON_H_

#include <string>

using namespace std;

class Person
{
public:
    Person();
    Person(string name, double score);
    ~Person();

    string m_name;
    double m_score;
};

#endif // !_PERSON_H_
