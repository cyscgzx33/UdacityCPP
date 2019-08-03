#include <iostream>
// Illustration of memory allocation and deallocation
int main() {

    int *ptr = nullptr;
    /*
     * When using new, best practice in coding states that we need to enclose it within a try-catch block. 
     * The new operator throws an exception and does not return a value. 
     * To force the new operator to return a value, you canuse the nothrow qualifier as shown below:
     */
    ptr = new(std::nothrow) int;
    if (!ptr) {
        std::cout << "Mem alloc failed!" << std::endl;
    }
    else {
        // assigning value to newly allocated address
        *ptr = 31;
        // checking our pointer state:
        std::cout<<" Address is: " << ptr << std::endl;
        std::cout<<" Value is: " << *ptr << std::endl;
    }

    // We are creating pointer to array of integers
    int *arr_ptr = new(std::nothrow) int[3];
    // We are storing new values to created array
    // 0 1 4
    for (int i=0; i<3; i++)
        arr_ptr[i] = (i*i);

    // Writing our arr_ptr pointer info:

    for (int i=0; i<3; i++) {
        // notice notation for retrieval of memory address
        // in array pointers ( we are using references)
        std::cout<<" Address is: " << &arr_ptr[i] << std::endl;
        std::cout<<" Value is: " << arr_ptr[i] << std::endl;
    }

    // Before our program is finished, we have responsibility
    // to deallocate all of our allocated memory:

    // memory is released in memory where
    // pointer-variable is pointing
    // integer pointer
    delete ptr;
    // this is going to release whole array which
    // pointer is pointing to
    // array of integers pointer - block of memory
    delete[] arr_ptr;

    return 0;
}