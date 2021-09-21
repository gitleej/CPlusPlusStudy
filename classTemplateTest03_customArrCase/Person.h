#pragma once
#ifndef _PERSON_H_
#define _PERSON_H_

#include <iostream>
#include <string>

using namespace std;

class Person
{
public:
	Person();
	Person(string name, int age);
	~Person();

	// << ÔËËã·ûÖØ¹¹
	friend ostream &operator<<(ostream &output, const Person &person);

private:
	string m_name;
	int m_age;
};

#endif // !_PERSON_H_

