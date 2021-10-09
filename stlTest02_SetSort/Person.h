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

    string m_name;      // ����
    int m_age;          // ����
    int m_height;       // ���
    double m_weight;    // ����

    /**
     * @brief   << �������ع�
     */
    friend ostream& operator<<(ostream& output, const Person& person);

    /**
     * @brief   < ����������
     */
    bool operator<(const Person& person);

    /**
     * @brief   > ����������
     */
    bool operator>(const Person& person);
};

#endif // !_SET_SORT_PERSON_H_
