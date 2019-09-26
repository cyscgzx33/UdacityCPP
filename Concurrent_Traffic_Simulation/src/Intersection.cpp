#include <iostream>
#include <thread>
#include <chrono>
#include <future>
#include <random>

#include "Street.h"
#include "Intersection.h"
#include "Vehicle.h"

/* Implementation of class "WaitingVehicles" */

int WaitingVehicles::getSize()
{
    std::lock_guard<std::mutex> lock(mutex_);

    return vehicles_.size();
}

void WaitingVehicles::pushBack(std::shared_ptr<Vehicle> vehicle, std::promise<void> &&promise)
{
    std::lock_guard<std::mutex> lock(mutex_);

    vehicles_.push_back(vehicle);
    promises_.push_back(std::move(promise));
}

void WaitingVehicles::permitEntryToFirstInQueue()
{
    std::lock_guard<std::mutex> lock(mutex_);

    /* Task L2.3 */
    // get entries from the front of both queues
    auto firstPromise = promises_.begin();
    auto firstVehicle = vehicles_.begin();

    // fulfill promise and send signal back that permission to enter has been granted
    firstPromise->set_value();

    // remove front elements from both queues
    vehicles_.erase(firstVehicle);
    promises_.erase(firstPromise);
}

/* Implementation of class "Intersection" */

Intersection::Intersection()
{
    type_ = ObjectType::objectIntersection;
    is_blocked_ = false;
}

void Intersection::addStreet(std::shared_ptr<Street> street)
{
    streets_.push_back(street);
}

std::vector<std::shared_ptr<Street>> Intersection::queryStreets(std::shared_ptr<Street> incoming)
{
    // store all outgoing streets in a vector ...
    std::vector<std::shared_ptr<Street>> outgoings;
    for (auto it : streets_)
    {
        if (incoming->getID() != it->getID()) // ... except the street making the inquiry
        {
            outgoings.push_back(it);
        }
    }

    return outgoings;
}

// adds a new vehicle to the queue and returns once the vehicle is allowed to enter
void Intersection::addVehicleToQueue(std::shared_ptr<Vehicle> vehicle)
{
    std::unique_lock<std::mutex> lck(mtx_);
    std::cout << "Intersection #" << id_ << "::addVehicleToQueue: thread id = " << std::this_thread::get_id() << std::endl;
    lck.unlock();

    /* Task L2.2 */
    // add new vehicle to the end of the waiting line
    std::promise<void> prmsVehicleAllowedToEnter;
    std::future<void> ftrVehicleAllowedToEnter = prmsVehicleAllowedToEnter.get_future();
    waiting_vehicles_.pushBack(vehicle, std::move(prmsVehicleAllowedToEnter));

    // wait until the vehicle is allowed to enter
    ftrVehicleAllowedToEnter.wait();
    lck.lock();
    std::cout << "Intersection #" << id_ << ": Vehicle #" << vehicle->getID() << " is granted entry." << std::endl;
    
    // FP.6b : use the methods TrafficLight::getCurrentPhase and TrafficLight::waitForGreen to block the execution until the traffic light turns green.
    lck.unlock();

    if (traffic_light_.getCurrentPhase() == TrafficLightPhase::kRed)
        traffic_light_.waitForGreen();
}

void Intersection::vehicleHasLeft(std::shared_ptr<Vehicle> vehicle)
{
    //std::cout << "Intersection #" << _id << ": Vehicle #" << vehicle->getID() << " has left." << std::endl;

    // unblock queue processing
    this->setIsBlocked(false);
}

void Intersection::setIsBlocked(bool isBlocked)
{
    is_blocked_ = isBlocked;
    //std::cout << "Intersection #" << _id << " isBlocked=" << isBlocked << std::endl;
}

// virtual function which is executed in a thread
void Intersection::simulate() // using threads + promises/futures + exceptions
{
    // FP.6a : In Intersection.h, add a private member _trafficLight of type TrafficLight. At this position, start the simulation of _trafficLight.
    traffic_light_.simulate();

    // launch vehicle queue processing in a thread
    threads_.emplace_back(std::thread(&Intersection::processVehicleQueue, this));
}

void Intersection::processVehicleQueue()
{
    // print id of the current thread
    //std::cout << "Intersection #" << _id << "::processVehicleQueue: thread id = " << std::this_thread::get_id() << std::endl;

    // continuously process the vehicle queue
    while (true)
    {
        // sleep at every iteration to reduce CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        // only proceed when at least one vehicle is waiting in the queue
        if (waiting_vehicles_.getSize() > 0 && !is_blocked_)
        {
            // set intersection to "blocked" to prevent other vehicles from entering
            this->setIsBlocked(true);

            // permit entry to first vehicle in the queue (FIFO)
            waiting_vehicles_.permitEntryToFirstInQueue();
        }
    }
}

bool Intersection::trafficLightIsGreen()
{
   // please include this part once you have solved the final project tasks
   if (traffic_light_.getCurrentPhase() == TrafficLightPhase::kGreen)
       return true;
   else
       return false;

  // return true; // makes traffic light permanently green
} 