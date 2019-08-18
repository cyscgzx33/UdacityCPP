/* [Description]
 *
 * In the previous example, we have to ensure that the existence of v2 outlives the completion of the thread t2 - 
 * otherwise there will be an attempt to access an invalidated memory address. 
 * An alternative is to use a heap-allocated object and a reference-counted pointer such as std::shared_ptr<Vehicle> 
 * to ensure that the object lives as long as it takes the thread to finish its work. 
 * The following example shows how this can be implemented:
 * 
 */

#include <iostream>
#include <thread>

class Vehicle {
  public:
    Vehicle() : id_(0) {}
    void addID(int id) { id_ = id; }
    void printID() {
        std::cout << "Vehicle ID = " << id_ << std::endl;
    }
  private:
    int id_;
};

int main() {
    // create thread
    std::shared_ptr<Vehicle> v(new Vehicle);
    std::thread t = std::thread(&Vehicle::addID, v, 2); // pass by reference, change will also be visible in the main thread

    // wait for thread to finish
    t.join();

    // print Vehicle ID
    v->printID();

    return 0;
}

/* [Output]
 * 
 * Vehicle ID = 2
 * 
 */