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
        skill = normalDistribution(gen, Doctor::MIN_SKILL, Doctor::MAX_SKILL);
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

void Hospital::findActiveDoctors()
{
    activeDoctors = priority_queue<Doctor>();
    traverse(doctors.root);
}

void Hospital::traverse(BTreeNode<Doctor, B_DOCTORS> *x)
{
    int i;
    for (i = 0; i < x->n; i++)
    {
        if (!x->leaf)
            traverse(x->children[i]);
        if (x->keys[i].isOnShift(currentTime))
            activeDoctors.push(x->keys[i]);
    }

    if (!x->leaf)
        traverse(x->children[i]);
}

Doctor Hospital::findDoctor(BTreeNode<Doctor, B_DOCTORS> *x, string name)
{
    int i = 0;
    while (i < x->n && name > x->keys[i].getName())
        i++;

    if (i < x->n && name == x->keys[i].getName())
        return x->keys[i];

    if (x->leaf)
        return Doctor();

    return findDoctor(x->children[i], name);
}

void Hospital::findRandomPatients()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> patientDist(20, 40);
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
            patientQueue.push(patient);
        }
    }
}

Hospital::Hospital() : people("people.txt")
{
    patientQueue = std::priority_queue<Patient>();
    activeDoctors = std::priority_queue<Doctor>();
    patients = BTree<Patient, B_PATIENTS>();
    doctors = BTree<Doctor, B_DOCTORS>();
    rooms = vector<Room>();
    currentTime = hours(0);

    populateDoctors();
    findActiveDoctors();
}

Patient Hospital::pop()
{
    Patient p = patientQueue.top();
    patientQueue.pop();
    return p;
}

Doctor Hospital::popDoctor()
{
    Doctor d = activeDoctors.top();
    activeDoctors.pop();
    return d;
}

void Hospital::populateRooms()
{
    rooms.clear();

    while (activeDoctors.size() > 0 && patientQueue.size() > 0)
    {
        Doctor d = popDoctor();
        Patient p = pop();
        Room room(rooms.size() * 18, d, p);
        rooms.push_back(room);
    }
}

void Hospital::healPatients()
{
    for (Room &room : rooms)
    {
        if (!room.assignedPatient.heal(room.assignedDoctor.skillLevel()))
        {
            patientQueue.push(room.assignedPatient);
        }
    }
}

hours Hospital::incrementTime()
{
    healPatients();
    currentTime++;

    if (currentTime == hours(24))
    {
        currentTime = hours(0);
    }

    findActiveDoctors();
    findRandomPatients();
    populateRooms();

    return currentTime;
}

Room Hospital::getRoom(int roomNumber)
{
    for (Room room : rooms)
    {
        if (room.roomNumber == roomNumber)
        {
            return room;
        }
    }

    return Room(-1, Doctor(), Patient());
}

Room Hospital::getRoomViaPatient(string name)
{
    for (Room room : rooms)
    {
        if (room.assignedPatient.getName() == name)
        {
            return room;
        }
    }

    return Room(-1, Doctor(), Patient());
}

Room Hospital::getRoomViaDoctor(string name)
{
    for (Room room : rooms)
    {
        if (room.assignedDoctor.getName() == name)
        {
            return room;
        }
    }

    return Room(-1, Doctor(), Patient());
}

Doctor Hospital::getDoctor(string name)
{
    return findDoctor(doctors.root, name);
}
