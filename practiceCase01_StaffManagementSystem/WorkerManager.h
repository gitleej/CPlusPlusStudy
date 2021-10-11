#pragma once
#include "Worker.h"
#include "Employee.h"
#include "Manager.h"
#include "Boss.h"

#include <iostream>
#include <fstream>
#include <vector>

// 宏定义结果保存位置
#define FILENAME "empInfo.txt"

using namespace std;

class WorkerManager {
public:
    WorkerManager();
    ~WorkerManager();

    // 获取职工数量
    int getEmpNum();

    // 获取文件状态
    bool getFileIsEmptyFlag();

    // 展示菜单
    void Show_Menu();

    // 退出程序
    void ExitSystem();

    // 添加职工
    void addEmp();

    // 保存职工信息到本地
    void save();

    // 从本地读取职工人数
    int getLocalEmpNum();

    // 从本地初始化职工信息
    void initEmpInfoFromLocal();

    // 显示职工信息
    void showEmpInfo();

    // 删除职工信息
    void delEmpInfo();

    // 判断职工是否存在
    int isEmpExist(int id);		// 通过ID判断
    int isEmpExist(string name, vector<int> &dstIndex);	// 通过姓名查找

    // 修改职工信息
    void modEmpInfo();

    // 查找员工信息
    void findEmpInfo();

    // 排序员工信息
    void sortEmpInfo();

    // 清空所有信息
    void claenAllInfo();

private:
    // 记录文件中的人数
    int m_empNum;

    // 员工数组指针
    Worker* * m_empArray;

    // 文件是否为空标志
    bool m_fileIsEmpty;
};
