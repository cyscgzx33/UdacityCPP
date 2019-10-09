#include "elevator.h"

int main(int argc, char** argv)
{
    Elevator elev(7);

    elev.handleExternalRequest( ExternalRequest(3, Direction::kUp) );
    elev.elevatorStatus();
    elev.handleExternalRequest( ExternalRequest(2, Direction::kDown) );
    elev.elevatorStatus();
    elev.openGate();
    elev.elevatorStatus();
    elev.closeGate();
    elev.elevatorStatus();
    elev.openGate();
    elev.elevatorStatus();
    elev.closeGate();
    elev.elevatorStatus();
    
    return 0;
}