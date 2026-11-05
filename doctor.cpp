#include "doctor.h"

Doctor::Doctor(std::string n, year y, month m, day d, int s, hours start, hours end) : Person(n, y, m, d)
{
    skill = s;
    shift_start = start;
    shift_end = end;

    if (skill > MAX_SKILL)
    {
        skill = MAX_SKILL;
    }
    else if (skill < MIN_SKILL)
    {
        skill = MIN_SKILL;
    }
}

Doctor::Doctor(std::string n, int y, int m, int d, int s, int start, int end) : Person(n, y, m, d)
{
    skill = s;
    shift_start = hours(start);
    shift_end = hours(end);

    if (skill > MAX_SKILL)
    {
        skill = MAX_SKILL;
    }
    else if (skill < MIN_SKILL)
    {
        skill = MIN_SKILL;
    }
}

int Doctor::skill_level()
{
    return skill;
}

bool Doctor::is_on_shift(hours current_time)
{
    return (current_time >= shift_start && current_time <= shift_end);
}

hours Doctor::shift_start_time()
{
    return shift_start;
}

hours Doctor::shift_end_time()
{
    return shift_end;
}