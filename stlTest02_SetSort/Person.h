#pragma once
#ifndef _SET_SORT_PERSON_H_
#define _SET_SORT_PERSON_H_

#include <iostream>
#include <string>

using namespace std;

class Person
{
public:
    Person(string name, int age, int height, double weight);
    ~Person();

    string m_name;      // 姓名
    int m_age;          // 年龄
    int m_height;       // 身高
    double m_weight;    // 体重

    /**
     * @brief   << 操作符重构
     */
    friend ostream& operator<<(ostream& output, const Person& person);

    /**
     * @brief   < 操作符重载
     */
    bool operator<(const Person& person);

    /**
     * @brief   > 操作符重载
     */
    bool operator>(const Person& person);
};

#endif // !_SET_SORT_PERSON_H_
