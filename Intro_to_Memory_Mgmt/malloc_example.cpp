/* [description of Malloc()]
 * Malloc is a function which is essentially forerunner to new operator in C++, originally inherited from C. 
 * Its function is to allocate a block of specific size, measured in bytes of memory, 
 * where result of this operation (function) is pointer to the beginning of the block. 
 * Data stored in this memory block is not initialized, which means that this space has non determinate values.
 * 
 * Prototype of this function is:
 * void* malloc(size_t size);
 * Size is unsigned integer value which represent memory block in bytes. 
 * It is important to note that in case of failed allocation return value is null pointer.
 * */

#include <iostream> // Included library for memset
#include <cstring> // included library for malloc
#include <cstdlib>

int main() {
    int *ptr = NULL;
    // Notice how pointer is allocated to single int memory space 
    // but later is redicerted to show to memory block
    ptr = new(std::nothrow) int;
    // We can initialize memory block using malloc
    // declaring memory space for: array of 4 integers
    // [Note] we need type cast here, as the function prototype if "void*"
    // otherwise: compiler will throw that "error: invalid conversion from ‘void*’ to ‘int*’ [-fpermissive]""
    ptr = std::malloc(4*sizeof(int));
        for (int i=0; i<4; i++){
        std::cout << "Address: "
        << &ptr[i] << " Value: "<< ptr[i] << std::endl;
    }
    // every memory place is used for initialization of specific value
    // here we are using letters for values, but casted to ints
    for( int i=0; i<4; i++){
        // sending address by reference
        std::memset(&ptr[i],('A' + i), sizeof(int));
    }
    // Printing state of our array
    // we are converting int values to char to see what is happening with our values
    for (int i=0; i<4; i++){
        std::cout << "Address: " << &ptr[i]
        << " Value: "<< char(ptr[i])
        << std::endl;
    }
    /* OUTPUT:
    Address: 0x1031c20 Value: 0
    Address: 0x1031c24 Value: 0
    Address: 0x1031c28 Value: 0
    Address: 0x1031c2c Value: 0
    Address: 0x1031c20 Value: A
    Address: 0x1031c24 Value: B
    Address: 0x1031c28 Value: C
    Address: 0x1031c2c Value: D
    */
    return 0;
}
