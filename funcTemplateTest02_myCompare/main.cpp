#include <iostream>
#include <string>

using namespace std;

/**
 * @brief	模板的局限性
 *			模板并不是万能的，有些特定的数据类型需要用具体化方式做特殊实现
 */

/**
 * @brief	自定义数据类型
 * @class	Person
 */
class Person
{
public:
	Person(string name, int age) : m_name(name), m_age(age){};
	~Person() {};

public:
	string m_name;		// 姓名
	int m_age;			// 年龄
};


/**
 * @brief	比较两个数据是否相等
 */
template<typename T>
bool myCompare(T &a, T &b) {
	if (a == b) {
		return true;
	}
	else {
		return false;
	}
}

/**
 * @brief	利用具体化Person的版本实现代码，具体化优先调用
 */
template<> bool myCompare(Person &p1, Person &p2) {
	if (p1.m_age == p2.m_age && p1.m_name == p2.m_name) {
		return true;
	}
	else {
		return false;
	}
}

/**
 * @brief	测试函数1
 */
void test_01() {
	int a = 10;
	int b = 20;

	bool ret = myCompare(a, b);
	if (ret) {
		cout << "a == b" << endl;
	}
	else {
		cout << "a != b" << endl;
	}
}

/**
 * @brief	测试函数2
 */
void test_02() {
	Person p1("Tom", 10);
	Person p2("Tom", 10);

	bool ret = myCompare(p1, p2);
	if (ret) {
		cout << "a == b" << endl;
	}
	else {
		cout << "a != b" << endl;
	}
}

/**
 * @brief	主函数
 */
int main(int argc, char** argv) {
	test_01();		// 测试函数1
	test_02();		// 测试具体化变量

	system("pause");
	return 0;
}