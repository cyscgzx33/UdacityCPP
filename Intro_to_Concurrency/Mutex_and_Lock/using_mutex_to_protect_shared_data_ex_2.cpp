/**
 * [Description]
 * In its simplest form, using a mutex consists of four straight-forward steps:
 *   1. Include the <mutex> header
 *   2. Create an std::mutex
 *   3. Lock the mutex using lock() before read/write is called
 *   4. Unlock the mutex after the read/write operation is finished using unlock()
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
  private:
    int id_;
};

class WaitingVehicles
{
  public:
    WaitingVehicles() {}

    // getters / setters
    /**
     * [Explain] 
     * Note that the mutex is also locked in the function printSize just before printing the size of the vector. 
     * The reason for this lock is two-fold: First, we want to prevent a data race that would occur when a read-access 
     * to the vector and a simultaneous write access (even when under the lock) would occur. And second, we want to 
     * exclusively reserve the standard output to the console for printing the vector size without other threads 
     * printing to it at the same time.
     * */
    void printSize()
    {
      mutex_.lock();
      std::cout << "#vehicles = " << vehicles_.size() << std::endl;
      mutex_.unlock();
    }

    // typical behavior methods
    /**
     * [Explain]
     * In order to protect the access to _vehicles from being manipulated by several threads at once, 
     * a mutex has been added to the class as a private data member. In the pushBack function, 
     * the mutex is locked before a new element is added to the vector and unlocked after the operation is complete.
     * */
    void pushBack(Vehicle&& v)
    {
      mutex_.lock();
      vehicles_.emplace_back( std::move(v) ); // data race would cause an exception
      mutex_.unlock();
    }

  private:
    std::vector<Vehicle> vehicles_; // list of all vehicles waiting to enter this intersection
    std::mutex mutex_;
};

int main()
{
  std::shared_ptr<WaitingVehicles> queue(new WaitingVehicles);
  std::vector<std::future<void>> futures;
  for (int i = 0; i < 1000; i++)
  {
    Vehicle v(i);
    futures.emplace_back( std::async( std::launch::async, &WaitingVehicles::pushBack, queue, std::move(v) ) );
  }

  std::for_each( futures.begin(), futures.end(), [](std::future<void>& ftr) {
    ftr.wait();
  } );

  queue->printSize();

  return 0;
}