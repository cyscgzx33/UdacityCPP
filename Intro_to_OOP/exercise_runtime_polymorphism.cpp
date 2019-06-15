/*
 * [Introduction to Runtime Polymorphism]
 * Runtime polymorphism is accomplished by performing function overriding. 
 * This is performed using class hierarchies. 
 * Any derived class can override function members that belong to the base class.
 * 
 * [How to conduct Runtime Polymorphism (or Function Overriding)]
 * Function overriding occurs when a derived class function calls its own definition of a method, 
 * instead of the base class's implementation. 
 * In this case, the base class's method has been "overridden."
 */

#include <iostream>

class Base {
  public:
  	Base();
  	void virtual Print();
  	void calc();
};

class Derived {
  public:
  	Derived();
  	void Print(); // No need to explicitly add "virtual" here
  	void calc();
};


int main() {
	
}