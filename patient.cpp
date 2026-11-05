#include "person.h"

class Patient : public Person
{
protected:
    int condition;

public:
    int condition()
    {
        return condition;
    }
    int setCondition(int c)
    {
        if (c < 0)
            condition = 0;
        else if (c > 10)
            condition = 10;
        else
            condition = c;
    }

    bool operator==(const Patient &rhs)
    {
        return condition == rhs.condition;
    }
    bool operator!=(const Patient &rhs)
    {
        return condition != rhs.condition;
    }
    bool operator<(const Patient &rhs)
    {
        return condition < rhs.condition;
    }
    bool operator>(const Patient &rhs)
    {
        return condition > rhs.condition;
    }
    bool operator<=(const Patient &rhs)
    {
        return condition <= rhs.condition;
    }
    bool operator>=(const Patient &rhs)
    {
        return condition >= rhs.condition;
    }
};