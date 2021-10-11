#pragma once
#include "Worker.h"
class Manager :
    public Worker
{
public:
    Manager();
    Manager(int id, string name, int departId);
    ~Manager();

    // 显示个人信息
    virtual void showInfo();

    // 获取岗位名称
    virtual string getDepartName();
};

