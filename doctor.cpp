#include "person.h"
using namespace std::chrono;
// Doctor: name, age, date of birth, skill, shift start, shift end.
class Doctor : public Person
{
private:
    int skill;
    hours shift_start;
    hours shift_end;

public:
    Doctor(std::string n, year y, month m, day d, int s, hours start, hours end) : Person(n, y, m, d)
    {
        skill = s;
        shift_start = start;
        shift_end = end;

        if (skill > 10)
        {
            skill = 10;
        }
        else if (skill < 0)
        {
            skill = 0;
        }
    }

    Doctor(std::string n, int y, int m, int d, int s, int start, int end) : Person(n, y, m, d)
    {
        skill = s;
        shift_start = hours(start);
        shift_end = hours(end);

        if (skill > 10)
        {
            skill = 10;
        }
        else if (skill < 0)
        {
            skill = 0;
        }
    }

    int skill_level()
    {
        return skill;
    }

    bool is_on_shift(hours current_time)
    {
        return (current_time >= shift_start && current_time <= shift_end);
    }

    hours shift_start_time()
    {
        return shift_start;
    }

    hours shift_end_time()
    {
        return shift_end;
    }
};