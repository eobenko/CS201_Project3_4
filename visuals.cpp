//#include "hospital.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Window.hpp>
#include <string>
#include <iostream>
#include <array>

using namespace std;
using namespace sf;
//Hospital &hospital
void runVisuals()
{
    //Create window
    RenderWindow window(VideoMode({1000, 650}), "Nota Hospital");
    window.setFramerateLimit(60);

    //Colors
    Color background(30, 45, 55);
    Color buttonColor(220, 220, 210);
    Color textColor(30, 45, 55);

    //Load font
    Font font;
    if (!font.openFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"))
    {
        cout<<"Font failed to load"<<endl;
        return;
    }

    //Main menu title
    Text title(font, "NOTA HOSPITAL", 48);
    title.setFillColor(Color::White);
    title.setPosition({285.f, 110.f});

    //Main menu buttons
    RectangleShape patientButton({300.f, 120.f});//Patient button
    patientButton.setPosition({175.f, 300.f});
    patientButton.setFillColor(buttonColor);

    RectangleShape doctorButton({300.f, 120.f});//Doctor button
    doctorButton.setPosition({525.f, 300.f});
    doctorButton.setFillColor(buttonColor);

    Text patientText(font, "PATIENT", 30);//Patient text
    patientText.setFillColor(textColor);
    patientText.setPosition({255.f, 340.f});

    Text doctorText(font, "DOCTOR", 30);//Doctor text
    doctorText.setFillColor(textColor);
    doctorText.setPosition({615.f, 340.f});
 
    //Advance time button
    RectangleShape timeButton({300.f, 80.f});//Advance time button
    timeButton.setPosition({350.f, 465.f});
    timeButton.setFillColor(buttonColor);

    Text timeButtonText(font, "ADVANCE TIME", 27);//Advance time button text
    timeButtonText.setFillColor(textColor);
    timeButtonText.setPosition({387.f, 483.f});

    //Simulation time counter
    int currentHour=0;
    int currentDay=1;

    Text timeCounter(font, "DAY: " + to_string(currentDay) + "  HOUR: " + to_string(currentHour), 20);
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
    RectangleShape backButton({170.f, 60.f});//Back button
    backButton.setPosition({210.f, 535.f});
    backButton.setFillColor(buttonColor);

    Text backText(font, "BACK", 26);//Back text
    backText.setFillColor(textColor);
    backText.setPosition({253.f, 547.f});

    //Search button
    RectangleShape searchButton({170.f, 60.f});//Search button
    searchButton.setPosition({620.f, 535.f});
    searchButton.setFillColor(buttonColor);

    Text searchText(font, "SEARCH", 26);//Search text
    searchText.setFillColor(textColor);
    searchText.setPosition({643.f, 547.f});

    //0=main menu, 1=patient, 2=doctor
    int page=0;
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


    //Main loop
    while (window.isOpen()) 
    {
        while (const optional event=window.pollEvent()) 
        {
            if (event->is<Event::Closed>()) 
            {
                window.close();
            }

            //Detect mouse clicks
            //Detect mouse clicks
            if (const auto* mouse=event->getIf<Event::MouseButtonPressed>())
            {
                if (mouse->button==Mouse::Button::Left)
                {
                    Vector2f mousePos(static_cast<float>(mouse->position.x), static_cast<float>(mouse->position.y));

                    if (page==0)
                    {
                        if (patientButton.getGlobalBounds().contains(mousePos))
                        {
                            page=1;
                        }
                        else if (doctorButton.getGlobalBounds().contains(mousePos))
                        {
                            page=2;
                        }
                        else if (timeButton.getGlobalBounds().contains(mousePos))
                        {
                            //TODO: Replace with hospital.incrementTime() once integrated

                            //Temporary simulation time logic
                            currentHour++;

                            if (currentHour==24)
                            {
                                currentHour=0;
                                currentDay++;
                            }

                            //Update displayed counter
                            string hourString=to_string(currentHour);

                            if (currentHour<10)
                            {
                                hourString="0"+hourString;
                            }

                            timeCounter.setString("DAY: "+to_string(currentDay)+"  HOUR: "+hourString);
                        }
                    }
                    else
                    {
                        if (backButton.getGlobalBounds().contains(mousePos))
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
                        else if (nameBox.getGlobalBounds().contains(mousePos))
                        {
                            selectedBox=1;
                        }
                        else if (monthBox.getGlobalBounds().contains(mousePos))
                        {
                            selectedBox=2;
                        }
                        else if (dayBox.getGlobalBounds().contains(mousePos))
                        {
                            selectedBox=3;
                        }
                        else if (yearBox.getGlobalBounds().contains(mousePos))
                        {
                            selectedBox=4;
                        }
                        else if (searchButton.getGlobalBounds().contains(mousePos))
                        {
                            selectedBox=0;
                            searchMessage.setString("");

                            if (nameInput.empty() || monthInput.empty() ||
                                dayInput.empty() || yearInput.empty())
                            {
                                resultStatus=2;
                                resultText.setFillColor(Color::Red);
                                resultText.setString("Please complete every field.");
                            }
                            else
                            {
                                //TODO: Connect to Hospital B-Tree search
                                //TODO: Search patients if page==1
                                //TODO: Search doctors if page==2
                                //TODO: Populate resultText with returned information

                                //Temporary demonstration
                                if (nameInput=="TEST")
                                {
                                    resultStatus=1;
                                    resultText.setFillColor(textColor);

                                    if (page==1)
                                    {
                                        resultText.setString(
                                            "RECORD FOUND (DEMO)\n"
                                            "Name: Test Patient\n"
                                            "DOB: 01/01/2000\n"
                                            "Age: 26\n"
                                            "Condition: 6 / 10"
                                        );
                                    }
                                    else
                                    {
                                        resultText.setString(
                                            "RECORD FOUND (DEMO)\n"
                                            "Name: Test Doctor\n"
                                            "DOB: 01/01/2000\n"
                                            "Age: 26\n"
                                            "Skill: 8 / 10\n"
                                            "Shift: 08:00 - 16:00\n"
                                            "On shift: Yes"
                                        );
                                    }
                                }
                                else
                                {
                                    resultStatus=2;
                                    resultText.setFillColor(Color::Red);
                                    resultText.setString(
                                        "RECORD NOT FOUND (DEMO)\n\n"
                                        "No matching record.\n"
                                        "Check the name and date of birth."
                                    );
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
            if (const auto* text=event->getIf<Event::TextEntered>())
            {
                if (page!=0 && selectedBox!=0)
                {
                    string* input=nullptr;
                    int maxLength=0;

                    if (selectedBox==1)
                    {
                        input=&nameInput;
                        maxLength=24;
                    }
                    else if (selectedBox==2)
                    {
                        input=&monthInput;
                        maxLength=2;
                    }
                    else if (selectedBox==3)
                    {
                        input=&dayInput;
                        maxLength=2;
                    }
                    else if (selectedBox==4)
                    {
                        input=&yearInput;
                        maxLength=4;
                    }

                    if (input!=nullptr)
                    {
                        if (text->unicode==8)
                        {
                            if (!input->empty())
                            {
                                input->pop_back();
                            }
                        }
                        else if (input->size()<static_cast<size_t>(maxLength))
                        {
                            if (selectedBox==1)
                            {
                                //Letters and spaces
                                if ((text->unicode>=65 && text->unicode<=90) ||
                                    (text->unicode>=97 && text->unicode<=122) ||
                                    text->unicode==32)
                                {
                                    *input+=static_cast<char>(text->unicode);
                                }
                            }
                            else
                            {
                                //Numbers only
                                if (text->unicode>=48 && text->unicode<=57)
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
        }

        //Highlight selected text box
        nameBox.setFillColor(selectedBox==1 ? selectedColor : buttonColor);
        monthBox.setFillColor(selectedBox==2 ? selectedColor : buttonColor);
        dayBox.setFillColor(selectedBox==3 ? selectedColor : buttonColor);
        yearBox.setFillColor(selectedBox==4 ? selectedColor : buttonColor);

        window.clear(background);

        if (page==0)//Drawing the main menu
        {
            // Main menu
            window.draw(title);
            window.draw(patientButton);
            window.draw(doctorButton);
            window.draw(patientText);
            window.draw(doctorText);
            window.draw(timeButton);
            window.draw(timeButtonText);
            window.draw(timeCounter);
        }
        else//Drawing the patient or doctor record page
        {
            
            if (page==1) 
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
            if (resultStatus!=0)
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
        }

        window.display();
    }
}


#ifdef TEST_VISUALS
int main()
{
    runVisuals();
    return 0;
}
#endif
