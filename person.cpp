#include "person.h"

class Person {
protected:
    std::string name;
    std::chrono::year_month_day dob;
public:
    Person(std::string& n, std::chrono::year& y, std::chrono::month& m, std::chrono::day& d) {
        name = n;
        dob = std::chrono::year_month_day(y, m, d);
    }
    Person(std::string& n, int y, int m, int d) {
        name = n;
        dob = std::chrono::year_month_day(std::chrono::year(y), std::chrono::month(m), std::chrono::day(d));
    }
    std::string name() {
        return name;
    }
    std::chrono::year_month_day dob() {
        return dob;
    }
    std::chrono::years age() {
        std::chrono::year_month_day today(floor<std::chrono::days>(std::chrono::system_clock::now()));
        std::chrono::years age = today.year() - dob.year();
        if (std::chrono::month_day(today.month(), today.day()) < std::chrono::month_day(dob.month(), dob.day()))
            age -= std::chrono::years(1);
        return age;
    }
};