#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <chrono>

class Person {
protected:
    std::string name;
    std::chrono::year_month_day dob;
public:
    Person(std::string n, std::chrono::year y, std::chrono::month m, std::chrono::day d);
    Person(std::string n, int y, int m, int d);
    std::string name();
    std::chrono::year_month_day dob();
    std::chrono::years age();
};

#endif