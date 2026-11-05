#include <queue>
#include "bTree.h"
#include "patient.cpp" //Will change to patient.h
#include "doctor.cpp" //Will change to doctor.h

class Hospital {
protected:
    std::priority_queue<Patient&> patientQueue;
    //BTree<Person, /*B-value*/> patients;
    //BTree<Person, /*B-value*/> doctors;
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