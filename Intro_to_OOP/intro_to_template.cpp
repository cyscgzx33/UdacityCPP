/* [Introdution to Generic Programming -- via Template]
 * With templates, the idea is to pass a data type as a parameter so that 
 * you don’t need to write the same function code for operating on different data types. 
 * For example, you might need a function that has to accept many different data types 
 * in order for it to perform some operations or other actions on those data types. 
 * Some of these actions can be dividing, sorting, etc. Rather than writing and 
 * maintaining the multiple function declarations, each accepting slightly different arguments, 
 * you can write one function and pass the argument types as parameters. 
 * At compile time, the compiler then expands the code using the types that are passed as parameters.
 */

#include<iostream>

// template<class T, class U = char> is also workable,
// but the keyword "typename" is preferred here, instead of "class".
template<typename T, typename U = char>
class A  {
    public:
        T x;
        U y;
        A() { std::cout << "Constructor Called" << "\n"; }
};

int main()  
{
    A<char> a;  // This will call A<char, char>    
}