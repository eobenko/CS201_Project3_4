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
    hours currentTime;
    ifstream people;
    priority_queue<Patient> patientQueue;
    vector<Doctor> activeDoctors;
    BTree<Patient, B_PATIENTS> patients;
    BTree<Doctor, B_DOCTORS> doctors;
    vector<Room> rooms;
    void populateDoctors();
    int normalDistribution(mt19937 &gen, int min, int max);
    void findActiveDoctors();
    void traverse(BTreeNode<Doctor, B_DOCTORS> *x);
    void findRandomPatients();
    void push(Patient p);
    Patient pop();
    void populateRooms();

public:
    Hospital();
    hours incrementTime();
    Room getRoom(int roomNumber);
    Room getRoomViaPatient(string name, int year, int month, int day); // Search all rooms not the b-tree
    Doctor getDoctor(string name, int year, int month, int day);       // Search the b-tree for the doctor
};

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