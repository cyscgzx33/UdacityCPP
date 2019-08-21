/* [Description]
 * One of the primary sources of error in concurrent programming are data races. 
 * They occur, when two concurrent threads are accessing the same memory location 
 * while at least one of them is modifying (the other thread might be reading or modifying).
 * 
 * 
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

 * 
 */