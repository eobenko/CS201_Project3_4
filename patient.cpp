#include "patient.h"

// Creates a healthy patient with the given name and date of birth
Patient::Patient(std::string n, int y, int m, int d) : Person(n, y, m, d)
{
    condition = MIN_CONDITION;
}

// Creates a healthy patient with the given name and date of birth
Patient::Patient(std::string n, year y, month m, day d) : Person(n, y, m, d)
{
    condition = MIN_CONDITION;
}

// Creates an empty patient
Patient::Patient() : Patient("", 0, 1, 1) {}

// Returns the current condition
int Patient::getCondition() const
{
    return condition;
}

// Sets the condition, clamped to MIN_CONDITION and MAX_CONDITION
void Patient::setCondition(int c)
{
    if (c < MIN_CONDITION)
        condition = MIN_CONDITION;
    else if (c > MAX_CONDITION)
        condition = MAX_CONDITION;
    else
        condition = c;
}

// Lowers the condition by amount, never below MIN_CONDITION. Returns true once the patient is healthy.
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
