#include <iostream>
using std::cout;

int main() 
{
    /*
        ===== Examle I: Color enum =====
    */
    

    // Create the enum Color with fixed values.
    enum class Color {white, black, blue, red};

    // Create a Color variable and set it to Color::blue.
    Color my_color = Color::blue;

    // Test to see if my car is red.
    if (my_color == Color::red) {
        cout << "The color of my car is red!" << "\n";
    } else {
        cout << "The color of my car is not red." << "\n";
    }

    /*
        ===== Examle II: Direction enum =====
    */

    enum class Direction {kUp, kDown, kLeft, kRight};

    Direction a = Direction::kUp;

    // Note: for the switch statement, don't forget the "break" command
    switch (a) {
      case Direction::kUp : cout << "Going up!" << "\n";
        break;
      case Direction::kDown : cout << "Going down!" << "\n";
        break;
      case Direction::kLeft : cout << "Going left!" << "\n";
        break;
      case Direction::kRight : cout << "Going right!" << "\n";
        break;
    }
}