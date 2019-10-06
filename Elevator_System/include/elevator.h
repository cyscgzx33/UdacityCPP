#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <vector>
#include <string>
#include "request.h"


enum class Status
{
    kUp = 0,
    kDown = 1
};

class ElevatorButton
{
  private:
    int level;
    Elevator* elevator;

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
    std::string elevatorStatus() const;
};

#endif /* ELEVATOR_H */