// In the previous example (randomness_of_events.cpp), the order of execution is determined by the scheduler. 
// If we wanted to ensure that the thread function completed its work before the
// main function started its own work (because it might be waiting for a result to be available),
// we could achieve this by repositioning the call to join.

// In the file on the right, the .join() has been moved to before the work in main(). 
// The order of execution now always looks like the following

#include <iostream>
#include <thread>

void threadFunction()
{
    std::this_thread::sleep_for( std::chrono::microseconds(50) ); // simulate work
    std::cout << "Finished work 1 in thread\n";

    std::this_thread::sleep_for( std::chrono::microseconds(50) ); // simulate work
    std::cout << "Finished work 2 in thread\n";
}

int main()
{
    // create thread
    std::thread t(threadFunction);

    // wait for thread to finish
    t.join();

    // do something in main()
    std::this_thread::sleep_for( std::chrono::microseconds(50) ); // simulate work
    std::cout << "Finished work 1 in main\n";

    std::this_thread::sleep_for( std::chrono::microseconds(50) ); // simulate work
    std::cout << "Finished work 2 in main\n";

    return 0;
}
