#include "person.h"
using namespace std::chrono;

class Doctor : public Person
{
private:
    int skill;
    hours shiftStart;
    hours shiftEnd;

public:
    static const int MIN_SKILL = 1;
    static const int MAX_SKILL = 10;

    Doctor(std::string n, year y, month m, day d, int s, hours start, hours end);
    Doctor(std::string n, int y, int m, int d, int s, int start, int end);
    Doctor();
    int skillLevel() const;
    bool isOnShift(hours current_time) const;
    hours shiftStartTime() const;
    hours shiftEndTime() const;
};
