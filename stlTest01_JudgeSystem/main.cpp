#include "Person.h"

#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>

/**
 * @brief    有n名选手，10个评委对每个选手进行打分，去掉最高分和最低分，取平均值
 */

using namespace std;

int enterPlayerInfo(vector<Person> &players, int playerNum)
{
    for (int i = 0; i < playerNum; i++)
    {
        string name;
        cout << "Please enter the name of the [" << i + 1 << "] player: ";
        cin >> name;
        getchar();
        Person *player = new Person(name, 0);
        players.push_back(*player);
    }

    return 0;
}

int scoringByjudges(vector<Person> &players)
{
    for (auto it = players.begin(); it != players.end(); it++)
    {
        cout << "Please enter the score of player " << (*it).m_name << endl;
        deque<double> judgeScore(10, 0);
        for (auto it = judgeScore.begin(); it != judgeScore.end(); it++)
        {
            cin >> *it;
        }
        // 排序
        sort(judgeScore.begin(), judgeScore.end());
        // 去除最高分和最低分
        judgeScore.pop_front();
        judgeScore.pop_back();
        // 求平均值
        double sum = 0;
        for (auto dit = judgeScore.begin(); dit != judgeScore.end(); dit++)
        {
            sum += (*dit);
        }
        (*it).m_score = sum / judgeScore.size();
    }
    return 0;
}

int showFinalScore(const vector<Person> &players)
{
    for (auto  it = players.begin(); it != players.end(); it++)
    {
        cout << "Player name: " << (*it).m_name << "\tscore: " << (*it).m_score << endl;
    }

    return 0;
}

void test01()
{
    char funcChoose = 0;             // 功能选择
    int playerNum = 0;              // 选手数量
    vector<Person> players;         // 选手信息
    

    while (funcChoose!='q')
    {
        cout << "Please enter the corresponding function number:\n"
            << "[0]-Enter player information\n"
            << "[1]-Scoring by the judges\n"
            << "[2]-Show the player's final score\n"
            << "[q]-quit" << endl;
        cin >> funcChoose;
        getchar();
        // 功能选择分支
        switch (funcChoose)
        {
        case '0':
        {
            cout << "Please enter the number of players: ";
            cin >> playerNum;
            getchar();
            enterPlayerInfo(players, playerNum);
            break;
        }
        case '1':
        {
            scoringByjudges(players);
            break;
        }
        case '2':
        {
            showFinalScore(players);
            break;
        }
        default:
            break;
        }
    }
    
}

int main(int argc, char **argv)
{
    test01();

    system("pause");
    return 0;
}