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
        futures.emplace_back( std::async( std::launch::async, &WaitingVehicles::pushBack, queue, std::move(v) ) );
    }

    std::for_each( futures.begin(), futures.end(), [](std::future<void>& ftr) {
        ftr.wait();
    } );

    queue->printSize();

    return 0;
}