#include "person.h"
using namespace std::chrono;
class Person
{
protected:
    std::string name;
    year_month_day dob;

public:
    Person(std::string &n, year &y, month &m, day &d)
    {
        name = n;
        dob = year_month_day(y, m, d);
    }
    Person(std::string &n, int y, int m, int d)
    {
        name = n;
        dob = year_month_day(year(y), month(m), day(d));
    }
    std::string name()
    {
        return name;
    }
    year_month_day dob()
    {
        return dob;
    }
    years age()
    {
        year_month_day today(floor<days>(system_clock::now()));
        years age = today.year() - dob.year();
        if (month_day(today.month(), today.day()) < month_day(dob.month(), dob.day()))
            age -= years(1);
        return age;
    }

    bool operator==(const Person &rhs)
    {
        return dob == rhs.dob;
    }
    bool operator!=(const Person &rhs)
    {
        return dob != rhs.dob;
    }
    bool operator<(const Person &rhs)
    {
        return dob < rhs.dob;
    }
    bool operator>(const Person &rhs)
    {
        return dob > rhs.dob;
    }
    bool operator<=(const Person &rhs)
    {
        return dob <= rhs.dob;
    }
    bool operator>=(const Person &rhs)
    {
        return dob >= rhs.dob;
    }
};