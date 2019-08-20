/* [Description]
 *
 * In this section, we want to explore the influence of the number of threads on the performance of a program 
 * with respect to its overall runtime. The example below has a thread function called "workerThread" 
 * which contains a loop with an adjustable number of cycles in which a mathematical operation is performed.
 * 
 * 
 *
 */

#include <iostream>
#include <thread>
#include <future>
#include <cmath>
#include <vector>
#include <chrono>

void workerFunction(int n)
{
    // print system id of worker thread
    std::cout << "Worker thread id = " << std::this_thread::get_id() << std::endl;

    // perform work
    for (int i = 0; i < n; i++)
        sqrt(12345.6789);
}

int main()
{
    // print system id of worker thread
    std::cout << "Main thread id = " << std::this_thread::get_id() << std::endl;

    // start time measurement
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    // launch various tasks
    std::vector<std::future<void>> futures;
    int n_loops = 10, n_threads = 5;

    for (int i = 0; i < n_threads; i++)
        futures.emplace_back( std::async(std::launch::async, workerFunction, n_loops) );
    
    // wait for tasks to complete
    for (const std::future<void>& ftr : futures)
        ftr.wait();
    
    // stop time measurement and print execution time
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds> (t2 - t1).count();
    std::cout << "Execution finished after " << duration << " microseconds" << std::endl;

    return 0;
}