#include "Staff.h"

Staff::Staff(string name, int salary)
{
    this->m_name = name;
    this->m_salary = salary;
}

Staff::~Staff()
{
}

ostream & operator<<(ostream & output, const Staff & staff)
{
    output << "name: " << staff.m_name
        << " salary: " << staff.m_salary;

    return output;
}
