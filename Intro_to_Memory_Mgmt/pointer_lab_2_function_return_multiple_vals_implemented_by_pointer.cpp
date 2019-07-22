/* LAB 2
 * 
 * - Objectives
 * In this example we are showing technique of an implementation of function which will return multiple values. 
 * Using pointers we can implement this via references. If we take into consideration that passage of 
 * data by reference doesn't copy this object, we can pass our object to a function and execute required actions. 
 * In this example we are going to make a primitive function
 * which calculates cosine and sine values of a specific angle (in radians) using just one function.
 * 
 * - Steps
 * #1 Include standard library iostream
 * #2 Include math.h library for usage of trigonometrical functions
 * #3 create a function which will have three parameters: _sin, _cos and angle. all parameters are double
 * #4 Return type of this function is void
 * #5 Declare input parameters (except angle variable) as pointers to double type
 * #6 Create main function
 * #7 Declare three double variables: angle, _sin, _cos
 * #8 Ask for input value of angle via cin from a user
 * #9 Call trigonometry function (pass sin and cos variables by references)
 * #10 Print results in console
 */

#include <iostream>
#include <cmath>

void trigonometry(double angle, double *_sin, double *_cos){
    *_sin = std::sin(angle);
    *_cos = std::cos(angle);
}

int main () {

    double angle, _sin, _cos;

    std::cout << "Write angle in radians:";
    std::cin >> angle;
    std::cout << " Trigonometry values are: " << std::endl;
    trigonometry(angle, &_sin, &_cos);
    std::cout << "Sine is: "<< _sin << std::endl;
    std::cout << "Cosine is: "<< _cos << std::endl;

    return 0;
}