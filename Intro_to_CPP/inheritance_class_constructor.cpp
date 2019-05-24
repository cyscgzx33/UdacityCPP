#include <iostream>
#include <string>
using std::string;
using std::cout;

class Car {
  public:
    void PrintCarData() 
    {
        cout << "The distance that the " << color << " car " << number << " has traveled is: " << distance << "\n";
    }

    void IncrementDistance() 
    {
        distance++;
    }
    
    // Adding a constructor here:
    Car(string c, int n) 
    {
        // Setting the class attributes with
        // The values passed into the constructor.
        color = c;
        number = n;
    }
  private:
    string color;
    int distance = 0;
    int number;
};

class Sedan : public Car {
  public:
    Sedan(string clr, int num, string brd, string mdl, string trm) 
        : Car(clr, num), // call base function constructor
          brand(brd),
          model(mdl),
          trim(trm)
    {
        std::cout << "Sedan Initialzied Successfully!" << std::endl;
    }
  private:
    string brand;
    string model;
    string trim;
};


int main() 
{
    // Create class instances for each car.
    Car car_1 = Car("green", 1);
    Car car_2 = Car("red", 2);
    Car car_3 = Car("blue", 3);

    // Create class instance for each Sedan
    Sedan sedan_1 = Sedan("gray", 1, "BMW", "3-Series", "330i-xdrive");
    Sedan sedan_2 = Sedan("blue", 2, "Mercedes", "C-class", "C300");
    
    // Increment car_1's position by 1.
    car_1.IncrementDistance();

    // Print out the position and color of each car.
    car_1.PrintCarData();
    car_2.PrintCarData();
    car_3.PrintCarData();
}