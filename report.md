# Nota Hospital Simulation - Project 3 and Project 4 Report

Team: Ethan Benko, Ronin Goldstine, Benjamin Casciano, Alexander Loff

Build and run: 'make' then 'make run' (needs SFML: '-lsfml-graphics -lsfml-window -lsfml-system'). The UML class diagram is in 'uml_diagram.png'.

# Project 3

## 1. How does the simulation work?

### Data

We used data from the internet with custom C++ programs to generate the doctors and patients, which are read during our program's initialization.

### Data structures

#### B-tree of Patients

Has every patient at the hospital

#### B-tree of Doctors

Has every doctor

#### priority_queue of Patients

Orders patients by condition; the most critical patients are seen first.

#### priority_queue of Doctors

Orders doctors by skill; the most skilled doctors are sent to treat patients first.

#### Vector of Rooms

Has all of the rooms being used during the current hour.

### One hour of simulation

The "Advance Time" button calls "Hospital::incrementTime()", which does the following:

Heals: Each patient in a room with a doctor is healed by the amount of skill that the doctor has. If they still aren't healthy, they go into the waiting queue for the next hour. If they are healthy now, they are discharged from the hospital.

Worsens conditions: If a patient is not receiving care in the current hour, there condition gets 1 point worse.

Finds doctors and admits new patients: New patients are admitted to the hospital with a random condition. They are added to the appropriate data structures. All doctors who are on shift are also loaded into the appropriate data structures.

Fill rooms: The most skilled doctors are put into rooms with the most critical patients until all patients are being treated or there are no more doctors.

### Example

At hour 9 a doctor with skill 7 on shift is paired with a patient with condition 9.
Hour 10, step 1: the patient is healed 9 − 7 = 2, which is not yet healthy, so they return to the queue.
Step 2: while waiting they worsen to 3.
If they are paired with a doctor again, then at hour 11 they are healed by that doctor's skill. A skill of 3 or more takes them to 0, so they are discharged and their record is removed.

### Visual Component

The program runs 8 hours of simulation to get things rocking and rolling. Then a window is opened.
The name of the hospital and the current hour are shown in the main page. There are also buttons to access other pages. Patient search allows for searching for patients with their name and DOB. Doctor search allows searching for doctors by name and DOB. Room list lists every room with a patient. Room lookup allows for showing a room by its room number.

## 2. B-tree: what value of t was chosen, and why?

We chose to have a t value of 2. This results in nodes having a maximum of 3 keys, which results in a very beautiful tree that is easy to work with. We believe that this moderate size is appropriate for the size of our dataset.

## 3. Team contributions


| Member | Contribution |
|---|---|
| Ethan Benko | SFML visuals (visuals.cpp): main menu, patient and doctor record pages, room list with scrolling, room lookup |
| Ronin Goldstine | Hospital simulation core: patient healing, room pairing, doctor and patient generation, normal distribution of doctor skill, doctor shift lookup, Doctor and Person classes |
| Benjamin Casciano | Project setup: README, creating the hospital in main.cpp, randomizer.cpp helper functions |
| Alexander Loff | Makefile; .gitignore; various bug fixes; report.md; uml_diagram.png; comments |


# Project 4

## 1. How does the new simulation work?

Project 4 adds four components.

### Addition 1: B-tree delete

'BTree::remove(k)' was implemented. It deletes from a leaf, from an internal node (using the predecessor or successor, or a merge), and rebalances by borrowing from a sibling or merging with it. If a merge empties the root, its only child becomes the new root. An empty leaf root is kept so later inserts still work. A randomized test against 'std::set' passes.

It is needed because patients leave the hospital. Without delete, the patient B-tree would keep records of everyone who had ever visited, and a search would find patients who were already discharged.

### Addition 2: Patient discharge

When a patient is healed (condition 0), they leave: their record is deleted from the patient B-tree and they do not return to the queue. The patient tree therefore holds only patients currently in the hospital.

### Addition 3: Delete a patient in the GUI

After a successful patient search, a DELETE button appears. 'Hospital::deletePatient' removes the patient from the B-tree, from the waiting queue, and from their room if they are in one. The room list skips the gap left by a deleted room instead of stopping.

### Addition 4: Waiting room page

The main menu has a waiting room button. It opens a list of every patient waiting to be seen, with the most critical first, showing each patient's place in the queue, name, condition, date of birth and age. It scrolls with the mouse wheel like the room list. 'Hospital::getWaitingPatients()' returns a copy of the queue in priority order, so the page shows the same order the simulation uses and does not change the queue.

## 2. Team contributions


| Member | Contribution |
|---|---|
|Ethan Benko | Added all of project 4's visual features |
| Ronin Goldstine | Finished the B-Tree logic |
| Benjamin Casciano | Helped plan features and gave feedback during code review |
| Alexander Loff | Testing, git management, and documentation |


# Sources

Our sources can be found in sources.txt
