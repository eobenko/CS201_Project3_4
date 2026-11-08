#include "person.h"

class Patient : public Person
{
protected:
    int condition;

public:
    Patient(std::string n, int y, int m, int d);
    Patient(std::string n, year y, month m, day d);

    int getCondition();
    void setCondition(int c);

    bool operator==(const Patient &rhs);
    bool operator!=(const Patient &rhs);
    bool operator<(const Patient &rhs);
    bool operator>(const Patient &rhs);
    bool operator<=(const Patient &rhs);
    bool operator>=(const Patient &rhs);
};