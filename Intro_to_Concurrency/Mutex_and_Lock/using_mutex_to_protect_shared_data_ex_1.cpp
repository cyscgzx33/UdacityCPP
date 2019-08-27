#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <algorithm>

class Vehicle {
  public:
    Vehicle(int id) : id_(id) {}

  private:
    int id_;
};

class WaitingVehicles {
  public:
    WaitingVehicles() : tmp_vehicles_(0) {}

    // getters & setters
    void printSize() {
        std::cout << "#vehicles = " << tmp_vehicles_ << std::endl;
    }

    // typical behavior methods
    void pushBack(Vehicle &&v) { // rvalue reference, new feature in cpp
        // vehicles_.push_back( std::move(v) ); // data race would cause an exception
        int old_num = tmp_vehicles_;
        std::this_thread::sleep_for( std::chrono::microseconds(1) );
        tmp_vehicles_ = old_num + 1;
    }

  private:
    int tmp_vehicles_;
    std::vector<Vehicle> vehicles_;
};

int main() {
    std::shared_ptr<WaitingVehicles> queue(new WaitingVehicles);
    std::vector<std::future<void> > futures;

    for (int i = 0; i < 1000; i++) {
        Vehicle v(i);
        
        /** 
         * Explain: 
         * 1. Running the program synchronously with launch option std::launch::deferred generates the output in a way that
         *    each task inserted an element into the queue with the total number of vehicles amounting to 1000;
         *    #vehicles = 1000
         * 
         * 2. Running with enforcing a concurrent behavior and change the launch option to std::launch::async,
         *    then this will generate the output (with different results each time)
         *    #vehicles = 498
         * 
         * 3. It seems that in 2. not all the vehicles could be added to the queue. But why is that? Note that in the 
         *    thread function "pushBack" there is a call to sleep_for, which pauses the thread execution for a short time.
         *    his is the position where the data race occurs: First, the current value of _tmpVehicles is stored in a 
         *    temporary variable oldNum. While the thread is paused, there might (and will) be changes to _tmpVehicles 
         *    performed by other threads. When the execution resumes, the former value of _tmpVehicles is written back, 
         *    thus invalidating the contribution of all the threads who had write access in the mean time. Interestingly, 
         *    when sleep_for is commented out, the output of the program is the same as with std::launch::deferred - 
         *    at least that will be the case for most of the time when we run the program. 
         *    But once in a while, there might be a scheduling constellation which causes the bug to expose itself.
         * */
        futures.emplace_back( std::async( std::launch::deferred, &WaitingVehicles::pushBack, queue, std::move(v) ) ); // or std::launch::async


    }

    std::for_each( futures.begin(), futures.end(), [](std::future<void>& ftr) {
        ftr.wait();
    } );

    queue->printSize();

    return 0;
}