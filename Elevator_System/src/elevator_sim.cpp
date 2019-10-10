#include "elevator.h"

int main(int argc, char** argv)
{
    Elevator elev(7);

    elev.handleExternalRequest( ExternalRequest(3, Direction::kDown) );
    std::cout << elev.elevatorStatus();
    elev.handleExternalRequest( ExternalRequest(2, Direction::kUp) );
    std::cout << elev.elevatorStatus();
    elev.openGate();
    std::cout << elev.elevatorStatus();
    elev.closeGate();
    std::cout << elev.elevatorStatus();
    elev.openGate();
    std::cout << elev.elevatorStatus();
    elev.closeGate();
    std::cout << elev.elevatorStatus();
    
    return 0;
}