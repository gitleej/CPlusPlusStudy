/**
 * @brief	��һ�ַ�ʽ����������ʵ�ַֿ���д������cppԴ�ļ���ͨ����������
 */
#include "Person.cpp"

/**
 * @brief	�ڶ��ַ�ʽ����������ʵ��д��ͬһ���ļ��У������ļ���׺����Ϊhpp������hpp�ļ�
 */
#include "Person.hpp"

#include <iostream>

void test01() {
	Person<string, int> p("����", 18);
	p.showPerson();
}

int main(int argc, char **argv) {
	test01();

	system("pause");
	return 0;
}