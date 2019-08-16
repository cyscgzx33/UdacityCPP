#include <iostream>
#include <thread>

int main() {
    int id = 0; // Define an integer variable

    // starting a first thread (by reference)
    auto f0 = [&id]() {
        std::this_thread::sleep_for( std::chrono::milliseconds(100) );
        std::cout << "a) ID in Thread (call-by-reference) = " << id << std::endl;
    };
    std::thread t1(f0);

    // starting a second thread (by value)
    std::thread t2( [id]() mutable {
        std::this_thread::sleep_for( std::chrono::milliseconds(50) );
        std::cout << "b) ID in thread (call-by-value) = " << id << std::endl;
    } );

    // increment and print id in main
    ++id;
    std::cout << "c) ID in Main (call-by-value) = " << id << std::endl;

    // wait for threads before returning
    t1.join();
    t2.join();

    return 0;
}

/*  
 * [Output]
 *   c) ID in Main (call-by-value) = 1
 *   b) ID in thread (call-by-value) = 0
 *   a) ID in Thread (call-by-reference) = 1
 * 
 * [Explain]
 *   As you can see, the output in the main thread is generated first, 
 *   at which point the variable ID has taken the value 1. 
 *   Then, the call-by-value thread is executed with ID at a value of 0. 
 *   Then, the call-by-reference thread is executed with ID at a value of 1. 
 *   This illustrates the effect of passing a value by reference: 
 *   when the data to which the reference refers changes before the thread is executed, 
 *   those changes will be visible to the thread. 
 *   We will see other examples of such behavior later in the course, 
 *   as this is a primary source of concurrency bugs.
*/