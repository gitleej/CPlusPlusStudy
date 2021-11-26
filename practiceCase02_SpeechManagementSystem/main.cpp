/**
 * @file    main.cpp
 * @brief   演讲比赛流程管理系统
 * @detail  进入系统时，先检查是否有正在进行的比赛，如果有比赛，选择需要继续进行
            的比赛或开始新的比赛。
 * @section 比赛规则发布
 * -# 开始比赛前制定比赛规则，比赛分为海选、复赛和决赛；
 * -# 海选人数 > 海选组数 X (每组晋级人数 + 1)；
 * -# 3 < (复赛组数 X 每组晋级人数) < 复赛总人数，且保持每组人数一致；
 * -# 决赛决出冠军、亚军和季军；
 * @section 选手信息管理
 * -# 选手信息包含：姓名、年龄、身份证号和联系电话；
 * -# 添加选手到规则设定人数后停止招募选手；
 * -# 支持退出系统，接续招募；
 * -# 支持删除选手信息；
 * -# 支持修改选手信息；
 * -# 支持查找选手信息，按姓名、年龄、身份证号和联系电话查找；
 * @section 开始比赛
 * -# 选手随机抽签排序分组；
 * -# 分组进行比赛，由10名评委打分，去除一个最高分和一个最低分，其平均分为最终得分；
 * -# 对应晋级人数晋级；
 * -# 每轮比赛后显示每组晋级选手信息；
 * -# 支持重赛；
 * -# 支持中途停赛；
 * @section 查看往届比赛记录
 * -# 查看所有记录；
 * -# 查看海选记录；
 * -# 查看复赛记录；
 * -# 查看决赛记录；
 * @section 清空比赛记录
 * -# 再次确认是否清除；
 * @section 退出系统
 */
#include "SpeechManager.h"

#include <iostream>
#include <algorithm>
#include <ctime>

int main(int argc, char **argv)
{
    // 设置随机种子
    srand((unsigned int)time(NULL));

    // 创建管理实例
    SpeechManager sm;
    // 菜单选择标志
    int choise = -1;
    
    while (true)
    {
        // 检查是否有未完成的比赛，如果有显示未完成的比赛，如果没有，显示开始新比赛的菜单
        if (sm.m_unfinishedContests.size() != 0) {
            cout << "【提醒】：当前有一下为完成的比赛：" << endl;
            sm.coutHistoryRecord(sm.m_unfinishedContests);
            sm.showMenu(CONTINUE_MENU);
            // 接受菜单参数
            cout << "请输入您的选择：" << endl;
            cin >> choise;
            if (choise == 0) {
                sm.exitSystem();
                break;
            } else if (choise == 1) {
                sm.startNewContest();
            }else if(choise == 2) {
                sm.continueContest();
            }
        }

    }
    system("pause");
    return 0;
}