/**
 * @brief	ģ���������������
 *			1. ��ʾָ����������
 *			2. ����ģ�廯
 *			3. ������ģ�廯
 */
#include <iostream>
#include <string>

using namespace std;


template<class T1, class T2>
class Person {
public:
	Person(T1 name, T2 age);

	void showPerson();

	T1 m_name;
	T2 m_age;
};

template<class T1, class T2>
Person<T1, T2>::Person(T1 name, T2 age) {
	this->m_name = name;
	this->m_age = age;
}

template<class T1, class T2>
void Person<T1, T2>::showPerson() {
	cout << "������ " << this->m_name << "���䣺" << this->m_age << endl;
}

/**
 * @brief	ָ����������
 */
void printPerson1(Person<string, int>&p) {
	p.showPerson();
}

/**
 * @brief	����ģ�廯
 */
template<typename T1, typename T2>
void printPerson2(Person<T1, T2> p) {
	p.showPerson();
	cout << "T1 data type: " << typeid(T1).name() << endl;
	cout << "T2 data type: " << typeid(T2).name() << endl;
}

/**
 * @brief	������ģ�廯
 */
template<typename T>
void printPerson3(T &p) {
	p.showPerson();
	cout << "T data type: " << typeid(T).name() << endl;

}

void test01() {
	Person<string, int> p("����", 18);
	printPerson1(p);
}

void test02() {
	Person<string, int> p("����", 19);
	printPerson2(p);
}

void test03() {
	Person<string, int> p("����", 20);
	printPerson3(p);
}


int main(int argc, char** argv) {
	test01();
	test02();
	test03();

	system("pause");
	return 0;
}
