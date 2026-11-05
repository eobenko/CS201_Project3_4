#include "person.h"
#include <chrono>

class Doctor : public Person {
protected:
    static const int MIN_SKILL = 1;
    static const int MAX_SKILL = 10;

    int skillLevel;
    std::chrono::hh_mm_ss<std::chrono::minutes> shiftStart;
    std::chrono::hh_mm_ss<std::chrono::minutes> shiftEnd;
public:
    int skillLevel() {
        return skillLevel;
    }
    void setSkillLevel(int l) {
        if      (l > MIN_SKILL) skillLevel = MIN_SKILL;
        else if (l < MAX_SKILL) skillLevel = MAX_SKILL;
        else                    skillLevel = l;
    }
    std::chrono::hh_mm_ss<std::chrono::minutes> shiftStart() {
        return shiftStart;
    }
    std::chrono::hh_mm_ss<std::chrono::minutes> shiftEnd() {
        return shiftEnd;
    }
    /*bool isIn() {
        return (NOW) >= shiftStart && (NOW) < shiftEnd;
    }*/
};