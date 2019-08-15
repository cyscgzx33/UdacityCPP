// Let us now take a look at what happens if we don’t join a thread before its destructor is called. 
// When we comment out join in the example above and then run the program again, it aborts with an error. 
// The reason why this is done is that the designers of the C++ standard wanted to make debugging a multi-threaded program easier: 
// Having the program crash forces the programer to remember joining the threads that are created in a proper way. 
// Such a hard error is usually much easier to detect than soft errors that do not show themselves so obviously.

// There are some situations however, where it might make sense to not wait for a thread to finish its work. 
// This can be achieved by "detaching" the thread, by which the internal state variable "joinable" is set to "false". 
// This works by calling the detach() method on the thread. The destructor of a detached thread does nothing: 
// It neither blocks nor does it terminate the thread. In the following example, detach is called on the thread object, 
// which causes the main thread to immediately continue until it reaches the end of the program code and returns. 

// Note that a detached thread can not be joined ever again.

#include <iostream>
#include <thread>

void threadFunction()
{
    std::this_thread::sleep_for( std::chrono::microseconds(50) ); // simulate work
    std::cout << "Finish work in thread\n";
}

int main()
{
    // create thread
    std::thread t(threadFunction);

    // detach thread and continue with main
    t.detach();

    // do something in main()
    std::this_thread::sleep_for( std::chrono::milliseconds(50) ); // simulate work
    std::cout << "Finished work in main\n";

    return 0;
}

// Programmers should be very careful though when using the detach()-method. 
// You have to make sure that the thread does not access any data that might get out of scope or be deleted. 
// Also, we do not want our program to terminate with threads still running. Should this happen, 
// such threads will be terminated very harshly without giving them the chance to properly clean up their resources - what would usually happen in the destructor. 
// So a well-designed program usually has a well-designed mechanism for joining all threads before exiting.