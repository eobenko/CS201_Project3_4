#include "hospital.h"

void Hospital::populateDoctors()
{
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
        if (count >= DOCTOR_AMOUNT)
        {
            break;
        }
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
}

/*
int Hospital::normalDistribution(mt19937 &gen, int min, int max)
{
    if (min >= max)
    {
        return min;
    }

    double mean = (min + max) / 2.0;
    double standard_deviation = (max - min) / 6.0;
    normal_distribution<double> dist(mean, standard_deviation);

    int result;
    do
    {
        result = round(dist(gen));
    } while (result < min || result > max);

    return result;
}
*/
void Hospital::findActiveDoctors()
{
    activeDoctors.clear();
    traverse(doctors.root);
}

void Hospital::traverse(BTreeNode<Doctor, B_DOCTORS> *x)
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

void Hospital::findRandomPatients()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> patientDist(0, 5);
    uniform_int_distribution<int> conditionDist(Patient::MIN_CONDITION, Patient::MAX_CONDITION);

    for (int i = 0; i < patientDist(gen); i++)
    {
        string firstName;
        string lastName;
        int year;
        int month;
        int day;
        if (people >> firstName >> lastName >> year >> month >> day)
        {
            Patient patient(firstName + " " + lastName, year, month, day);
            patients.insert(patient);
            patient.setCondition(conditionDist(gen));
            push(patient);
        }
    }
}

Hospital::Hospital() : people("people.txt")
{
    patientQueue = std::priority_queue<Patient>();
    patients = BTree<Patient, B_PATIENTS>();
    doctors = BTree<Doctor, B_DOCTORS>();
    current_time = hours(0);

    populateDoctors();
    findActiveDoctors();
}

void Hospital::push(Patient p)
{
    patientQueue.push(p);
}

Patient Hospital::pop()
{
    Patient p = patientQueue.top();
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
    findRandomPatients();
}