#include <queue>
#include "bTree.h"
#include "patient.cpp" //Will change to patient.h
#include "doctor.cpp" //Will change to doctor.h

class Hospital {
protected:
    static const int B_PATIENTS = 4;
    static const int B_DOCTORS = 4;

    std::priority_queue<Patient&> patientQueue;
    BTree<Person&, B_PATIENTS> patients;
    BTree<Person&, B_DOCTORS> doctors;
public:
    void push(Patient& p) {
        patientQueue.push(p);
    }
    Patient& pop() {
        Patient& p = patientQueue.top();
        patientQueue.pop();
        return p;
    }
};