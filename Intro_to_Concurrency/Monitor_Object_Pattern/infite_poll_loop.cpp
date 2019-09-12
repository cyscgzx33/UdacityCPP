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

	bool dataIsAvailable()
	{
		std::lock_guard<std::mutex> my_lock(mutex_);
		return !vehicles_.empty();
	}

	Vehicle popBack()
	{
		// perform vector modification under the lock
		std::lock_guard<std::mutex> u_lock(mutex_);

		// remove last vector element from queue
		Vehicle v = std::move( vehicles_.back() );
		vehicles_.pop_back();

		return v; // will not be copied due to return value optimization (RVO) in C++
	}

	void pushBack(Vehicle&& v)
	{
		// simulate some work
		std::this_thread::sleep_for( std::chrono::milliseconds(100) );

		// perform vector modification under the lock
		std::lock_guard<std::mutex> u_lock(mutex_);

		// add vector to queue
		std::cout << "  Vehicle #" << v.getID() << " will be added to the queue" << std::endl;
		vehicles_.emplace_back( std::move(v) );
	}
  private:
	std::vector<Vehicle> vehicles_; // list of all vehicles waiting to enter this intersection
	std::mutex mutex_;
};

int main()
{
	// create monitor object as a shared pointer to enable access by multiple threads
	std::shared_ptr<WaitingVehicles> queue(new WaitingVehicles);

	std::cout << "Spawning threads..." << std::endl;
	std::vector<std::future<void>> futures;
	for (int i = 0; i < 10; i++)
	{
		// create a new Vehicle instance and move it into the queue
		Vehicle v(i);
		futures.emplace_back( std::async( std::launch::async, &WaitingVehicles::pushBack, queue, std::move(v) ) );
	}

	std::cout << "Collecting results ... " << std::endl;
	while (true)
	{
		if ( queue->dataIsAvailable() )
		{
			Vehicle v = queue->popBack();
			std::cout << "  Vehicle #" << v.getID() << " has been removed from the queue" << std::endl;
		}
	}

	std::for_each(futures.begin(), futures.end(), [](std::future<void>& ftr) { ftr.wait(); } );

	std::cout << "Finished processing queue" << std::endl;

	return 0;
}