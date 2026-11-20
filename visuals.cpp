//#include "hospital.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Window.hpp>
#include <string>
#include <iostream>
#include <array>
#include <vector>
#include "hospital.h"

using namespace std;
using namespace sf;
//Hospital &hospital, copy into () of runVisuals to connect to hospital
//void runVisuals()
// Opens the window and runs the GUI loop. Pages: 0 main menu, 1 patient, 2 doctor, 3 room list, 4 room lookup.
void runVisuals(Hospital &hospital)
{
    //Advance simulation to hour 8 before opening the window, but does it in a way that allows us to see scroll feature
    std::chrono::hours hospitalTime{0};
    for(int i=0;i<8;i++)
    {
        hospitalTime=hospital.incrementTime();
    }

    //Create window
    RenderWindow window(VideoMode({1000, 650}), "Nota Hospital", Style::Titlebar | Style::Close);
    window.setFramerateLimit(60);

    //Colors
    Color background(30, 45, 55);
    Color buttonColor(220, 220, 210);
    Color textColor(30, 45, 55);

    //Load font
    Font font;
    //if(!font.openFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"))
    if(!font.openFromFile("./DejaVuSans.ttf"))
    {
        cout<<"Font failed to load"<<endl;
        return;
    }

    //Main menu title
    Text title(font, "NOTA HOSPITAL", 48);
    title.setFillColor(Color::White);
    title.setPosition({285.f, 95.f});

    //Patient button
    RectangleShape patientButton({250.f, 90.f});
    patientButton.setPosition({75.f, 270.f});
    patientButton.setFillColor(buttonColor);

    Text patientText(font, "PATIENT", 28);//Patient button text
    patientText.setFillColor(textColor);
    patientText.setPosition({140.f, 295.f});

    //Doctor button
    RectangleShape doctorButton({250.f, 90.f});
    doctorButton.setPosition({375.f, 270.f});
    doctorButton.setFillColor(buttonColor);

    Text doctorText(font, "DOCTOR", 28);//Doctor button text
    doctorText.setFillColor(textColor);
    doctorText.setPosition({440.f, 295.f});

    //Room lookup button
    RectangleShape roomButton({250.f, 90.f});
    roomButton.setPosition({675.f, 270.f});
    roomButton.setFillColor(buttonColor);

    Text roomButtonText(font, "ROOM LOOKUP", 24);//Room lookup button text
    roomButtonText.setFillColor(textColor);
    roomButtonText.setPosition({710.f, 297.f});

    // Waiting room button, opens the list of patients waiting to be seen
    RectangleShape waitButton({250.f, 90.f});
    waitButton.setPosition({375.f, 540.f});
    waitButton.setFillColor(buttonColor);

    Text waitButtonText(font, "WAITING ROOM", 24);
    waitButtonText.setFillColor(textColor);
    waitButtonText.setPosition({400.f, 567.f});

    //Advance time button
    RectangleShape timeButton({250.f, 90.f});
    timeButton.setPosition({225.f, 420.f});
    timeButton.setFillColor(buttonColor);

    Text timeButtonText(font, "ADVANCE TIME", 24);//Advance time button text
    timeButtonText.setFillColor(textColor);
    timeButtonText.setPosition({265.f, 447.f});

    //Patient list button
    RectangleShape listButton({250.f, 90.f});
    listButton.setPosition({525.f, 420.f});
    listButton.setFillColor(buttonColor);

    Text listButtonText(font, "PATIENT LIST", 24);//Patient list button text
    listButtonText.setFillColor(textColor);
    listButtonText.setPosition({575.f, 447.f});

    //Simulation time counter
    //int currentDay=1;
    Text timeCounter(font, "  HOUR: " + to_string(hospitalTime.count()), 20);
    timeCounter.setFillColor(Color::White);
    timeCounter.setPosition({770.f, 20.f});

    //Record page title
    Text pageTitle(font, "", 45);//Page title
    pageTitle.setFillColor(Color::White);
    pageTitle.setPosition({350.f, 75.f});


    //Name label and box
    Text nameLabel(font, "NAME", 24);//Name label
    nameLabel.setFillColor(Color::White);
    nameLabel.setPosition({60.f, 205.f});

    RectangleShape nameBox({400.f, 65.f});//Name box
    nameBox.setPosition({60.f, 245.f});
    nameBox.setFillColor(buttonColor);

    //Date of birth label and boxes
    Text dobLabel(font, "DATE OF BIRTH", 24);//Date of birth label
    dobLabel.setFillColor(Color::White);
    dobLabel.setPosition({60.f, 345.f});

    RectangleShape monthBox({105.f, 65.f});//Month box
    monthBox.setPosition({60.f, 390.f});
    monthBox.setFillColor(buttonColor);

    RectangleShape dayBox({105.f, 65.f});//Day box
    dayBox.setPosition({180.f, 390.f});
    dayBox.setFillColor(buttonColor);

    RectangleShape yearBox({160.f, 65.f});//Year box
    yearBox.setPosition({300.f, 390.f});
    yearBox.setFillColor(buttonColor);

    Text monthText(font, "MM", 23);//Month text
    monthText.setFillColor(textColor);
    monthText.setPosition({80.f, 405.f});

    Text dayText(font, "DD", 23);//Day text
    dayText.setFillColor(textColor);
    dayText.setPosition({200.f, 405.f});

    Text yearText(font, "YYYY", 23);//Year text
    yearText.setFillColor(textColor);
    yearText.setPosition({330.f, 405.f});


    //Back button
    RectangleShape backButton({170.f, 60.f});
    backButton.setPosition({210.f, 535.f});
    backButton.setFillColor(buttonColor);

    Text backText(font, "BACK", 26);//Back text
    backText.setFillColor(textColor);
    backText.setPosition({253.f, 547.f});

    //Patient list back button
    RectangleShape listBackButton({170.f, 60.f});
    listBackButton.setPosition({415.f, 560.f});
    listBackButton.setFillColor(buttonColor);

    Text listBackText(font, "BACK", 26);//Back button text
    listBackText.setFillColor(textColor);
    listBackText.setPosition({458.f, 572.f});

    //Search button
    RectangleShape searchButton({170.f, 60.f});//Search button
    searchButton.setPosition({620.f, 535.f});
    searchButton.setFillColor(buttonColor);

    Text searchText(font, "SEARCH", 26);//Search text
    searchText.setFillColor(textColor);
    searchText.setPosition({643.f, 547.f});

    // Delete button, only shown on the patient page while a found patient is displayed
    RectangleShape deleteButton({170.f, 60.f});
    deleteButton.setPosition({415.f, 535.f});
    deleteButton.setFillColor(buttonColor);

    Text deleteText(font, "DELETE", 26);
    deleteText.setFillColor(textColor);
    deleteText.setPosition({440.f, 547.f});

    //0=main menu, 1=patient, 2=doctor, 3=room list, 4=room lookup
    int page=0;



    //Temporary patient information
    struct PatientRow
    {
        int roomNumber;
        string patientName;
        int condition;
        string doctorName;
        string doctorDob;
        string dob;
        int age;
    };

    //Patient list populated from occupied rooms
    vector<PatientRow> patientList;
    auto refreshPatients=[&]()//clears the patient list and repopulates it with the current occupied rooms
    {
        patientList.clear();

        for(int number=0;number<10000;number+=18)//Iterate through all possible room numbers, but only the ones that are multiples of 18
        {
            Room room=hospital.getRoom(number);

            // Skip empty room numbers instead of stopping, since a discharged or deleted patient leaves a gap
            if(room.roomNumber==-1)
            {
                continue;
            }

            Patient patient=room.assignedPatient;
            Doctor doctor=room.assignedDoctor;

            auto dob=patient.getDob();
            auto doctorDob=doctor.getDob();

            string dobText=to_string(unsigned(dob.month()))+"/"+to_string(unsigned(dob.day()))+"/"+to_string(int(dob.year()));
            string doctorDobText=to_string(unsigned(doctorDob.month()))+"/"+to_string(unsigned(doctorDob.day()))+"/"+to_string(int(doctorDob.year()));
            patientList.push_back({room.roomNumber, patient.getName(), patient.getCondition(), doctor.getName(), doctorDobText, dobText, static_cast<int>(patient.getAge().count())});
        }
    };

    refreshPatients();

    //Scrolling information
    int scrollOffset=0;
    const int visibleRows=6;

    //Patient list title
    Text listTitle(font, "PATIENT LIST", 42);
    listTitle.setFillColor(Color::White);
    listTitle.setPosition({340.f, 55.f});

    //Table headers
    Text roomHeader(font, "ROOM", 15);//Room header
    roomHeader.setFillColor(Color::White);
    roomHeader.setPosition({24.f,140.f});

    Text nameHeader(font, "PATIENT", 15);//Patient header
    nameHeader.setFillColor(Color::White);
    nameHeader.setPosition({95.f,140.f});

    Text conditionHeader(font, "CONDITION", 15);//Condition header
    conditionHeader.setFillColor(Color::White);
    conditionHeader.setPosition({275.f,140.f});

    Text dobHeader(font, "PATIENT DOB", 15);//Patient DOB header
    dobHeader.setFillColor(Color::White);
    dobHeader.setPosition({380.f,140.f});

    Text ageHeader(font, "PATIENT AGE", 15);//Patient age header
    ageHeader.setFillColor(Color::White);
    ageHeader.setPosition({525.f,140.f});

    Text doctorHeader(font, "DOCTOR", 15);//Doctor header
    doctorHeader.setFillColor(Color::White);
    doctorHeader.setPosition({655.f,140.f});

    Text doctorDobHeader(font, "DOCTOR DOB", 15);//Doctor DOB header
    doctorDobHeader.setFillColor(Color::White);
    doctorDobHeader.setPosition({830.f,140.f});

    //Reusable room row
    RectangleShape listRow({960.f, 48.f});
    Text rowText(font, "", 14);
    rowText.setFillColor(textColor);

    //Scroll instructions
    Text scrollInstructions(font, "Use mouse wheel to scroll", 17);
    scrollInstructions.setFillColor(Color::White);
    scrollInstructions.setPosition({650.f, 545.f});

    // Waiting room page title and column headers
    Text waitTitle(font, "WAITING ROOM", 42);
    waitTitle.setFillColor(Color::White);
    waitTitle.setPosition({300.f, 55.f});

    Text waitRankHeader(font, "#", 15);
    waitRankHeader.setFillColor(Color::White);
    waitRankHeader.setPosition({24.f,140.f});

    Text waitNameHeader(font, "PATIENT", 15);
    waitNameHeader.setFillColor(Color::White);
    waitNameHeader.setPosition({95.f,140.f});

    Text waitConditionHeader(font, "CONDITION", 15);
    waitConditionHeader.setFillColor(Color::White);
    waitConditionHeader.setPosition({275.f,140.f});

    Text waitDobHeader(font, "PATIENT DOB", 15);
    waitDobHeader.setFillColor(Color::White);
    waitDobHeader.setPosition({695.f,140.f});

    Text waitAgeHeader(font, "PATIENT AGE", 15);
    waitAgeHeader.setFillColor(Color::White);
    waitAgeHeader.setPosition({850.f,140.f});

    // Patients waiting to be seen, most critical first. Refreshed each time the page opens.
    vector<Patient> waitingList;


    //0=none, 1=name, 2=month, 3=day, 4=year
    int selectedBox=0;

    //User-entered information
    string nameInput="";
    string monthInput="";
    string dayInput="";
    string yearInput="";

    //Selected box color
    Color selectedColor(255, 235, 150);


    //Name input text
    Text nameValue(font, "", 25);
    nameValue.setFillColor(textColor);
    nameValue.setPosition({75.f, 260.f});

    //Search feedback
    Text searchMessage(font, "", 18);
    searchMessage.setFillColor(Color::White);
    searchMessage.setPosition({60.f, 485.f});

    //Result panel
    RectangleShape resultBox({430.f, 275.f});
    resultBox.setPosition({510.f, 190.f});
    resultBox.setFillColor(buttonColor);

    Text resultHeading(font, "SEARCH RESULT", 23);//Result heading
    resultHeading.setFillColor(textColor);
    resultHeading.setPosition({535.f, 205.f});

    Text resultText(font, "", 18);//Result text
    resultText.setFillColor(textColor);
    resultText.setPosition({535.f, 250.f});

    //0=not searched, 1=found, 2=not found
    int resultStatus=0;

    // The patient currently shown on the patient page, used by the delete button
    bool patientShown=false;
    string shownName="";
    int shownYear=0;
    int shownMonth=0;
    int shownDay=0;

    //Room lookup page
    string roomInput="";
    bool roomSelected=false;
    bool roomSearched=false;

    Text roomTitle(font, "ROOM LOOKUP", 45);//Room lookup page title
    roomTitle.setFillColor(Color::White);
    roomTitle.setPosition({330.f, 75.f});

    Text roomLabel(font, "ROOM NUMBER", 24);//Room number label
    roomLabel.setFillColor(Color::White);
    roomLabel.setPosition({60.f, 205.f});

    RectangleShape roomBox({400.f, 65.f});//Room number input box
    roomBox.setPosition({60.f, 245.f});
    roomBox.setFillColor(buttonColor);

    Text roomValue(font, "", 25);//Room number input text
    roomValue.setFillColor(textColor);
    roomValue.setPosition({75.f, 260.f});

    //Room results panel
    RectangleShape roomResultBox({430.f, 330.f});
    roomResultBox.setPosition({510.f, 175.f});
    roomResultBox.setFillColor(buttonColor);

    Text roomResultText(font, "", 18);//Room results text
    roomResultText.setFillColor(textColor);
    roomResultText.setPosition({535.f, 195.f});

    //Main loop
    while(window.isOpen())
    {
        while(const optional event=window.pollEvent())
        {
            if(event->is<Event::Closed>())
            {
                window.close();
            }

            //Detect mouse clicks
            //Detect mouse clicks
            if(const auto* mouse=event->getIf<Event::MouseButtonPressed>())
            {
                if(mouse->button==Mouse::Button::Left)//Left mouse button
                {
                    Vector2f mousePos=window.mapPixelToCoords(mouse->position);//Get mouse position in window coordinates

                    if(page==0)//Main menu
                    {
                        if(patientButton.getGlobalBounds().contains(mousePos))//Patient button clicked
                        {
                            page=1;
                        }
                        else if(doctorButton.getGlobalBounds().contains(mousePos))//Doctor button clicked
                        {
                            page=2;
                        }
                        else if(timeButton.getGlobalBounds().contains(mousePos))//Advance time button clicked
                        {
                            //Advance the actual hospital simulation
                            hospitalTime=hospital.incrementTime();

                            //Update displayed counter
                            string hourString=to_string(hospitalTime.count());

                            if(hospitalTime.count()<10)
                            {
                                hourString="0"+hourString;
                            }

                            timeCounter.setString("  HOUR: "+hourString);
                        }
                        else if(listButton.getGlobalBounds().contains(mousePos))//Patient list button clicked
                        {
                            refreshPatients();
                            page=3;
                            scrollOffset=0;
                        }
                        else if(roomButton.getGlobalBounds().contains(mousePos))//Room lookup button clicked
                        {
                            page=4;
                            roomInput="";
                            roomValue.setString("");
                            roomSelected=false;
                            roomSearched=false;
                        }
                        else if(waitButton.getGlobalBounds().contains(mousePos))// Waiting room button clicked
                        {
                            waitingList=hospital.getWaitingPatients();
                            page=5;
                            scrollOffset=0;
                        }
                    }
                    else if(page==5)// Waiting room page
                    {
                        if(listBackButton.getGlobalBounds().contains(mousePos))
                        {
                            page=0;
                            scrollOffset=0;
                        }
                    }
                    else if(page==3)//Patient list page
                    {
                        if(listBackButton.getGlobalBounds().contains(mousePos))
                        {
                            page=0;
                            scrollOffset=0;
                        }
                    }
                    else if(page==4)//Room lookup page
                    {
                        if(backButton.getGlobalBounds().contains(mousePos))//Back button clicked
                        {
                            page=0;
                            roomInput="";
                            roomValue.setString("");
                            roomSelected=false;
                            roomSearched=false;
                        }
                        else if(roomBox.getGlobalBounds().contains(mousePos))//Room number input box clicked
                        {
                            roomSelected=true;
                        }
                        else if(searchButton.getGlobalBounds().contains(mousePos))//Search button clicked
                        {
                            roomSelected=false;
                            roomSearched=true;

                            if(roomInput.empty())//No room number entered
                            {
                                roomResultText.setString("Please enter a room number.");
                            }
                            else//Room number entered, search for room
                            {
                                int number=stoi(roomInput);
                                Room room=hospital.getRoom(number);

                                if(room.roomNumber==-1)
                                {
                                    roomResultText.setString("Room not found.");
                                }
                                else
                                {
                                    Patient patient=room.assignedPatient;
                                    Doctor doctor=room.assignedDoctor;

                                    auto patientDob=patient.getDob();
                                    string patientDobText=to_string(unsigned(patientDob.month()))+"/"+to_string(unsigned(patientDob.day()))+"/"+to_string(int(patientDob.year()));

                                    auto doctorDob=doctor.getDob();
                                    string doctorDobText=to_string(unsigned(doctorDob.month()))+"/"+to_string(unsigned(doctorDob.day()))+"/"+to_string(int(doctorDob.year()));
                                    roomResultText.setString(//Display room information, structured for readability because it was too hard to order them before
                                        "ROOM: "+to_string(number)+"\n\n"
                                        "PATIENT\n"
                                        "Name: "+patient.getName()+"\n"
                                        "DOB: "+patientDobText+"\n"
                                        "Age: "+to_string(patient.getAge().count())+"\n"
                                        "Condition: "+to_string(patient.getCondition())+"/10\n\n"
                                        "DOCTOR\n"
                                        "Name: "+doctor.getName()+"\n"
                                        "Skill: "+to_string(doctor.skillLevel())+"/10\n"
                                        "DOB: "+doctorDobText+"\n"
                                        "Shift: "+to_string(doctor.shiftStartTime().count())+
                                        ":00 - "+to_string(doctor.shiftEndTime().count())+":00"
                                    );
                                }
                            }
                        }
                        else
                        {
                            roomSelected=false;
                        }
                    }
                    else//Patient or doctor record page, 1 and 2 were implemented before the others but after 0 option. They are functionally the same
                    {
                        if(backButton.getGlobalBounds().contains(mousePos))
                        {
                            page=0;
                            selectedBox=0;

                            //Clear stored inputs
                            nameInput="";
                            monthInput="";
                            dayInput="";
                            yearInput="";

                            //Reset displayed text
                            nameValue.setString("");
                            monthText.setString("MM");
                            dayText.setString("DD");
                            yearText.setString("YYYY");

                            //Clear search message and results
                            searchMessage.setString("");
                            resultStatus=0;
                            resultText.setString("");
                        }
                        else if(page==1 && resultStatus==1 && patientShown && deleteButton.getGlobalBounds().contains(mousePos))// Delete button clicked, removes the shown patient from the hospital
                        {
                            hospital.deletePatient(shownName,shownYear,shownMonth,shownDay);
                            patientShown=false;
                            selectedBox=0;
                            resultStatus=2;
                            resultText.setFillColor(Color::Red);
                            resultText.setString("PATIENT DELETED");
                        }
                        else if(nameBox.getGlobalBounds().contains(mousePos))//Name input box clicked
                        {
                            selectedBox=1;
                        }
                        else if(monthBox.getGlobalBounds().contains(mousePos))//Month input box clicked
                        {
                            selectedBox=2;
                        }
                        else if(dayBox.getGlobalBounds().contains(mousePos))//Day input box clicked
                        {
                            selectedBox=3;
                        }
                        else if(yearBox.getGlobalBounds().contains(mousePos))//Year input box clicked
                        {
                            selectedBox=4;
                        }
                        else if(searchButton.getGlobalBounds().contains(mousePos))//Search button clicked
                        {
                            selectedBox=0;
                            searchMessage.setString("");

                            if(nameInput.empty() || monthInput.empty() || dayInput.empty() || yearInput.empty())//Check if any input fields are empty
                            {
                                resultStatus=2;
                                resultText.setFillColor(Color::Red);
                                resultText.setString("Please complete every field.");
                            }
                            else//All fields filled, search for record
                            {
                                int month=stoi(monthInput);
                                int day=stoi(dayInput);
                                int year=stoi(yearInput);

                                patientShown=false; // A new search clears the patient shown for deletion
                                resultStatus=2;
                                resultText.setFillColor(Color::Red);
                                resultText.setString("RECORD NOT FOUND");

                                if(page==1)
                                {
                                    // Search the b-tree for the patient, then check whether they are in an occupied room
                                    Patient patient=hospital.getPatient(nameInput,year,month,day);
                                    Room room=hospital.getRoomViaPatient(nameInput);

                                    if(patient.getName()!="")//If the patient exists in the b-tree, display their information
                                    {
                                        // Use the room's copy if they are in a room, since it has the current condition
                                        // Remember the patient's key so the delete button can remove them
                                        patientShown=true;
                                        shownName=nameInput;
                                        shownYear=year;
                                        shownMonth=month;
                                        shownDay=day;

                                        bool inRoom=room.roomNumber!=-1 && room.assignedPatient==patient;
                                        Patient current=inRoom ? room.assignedPatient : patient;

                                        resultStatus=1;
                                        resultText.setFillColor(textColor);

                                        resultText.setString(//Display patient information, structured for readability like before
                                            "PATIENT FOUND\n\n"
                                            "Name: "+current.getName()+"\n"
                                            "DOB: "+monthInput+"/"+dayInput+"/"+yearInput+"\n"
                                            "Age: "+to_string(current.getAge().count())+"\n"
                                            "Condition: "+to_string(current.getCondition())+"/10\n"
                                            "Room: "+(inRoom ? to_string(room.roomNumber) : string("Not in a room"))
                                        );
                                    }
                                }
                                else if(page==2)//Doctor record page
                                {
                                    // Search the b-tree for the doctor by name and date of birth
                                    Doctor doctor=hospital.getDoctor(nameInput,year,month,day);

                                    if(doctor.getName()!="")
                                    {
                                        auto dob=doctor.getDob();

                                        if(int(dob.year())==year && unsigned(dob.month())==static_cast<unsigned>(month) && unsigned(dob.day())==static_cast<unsigned>(day))//If the date of birth matches, display doctor information
                                        {
                                            resultStatus=1;
                                            resultText.setFillColor(textColor);

                                            resultText.setString(
                                                "DOCTOR FOUND\n\n"
                                                "Name: "+doctor.getName()+"\n"
                                                "DOB: "+monthInput+"/"+dayInput+"/"+yearInput+"\n"
                                                "Age: "+to_string(doctor.getAge().count())+"\n"
                                                "Skill: "+to_string(doctor.skillLevel())+"/10\n"
                                                "Shift: "+to_string(doctor.shiftStartTime().count())+
                                                ":00 - "+to_string(doctor.shiftEndTime().count())+":00"
                                            );
                                        }
                                    }
                                }
                            }
                        }

                        else
                        {
                            selectedBox=0;
                        }
                    }
                }
            }
            //Keyboard text input
            if(const auto* text=event->getIf<Event::TextEntered>())
            {
                if(page!=0 && selectedBox!=0)
                {
                    string* input=nullptr;
                    int maxLength=0;

                    if(selectedBox==1)
                    {
                        input=&nameInput;
                        maxLength=24;
                    }
                    else if(selectedBox==2)
                    {
                        input=&monthInput;
                        maxLength=2;
                    }
                    else if(selectedBox==3)
                    {
                        input=&dayInput;
                        maxLength=2;
                    }
                    else if(selectedBox==4)
                    {
                        input=&yearInput;
                        maxLength=4;
                    }

                    if(input!=nullptr)
                    {
                        if(text->unicode==8)
                        {
                            if(!input->empty())
                            {
                                input->pop_back();
                            }
                        }
                        else if(input->size()<static_cast<size_t>(maxLength))
                        {
                            if(selectedBox==1)
                            {
                                //Letters and spaces
                                if((text->unicode>=65 && text->unicode<=90) ||
                                    (text->unicode>=97 && text->unicode<=122) ||
                                    text->unicode==32)
                                {
                                    *input+=static_cast<char>(text->unicode);
                                }
                            }
                            else
                            {
                                //Numbers only
                                if(text->unicode>=48 && text->unicode<=57)
                                {
                                    *input+=static_cast<char>(text->unicode);
                                }
                            }
                        }

                        //Update displayed text
                        nameValue.setString(nameInput);
                        monthText.setString(monthInput.empty() ? "MM" : monthInput);
                        dayText.setString(dayInput.empty() ? "DD" : dayInput);
                        yearText.setString(yearInput.empty() ? "YYYY" : yearInput);

                        searchMessage.setString("");
                        resultStatus=0;
                        resultText.setString("");
                    }
                }
            }

            //Room number keyboard input
            if(const auto* text=event->getIf<Event::TextEntered>())
            {
                if(page==4 && roomSelected)//Room lookup page and room number input box selected
                {
                    if(text->unicode==8)//Backspace
                    {
                        if(!roomInput.empty())
                        {
                            roomInput.pop_back();
                        }
                    }
                    else if(text->unicode>=48 && text->unicode<=57 && roomInput.size()<5)//Numbers only, max 5 digits
                    {
                        roomInput+=static_cast<char>(text->unicode);//Append character to room input
                    }

                    roomValue.setString(roomInput);//Update displayed room number input
                    roomSearched=false;
                }
            }

            //Scroll patient list
            if(const auto* wheel=event->getIf<Event::MouseWheelScrolled>())
            {
                if(page==3 || page==5)// Patient list or waiting room page
                {
                    int listSize=page==3 ? static_cast<int>(patientList.size()) : static_cast<int>(waitingList.size());
                    if(wheel->delta<0 && scrollOffset+visibleRows<listSize)//Scroll down, but only if there are more rows to show, this was was easier than I expected
                    {
                        scrollOffset++;
                    }
                    else if(wheel->delta>0 && scrollOffset>0)//Scroll up, but only if not already at the top
                    {
                        scrollOffset--;
                    }
                }
            }
        }

        //Highlight selected text box
        nameBox.setFillColor(selectedBox==1 ? selectedColor : buttonColor);
        monthBox.setFillColor(selectedBox==2 ? selectedColor : buttonColor);
        dayBox.setFillColor(selectedBox==3 ? selectedColor : buttonColor);
        yearBox.setFillColor(selectedBox==4 ? selectedColor : buttonColor);

        window.clear(background);

        if(page==0)//Drawing the main menu, lots of drawing from here out
        {
            //Main menu
            window.draw(title);
            window.draw(patientButton);
            window.draw(doctorButton);
            window.draw(patientText);
            window.draw(doctorText);
            window.draw(timeButton);
            window.draw(timeButtonText);
            window.draw(listButton);
            window.draw(listButtonText);
            window.draw(roomButton);
            window.draw(roomButtonText);
            window.draw(waitButton);
            window.draw(waitButtonText);
        }
        else if(page==4)//Drawing the room lookup page, lots of drawing
        {
            roomBox.setFillColor(roomSelected ? selectedColor : buttonColor);//Highlight room number input box if selected

            window.draw(roomTitle);
            window.draw(roomLabel);
            window.draw(roomBox);
            window.draw(roomValue);

            if(roomSearched)
            {
                window.draw(roomResultBox);
                window.draw(roomResultText);
            }

            window.draw(backButton);
            window.draw(backText);
            window.draw(searchButton);
            window.draw(searchText);
        }
        else if(page==3)//Drawing the patient list
        {
            window.draw(listTitle);
            window.draw(roomHeader);
            window.draw(nameHeader);
            window.draw(conditionHeader);
            window.draw(dobHeader);
            window.draw(ageHeader);
            window.draw(doctorHeader);
            window.draw(doctorDobHeader);

            for(int i=0;i<visibleRows;i++)//Draw each visible row of the patient list
            {
                int index=scrollOffset+i;

                if(index>=static_cast<int>(patientList.size()))
                {
                    break;
                }

                float y=185.f+i*54.f;

                listRow.setPosition({12.f,y});

                if(i%2==0)
                {
                    listRow.setFillColor(Color(220,220,210));
                }
                else
                {
                    listRow.setFillColor(Color(195,205,205));
                }

                window.draw(listRow);


                //Room number
                rowText.setString(to_string(patientList[index].roomNumber));
                rowText.setPosition({24.f,y+12.f});
                window.draw(rowText);

                //Patient
                rowText.setString(patientList[index].patientName);
                rowText.setPosition({95.f,y+12.f});
                window.draw(rowText);

                //Condition
                rowText.setString(to_string(patientList[index].condition)+"/10");
                rowText.setPosition({275.f,y+12.f});
                window.draw(rowText);

                //Patient DOB
                rowText.setString(patientList[index].dob);
                rowText.setPosition({380.f,y+12.f});
                window.draw(rowText);

                //Patient age
                rowText.setString(to_string(patientList[index].age));
                rowText.setPosition({525.f,y+12.f});
                window.draw(rowText);

                //Doctor
                rowText.setString(patientList[index].doctorName);
                rowText.setPosition({655.f,y+12.f});
                window.draw(rowText);

                //Doctor DOB
                rowText.setString(patientList[index].doctorDob);
                rowText.setPosition({830.f,y+12.f});
                window.draw(rowText);
            }

            window.draw(scrollInstructions);
            window.draw(listBackButton);
            window.draw(listBackText);
        }
        else if(page==5)// Drawing the waiting room list
        {
            window.draw(waitTitle);
            window.draw(waitRankHeader);
            window.draw(waitNameHeader);
            window.draw(waitConditionHeader);
            window.draw(waitDobHeader);
            window.draw(waitAgeHeader);

            for(int i=0;i<visibleRows;i++)// Draw each visible waiting patient
            {
                int index=scrollOffset+i;

                if(index>=static_cast<int>(waitingList.size()))
                {
                    break;
                }

                float y=185.f+i*54.f;

                listRow.setPosition({12.f,y});
                listRow.setFillColor(i%2==0 ? Color(220,220,210) : Color(195,205,205));
                window.draw(listRow);

                Patient patient=waitingList[index];
                auto dob=patient.getDob();
                string dobText=to_string(unsigned(dob.month()))+"/"+to_string(unsigned(dob.day()))+"/"+to_string(int(dob.year()));

                //Position in the queue
                rowText.setString(to_string(index+1));
                rowText.setPosition({24.f,y+12.f});
                window.draw(rowText);

                //Patient
                rowText.setString(patient.getName());
                rowText.setPosition({95.f,y+12.f});
                window.draw(rowText);

                //Condition
                rowText.setString(to_string(patient.getCondition())+"/10");
                rowText.setPosition({275.f,y+12.f});
                window.draw(rowText);

                //Patient DOB
                rowText.setString(dobText);
                rowText.setPosition({695.f,y+12.f});
                window.draw(rowText);

                //Patient age
                rowText.setString(to_string(patient.getAge().count()));
                rowText.setPosition({850.f,y+12.f});
                window.draw(rowText);
            }

            window.draw(scrollInstructions);
            window.draw(listBackButton);
            window.draw(listBackText);
        }

        else//Drawing the patient or doctor record page
        {
            if(page==1)
            {
                pageTitle.setString("PATIENT");
            }
            else
            {
                pageTitle.setString("DOCTOR");
            }

            window.draw(pageTitle);

            window.draw(nameLabel);
            window.draw(nameBox);
            window.draw(nameValue);

            window.draw(dobLabel);
            window.draw(monthBox);
            window.draw(dayBox);
            window.draw(yearBox);

            window.draw(monthText);
            window.draw(dayText);
            window.draw(yearText);

            //Display search results
            if(resultStatus!=0)
            {
                window.draw(resultBox);
                window.draw(resultHeading);
                window.draw(resultText);
            }

            window.draw(backButton);
            window.draw(backText);
            window.draw(searchButton);
            window.draw(searchText);
            window.draw(searchMessage);

            // Delete button is only drawn while a found patient is displayed
            if(page==1 && resultStatus==1 && patientShown)
            {
                window.draw(deleteButton);
                window.draw(deleteText);
            }
        }

        //Display hospital time on every screen
        window.draw(timeCounter);

        window.display();
    }
}

/*
#ifdef TEST_VISUALS
int main()
{
    runVisuals();
    return 0;
}
#endif*/

