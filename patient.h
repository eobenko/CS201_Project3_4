#include "person.h"

class Patient : public Person
{
protected:
    int condition;

public:
    Patient(std::string n, int y, int m, int d, int c);
    Patient(std::string n, year y, month m, day d, int c);

    int getCondition();
    int setCondition(int c);

    bool operator==(const Patient &rhs);
    bool operator!=(const Patient &rhs);
    bool operator<(const Patient &rhs);
    bool operator>(const Patient &rhs);
    bool operator<=(const Patient &rhs);
    bool operator>=(const Patient &rhs);
};