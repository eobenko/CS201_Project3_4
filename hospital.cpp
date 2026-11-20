#include "hospital.h"

// Reads the doctors from people.txt, gives each a random skill and shift, and inserts them into the doctor b-tree
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

// Returns a whole number from a normal distribution centred between min and max, retried until it falls inside min and max
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

// Clears the active doctor queue and refills it with the doctors on shift at the current hour
void Hospital::findActiveDoctors()
{
    activeDoctors = priority_queue<Doctor, vector<Doctor>, DoctorPriority>();
    traverse(doctors.root);
}

// In-order walk of the doctor b-tree, pushing each doctor who is on shift onto the active queue
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

// Walks down the doctor b-tree comparing names, returns an empty doctor if the name is not found
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

// Reads a random number of patients from people.txt. Each gets a random condition, then goes into the b-tree and the waiting queue.
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
            patient.setCondition(conditionDist(gen));
            patients.insert(patient);
            patientQueue.push(patient);
        }
    }
}

// Sets up empty queues, rooms and b-trees, then loads the doctors and finds who is on shift at hour 0
Hospital::Hospital() : people("people.txt")
{
    patientQueue = std::priority_queue<Patient, vector<Patient>, PatientPriority>();
    activeDoctors = std::priority_queue<Doctor, vector<Doctor>, DoctorPriority>();
    patients = BTree<Patient, B_PATIENTS>();
    doctors = BTree<Doctor, B_DOCTORS>();
    rooms = vector<Room>();
    currentTime = hours(0);

    populateDoctors();
    findActiveDoctors();
}

// Removes and returns the waiting patient with the highest condition
Patient Hospital::pop()
{
    Patient p = patientQueue.top();
    patientQueue.pop();
    return p;
}

// Removes and returns the active doctor with the highest skill
Doctor Hospital::popDoctor()
{
    Doctor d = activeDoctors.top();
    activeDoctors.pop();
    return d;
}

// Empties the rooms, then pairs the best active doctor with the most critical waiting patient until one of the two runs out
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

// Heals each patient in a room by their doctor's skill. A patient who is not yet healed goes back to the queue with an updated record. A patient who is healed is discharged and their record is removed.
void Hospital::healPatients()
{
    for (Room &room : rooms)
    {
        if (!room.assignedPatient.heal(room.assignedDoctor.skillLevel()))
        {
            updatePatientRecord(room.assignedPatient);
            patientQueue.push(room.assignedPatient);
        }
        else
        {
            patients.remove(room.assignedPatient);
        }
    }
}

// Waiting patients get worse every hour until they are seen, reaching critical at 10
void Hospital::worsenWaitingPatients()
{
    priority_queue<Patient, vector<Patient>, PatientPriority> waiting;
    while (patientQueue.size() > 0)
    {
        Patient p = pop();
        p.setCondition(p.getCondition() + CONDITION_WORSEN);
        updatePatientRecord(p);
        waiting.push(p);
    }
    patientQueue = waiting;
}

// Replaces a patient's record in the b-tree. The name and date of birth are the key, so the old record is found and replaced with the current condition.
void Hospital::updatePatientRecord(Patient p)
{
    patients.remove(p);
    patients.insert(p);
}

// Advances the simulation by one hour. Heals patients in rooms, worsens the waiting patients, moves the clock on, then refreshes doctors, admits new patients and refills the rooms.
hours Hospital::incrementTime()
{
    healPatients();
    worsenWaitingPatients();
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

// Returns the room with the given number, or a room with number -1 if there is none
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

// Returns the room of the first patient with the given name, or a room with number -1 if there is none
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

// Returns the room of the first doctor with the given name, or a room with number -1 if there is none
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

// Searches the doctor b-tree by name only
Doctor Hospital::getDoctor(string name)
{
    return findDoctor(doctors.root, name);
}

// Search the b-tree for a doctor using their full name and date of birth
Doctor Hospital::getDoctor(string name, int year, int month, int day)
{
    Doctor key(name, year, month, day, 0, 0, 0);
    BTreeNode<Doctor, B_DOCTORS> *node = doctors.search(key);
    if (node != nullptr)
    {
        for (int i = 0; i < node->n; i++)
        {
            if (node->keys[i] == key)
                return node->keys[i];
        }
    }
    return Doctor();
}

// Search the b-tree for a patient using their full name and date of birth
Patient Hospital::getPatient(string name, int year, int month, int day)
{
    Patient key(name, year, month, day);
    BTreeNode<Patient, B_PATIENTS> *node = patients.search(key);
    if (node != nullptr)
    {
        for (int i = 0; i < node->n; i++)
        {
            if (node->keys[i] == key)
                return node->keys[i];
        }
    }
    return Patient();
}

// Deletes a patient from the b-tree, takes them out of the waiting queue, and removes their room if they are in one. The room's doctor is free again at the next hour.
void Hospital::deletePatient(string name, int year, int month, int day)
{
    Patient key(name, year, month, day);
    patients.remove(key);

    priority_queue<Patient, vector<Patient>, PatientPriority> waiting;
    while (patientQueue.size() > 0)
    {
        Patient p = pop();
        if (p != key)
            waiting.push(p);
    }
    patientQueue = waiting;

    for (auto it = rooms.begin(); it != rooms.end(); ++it)
    {
        if (it->assignedPatient == key)
        {
            rooms.erase(it);
            break;
        }
    }
}

// Returns a copy of the waiting queue, taken from a copy of the queue so the real queue is not changed
vector<Patient> Hospital::getWaitingPatients()
{
    vector<Patient> list;
    priority_queue<Patient, vector<Patient>, PatientPriority> copy = patientQueue;
    while (copy.size() > 0)
    {
        list.push_back(copy.top());
        copy.pop();
    }
    return list;
}
