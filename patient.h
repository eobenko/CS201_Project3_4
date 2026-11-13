#include "person.h"

class Patient : public Person
{
protected:
    int condition;

public:
    Patient(std::string n, int y, int m, int d);
    Patient(std::string n, year y, month m, day d);
	Patient();

    static const int MIN_CONDITION = 0;
    static const int MAX_CONDITION = 10;

    int getCondition();
    void setCondition(int c);
};
