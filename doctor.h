#include "person.h"
using namespace std::chrono;

class Doctor : public Person
{
private:
    int skill;
    hours shift_start;
    hours shift_end;

public:
    static const int MIN_SKILL = 1;
    static const int MAX_SKILL = 10;

    Doctor(std::string n, year y, month m, day d, int s, hours start, hours end);
    Doctor(std::string n, int y, int m, int d, int s, int start, int end);
    int skill_level();
    bool is_on_shift(hours current_time);
    hours shift_start_time();
    hours shift_end_time();
};