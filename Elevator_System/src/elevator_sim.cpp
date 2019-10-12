#include "elevator.h"

int main(int argc, char** argv)
{   
    // Let the user init a N-floor elevator system
    int N = 0;
    std::cout << "Please set elevator system with N floors/levels, where N should a positive integer: " << std::endl;
    std::cin >> N; 

    // instantiate the object
    Elevator elev(N);

    // execute a infite loop to simulate the elevator system
    while (true)
    {   int ext_req_floor = 0; // external request floor #
        std::string ext_req_dir; // external request direction
        std::cout << "At this moment, the elevator system has a state information as: " << std::endl;
        std::cout << elev.getElevatorStatusInfo();

        int ext_button_num = 0;
        std::cout << "Now let's start. Firstly let's shoot some external requests first!\n";
        std::cout << "Please give an input: at how many floors the external elevator button is pushed (from 1 to " << N << ") \n";
        std::cin >> ext_button_num;


        // iterate for ext_button_num times to obtain all the information from user
        for (int i = 0; i < ext_button_num; i++)
        {
            std::cout << "Please give an input: at which floor the external elevator button is pushed (from 1 to " << N << ") \n";
            std::cin >> ext_req_floor;
            std::cout << "Which button you would press, Up or Down (u/d)? \n";
            std::cin >> ext_req_dir;

            std::cout << "Thanks for the input! The elevator's stop request list has been updated! \n";
            if (ext_req_dir == "u" || 
                ext_req_dir == "U" || 
                ext_req_dir == "up" || 
                ext_req_dir == "Up" || 
                ext_req_dir == "UP")
            {
                elev.handleExternalRequest( ExternalRequest(ext_req_floor, Direction::kUp) );
            }
            else if (ext_req_dir == "d" || 
                     ext_req_dir == "D" || 
                     ext_req_dir == "down" || 
                     ext_req_dir == "Down" || 
                     ext_req_dir == "DOWN")
            {
                elev.handleExternalRequest( ExternalRequest(ext_req_floor, Direction::kDown) );
            }
        }

        // start to execute the previous requests
        std::cout << "The elevator system starts to execute the requests ! \n";
        while (elev.getStatus() != Status::kIdle)
        {   
            elev.openGate();

            int int_req_floor = 0; // internal request floor #

            if (elev.getStatus() == Status::kUp)
                std::cout << "Please give an input: which floor do you plan to land (from " << elev.getCurLevel() + 1 << " to " << N << "); \n";
            else
                std::cout << "Please give an input: which floor do you plan to land (from 0 to " << elev.getCurLevel() + 1 << "); \n";
            std::cout << "Or you can type in \"-1\" request to step out the elevator. \n";

            std::cin >> int_req_floor;
            if (int_req_floor >= 0 && int_req_floor <= N)
                elev.handleInternalRequest( InternalRequest(int_req_floor) );
            
            elev.closeGate();
        }

        std::cout << "All the external & internal requests have been process!\n\n";
    } 

    return 0;
}