/**
 * @file    main.cpp
 * @brief   STL案例二——员工分组案例
 *          
 * @section 案例描述
 * -# 招聘10名员工，员工入职后需要指派到不同部门工作；
 * -# 员工信息：姓名、工资组成；
 * -# 部门类别：策划、美工、研发；
 * -# 随机给10名员工分配部门和工资；
 * -# 通过multimap进行信息的插入key(部门)，value(员工)
 * -# 分部门显示员工信息
 * @section 实现步骤
 * -# 创建10名员工，存入vector；
 * -# 遍历vector，取出员工，进行随机分组；
 * -# 分组后将部门编号作为key，具体员工作为value，放入multimap；
 * -# 分组显示员工信息
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
        int group = rand() % 3;             // 0, 1, 2 代表三个部门
        int salary = 0;
        switch (group) // 不同部门工资水平不同
        {
        case MEIGONG:
        {
            salary = rand() % 2001 + 10000; // 薪资在10000-12000之间
            break;
        }
        case CEHUA:
        {
            salary = rand() % 3001 + 12000; // 薪资在12000-15000之间
            break;
        }
        case YANFA:
        {
            salary = rand() % 5001 + 15000; // 薪资在15000-20000之间
            break;
        }
        default:
            break;
        }

        it->m_salary = salary;
        // 插入到multimap中
        groupedStaff.insert(pair<int, Staff>(group, *it));
    }
}

void showStaffByGroup(const multimap<int, Staff>& m, const map<int, string>& groupName)
{
    for (int i = MEIGONG; i <= YANFA; i++)
    {
        cout << "-------------- GROUP "<< groupName.find(i)->second <<" --------------" << endl;
        // 查找
        multimap<int, Staff>::const_iterator pos = m.find(i);
        // 统计
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
    // 创建10个员工
    vector<Staff> staffVec;
    createStaff(staffVec, 10);
    // cout << "New employee information: " << endl;
    // showStaff<vector<Staff> >(staffVec);

    // 分组和分配薪水
    multimap<int, Staff> groupedStaff;
    setGroup(groupedStaff, staffVec);

    // 按部门显示
    map<int, string> gropName;
    gropName.insert(pair<int, string>(MEIGONG, "Art"));
    gropName.insert(pair<int, string>(CEHUA, "Planning"));
    gropName.insert(pair<int, string>(YANFA, "R&D"));
    showStaffByGroup(groupedStaff, gropName);
}

int main(int argc, char** argv)
{
    // 设置随机种子
    srand((unsigned int)time(NULL));

    // test01();
    test02();

    system("pause");
    return 0;
}