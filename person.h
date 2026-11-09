#ifndef PERSON_H
#define PERSON_H
#include <chrono>
#include <string>
using namespace std::chrono;

class Person
{
protected:
    std::string name;
    std::chrono::year_month_day dob;

public:
    Person(std::string n, std::chrono::year y, month m, day d);
    Person(std::string n, int y, int m, int d);
    std::string getName();
    year_month_day getDob();
    years getAge();
    bool operator==(const Person &rhs);
    bool operator!=(const Person &rhs);
    bool operator<(const Person &rhs);
    bool operator>(const Person &rhs);
    bool operator<=(const Person &rhs);
    bool operator>=(const Person &rhs);
};

#endif
