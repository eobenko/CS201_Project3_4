#include "hospital.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Window.hpp>
#include <string>
#include <iostream>
#include <array>

using namespace std;
using namespace sf;

void runVisuals(Hospital &hospital)
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

    //Record page title
    Text pageTitle(font, "", 45);//Page title
    pageTitle.setFillColor(Color::White);
    pageTitle.setPosition({350.f, 75.f});

    //Name label and box
    Text nameLabel(font, "NAME", 24);//Name label
    nameLabel.setFillColor(Color::White);
    nameLabel.setPosition({150.f, 205.f});

    RectangleShape nameBox({700.f, 65.f});//Name box
    nameBox.setPosition({150.f, 245.f});
    nameBox.setFillColor(buttonColor);

    //Date of birth label and boxes
    Text dobLabel(font, "DATE OF BIRTH", 24);//Date of birth label
    dobLabel.setFillColor(Color::White);
    dobLabel.setPosition({150.f, 345.f});

    RectangleShape monthBox({180.f, 65.f});//Month box
    monthBox.setPosition({150.f, 390.f});
    monthBox.setFillColor(buttonColor);

    RectangleShape dayBox({180.f, 65.f});//Day box
    dayBox.setPosition({365.f, 390.f});
    dayBox.setFillColor(buttonColor);

    RectangleShape yearBox({270.f, 65.f});//Year box
    yearBox.setPosition({580.f, 390.f});
    yearBox.setFillColor(buttonColor);

    Text monthText(font, "MM", 23);//Month text
    monthText.setFillColor(textColor);
    monthText.setPosition({215.f, 405.f});

    Text dayText(font, "DD", 23);//Day text
    dayText.setFillColor(textColor);
    dayText.setPosition({430.f, 405.f});

    Text yearText(font, "YYYY", 23);//Year text
    yearText.setFillColor(textColor);
    yearText.setPosition({680.f, 405.f});

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
    nameValue.setPosition({165.f, 260.f});

    //Search feedback
    Text searchMessage(font, "", 18);
    searchMessage.setFillColor(Color::White);
    searchMessage.setPosition({150.f, 485.f});

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
            if (const auto* mouse=event->getIf<Event::MouseButtonPressed>()) 
                    {

                if (mouse->button==Mouse::Button::Left) 
                {
                    Vector2f mousePos(static_cast<float>(mouse->position.x), static_cast<float>(mouse->position.y));

                    if (page==0) 
                    {
                        if (patientButton.getGlobalBounds().contains(mousePos)) 
                        {
                            page = 1;
                        }
                        else if (doctorButton.getGlobalBounds().contains(mousePos)) 
                        {
                            page = 2;
                        }
                    }
                    else
                    {
                        if (backButton.getGlobalBounds().contains(mousePos))
                        {
                            page=0;
                            selectedBox=0;
                            searchMessage.setString("");
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

                            if (nameInput.empty() || monthInput.empty() ||
                                dayInput.empty() || yearInput.empty())
                            {
                                searchMessage.setString("Please complete every field.");
                            }
                            else
                            {
                                cout<<"Searching for: "<<nameInput<<endl;
                                cout<<"Date of birth: "<<monthInput<<"/"
                                    <<dayInput<<"/"<<yearInput<<endl;

                                searchMessage.setString("Search submitted (B-Tree not connected).");
                            }
                        }
                        else
                        {
                            selectedBox=0;
                        }
                    }
                }
            }
        }

        window.clear(background);

        if (page==0)//Drawing the main menu
        {
            // Main menu
            window.draw(title);
            window.draw(patientButton);
            window.draw(doctorButton);
            window.draw(patientText);
            window.draw(doctorText);
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

            window.draw(dobLabel);
            window.draw(monthBox);
            window.draw(dayBox);
            window.draw(yearBox);

            window.draw(monthText);
            window.draw(dayText);
            window.draw(yearText);

            window.draw(backButton);
            window.draw(backText);
        }

        window.display();
    }
}