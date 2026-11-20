#include "doctor.h"

// Creates a doctor with a date of birth, skill, and shift. Skill is clamped to MIN_SKILL and MAX_SKILL.
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

// Creates a doctor with a date of birth, skill, and shift. Skill is clamped to MIN_SKILL and MAX_SKILL.
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

// Creates an empty doctor
Doctor::Doctor() : Doctor("", 0, 1, 1, 0, 0, 0) {}

// Returns the skill, from MIN_SKILL to MAX_SKILL
int Doctor::skillLevel() const
{
    return skill;
}

// Returns true if the given hour falls inside the shift. A shift that ends before it starts wraps past midnight.
bool Doctor::isOnShift(hours current_time) const
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

// Returns the hour the shift starts
hours Doctor::shiftStartTime() const
{
    return shiftStart;
}

// Returns the hour the shift ends
hours Doctor::shiftEndTime() const
{
    return shiftEnd;
}
