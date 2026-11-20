#include "person.h"
using namespace std::chrono;

// A doctor with a skill from 1 to 10 and a shift that can wrap past midnight
class Doctor : public Person
{
private:
    int skill;
    hours shiftStart;
    hours shiftEnd;

public:
    static const int MIN_SKILL = 1;
    static const int MAX_SKILL = 10;

    // Creates a doctor with a date of birth, skill and shift
    Doctor(std::string n, year y, month m, day d, int s, hours start, hours end);
    // Creates a doctor with a date of birth, skill and shift
    Doctor(std::string n, int y, int m, int d, int s, int start, int end);
    // Creates an empty doctor
    Doctor();
    // Returns the skill, from MIN_SKILL to MAX_SKILL
    int skillLevel() const;
    // Returns true if the given hour falls inside the shift
    bool isOnShift(hours current_time) const;
    // Returns the hour the shift starts
    hours shiftStartTime() const;
    // Returns the hour the shift ends
    hours shiftEndTime() const;
};
