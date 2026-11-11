#include "patient.h"

Patient::Patient(std::string n, int y, int m, int d) : Person(n, y, m, d)
{
    condition = MIN_CONDITION;
}

Patient::Patient(std::string n, year y, month m, day d) : Person(n, y, m, d)
{
    condition = MIN_CONDITION;
}

int Patient::getCondition()
{
    return condition;
}

void Patient::setCondition(int c)
{
    if (c < MIN_CONDITION)
        condition = MIN_CONDITION;
    else if (c > MAX_CONDITION)
        condition = MAX_CONDITION;
    else
        condition = c;
}
