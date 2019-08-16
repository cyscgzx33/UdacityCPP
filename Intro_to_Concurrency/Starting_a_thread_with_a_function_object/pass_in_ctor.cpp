#include <iostream>
#include <thread>

class Vehicle {
  public:
    Vehicle(int id) : id_(id) {}
    void operator() () {
        std::cout << "Vehicle object has been created. \n" << std::endl;
    }
  private:
    int id_;
};

int main() {
    // create thread
    std::thread t( Vehicle(1) );                 // C++'s most vexing parse;
                                                    // thus, an extra pair of parenthesis is added here,
                                                    // to avoid ambiguity

    // do something in main()
    std::cout << "Finishing work in main().\n";

    // wait for thread to finish
    t.join();

    return 0;
}
