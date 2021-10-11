#pragma once
#include <iostream>
#include <string>

using namespace std;

// 职工抽象类
class Worker
{
public:
    Worker();
    virtual ~Worker() = 0;

    // 显示个人信息（纯虚函数）
    virtual void showInfo() = 0;

    // 获取岗位名称（纯虚函数）
    virtual string getDepartName() = 0;

    int m_Id;	// 员工编号
    string m_name;	// 员工姓名
    int m_departId;	// 员工所在部门名称编号
};

