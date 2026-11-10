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
    void populateDoctors();
    int randomSkill(mt19937 &gen);
    void findActiveDoctors();
    void traverse(BTreeNode<Doctor &, B_DOCTORS> *x);
    void findRandomPatients();
    void push(Patient &p);
    Patient &pop();

public:
    Hospital();
    void incrementTime();
};