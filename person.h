#ifndef PERSON_H
#define PERSON_H
#include <chrono>
#include <string>
using namespace std::chrono;

// A person with a name and date of birth. Base class for patients and doctors.
class Person
{
protected:
    std::string name;
    std::chrono::year_month_day dob;

public:
    // Creates a person with the given name and date of birth
    Person(std::string n, std::chrono::year y, month m, day d);
    // Creates a person with the given name and date of birth
    Person(std::string n, int y, int m, int d);
    // Returns the full name
    std::string getName();
    // Returns the date of birth
    year_month_day getDob();
    // Returns the age in whole years today
    years getAge();
    // Two people are equal when both name and date of birth match
    bool operator==(const Person &rhs) const;
    // Two people are different when the name or date of birth differ
    bool operator!=(const Person &rhs) const;
    // Orders by name, then by date of birth. This is the b-tree key order.
    bool operator<(const Person &rhs) const;
    // Orders by name, then by date of birth. This is the b-tree key order.
    bool operator>(const Person &rhs) const;
    // Orders by name, then by date of birth. This is the b-tree key order.
    bool operator<=(const Person &rhs) const;
    // Orders by name, then by date of birth. This is the b-tree key order.
    bool operator>=(const Person &rhs) const;
};

#endif
