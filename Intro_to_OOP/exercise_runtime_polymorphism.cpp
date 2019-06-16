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
  	Base() {}; // Important note: 
  			   // MUST add "{}" to specify it is an EMPTY CONSTRUCTOR
  	void virtual Print() = 0; // Important note:
  							  // If one doesn't plan to implement a virtual function in base class
  							  // "= 0" MUST be added in the tail. 
  	void calc();
};

class Derived : public Base {
  public:
  	Derived() {}; // Important note: 
  			   	  // MUST add "{}" to specify it is an EMPTY CONSTRUCTOR
  	void Print(); // No need to explicitly add "virtual" here
  	void calc();
};


void Base::calc() {
	std::cout << "Base::calc() is called!" << std::endl;
}

void Derived::Print() {
	std::cout << "Derived::Print() is called!" << std::endl;
}

void Derived::calc() {
	std::cout << "Derived::calc() is called!" << std::endl;
}

int main() {
	Base* base_ptr;
	Derived derived;
	base_ptr = &derived;

	base_ptr->Print();
	base_ptr->calc();
}