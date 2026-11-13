#include "doctor.h"

Doctor::Doctor(std::string n, year y, month m, day d, int s, hours start, hours end) : Person(n, y, m, d)
{
    skill = s;
    shiftStart = start;
    shiftEnd = end;

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
    shiftStart = hours(start);
    shiftEnd = hours(end);

    if (skill > MAX_SKILL)
    {
        skill = MAX_SKILL;
    }
    else if (skill < MIN_SKILL)
    {
        skill = MIN_SKILL;
    }
}

Doctor::Doctor() : Doctor("", 0, 1, 1, 0, 0, 0) {}

int Doctor::skillLevel()
{
    return skill;
}

bool Doctor::isOnShift(hours current_time)
{
    if (shiftStart <= shiftEnd)
    {
        return (current_time >= shiftStart && current_time <= shiftEnd);
    }
    else
    {
        return (current_time >= shiftStart || current_time <= shiftEnd);
    }
}

hours Doctor::shiftStartTime()
{
    return shiftStart;
}

hours Doctor::shiftEndTime()
{
    return shiftEnd;
}
