#include "person.h"

class Patient : public Person
{
protected:
    int condition;

public:
    int getCondition();
    int setCondition(int c);
    bool operator==(const Patient &rhs);
    bool operator!=(const Patient &rhs);
    bool operator<(const Patient &rhs);
    bool operator>(const Patient &rhs);
    bool operator<=(const Patient &rhs);
    bool operator>=(const Patient &rhs);
};