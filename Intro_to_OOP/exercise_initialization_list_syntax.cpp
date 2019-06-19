/* [Initialization list syntax]
 * Initialization lists are used for a number of reasons: 
 *   (1) First, the compiler can optimize initialization faster than if the members were initialized from within the constructor, 
 *       the code directly assigns to the class attributes. 
 *   (2) The second reason is a bit of a technical paradox. If you have a constant class attribute, 
 *       you can only initialize it using an initialization list. 
 *       Otherwise, you would violate the const keyword simply by initializing the member in the constructor! 
 *   (3) The third reason is that attributes defined as references must use initialization lists.
 */

#include <iostream>
#include <string>
class InitList {
    public:
        // Initialization list is defined as part of constructor syntax
        InitList(int &_ref,char _c): ref(_ref), c(_c) {}
        void print() 
        {
            std::cout << ref << " " << c << "\n";
        }
    private:
        int &ref; // reference
        const char c; // const
};

int main()
{
    int var = 10;
    InitList obj(var, 'A');
    obj.print();
    // Referenced variable:
    var += 10;
    obj.print(); // obj.ref == 20
}
