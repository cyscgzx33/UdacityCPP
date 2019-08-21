/* [Description]
 * The problem with passing a proprietary class is that the standard copy constructor makes a 1:1 copy of all data members, 
 * including pointers to objects. This behavior is also referred to as "shallow copy". 
 * In the above example we would have liked (and maybe expected) a "deep copy" of the object though, 
 * i.e. a copy of the data to which the pointer refers. A solution to this problem is to create a proprietary copy constructor 
 * in the class Vehicle. The following piece of code overwrites the default copy constructor and can be modified 
 * to make a customized copy of the data members.
 * */

#include <iostream>
#include <thread>
#include <future>

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
    Vehicle v0; // default ctor
    Vehicle v1(1, "Vehicle 1"); // init ctor

    // launch a thread that modifies the Vehicle name
    std::future<void> ftr = std::async( [](Vehicle v) {
        std::this_thread::sleep_for( std::chrono::milliseconds(500) ); // simulate work
        v.setName("Vehicle 2");
    }, v0 );

    v0.setName("Vehicle 3");

    ftr.wait();
    std::cout << v0.getName() << std::endl;

    return 0;
}

/* [Output]
 * 
 * Vehicle #0 Default consturctor called!
 * Vehicle #1 Initializing consturctor called!
 * Vehicle #0 Copy consturctor called!
 * Vehicle #0 Copy consturctor called!
 * Vehicle #0 Copy consturctor called!
 * Vehicle 3
 */