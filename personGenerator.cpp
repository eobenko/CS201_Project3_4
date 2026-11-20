#include <fstream>
#include <iostream>
#include <random>

using namespace std;

// Writes people.txt, one line per name in randomnames.txt, with a random date of birth
int main()
{
    ifstream names("randomnames.txt");
    if (!names)
    {
        cerr << "Failed to open randomnames.txt\n";
        return 1;
    }

    ofstream people("people.txt");
    if (!people)
    {
        cerr << "Failed to open people.txt\n";
        return 1;
    }

    string firstName;
    string lastName;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> yearDistribution(1926, 2008);
    uniform_int_distribution<int> monthDistribution(1, 12);
    uniform_int_distribution<int> day31(1, 31);
    uniform_int_distribution<int> day30(1, 30);
    uniform_int_distribution<int> day29(1, 29);
    uniform_int_distribution<int> day28(1, 28);
    int year;
    int month;
    int day;

    while (names >> firstName >> lastName)
    {
        people << firstName << " " << lastName << " ";
        year = yearDistribution(gen);
        month = monthDistribution(gen);
        if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
        {
            day = day31(gen);
        }
        else if (month == 4 || month == 6 || month == 9 || month == 11)
        {
            day = day30(gen);
        }
        else
        { // month == 2
            if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
            { // Leap year
                day = day29(gen);
            }
            else
            {
                day = day28(gen);
            }
        }
        people << year << " " << month << " " << day << endl;
    }

    return 0;
}
