/* [Description]
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
    Vehicle() : id_(0), name_( new std::string("Default Name") )
    {
        std::cout << "Vehicle #" << id_ << " Default consturctor called!" << std::endl;
    }

    // Initializing constructor
    Vehicle(int id, std::string name) : id_(id), name_( new std::string(name) )
    {
        std::cout << "Vehicle #" << id_ << " Initializing consturctor called!" << std::endl;
    }

    // copy constructor (deep copy / proprietary copy)
    Vehicle(const Vehicle& src)
    {
        id_ = src.id_;
        if (src.name_ != nullptr)
        {
            name_ = new std::string;
            *name_ = *src.name_;
        }
        std::cout << "Vehicle #" << id_ << " Copy consturctor called!" << std::endl;
    }

    // move constructor
    Vehicle(Vehicle&& src)
    {
        id_ = src.getID();
        name_ = new std::string( src.getName() );

        src.setID(0);
        src.setName("Default Name");

        std::cout << "Vehicle #" << id_ << " Move constructor called!" << std::endl;
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
    }, std::move(v0) );

    ftr.wait();
    std::cout << v0.getName() << std::endl;

    return 0;
}

/* 
 * [Output]
 * 
 * Vehicle #0 Default consturctor called!
 * Vehicle #1 Initializing consturctor called!
 * Vehicle #0 Move constructor called!
 * Vehicle #0 Move constructor called!
 * Vehicle #0 Move constructor called!
 * Default Name
 *
 * */