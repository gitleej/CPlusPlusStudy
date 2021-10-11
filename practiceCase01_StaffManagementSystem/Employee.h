// 普通员工文件
#pragma once
#include "Worker.h"

#include <iostream>

using namespace std;

class Employee :
    public Worker
{
public:
    Employee();
    Employee(int id, string name, int departId);
    ~Employee();

    // 显示个人信息
    virtual void showInfo();

    // 获取岗位名称
    virtual string getDepartName();
};

