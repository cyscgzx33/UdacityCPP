/* LAB 2
 * - [Objective]
 * 
 * A shared_ptr is a container for raw pointers. 
 * It is a reference counting ownership model i.e. it upholds the reference count of 
 * its contained pointer in correlation with all of the shared_ptr copies. 
 * Basically, any time a new pointer points to a memory block an incrementation of 
 * the counter happens. Likewise, it decrements when the destructor of the object is called. 
 * With this example we are going to use common method when handling these type of pointers.
 *
 */

#include <iostream>
#include <memory>

class A {
public:
	void classAMethod() {
		std::cout << "A::classAMethod()" << std::endl;
	}
};

int main() {
	std::shared_ptr<A> p1(new A);
	std::cout << p1.get() << std::endl; // show address

	std::shared_ptr<A> p2(p1);
	std::cout << p1.get() << std::endl;
	std::cout << p2.get() << std::endl;

	// return the number of shared_ptr objects
	// referring to the same managed object
	std::cout << p1.use_count() << std::endl;
	std::cout << p2.use_count() << std::endl;

	// relinquishes ownership of p1 on the object
	// and pointer becomes NULL
	p1.reset();
	std::cout << "p1 after reset: " << p1.get() << std::endl; // p1 becomes NULL
	std::cout << p2.use_count() << std::endl;
	std::cout << p2.get() << std::endl;

	return 0;
}