#include <queue>
#include "bTree.h"
#include "patient.h"
#include "doctor.h"
#include <fstream>
#include <random>
#include <vector>

using namespace std;

struct Room
{
public:
    int roomNumber;
    Doctor assignedDoctor;
    Patient assignedPatient;
    Room(int number, Doctor d, Patient p)
    {
        roomNumber = number;
        assignedDoctor = d;
        assignedPatient = p;
    }
};

class Hospital
{
private:
    static const int B_PATIENTS = 4;
    static const int B_DOCTORS = 4;
    hours currentTime;
    ifstream people;
    priority_queue<Patient> patientQueue;
    priority_queue<Doctor> activeDoctors;
    BTree<Patient, B_PATIENTS> patients;
    BTree<Doctor, B_DOCTORS> doctors;
    vector<Room> rooms;
    void populateDoctors();
    int normalDistribution(mt19937 &gen, int min, int max);
    void findActiveDoctors();
    void traverse(BTreeNode<Doctor, B_DOCTORS> *x);
    Doctor findDoctor(BTreeNode<Doctor, B_DOCTORS> *x, string name);
    void findRandomPatients();
    Patient pop();
    Doctor popDoctor();
    void populateRooms();

public:
    Hospital();
    hours incrementTime();
    Room getRoom(int roomNumber);
    Room getRoomViaPatient(string name); 
    Room getRoomViaDoctor(string name);  
    Doctor getDoctor(string name);       // Search the b-tree for the doctor
};