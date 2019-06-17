/* 
 * This lab demonstrates how a simple comparison between two variables of 
 * unknown type can work using templates. In this case, 
 * by defining a template that performs a comparison using the > operator, 
 * you can compare two variables of any type (both variables must be of the same type, though) 
 * as long as the operator > is defined for that type.
 */

#include <iostream>

// Here we will create the template
template <class T>
T ReturnMax(T a, T b) 
{
   if(a > b) 
       return a;
   else 
       return b;
}

int main()
{
    int num1 = 50;
    int num2 = 10;

    // Check if ReturnMax() will work for both int and double values
    // Return the larger of two integers
    int res = ReturnMax(num1, num2);
    std::cout << "Bigger one is: " << res << "\n";

    double n1 = 45.65;
    double n2 = 100.45;
    // Return the larger of two double
    double res2 = ReturnMax(n1, n2);
    std::cout << "Bigger one is: " << res2 << "\n";

    // Check if ReturnMax() will work for char variables
    char char1 = 'c';
    char char2 = 'y';
    char res3 = ReturnMax(char1, char2);
    std::cout << "Bigger one is: " << res3 << "\n";
}