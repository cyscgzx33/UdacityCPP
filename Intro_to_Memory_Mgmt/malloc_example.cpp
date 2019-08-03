#include <iostream>
// Included library for memset
#include <cstring>
// included library for malloc
#include <cstdlib>
int main() {
    int *ptr = NULL;
    // Notice how pointer is allocated to single int memory space 
    // but later is redicerted to show to memory block
    ptr = new(std::nothrow) int;
    //  We can initialize memory block using malloc
    //  declaring memory space for array of 4 integers
    ptr = (int*)std::malloc(4*sizeof(int));
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
