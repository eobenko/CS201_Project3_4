#include <fstream>
#include <iostream>
#include <random>

using namespace std;

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
    uniform_int_distribution<int> dayDistribution(1, 28);
    int year;
    int month;
    int day;

    while (names >> firstName >> lastName)
    {
        people << firstName << " " << lastName << " ";
        year = yearDistribution(gen);
        month = monthDistribution(gen);
        day = dayDistribution(gen);
        people << year << " " << month << " " << day << endl;
    }

    return 0;
}