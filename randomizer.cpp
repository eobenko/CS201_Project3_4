#include <random>
#include <fstream>
#include <string>
#include <chrono>
#include "patient.h"
#include "doctor.h"

using namespace std::chrono;

std::default_random_engine gen;
std::ifstream randomNames("randomnames.txt");
std::uniform_int_distribution<int> randomConditionLevel(1, 10);
std::uniform_int_distribution<int> randomSkillLevel(Doctor::MIN_SKILL, Doctor::MAX_SKILL);
std::uniform_int_distribution<int> randomYear(1920, 2000);
std::uniform_int_distribution<int> randomMonth(1, 12);
std::uniform_int_distribution<int> randomDate28(1, 28);
std::uniform_int_distribution<int> randomDate29(1, 29);
std::uniform_int_distribution<int> randomDate30(1, 30);
std::uniform_int_distribution<int> randomDate31(1, 31);

std::string getRandomName() {
    std::string name;
    randomNames >> name;
    return name;
}

int getRandomConditionLevel() {
    return randomConditionLevel(gen);
}

int getRandomSkillLevel() {
    return randomSkillLevel(gen);
}

std::chrono::year_month_day getRandomDob() {
    int y = randomYear(gen);
    int m = randomMonth(gen);
    int d;

    if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) {
        d = randomDate31(gen);
    } else if (m == 4 || m == 6 || m == 9 || m == 11) {
        d = randomDate30(gen);
    } else { // m == 2
        if (y % 400 == 0 || (y % 4 == 0 && y % 100 != 0)) { // Leap year
            d = randomDate29(gen);
        } else {
            d = randomDate28(gen);
        }
    }
}

Patient& randomPatient() {
    year_month_day t = getRandomDob();
    Patient p(getRandomName(), t.year(), t.month(), t.day(), getRandomConditionLevel());
    return p;
}

// STILL NEED randomDoctor