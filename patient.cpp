#include "person.h"

class Patient : public Person {
protected:
    int level;
public:
    int level() {
        return level;
    }
    int setLevel(int l) {
        if      (l < 0)     level = 0;
        else if (l > 10)    level = 10;
        else                level = l;
    }

    bool operator==(const Patient& rhs) {
        return level == rhs.level;
    }
    bool operator!=(const Patient& rhs) {
        return level != rhs.level;
    }
    bool operator<(const Patient& rhs) {
        return level < rhs.level;
    }
    bool operator>(const Patient& rhs) {
        return level > rhs.level;
    }
    bool operator<=(const Patient& rhs) {
        return level <= rhs.level;
    }
    bool operator>=(const Patient& rhs) {
        return level >= rhs.level;
    }
};