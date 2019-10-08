#include "elevator.h"

void Elevator::insertButton(ElevatorButton eb)
{
    buttons_.push_back(eb);
}

void Elevator::handleExternalRequest(ExternalRequest r)
{
    // handle the external request to go Up
    if (r.getDirection() == Direction::kUp)
    {
        up_stops_[r.getLevel() - 1] = true;
        if ( noRequests(down_stops_) )
            status_ = Status::kUp;
    }
    // handle the external request to go Down
    else
    {
        down_stops_[r.getLevel() - 1] = true;
        if ( noRequests(up_stops_) )
            status_ = Status::kDown;
    }
}

void Elevator::handleInternalRequest(InternalRequest r)
{
    if (status_ == Status::kUp)
    {
        if (r.getLevel() >= current_level_ + 1)
            up_stops_[r.getLevel() - 1] = true;
    }
    else if (status_ == Status::kDown)
    {
        if (r.getLevel() <= current_level_ + 1)
            down_stops_[r.getLevel() - 1] = true;
    }
}

void Elevator::openGate()
{
    if (status_ == Status::kUp)
    {
        for (int i = 0; i < up_stops_.size(); i++)
        {
            int check_level = (current_level_ + 1) % up_stops_.size();
            if ( up_stops_[check_level] == true)
            {
                current_level_ = check_level;
                up_stops_[check_level] = false;
                break;
            }
        }
    }
    else if (status_ == Status::kDown)
    {
        for (int i = 0; i < down_stops_.size(); i++)
        {
            int check_level = (current_level_ + 1) % down_stops_.size();
            if ( down_stops_[check_level] == true )
            {
                current_level_ = check_level;
                up_stops_[check_level] = false;
                break;
            }
        }
    }
}

void Elevator::closeGate()
{
    if (status_ == Status::kIdle)
    {
        if ( noRequests(down_stops_) )
        {
            status_ = Status::kUp;
            return;
        }

        if ( noRequests(up_stops_) )
        {
            status_ = Status::kDown;
            return;
        }
    }
    else if (status_ == Status::kUp)
    {
        if ( noRequests(up_stops_) )
        {
            if ( noRequests(down_stops_) )
                status_ = Status::kIdle;
            else
                status_ = Status::kDown;
        }
    }
    else // status_ = Status::kDown
    {
        if ( noRequests(down_stops_) )
        {
            if ( noRequests(up_stops_) )
                status_ = Status::kIdle;
            else
                status_ = Status::kUp;
        }
    }
}

bool Elevator::noRequests(const std::vector<bool>& stops)
{   
    // check if any of the levels needs stopping
    for (auto stop : stops)
    {
        if (stop == true)
            return false;
    }

    return true;
}

std::string Elevator::elevatorStatus() const
{
    std::string status;
    if (status_ == Status::kUp)
        status = "UP";
    if (status_ == Status::kDown)
        status = "DOWN";
    if (status_ == Status::kIdle)
        status = "IDLE";
    std::string description = "Current elevator status is : " + status + ".\n" + 
                              "Current level is : " + std::to_string
}