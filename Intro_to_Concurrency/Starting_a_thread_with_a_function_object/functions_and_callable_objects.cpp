#include <iostream>
#include <thread>

class Vehicle {
  public:
    void operator() () {
        std::cout << "Vehicle object has been created. \n" << std::endl;
    }
};

int main() {
    // create thread
    std::thread t1( ( Vehicle() ) );                 // C++'s most vexing parse;
                                                    // thus, an extra pair of parenthesis is added here,
                                                    // to avoid ambiguity

    std::thread t2 = std::thread( Vehicle() ); // or, use copy initialization

    std::thread t3{ Vehicle() };                    // or, use uniform initialization with braces

    // do something in main()
    std::cout << "Finishing work in main().\n";

    // wait for thread to finish
    t1.join();
    t2.join();
    t3.join();

    return 0;
}
