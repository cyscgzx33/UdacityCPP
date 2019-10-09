#include "elevator.h"

int main(int argc, char** argv)
{
    Elevator elev(7);

    elev.handleExternalRequest( ExternalRequest(3, Direction::kUp) );
    std::cout << elev.elevatorStatus() + '\n';
    elev.handleExternalRequest( ExternalRequest(2, Direction::kDown) );
    std::cout << elev.elevatorStatus() + '\n';
    elev.openGate();
    std::cout << elev.elevatorStatus() + '\n';
    elev.closeGate();
    std::cout << elev.elevatorStatus() + '\n';
    elev.openGate();
    std::cout << elev.elevatorStatus() + '\n';
    elev.closeGate();
    std::cout << elev.elevatorStatus() + '\n';
    
    return 0;
}