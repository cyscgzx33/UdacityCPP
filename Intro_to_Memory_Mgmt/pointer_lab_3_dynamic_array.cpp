/* LAB 3
 * 
 * - Objectives 3
 * 
 * In this example we are going to try to create dynamic array for integers. 
 * With this we can get primitive overview of how some of the popular container libraries 
 * in C++ work, such as : vector, queqe, stack etc. We know that dynamic declaration of 
 * array was initially supported in C++, but we don't have option to do resize or 
 * similar operation once array has been declared. Via pointers and access to memory 
 * it is pretty simple. So we are going to try to create couple of functions. 
 * First one is "createArr" which will create our array with specified size as input. 
 * Second one is going to be "resizeArr" which will resize our array and preserve our data. 
 * For the purpose of this example, to preserve simplicity 
 * we will only allow to expand our array to specified number of places.
 * */

#include <iostream>

int* createArr(int n) {
	int* ptr = new int[n];
	return ptr;
}

int* resizeArr(int* ptr, int size, int ex_value) {
	int* new_ptr = int[size + ex_value];

	for (int i = 0; i < size; i++) new_ptr[i] = ptr[i];

	delete []ptr;
	return new_ptr;
}

int main() {

	int size;
	std::cout << "size of array: " << std::endl;
	std::cin >> size;

	int* ptr = createArr(size);
	for (int i = 0; i < size; i++) ptr[i] = i * i;

	std::cout << "created array: " << std::endl;
	for (int i = 0; i < size; i++) std::cout << ptr[i] << std::endl;

	std::
}