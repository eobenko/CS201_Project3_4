#include <queue>
#include "bTree.h"
#include "patient.h"
#include "doctor.h"
#include <fstream>
#include <random>
#include <vector>

using namespace std;

// A room holds one doctor and one patient. Room numbers are multiples of 18.
struct Room
{
public:
    int roomNumber;
    Doctor assignedDoctor;
    Patient assignedPatient;
    // Creates a room with the given number, doctor and patient
    Room(int number, Doctor d, Patient p)
    {
        roomNumber = number;
        assignedDoctor = d;
        assignedPatient = p;
    }
};

// Orders patients so the one with the highest condition is seen first
struct PatientPriority
{
    bool operator()(const Patient &a, const Patient &b) const
    {
        return a.getCondition() < b.getCondition();
    }
};

// Orders doctors so the one with the highest skill is picked first
struct DoctorPriority
{
    bool operator()(const Doctor &a, const Doctor &b) const
    {
        return a.skillLevel() < b.skillLevel();
    }
};

// Runs the simulation. Holds the doctor and patient b-trees, the waiting queue, and the rooms. Time advances one hour per incrementTime() call.
class Hospital
{
private:
    static const int B_PATIENTS = 4;
    static const int B_DOCTORS = 4;
    static const int CONDITION_WORSEN = 1; // Condition gained per hour while a patient waits
    hours currentTime;
    ifstream people;
    priority_queue<Patient, vector<Patient>, PatientPriority> patientQueue;
    priority_queue<Doctor, vector<Doctor>, DoctorPriority> activeDoctors;
    BTree<Patient, B_PATIENTS> patients;
    BTree<Doctor, B_DOCTORS> doctors;
    vector<Room> rooms;
    // Reads the doctors from people.txt and inserts them into the doctor b-tree
    void populateDoctors();
    // Returns a random value between min and max, centred between them
    int normalDistribution(mt19937 &gen, int min, int max);
    // Rebuilds the queue of doctors who are on shift at the current hour
    void findActiveDoctors();
    // Walks the doctor b-tree and queues every doctor who is on shift
    void traverse(BTreeNode<Doctor, B_DOCTORS> *x);
    // Searches the doctor b-tree by name
    Doctor findDoctor(BTreeNode<Doctor, B_DOCTORS> *x, string name);
    // Adds 20 to 40 new patients from people.txt, each with a random condition, to the b-tree and waiting queue
    void findRandomPatients();
    // Removes and returns the waiting patient with the highest condition
    Patient pop();
    // Removes and returns the active doctor with the highest skill
    Doctor popDoctor();
    // Pairs active doctors with waiting patients to fill the rooms
    void populateRooms();
    // Heals each patient in a room by their doctor's skill. Unhealed patients go back to the queue, healed patients are discharged.
    void healPatients();
    // Makes each waiting patient worse by CONDITION_WORSEN and updates their record
    void worsenWaitingPatients();
    // Replaces a patient's record in the b-tree so the stored condition is current
    void updatePatientRecord(Patient p);

public:
    // Loads the doctors from people.txt, fills the doctor b-tree and starts at hour 0
    Hospital();
    // Advances the simulation by one hour and returns the new hour
    hours incrementTime();
    // Returns the room with the given number, or a room with number -1 if none
    Room getRoom(int roomNumber);
    // Returns the room of the patient with the given name, or a room with number -1 if none
    Room getRoomViaPatient(string name);
    // Returns the room of the doctor with the given name, or a room with number -1 if none
    Room getRoomViaDoctor(string name);
    Doctor getDoctor(string name); // Search the b-tree for the doctor
    Doctor getDoctor(string name, int year, int month, int day); // Search the b-tree using the full name and date of birth
    Patient getPatient(string name, int year, int month, int day); // Search the b-tree using the full name and date of birth
    // Deletes a patient from the b-tree, the waiting queue and their room, if they are in one
    void deletePatient(string name, int year, int month, int day);
    // Returns a copy of the waiting patients in the order they will be seen, most critical first
    vector<Patient> getWaitingPatients();
};
