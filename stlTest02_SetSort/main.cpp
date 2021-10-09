#include "Person.h"
#include "MyCompare.hpp"

#include <set>

template<typename T, typename K>
void showSet(const set<T, MyCompare<K> > & s)
{
    for (auto it = s.begin(); it != s.end(); it++)
    {
        cout << (*it) << endl;
    }
}

template<typename T>
void showSet(const set<T> & s)
{
    for (auto it = s.begin(); it != s.end(); it++)
    {
        cout << (*it) << endl;
    }
}

// 测试Person的操作符
void test01()
{
    Person p1("aaa", 10, 170, 65.5);
    Person p2("bbb", 10, 168, 60.4);
    Person p3("ccc", 20, 175, 66.0);

    cout << (p1 > p2) << endl;
    cout << (p2 < p3) << endl;
    cout << p1 << "\n"
        << p2 << "\n"
        << p3 << endl;
}

// 内置数据类型set测试
void test02()
{
    set<int> s1;
    s1.insert(10);
    s1.insert(30);
    s1.insert(20);
    s1.insert(50);
    s1.insert(40);
    cout << "s1: " << endl;
    showSet<int>(s1);

    set<int, MyCompare<int> > s2;
    s2.insert(10);
    s2.insert(30);
    s2.insert(20);
    s2.insert(50);
    s2.insert(40);
    cout << "s2: " << endl;
    showSet(s2);
}

// 自定义数据类型测试
void test03()
{
    Person p1("aaa", 30, 170, 65.5);
    Person p2("bbb", 30, 168, 61.4);
    Person p3("ccc", 40, 175, 66.0);
    Person p4("ddd", 20, 170, 65.5);
    Person p5("eee", 10, 190, 62.4);
    Person p6("fff", 30, 172, 66.5);
    Person p7("ggg", 30, 169, 60.4);
    Person p8("hhh", 40, 175, 64.0);
    Person p9("iii", 20, 169, 65.5);
    Person p10("jjj", 10, 190, 63.4);

    set<Person, MyCompare<Person> > s;
    s.insert(p1);
    s.insert(p2);
    s.insert(p3);
    s.insert(p4);
    s.insert(p5);
    s.insert(p6);
    s.insert(p7);
    s.insert(p8);
    s.insert(p9);
    s.insert(p10);
    cout << "s: " << endl;
    showSet(s);
}

int main(int argc, char **argv)
{
    test01();
    test02();
    test03();

    system("pause");
    return 0;
}