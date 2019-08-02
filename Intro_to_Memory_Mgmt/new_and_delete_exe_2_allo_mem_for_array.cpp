/* LAB 2
 * [Objectives 2]
 * We are going to use new and delete operators for memory management. 
 * In this example we are going to try to allocate block of memory for storage of array of integer numbers.
 * Upon completion we are going to use for loop for storage of input data to newly created array. 
 * After that, we are going to use delete array operator for freeing occupied memory before program exits.
 */


#include <iostream>

int main() {
	int* int_arr_ptr = new int[5];

	for (int i = 0; i < 5; i++) {
		std::cout << "Please type in an int value: " << std::endl;
		int input_val;
		std::cin >> input_val;
		int_arr_ptr[i] = input_val;
	}

	for (int i = 0; i < 5; i++) {
		std::cout << "number " << int_arr_ptr[i] << " is stored on:"
				  << (int_arr_ptr + i) << " address." << std::endl;
	}

	delete []int_arr_ptr;
	return 0;
}