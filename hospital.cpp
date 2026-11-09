#include "hospital.h"

void Hospital::populateTrees()
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
    const int DOCTOR_AMOUNT = 2000;
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

void Hospital::findActiveDoctors()
{
    activeDoctors.clear();
    traverse(doctors.root);
}

// Function to traverse the tree
void Hospital::traverse(BTreeNode<Doctor &, B_DOCTORS> *x)
{
    int i;
    for (i = 0; i < x->n; i++)
    {
        if (!x->leaf)
            traverse(x->children[i]);
        if (x->keys[i].isOnShift(current_time))
            activeDoctors.push_back(x->keys[i]);
    }

    if (!x->leaf)
        traverse(x->children[i]);
}

Hospital::Hospital()
{
    patientQueue = std::priority_queue<Patient &>();
    patients = BTree<Patient &, B_PATIENTS>();
    doctors = BTree<Doctor &, B_DOCTORS>();
    current_time = hours(0);
    populateTrees();
    findActiveDoctors();
}

void Hospital::push(Patient &p)
{
    patientQueue.push(p);
}

Patient &Hospital::pop()
{
    Patient &p = patientQueue.top();
    patientQueue.pop();
    return p;
}

void Hospital::incrementTime()
{
    current_time++;

    if (current_time == hours(24))
    {
        current_time = hours(0);
    }

    findActiveDoctors();
}