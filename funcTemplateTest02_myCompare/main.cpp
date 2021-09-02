#include <iostream>
#include <string>

using namespace std;

/**
 * @brief	ģ��ľ�����
 *			ģ�岢�������ܵģ���Щ�ض�������������Ҫ�þ��廯��ʽ������ʵ��
 */

/**
 * @brief	�Զ�����������
 * @class	Person
 */
class Person
{
public:
	Person(string name, int age) : m_name(name), m_age(age){};
	~Person() {};

public:
	string m_name;		// ����
	int m_age;			// ����
};


/**
 * @brief	�Ƚ����������Ƿ����
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
 * @brief	���þ��廯Person�İ汾ʵ�ִ��룬���廯���ȵ���
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
 * @brief	���Ժ���1
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
 * @brief	���Ժ���2
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
 * @brief	������
 */
int main(int argc, char** argv) {
	test_01();		// ���Ժ���1
	test_02();		// ���Ծ��廯����

	system("pause");
	return 0;
}