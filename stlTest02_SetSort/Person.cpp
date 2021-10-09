#include "Person.h"

Person::Person(string name, int age, int height, double weight)
{
    this->m_name = name;
    this->m_age = age;
    this->m_height = height;
    this->m_weight = weight;
}

Person::~Person()
{
}

bool Person::operator<(const Person & person)
{
    // 优先级按照年龄、身高、体重降序
    if (this->m_age == person.m_age)
    {
        if (this->m_height == person.m_height)
        {
            return this->m_weight < person.m_weight;
        }
        return this->m_height < person.m_height;
    }
    return this->m_age < person.m_age;
}

bool Person::operator>(const Person & person)
{
    // 优先级按照年龄、身高、体重升序
    if (this->m_age == person.m_age)
    {
        if (this->m_height == person.m_height)
        {
            return this->m_weight > person.m_weight;
        }
        return this->m_height > person.m_height;
    }
    return this->m_age > person.m_age;
}

ostream& operator<<(ostream& output, const Person& person)
{
    output << "name: " << person.m_name
        << " age: " << person.m_age
        << " height: " << person.m_height
        << " weight: " << person.m_weight;
    return output;
}