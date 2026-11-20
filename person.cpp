#include "person.h"

// Creates a person with the given name and date of birth
Person::Person(std::string n, std::chrono::year y, month m, day d)
{
    name = n;
    dob = year_month_day(y, m, d);
}

// Creates a person with the given name and date of birth
Person::Person(std::string n, int y, int m, int d)
{
    name = n;
    dob = year_month_day(year(y), month(m), day(d));
}

// Returns the full name
std::string Person::getName()
{
    return name;
}

// Returns the date of birth
year_month_day Person::getDob()
{
    return dob;
}

// Returns the age in whole years today. The age goes up on the birthday, not on 1 January.
years Person::getAge()
{
    year_month_day today(floor<days>(system_clock::now()));
    years age = today.year() - dob.year();
    if (month_day(today.month(), today.day()) < month_day(dob.month(), dob.day()))
        age -= years(1);
    return age;
}

// Two people are equal when both name and date of birth match
bool Person::operator==(const Person &rhs) const
{
    return dob == rhs.dob && name == rhs.name;
}

// Two people are different when the name or date of birth differ
bool Person::operator!=(const Person &rhs) const
{
    return !operator==(rhs);
}

// Orders by name, then by date of birth. This is the b-tree key order.
bool Person::operator<(const Person &rhs) const
{
    if (name != rhs.name)
        return name < rhs.name;
    return dob < rhs.dob;
}

// Orders by name, then by date of birth. This is the b-tree key order.
bool Person::operator>(const Person &rhs) const
{
    if (name != rhs.name)
        return name > rhs.name;
    return dob > rhs.dob;
}

// Orders by name, then by date of birth. This is the b-tree key order.
bool Person::operator<=(const Person &rhs) const
{
    return !operator>(rhs);
}

// Orders by name, then by date of birth. This is the b-tree key order.
bool Person::operator>=(const Person &rhs) const
{
    return !operator<(rhs);
}
