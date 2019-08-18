#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <vector>

int main() {
    // create threads
    std::vector<std::thread> threads;
    for (size_t i = 0; i < 10; i++) {
        // create new thread from a lambda
        threads.emplace_back( [i]() { // HERE IS THE BUG COMES FROM!
                                       // Instead of PASS BY REFERENCE <==> [&i]()
                                       // we should use PASS BY VALUE  <==>  [i]()
            // wait for certain amount of time
            std::this_thread::sleep_for( std::chrono::milliseconds(10 * i) );
            // perform work
            std::cout << "Hello from Worker thread #" << i << std::endl;
        } );
    }

    // do something in main()
    std::cout << "Hello from Main thread" << std::endl;

    // call join on all thread objects using a range-based loop
    for (auto& t : threads)
        t.join();

    return 0;
}