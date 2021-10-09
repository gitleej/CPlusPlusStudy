/**
 * @file    main.cpp
 * @brief   STL����������Ա�����鰸��
 *          
 * @section ��������
 * -# ��Ƹ10��Ա����Ա����ְ����Ҫָ�ɵ���ͬ���Ź�����
 * -# Ա����Ϣ��������������ɣ�
 * -# ������𣺲߻����������з���
 * -# �����10��Ա�����䲿�ź͹��ʣ�
 * -# ͨ��multimap������Ϣ�Ĳ���key(����)��value(Ա��)
 * -# �ֲ�����ʾԱ����Ϣ
 * @section ʵ�ֲ���
 * -# ����10��Ա��������vector��
 * -# ����vector��ȡ��Ա��������������飻
 * -# ����󽫲��ű����Ϊkey������Ա����Ϊvalue������multimap��
 * -# ������ʾԱ����Ϣ
 */

#include "Staff.h"

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <ctime>

typedef enum _GroupType
{
    MEIGONG,
    CEHUA,
    YANFA
}Group;

template<typename T>
void showStaff(T& data)
{
    for (auto it = data.begin(); it != data.end(); it++)
    {
        cout << (*it) << endl;
    }
}

void createStaff(vector<Staff>& staffVec, int num)
{
    char index = 'A';
    for (int i = 0; i < num; i++)
    {
        string name = "Staff_";
        name.push_back((char)(index + i));
        Staff staff(name, 0);
        staffVec.push_back(staff);
    }
}

void setGroup(multimap<int, Staff> &groupedStaff, vector<Staff>& staffVec)
{
    for (auto it = staffVec.begin(); it != staffVec.end(); it++)
    {
        int group = rand() % 3;             // 0, 1, 2 ������������
        int salary = 0;
        switch (group) // ��ͬ���Ź���ˮƽ��ͬ
        {
        case MEIGONG:
        {
            salary = rand() % 2001 + 10000; // н����10000-12000֮��
            break;
        }
        case CEHUA:
        {
            salary = rand() % 3001 + 12000; // н����12000-15000֮��
            break;
        }
        case YANFA:
        {
            salary = rand() % 5001 + 15000; // н����15000-20000֮��
            break;
        }
        default:
            break;
        }

        it->m_salary = salary;
        // ���뵽multimap��
        groupedStaff.insert(pair<int, Staff>(group, *it));
    }
}

void showStaffByGroup(const multimap<int, Staff>& m, const map<int, string>& groupName)
{
    for (int i = MEIGONG; i <= YANFA; i++)
    {
        cout << "-------------- GROUP "<< groupName.find(i)->second <<" --------------" << endl;
        // ����
        multimap<int, Staff>::const_iterator pos = m.find(i);
        // ͳ��
        int count = (int)m.count(i);
        for ( int index = 0; pos != m.end() && index < count; pos++, index++)
        {
            cout << (*pos).second << endl;
        }
    }
}

void test01()
{
    Staff staff1("aaa", 10000);

    cout << staff1 << endl;
}

void test02()
{
    // ����10��Ա��
    vector<Staff> staffVec;
    createStaff(staffVec, 10);
    // cout << "New employee information: " << endl;
    // showStaff<vector<Staff> >(staffVec);

    // ����ͷ���нˮ
    multimap<int, Staff> groupedStaff;
    setGroup(groupedStaff, staffVec);

    // ��������ʾ
    map<int, string> gropName;
    gropName.insert(pair<int, string>(MEIGONG, "Art"));
    gropName.insert(pair<int, string>(CEHUA, "Planning"));
    gropName.insert(pair<int, string>(YANFA, "R&D"));
    showStaffByGroup(groupedStaff, gropName);
}

int main(int argc, char** argv)
{
    // �����������
    srand((unsigned int)time(NULL));

    // test01();
    test02();

    system("pause");
    return 0;
}