#include <iostream>

#include "WorkerManager.h"
#include "Worker.h"
#include "Employee.h"
#include "Manager.h"
#include "Boss.h"

// 定义测试开关
#define TEST 0

using namespace std;

// 测试代码
void test()
{
    Worker *worker = NULL;
    worker = new Employee(1, "张三", 1);
    worker->showInfo();
    delete worker;

    worker = new Manager(2, "李四", 2);
    worker->showInfo();
    delete worker;

    worker = new Boss(3, "王五", 3);
    worker->showInfo();
    delete worker;
}

void func()
{
    // 实例化 WorkerManager 对象
    WorkerManager wm;
    // 菜单选择标志
    int choise = -1;

    // 循环进行分支菜单选择
    while (true)
    {
        // 显示菜单
        wm.Show_Menu();

        // 接受菜单参数
        cout << "请输入您的选择：" << endl;
        cin >> choise;

        // 分支选择
        switch (choise)
        {
        case 0:	// 退出程序
            wm.ExitSystem();
            return;
            break;
        case 1:	// 添加员工
            wm.addEmp();
            break;
        case 2:	// 显示员工
            wm.showEmpInfo();
            break;
        case 3:	// 删除员工
            wm.delEmpInfo();
            break;
        case 4:	// 修改员工
            wm.modEmpInfo();
            break;
        case 5:	// 查找员工
            wm.findEmpInfo();
            break;
        case 6:	// 排序员工
            wm.sortEmpInfo();
            break;
        case 7:	// 清空文件
            wm.claenAllInfo();
            break;
        default:// 刷新屏幕
            system("cls");
            break;
        }
    }
}

int main() {
#if TEST
    // 测试
    test();
#else
    // 功能函数
    func();
#endif // TEST
    system("pause");

    return 0;
}