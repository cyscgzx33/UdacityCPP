/* [Exercise: Function Template]
 * Function templates are used as a tool for generic implementation of a function. 
 * Creating generic function implementations that are capable of working with 
 * many types of numerical data is useful in various applications. 
 * Most of the numerical data types rely on same logic, making it possible to 
 * create a template that works across types. 
 *
 * In this example, you'll see how templates are used for function implementation. 
 * It relies on deduction in function call, where you specify your type as parameter 
 * in form of function_name <typeName>();
 *
 * [OBJECTIVES]
 * (1) Using template arguments, form generic functions using templates.
 * (2) Define average function for calculating numbers and number look alike.
 * (3) Print all results in console.
*/

#include <iostream>

template <typename _Tf>
_Tf Average(const _Tf& num1, const _Tf& num2) {
	return (num1 + num2) / 2;
}

int main() {

	// Test int type
	int int1 = 1, int2 = 2;
	std::cout << "The average of int1 and int2 is: " << Average(int1, int2) << std::endl;

	// Test double type
	double double1 = 1.0, double2 = 2.3;
	std::cout << "The average of double1 and double2 is: " << Average(double1, double2) << std::endl;

	// Test char type
	char char1 = 'a', char2 = 'z';
	std::cout << "The average of char1 and char2 is: " << Average(char1, char2) << std::endl;


}