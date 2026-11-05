#include "patient.h"

int Patient::getCondition()
{
    return condition;
}

int Patient::setCondition(int c)
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