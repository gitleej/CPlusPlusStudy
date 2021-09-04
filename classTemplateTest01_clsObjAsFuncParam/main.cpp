/**
 * @brief	模板对象作函数参数
 *			1. 显示指定传入类型
 *			2. 参数模板化
 *			3. 整个类模板化
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
	cout << "姓名： " << this->m_name << "年龄：" << this->m_age << endl;
}

/**
 * @brief	指定传入类型
 */
void printPerson1(Person<string, int>&p) {
	p.showPerson();
}

/**
 * @brief	参数模板化
 */
template<typename T1, typename T2>
void printPerson2(Person<T1, T2> p) {
	p.showPerson();
	cout << "T1 data type: " << typeid(T1).name() << endl;
	cout << "T2 data type: " << typeid(T2).name() << endl;
}

/**
 * @brief	整个类模板化
 */
template<typename T>
void printPerson3(T &p) {
	p.showPerson();
	cout << "T data type: " << typeid(T).name() << endl;

}

void test01() {
	Person<string, int> p("张三", 18);
	printPerson1(p);
}

void test02() {
	Person<string, int> p("李四", 19);
	printPerson2(p);
}

void test03() {
	Person<string, int> p("王五", 20);
	printPerson3(p);
}


int main(int argc, char** argv) {
	test01();
	test02();
	test03();

	system("pause");
	return 0;
}
