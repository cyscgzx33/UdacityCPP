#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <vector>
#include <string>
#include <iostream>
#include "request.h"

class Elevator; // It is necessary to declare it here!
                // as ElevatorButton class calls Elevator class inside of it
class ExternalRequest;
class InternalRequest;

enum class Status
{
    kUp = 0,
    kDown = 1,
    kIdle = 2
};

class ElevatorButton
{
  private:
    int level = 0;
    Elevator* elevator = nullptr;

  public:
    ElevatorButton(int l, Elevator* e) : level(l), elevator(e) {}
    
    void pressButton();
};

class Elevator
{
  private:
    std::vector<ElevatorButton> buttons_;
    std::vector<bool> up_stops_;
    std::vector<bool> down_stops_;
    int current_level_;
    Status status_;

  public:
    Elevator(int n);

    void insertButton(ElevatorButton eb);
    void handleExternalRequest(ExternalRequest r);
    void handleInternalRequest(InternalRequest r);
    void openGate();
    void closeGate();
    bool noRequests(const std::vector<bool>& stops);
    std::string getElevatorStatusInfo() const;
    std::string getElevatorRequestListInfo() const;
    Status getStatus() const { return status_; }
    int getCurLevel() const { return current_level_; }
};

#endif /* ELEVATOR_H */