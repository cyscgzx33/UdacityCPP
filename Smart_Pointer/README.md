# Smart_Pointer
* This project is about implementing a customized garbage collector, by using C++ default pointers. Futher, **verification of memory leakage** is provided to confirm the correctness of implementing such a garbage collector.
* In this project, a simple garbage collector pointer class has been implemented. The garbage collector basically uses three classes: `Pointer`, `PtrDetails` and `Iter`:
    * `Pointer` is the core garbage collector class, which implements a garbage-collection pointer
    * `PtrDetails` maintains a list reference counts with allocated memory, and bonds a reference count to a piece of allocated memory
    * `Iter` is a template class similar in function to an `STL` iterator, and it defines all pointer *operations*, including pointer arithmetic, such as `*`, `->`, `begin()`, and `end()`, which work much like their equivalents in the `STL`.

## Reference
* Udacity nanodegree repo `CppND-Garbage-Collector`.
https://github.com/udacity/CppND-Garbage-Collector
* Chaper 2 - A Simple Garbage Collector for C++, *The Art of C++*.
https://www.cmlab.csie.ntu.edu.tw/~chenhsiu/tech/The_Art_of_C++_ch2.pdf 
