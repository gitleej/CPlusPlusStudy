#pragma once
#include "Worker.h"
class Boss :
    public Worker
{
public:
    Boss();
    Boss(int id, string name, int departId);
    ~Boss();

    // 显示个人信息
    virtual void showInfo();

    // 获取岗位名称
    virtual string getDepartName();
};

