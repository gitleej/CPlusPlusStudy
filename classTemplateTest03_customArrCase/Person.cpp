#include "Person.h"



Person::Person()
{
}

Person::Person(string name, int age)
{
	this->m_name = name;
	this->m_age = age;
}

Person::~Person()
{
}

ostream & operator<<(ostream & output, const Person & person)
{
	// TODO: 在此处插入 return 语句
	output << "name: " << person.m_name << "\tage: " << person.m_age;
	return output;
}
