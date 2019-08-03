#include <cstring> // or <string>
#include <iostream>

int main() {
	char* ptr = new char('C');
	char str[4] = "AAA"; // [Important Note] it is ACTUALLY "AAA\0"
						 // and if we go with "str[3] = "AAA", compiler would throw an error:
						 // error: initializer-string for array of chars is too long [-fpermissive]
	char str_2[4] = "AAA";

	std::cout << "Before Value of *ptr: " << *ptr << std::endl;
	std::cout << "Before Value of str: " << str << std::endl;
	std::cout << "Before Value of str_2: " << str_2 << std::endl;

	/* [Description]
	 * 1. as for ptr: find the address of ptr, provided the value 'A', and the number of bases that you want to occupy.
	 * 2. as for str+1: find the address of str array, considering its next element, povided the value 'B', occupy only 1 space.
	 * 3. as for str_2+1: same as above, but will be occupying for 2 spaces.
	 * */
	memset(ptr, 'A', 1);
	memset(str + 1, 'B', 1);
	memset(str_2 + 1, 'B', 2 );

	std::cout << "After Value of *ptr: " << *ptr << std::endl;
	std::cout << "After Value of str: " << str << std::endl;
	std::cout << "After Value of str_2: " << str_2 << std::endl;

	delete ptr;

	return 0;
}