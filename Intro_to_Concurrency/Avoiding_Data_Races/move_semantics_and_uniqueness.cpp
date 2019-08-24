/**
 * [Description]
 * 
 * The std::string has now been changed to a unique pointer, which means 
 * that only a single reference to the memory location it points to is allowed. 
 * Accordingly, the move constructor transfers the unique pointer to the worker 
 * by using std::move and thus invalidates the pointer in the main thread.
 * 
 * The point of this example has been to illustrate that move semantics on its own is not enough to avoid data races. 
 * The key to thread safety is to use move semantics in conjunction with uniqueness. 
 * It is the responsibility of the programmer to ensure that pointers to objects that are moved between threads are unique.
 * 
 * */


#include <iostream>
#include <thread>
#include <future>
#include <memory>

class Vehicle
{
  public:
    // default constructor
    Vehicle() : id_(0), name_(new std::string("Default Nmae") )
    {
        std::cout << "Vehicle #" << id_ << " Default constructor called" << std::endl;
    }

    // initializing constructor
    Vehicle(int id, std::string name) : id_(id), name_( new std::string(name) )
    {
        std::cout << "Vehicle #" << id_ << " Initializing constructor called" << std::endl;
    }

    // move constructor with unique pointer
    Vehicle(Vehicle&& src) : name_( std::move(src.name_) )
    {
        // move id to this and reset id in source
        id_ = src.getID();
        src.setID(0);
    }

    // setter and getter
    void setID(int id) { id_ = id; }
    int getID() { return id_; }
    void setName(std::string name) { *name_ = name; }
    std::string getName() { return *name_; }

  private:
    int id_;
    std::unique_ptr<std::string> name_;
};

int main()
{
    // create instances of class Vehicle
    Vehicle v0;                  // default constructor
    Vehicle v1(1, "Vehicle 1");  // initializing constructor

    // launch a thread that modifies the Vehicle name
    std::future<void> ftr = std::async( [](Vehicle v) {
        v.setName("Vehicle 2");
    }, std::move(v0) );

    ftr.wait();
    std::cout << v0.getName() << std::endl; // this will now cause an exception
                                            // When calling v0.getName(), an exception is thrown, making it clear to the programmer that 
                                            // accessing the data at this point is not permissible - which is the whole point of using 
                                            // a unique pointer here as a data race will now be effectively prevented.

    return 0;
}

/**
 * [Output]
 * 
 * Vehicle #0 Default constructor called
 * Vehicle #1 Initializing constructor called
 * Segmentation fault (core dumped)
 * 
 * */