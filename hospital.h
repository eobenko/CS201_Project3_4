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
    vector<Doctor &> activeDoctors;
    BTree<Patient &, B_PATIENTS> patients;
    BTree<Doctor &, B_DOCTORS> doctors;
    void populateTrees();
    void findActiveDoctors();
    void traverse(BTreeNode<Doctor &, B_DOCTORS> *x);

public:
    Hospital();
    void push(Patient &p);
    Patient &pop();
    void incrementTime();
};