#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <vector>
#include <future>
#include <mutex>
#include <memory>
#include "TrafficObject.h"
#include "TrafficLight.h"

// forward declarations to avoid include cycle
class Street;
class Vehicle;

// auxiliary class to queue and dequeue waiting vehicles in a thread-safe manner
class WaitingVehicles
{
public:
    // getters / setters
    int getSize();

    // typical behaviour methods
    void pushBack(std::shared_ptr<Vehicle> vehicle, std::promise<void> &&promise);
    void permitEntryToFirstInQueue();

private:
    std::vector<std::shared_ptr<Vehicle>> vehicles_;          // list of all vehicles waiting to enter this intersection
    std::vector<std::promise<void>> promises_; // list of associated promises
    std::mutex mutex_;
};

class Intersection : public TrafficObject
{
public:
    // constructor / desctructor
    Intersection();

    // getters / setters
    void setIsBlocked(bool isBlocked);

    // typical behaviour methods
    void addVehicleToQueue(std::shared_ptr<Vehicle> vehicle);
    void addStreet(std::shared_ptr<Street> street);
    std::vector<std::shared_ptr<Street>> queryStreets(std::shared_ptr<Street> incoming); // return pointer to current list of all outgoing streets
    void simulate();
    void vehicleHasLeft(std::shared_ptr<Vehicle> vehicle);
    bool trafficLightIsGreen();

private:

    // typical behaviour methods
    void processVehicleQueue();

    // private members
    TrafficLight traffic_light_;
    std::vector<std::shared_ptr<Street>> streets_;   // list of all streets connected to this intersection
    WaitingVehicles waiting_vehicles_; // list of all vehicles and their associated promises waiting to enter the intersection
    bool is_blocked_;                  // flag indicating wether the intersection is blocked by a vehicle
};

#endif