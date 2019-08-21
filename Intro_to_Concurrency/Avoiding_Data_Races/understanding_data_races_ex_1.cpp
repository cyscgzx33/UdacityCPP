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

class Vehicle
{
  public:
    // default constructor
    Vehicle() : id_(0)
    {
        std::cout << "Vehicle #" << id_ << " Default constructor called" << std::endl;
    }

    // initializing constructor
    Vehicle(int id) : id_(id)
    {
        std::cout << "Vehicle #" << id_ << " initializing constructor called" << std::endl;
    }

    // setter and getter
    void setID(int id) { id_ = id; }
    int getID() { return id_; }

  private:
    int id_;
};

int main()
{
    // create instances of class Vehicle
    Vehicle v0; // default constructor
    Vehicle v1(1); // initializing constructor

    // read and write name in different threads
    // QUESTION: figure out which one of the above creates a data race?
    std::future<void> ftr = std::async( [](Vehicle v) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // simulate work
        v.setID(2);
    }, v0);

    v0.setID(3);

    ftr.wait();
    std::cout << "Vehicle #" << v0.getID() << std::endl;

    return 0;
}

/* [Description]
 * 
 * Passing data to a thread in this way is a clean and safe method as there is no danger of a data race - 
 * at least when atomic data types such as integers, doubles, chars or booleans are passed.
 * 
 * Note that the class Vehicle has a default constructor and an initializing constructor. 
 * In the main function, when the instances v0 and v1 are created, each constructor is called respectively. 
 * Note that v0 is passed by value to a Lambda, which serves as the thread function for std::async. 
 * Within the Lambda, the id of the Vehicle object is changed from the default (which is 0) to a new value 2. 
 * Note that the thread execution is paused for 500 milliseconds to guarantee that the change is performed well
 * after the main thread has proceeded with its execution.
 * 
 * In the main thread, immediately after starting up the worker thread, the id of v0 is changed to 3. 
 * Then, after waiting for the completion of the thread, the vehicle id is printed to the console. 
 * In this program, the output will always be the following:
 * 
 * [Output]
 * Vehicle #0 Default constructor called
 * Vehicle #1 initializing constructor called
 * Vehicle #3
 * 
 */