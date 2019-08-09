// C++ program to illustrate the use of unique_ptr
#include <iostream>
#include <memory>

class MyClass {
public:
	void classMethod() {
		std::cout << "MyClass::classMethod()" << std::endl;
	}
};

int main() {
	std::unique_ptr<MyClass> ptr_1 (new MyClass);
	ptr_1->classMethod();

	// return the memory address of ptr_1
	std::cout << ptr_1.get() << std::endl;

	// transfer ownership to ptr_2
	std::unique_ptr<MyClass> ptr_2 = std::move(ptr_1); // needs to use std::move()
	ptr_2->classMethod();
	std::cout << ptr_1.get() << std::endl;
	std::cout << ptr_2.get() << std::endl;

	// transfer ownership to ptr_3
	std::unique_ptr<MyClass> ptr_3 = std::move(ptr_2);
	ptr_3->classMethod();
	std::cout << ptr_1.get() << std::endl;
	std::cout << ptr_2.get() << std::endl;
	std::cout << ptr_3.get() << std::endl;

	/* Output */
	
	// MyClass::classMethod()
	// 0x12b0c20
	// MyClass::classMethod()
	// 0
	// 0x12b0c20
	// MyClass::classMethod()
	// 0
	// 0
	// 0x12b0c20

	
	return 0
;}