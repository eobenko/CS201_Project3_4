#include "patient.h"

Patient::Patient(std::string n, int y, int m, int d) : Person(n, y, m, d)
{
    condition = MIN_CONDITION;
}

Patient::Patient(std::string n, year y, month m, day d) : Person(n, y, m, d)
{
    condition = MIN_CONDITION;
}

Patient::Patient() : Patient("", 0, 1, 1) {}

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

bool Patient::heal(int amount)
{
    condition -= amount;
    if (condition <= MIN_CONDITION)
    {
        condition = MIN_CONDITION;
        return true;
    }
    return false;
}
