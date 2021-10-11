#include "Manager.h"



Manager::Manager()
{
    cout << "[info] Manager类构造" << endl;
}

Manager::Manager(int id, string name, int departId)
{
    this->m_Id = id;
    this->m_name = name;
    this->m_departId = departId;
    cout << "[info] Manager类构造" << endl;
}


Manager::~Manager()
{
    cout << "[info] Manager类析构" << endl;
}

void Manager::showInfo()
{
    cout << "职工编号：" << this->m_Id
        << "\t职工姓名：" << this->m_name
        << "\t岗位：" << this->getDepartName()
        << "\t岗位职责：完成老板交给的任务，并下发给普通员工" << endl;
}

string Manager::getDepartName()
{
    return string("经理");
}
