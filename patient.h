#include "person.h"

// A patient with a condition from 0 (healthy) to 10 (critical)
class Patient : public Person
{
protected:
    int condition;

public:
    // Creates a patient with the given name and date of birth, starting healthy
    Patient(std::string n, int y, int m, int d);
    // Creates a patient with the given name and date of birth, starting healthy
    Patient(std::string n, year y, month m, day d);
    // Creates an empty patient
    Patient();

    static const int MIN_CONDITION = 0;
    static const int MAX_CONDITION = 10;

    // Returns the current condition
    int getCondition() const;
    // Sets the condition, keeping it between MIN_CONDITION and MAX_CONDITION
    void setCondition(int c);
    // Lowers the condition by amount. Returns true once the patient is healthy.
    bool heal(int amount);
};
