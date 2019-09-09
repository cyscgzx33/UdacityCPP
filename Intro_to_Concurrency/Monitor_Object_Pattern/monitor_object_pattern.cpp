/**
 * [Description]
 * 
 * One important step towards such a construct is to implement a monitor object, 
 * which is a design pattern that synchronizes concurrent method execution to ensure that 
 * only one method at a time runs within an object. It also allows an object's methods to 
 * cooperatively schedule their execution sequences. The problem solved by this pattern 
 * is based on the observation that many applications contain objects whose methods are 
 * invoked concurrently by multiple client threads. These methods often modify the state of their objects, 
 * for example by adding data to an internal vector. For such concurrent programs to execute correctly, 
 * it is necessary to synchronize and schedule access to the objects very carefully. 
 * The idea of a monitor object is to synchronize  the access to an object's methods so that 
 * only one method can execute at any one time.
 * 
 * While the functionality of the monitor object we have constructed is an improvement over 
 * many other methods that allow passing data to threads, it has one significant disadvantage: 
 * The main thread has to wait until all worker threads have completed their jobs and only then 
 * can it access the added data in bulk. A system which is truly interactive however has to 
 * react to events as they arrive - it should not wait until all threads have completed 
 * their jobs but instead act immediately as soon as new data arrives. 
 * In the following, we want to add this functionality to our monitor object.
 * 
 * */

#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <mutex>
#include <algorithm>

class Vehicle
{
  public:
    Vehicle(int id) : id_(id) {}
    int getID() { return id_; }

  private:
    int id_;
};

class WaitingVehicles
{
  public:
    WaitingVehicles() {}

    void printIDs()
    {
        std::lock_guard<std::mutex> my_lock(mutex_); // lock is released when my_lock goes out of scope
        for (auto& v : vehicles_)
            std::cout << "   Vehicle #" << v.getID() << " is now waiting in the queue." << std::endl;
    }

    void pushBack(Vehicle&& v)
    {
        // perfrom vector modification under the lock
        std::lock_guard<std::mutex> uLock(mutex_);
        std::cout << "   Vehicle #" << v.getID() << " will be added to the queue." << std::endl;
        vehicles_.emplace_back( std::move(v) );

        // simulate some work
        std::this_thread::sleep_for( std::chrono::milliseconds(800) );
    }

  private:
    std::vector<Vehicle> vehicles_; // list of vehicles waiting to enter this intersection
    std::mutex mutex_;
};


int main()
{
    // create monitor object as a shared pointer to enable access by mutiple threads
    std::shared_ptr<WaitingVehicles> queue(new WaitingVehicles);

    std::cout << "Spawning threads..." << std::endl;
    std::vector<std::future<void>> futures;
    for (int i = 0; i < 10; i++)
    {
        // create a new Vehicle instance and move it into the queue
        Vehicle v(i);
        futures.emplace_back( std::async( std::launch::async, &WaitingVehicles::pushBack, queue, std::move(v) ) );
    }

    std::for_each( futures.begin(), futures.end(), [](std::future<void>& ftr) {
        ftr.wait();
    } );

    std::cout << "Collecting results ... " << std::endl;
    queue->printIDs();

    return 0;
}

/**
 * [Output]
 * 
 * Spawning threads...
   Vehicle #0 will be added to the queue.
   Vehicle #1 will be added to the queue.
   Vehicle #2 will be added to the queue.
   Vehicle #3 will be added to the queue.
   Vehicle #4 will be added to the queue.
   Vehicle #5 will be added to the queue.
   Vehicle #7 will be added to the queue.
   Vehicle #6 will be added to the queue.
   Vehicle #8 will be added to the queue.
   Vehicle #9 will be added to the queue.
Collecting results ... 
   Vehicle #0 is now waiting in the queue.
   Vehicle #1 is now waiting in the queue.
   Vehicle #2 is now waiting in the queue.
   Vehicle #3 is now waiting in the queue.
   Vehicle #4 is now waiting in the queue.
   Vehicle #5 is now waiting in the queue.
   Vehicle #7 is now waiting in the queue.
   Vehicle #6 is now waiting in the queue.
   Vehicle #8 is now waiting in the queue.
   Vehicle #9 is now waiting in the queue.
 *
 * Note: the spawning will take 800 ms each item, collecting is happened imediately
 * */