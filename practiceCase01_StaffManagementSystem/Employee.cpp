#include "Employee.h"


// 构造函数
Employee::Employee()
{
    cout << "[info] Employee类构造" << endl;
}

// 构造函数
Employee::Employee(int id, string name, int departId)
{
    this->m_Id = id;
    this->m_name = name;
    this->m_departId = departId;

    cout << "[info] Employee类构造" << endl;
}

// 析构函数
Employee::~Employee()
{
    cout << "[info] Employee类析构" << endl;
}

// 显示个人信息
void Employee::showInfo()
{
    cout << "职工编号：" << this->m_Id
        << "\t职工姓名：" << this->m_name
        << "\t岗位：" << this->getDepartName()
        << "\t岗位职责：完成经理交给的任务" << endl;
}

string Employee::getDepartName()
{
    return string("普通员工");
}
