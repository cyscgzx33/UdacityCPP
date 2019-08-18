/* [Description]
 * 
 * Using threads follows a basic concept called "fork-join-parallelism". 
 * The basic mechanism of this concept follows a simple three-step pattern:
 * 1. Split the flow of execution into a parallel thread ("fork")
 * 2. Perform some work in both the main thread and the parallel thread
 * 3. Wait for the parallel thread to finish and unite the split flow of execution again ("join")
 * 
 * The diagram in the README.md illustrates the basic idea of forking (TODO: add that diagram into the README.md)
 * 
 * 
 * In the main thread, the program flow is forked into three parallel branches. 
 * In both worker branches, some work is performed - which is why threads are often referred to as "worker threads". 
 * Once the work is completed, the flow of execution is united again in the main function using the join() command. 
 * In this example, join acts as a barrier where all threads are united. 
 * The execution of main is in fact halted, until both worker threads have successfully completed their respective work.
 * 
 *              ---- fork
 *            /       |    
 *      some work    fork ------
 *          |         |          \
 *          |     some work    some work 
 *          |         |           |
 *           \        |          /
 *            \       |         / 
 *             \      |        /
 *              \     |       /
 *               --  join  ---
 *                    | 
 *                  return  
 * */

#include <iostream>
#include <thread>
#include <vector>

void printHello() {
    // perform
    std::cout << "Hello from Worker thread #" << std::this_thread::get_id() << std::endl;
}

int main() {
    // create threads
    std::vector<std::thread> threads;
    for (size_t i = 0; i < 5; i++) {
        // copying thread objects will cause a compiler error
        /*
        std::thread t(printHello);
        threads.push_back(t);
        */

       // moving thread objects will work
       threads.emplace_back( std::thread(printHello) );
    }

    // do something in main()
    std::cout << "Hello from Main thread #" << std::this_thread::get_id() << std::endl;

    // call join on all thread objects using a range-based loop
    for (auto& t : threads)
        t.join();

    return 0;
}

/* [Output]
 * 
 * Hello from Worker thread #Hello from Worker thread #139742146299648139742129514240
 * Hello from Main thread #139742163887936
 * Hello from Worker thread #139742137906944
 * \n
 * Hello from Worker thread #139742121121536
 * Hello from Worker thread #139742112728832
 * 
 * [Explain]
 * 1. The order in which threads are executed is non-deterministic. Every time a program is executed, 
 *    there is a chance for a completely different order of execution.
 * 2. Threads may get preempted in the middle of execution and another thread may be selected to run.
 * 
 * Thus, these two properties pose a major problem with concurrent applications: A program may run correctly for 
 * thousands of times and suddenly, due to a particular interleaving of threads, there might be a problem. 
 * From a debugging perspective, such errors are very hard to detect as they can not be reproduced easily.
 * */