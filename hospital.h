#include <queue>
#include "bTree.h"
#include "patient.h"
#include "doctor.h"
#include <fstream>
#include <random>

using namespace std;
class Hospital
{
private:
    static const int B_PATIENTS = 4;
    static const int B_DOCTORS = 4;
    hours current_time;

    priority_queue<Patient &> patientQueue;
    BTree<Person &, B_PATIENTS> patients;
    BTree<Person &, B_DOCTORS> doctors;

public:
    Hospital();
    void populateTrees();
    void push(Patient &p);
    Patient &pop();
    void incrementTime();
};