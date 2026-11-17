#include "person.h"

Person::Person(std::string n, std::chrono::year y, month m, day d)
{
    name = n;
    dob = year_month_day(y, m, d);
}

Person::Person(std::string n, int y, int m, int d)
{
    name = n;
    dob = year_month_day(year(y), month(m), day(d));
}

std::string Person::getName()
{
    return name;
}
year_month_day Person::getDob()
{
    return dob;
}
years Person::getAge()
{
    year_month_day today(floor<days>(system_clock::now()));
    years age = today.year() - dob.year();
    if (month_day(today.month(), today.day()) < month_day(dob.month(), dob.day()))
        age -= years(1);
    return age;
}

bool Person::operator==(const Person &rhs) const
{
    return dob == rhs.dob && name == rhs.name;
}
bool Person::operator!=(const Person &rhs) const
{
    return !operator==(rhs);
}
bool Person::operator<(const Person &rhs) const
{
    if (name != rhs.name)
        return name < rhs.name;
    return dob < rhs.dob;
}
bool Person::operator>(const Person &rhs) const
{
    if (name != rhs.name)
        return name > rhs.name;
    return dob > rhs.dob;
}
bool Person::operator<=(const Person &rhs) const
{
    return !operator>(rhs);
}
bool Person::operator>=(const Person &rhs) const
{
    return !operator<(rhs);
}
