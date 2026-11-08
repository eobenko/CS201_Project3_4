#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Window.hpp>
#include <string>
#include <iostream>
#include <array>

using namespace std;
using namespace sf;

int main() {
    // Create window
    RenderWindow window(VideoMode({1000, 650}), "Nota Hospital");
    window.setFramerateLimit(60);

    // Background colors
    Color background(30, 45, 55);
    Color buttonColor(220, 220, 210);

    // Background
    RectangleShape backgroundShape({1000.f, 650.f});
    backgroundShape.setFillColor(background);

    // Patient button
    RectangleShape patientButton({300.f, 120.f});
    patientButton.setPosition({175.f, 300.f});
    patientButton.setFillColor(buttonColor);

    // Doctor button
    RectangleShape doctorButton({300.f, 120.f});
    doctorButton.setPosition({525.f, 300.f});
    doctorButton.setFillColor(buttonColor);

    // Load font
    Font font;
    if (!font.openFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        cout << "Font failed to load" << endl;
        return 1;
    }

    // Hospital title
    Text title(font, "NOTA HOSPITAL", 48);
    title.setFillColor(Color::White);
    title.setPosition({285.f, 110.f});

    // Patient label
    Text patientText(font, "PATIENT", 30);
    patientText.setFillColor(Color::Black);
    patientText.setPosition({255.f, 340.f});

    // Doctor label
    Text doctorText(font, "DOCTOR", 30);
    doctorText.setFillColor(Color::Black);
    doctorText.setPosition({615.f, 340.f});

    // Main loop
    while (window.isOpen()) {
        while (const optional event = window.pollEvent()) {
            if (event->is<Event::Closed>()) {
                window.close();
            }
        }

        window.clear();

        window.draw(backgroundShape);
        window.draw(title);
        window.draw(patientButton);
        window.draw(doctorButton);
        window.draw(patientText);
        window.draw(doctorText);

        window.display();
    }

    return 0;
}