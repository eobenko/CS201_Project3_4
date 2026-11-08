#include "patient.h"

Patient::Patient(std::string n, int y, int m, int d) : Person(n, y, m, d)
{
    condition = 0;
}

Patient::Patient(std::string n, year y, month m, day d) : Person(n, y, m, d)
{
    condition = 0;
}

int Patient::getCondition()
{
    return condition;
}

void Patient::setCondition(int c)
{
    if (c < 0)
        condition = 0;
    else if (c > 10)
        condition = 10;
    else
        condition = c;
}

bool Patient::operator==(const Patient &rhs)
{
    return condition == rhs.condition;
}
bool Patient::operator!=(const Patient &rhs)
{
    return condition != rhs.condition;
}
bool Patient::operator<(const Patient &rhs)
{
    return condition < rhs.condition;
}
bool Patient::operator>(const Patient &rhs)
{
    return condition > rhs.condition;
}
bool Patient::operator<=(const Patient &rhs)
{
    return condition <= rhs.condition;
}
bool Patient::operator>=(const Patient &rhs)
{
    return condition >= rhs.condition;
}