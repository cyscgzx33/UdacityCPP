// One very important trait of concurrent programs is their non-deterministic behavior.
// It can not be predicted which thread the scheduler will execute at which point in time. 
// In the code on the right, the amount of work to be performed both in the thread function 
// and in main has been split into two separate jobs.


// This program, after compilation, it would shoot different output each time running it.

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

    // do something in main()
    std::this_thread::sleep_for( std::chrono::microseconds(50) ); // simulate work
    std::cout << "Finished work 1 in main\n";

    std::this_thread::sleep_for( std::chrono::microseconds(50) ); // simulate work
    std::cout << "Finished work 2 in main\n";

    // wait for thread to finish
    t.join();

    return 0;
}
