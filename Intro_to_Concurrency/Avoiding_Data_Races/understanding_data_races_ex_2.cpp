/* [Description]
 *
 * When passing a complex data structure however, there are sometimes pointer variables hidden within, 
 * that point to a (potentially) shared data buffer - which might cause a data race even though 
 * the programmer believes that the copied data will effectively preempt this. 
 * The next example illustrates this case by adding a new member variable to the Vehicle class, 
 * which is a pointer to a string object, as well as the corresponding getter and setter functions.
 * 
 * */

#include <iostream>
#include <thread>
#include <future>
#include <string>

class Vehicle
{
  public:
    // default constructor
    Vehicle() : id_(0), name_( new std::string("Default name") )
    {
        std::cout << "Vehicle #" << id_ << " Default constructor called" << std::endl;
    }

    // initializing constructor
    Vehicle(int id, std::string name) : id_(id), name_( new std::string(name) )
    {
        std::cout << "Vehicle #" << id_ << " initializing constructor called" << std::endl;
    }

    // setter and getter
    void setID(int id) { id_ = id; }
    int getID() { return id_; }
    void setName(std::string name) { *name_ = name; }
    std::string getName() { return *name_; }

  private:
    int id_;
    std::string* name_;
};

int main()
{
    // create instances of class Vehicle
    Vehicle v0; // default constructor
    Vehicle v1(1, "Vehicle 1"); // initializing constructor

    // read and write name in different threads
    // QUESTION: figure out which one of the above creates a data race?
    std::future<void> ftr = std::async( [](Vehicle v) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // simulate work
        v.setName("Vehicle 2");
    }, v0);

    v0.setName("vehicle 3");

    ftr.wait();
    std::cout << v0.getName() << std::endl;

    return 0;
}

/* [Description]
 * 
 *
 * 
 * [Output]
 * Vehicle #0 Default constructor called
 * Vehicle #1 initializing constructor called
 * Vehicle 2

 * The basic program structure is mostly identical to the previous example with 
 * the object v0 being copied by value when passed to the thread function. 
 * This time however, even though a copy has been made, the original object v0 is modified, 
 * when the thread function sets the new name. This happens because 
 * the member _name is a pointer to a string and after copying, even though 
 * the pointer variable has been duplicated, it still points to the same location as its value 
 * (i.e. the memory location) has not changed. Note that when the delay is removed in the thread function, 
 * the console output varies between "Vehicle 2" and "Vehicle 3", depending on the system scheduler. 
 * Such an error might go unnoticed for a long time. 
 * It could show itself well after a program has been shipped to the client - 
 * which is what makes this error type so treacherous.
 * 
 * */