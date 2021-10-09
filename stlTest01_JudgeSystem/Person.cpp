#include "Person.h"

Person::Person()
{
}

Person::Person(string name, double score)
{
    this->m_name = name;
    this->m_score = score;
}

Person::~Person()
{}