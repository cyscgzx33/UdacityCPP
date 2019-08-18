/* [Description]
 *
 * In this section, we want to look at a way to pass data in the opposite direction - 
 * that is from the worker threads back to the parent thread.
 *
 * In order to achieve this, the threads need to adhere to a strict synchronization protocol. 
 * There is a such a mechanism available in the C++ standard that we can use for this purpose. 
 * This mechanism acts as a single-use channel between the threads. 
 * The sending end of the channel is called "promise" while the receiving end is called "future".
 * 
 * In the C++ standard, the class template std::promise provides a convenient way to store
 * a value or an exception that will acquired asynchronously at a later time via a std::future object. 
 * Each std::promise object is meant to be used only a single time.
 */

#include <iostream>
#include <thread>

void printMessage(std::string message) {
    std::this_thread::sleep_for( std::chrono::milliseconds(10) ); // simulate work
    std::cout << "Thread 1: " << message << std::endl;
}

int main() {
    // define message
    std::string message = "My Message";

    // start thread using variadic templates
    std::thread t1(printMessage, message);

    // start thread using a Lambda
    std::thread t2( [message] {
        std::this_thread::sleep_for( std::chrono::milliseconds(10) ); // simulink work
        std::cout << "Thread 2: " << message << std::endl;
    });

    // thread barrier
    t1.join();
    t2.join();

    return 0;
}