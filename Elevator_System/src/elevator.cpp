#include "elevator.h"

void Elevator::insertButton(ElevatorButton eb)
{
    buttons_.push_back(eb);
}

void Elevator::handleExternalRequest(ExternalRequest r)
{
    // handle the external request to go up
    if (r.getDirection() == Direction::kUp)
    {
        up_stops_[r.getLevel() - 1] = true;
        if ( noRequests(down_stops_) )
            status_ = Status::kUp;
    }
    // handle the external request to go down
    else
    {
        down_stops_[r.getLevel() - 1] = true;
        if ( noRequests(up_stops_) )
            status_ = Status::kDown;
    }
}