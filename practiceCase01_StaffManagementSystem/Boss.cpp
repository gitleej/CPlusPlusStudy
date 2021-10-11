#include "Boss.h"

Boss::Boss()
{
    cout << "[info] Boos类构造" << endl;
}

Boss::Boss(int id, string name, int departId)
{
    this->m_Id = id;
    this->m_name = name;
    this->m_departId = departId;
    cout << "[info] Boos类构造" << endl;
}


Boss::~Boss()
{
    cout << "[info] Boos类析构" << endl;
}

void Boss::showInfo()
{
    cout << "职工编号：" << this->m_Id
        << "\t职工姓名：" << this->m_name
        << "\t岗位：" << this->getDepartName()
        << "\t岗位职责：管理公司所有事务" << endl;
}

string Boss::getDepartName()
{
    return string("老板");
}
