/**
 * @brief	第一种方式，将声明和实现分开编写，引用cpp源文件，通常不这样做
 */
#include "Person.cpp"

/**
 * @brief	第二种方式，将声明和实现写在同一个文件中，并将文件后缀名改为hpp，引用hpp文件
 */
#include "Person.hpp"

#include <iostream>

void test01() {
	Person<string, int> p("张三", 18);
	p.showPerson();
}

int main(int argc, char **argv) {
	test01();

	system("pause");
	return 0;
}