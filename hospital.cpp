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

    void populateTrees()
    {
        ifstream people("people.txt");

        if (!people)
        {
            cerr << "Failed to open people.txt\n";
            return;
        }

        string firstName;
        string lastName;
        int year;
        int month;
        int day;
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> skillDist(Doctor::MIN_SKILL, Doctor::MAX_SKILL);
        uniform_int_distribution<int> shiftStartDist(0, 23);
        uniform_int_distribution<int> shiftEndDist(0, 23);
        int skill;
        int shiftStart;
        int shiftEnd;
        const int DOCTOR_AMOUNT = 1000;
        int count = 0;

        while (people >> firstName >> lastName >> year >> month >> day)
        {
            if (count < DOCTOR_AMOUNT)
            {
                skill = skillDist(gen);
                shiftStart = shiftStartDist(gen);
                shiftEnd = shiftEndDist(gen);

                while (shiftEnd == shiftStart)
                {
                    shiftEnd = shiftEndDist(gen);
                }

                Doctor doctor(firstName + " " + lastName, year, month, day, skill, shiftStart, shiftEnd);
                doctors.insert(doctor);
                count++;
            }
            else
            {
                Patient patient(firstName + " " + lastName, year, month, day);
                patients.insert(patient);
            }
        }
    }

public:
    Hospital()
    {
        patientQueue = std::priority_queue<Patient &>();
        patients = BTree<Person &, B_PATIENTS>();
        doctors = BTree<Person &, B_DOCTORS>();
        current_time = hours(0);
        populateTrees();
    }

    void push(Patient &p)
    {
        patientQueue.push(p);
    }

    Patient &pop()
    {
        Patient &p = patientQueue.top();
        patientQueue.pop();
        return p;
    }

    void incrementTime()
    {
        current_time++;

        if (current_time == hours(24))
        {
            current_time = hours(0);
        }
    }
};