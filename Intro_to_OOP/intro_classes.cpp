#include <iostream>

class Date {
    // Declare member variables 
    public:
        int day;
        int month;
        int year;
        
        // Declare member setter function
        void SetDate(int day, int month, int year);   
};

// Define the SetDate() function
void Date::SetDate(int day, int month, int year) 
{
    int day_numbers[]{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // check if input year is a leap year
    // and if it is, give February 29 days
    if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) day_numbers[1]++;
    
    // Validate inputs
    if(year < 1 || day < 1 || month < 1 || month > 12 || day > day_numbers[month - 1])
        throw std::domain_error("Invalid date!");

    // Set date
    // TODO: (chenyus@umich.edu) to verify the difference between "Data::" and "this->" here
    Date::day = day; 
    Date::month = month; 
    Date::year = year;
}

// Test in main
int main()
{
   Date date;
   date.SetDate(29, 2, 1704);
   std::cout << date.day << "/" << date.month << "/" << date.year << "\n";
}
