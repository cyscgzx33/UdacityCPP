#include <iostream>
#include <thread>

void threadFunctionEven()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1)); // simulate work
    std::cout << "Even thread\n";
}

/* Student Task START */
void threadFunctionOdd()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1)); // simulate work
    std::cout << "Odd thread\n";
}
/* Student Task END */

int main()
{
    /* Student Task START */
    for (int i = 0; i < 6; ++i)
    {
        if (i % 2 == 0)
        {
            std::thread t(threadFunctionEven);
            t.detach();
        }
        else
        {
            std::thread t(threadFunctionOdd);
            t.detach();
        }
    }
    /* Student Task END */


    // Experiment: if commenting out sleep_for() function, what will happen?

    // The order in which even and odd threads are executed changes. 
    // Also, some threads are executed after the main function reaches its end. 
    // When sleep_for is removed, threads will not finish before the program terminates.
    
    // ensure that main does not return before the threads are finished
    std::this_thread::sleep_for(std::chrono::milliseconds(1)); // simulate work

    // the time of sleep also matters
    // if only 1 ms, it might not be enough to execute all the 6 commands of odd/even

    std::cout << "End of main is reached" << std::endl;
    return 0;
}
