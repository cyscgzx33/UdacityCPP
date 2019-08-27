/**
 * [Description]
 * In the following, a short overview of the different available mutex types is given:
 *  1. mutex: provides the core functions lock() and unlock() and the non-blocking try_lock() method that 
 *     returns if the mutex is not available.
 *  2. recursive_mutex: allows multiple acquisitions of the mutex from the same thread.
 *  3. timed_mutex: similar to mutex, but it comes with two more methods try_lock_for() and try_lock_until() that
 *     try to acquire the mutex for a period of time or until a moment in time is reached.
 *  4. recursive_timed_mutex: is a combination of timed_mutex and recursive_mutex.
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

    // getters / setters
    void printSize()
    {
      mutex_.lock();
      std::cout << "#vehicles = " << vehicles_.size() << std::endl;
      mutex_.unlock();
    }

    // typical behavior methods
    void pushBack(Vehicle&& v)
    {
      for (size_t i = 0; i < 3; i++)
      {
        if ( mutex_.try_lock_for( std::chrono::milliseconds(100) ) ) // be alert to the difference of milliseconds and microseconds
        {
          vehicles_.emplace_back( std::move(v) );
          // std::this_thread::sleep_for( std::chrono::microseconds(100) );
          mutex_.unlock();
          break;
        }
        else
        {
          std::cout << "Error! Vehicle #" << v.getID() << " could not be added to the vector" << std::endl;
          std::this_thread::sleep_for( std::chrono::milliseconds(100) );
        }
      }
    }

  private:
    std::vector<Vehicle> vehicles_; // list of all vehicles waiting to enter this intersection
    std::timed_mutex mutex_;
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