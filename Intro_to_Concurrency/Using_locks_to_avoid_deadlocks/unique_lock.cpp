/**
 * [Description]
 * In this version of the code, std::lock_guard has been replaced with std::unique_lock. As before, the lock object lck will unlock 
 * the mutex in its destructor, i.e. when the function divideByNumber returns and lck gets out of scope. In addition to this automatic unlocking, 
 * std::unique_lock offers the additional flexibility to engage and disengage the lock as needed by manually calling the methods lock() and unlock(). 
 * This ability can greatly improve the performance of a concurrent program, especially when many threads are waiting for access to a locked resource. 
 * In the example, the lock is released before some non-critical work is performed (simulated by sleep_for) and re-engaged before some other work 
 * is performed in the critical section and thus under the lock again at the end of the function. 
 * This is particularly useful for optimizing performance and responsiveness when a significant amount of time passes between two accesses to a critical resource.
 * 
 * The main advantages of using std::unique_lock<> over std::lock_guard are briefly summarized in the following. 
 *
 * Using std::unique_lock allows you to...
 * ...construct an instance without an associated mutex using the default constructor
 * ...construct an instance with an associated mutex while leaving the mutex unlocked at first using the deferred-locking constructor
 * ...construct an instance that tries to lock a mutex, but leaves it unlocked if the lock failed using the try-lock constructor
 * ...construct an instance that tries to acquire a lock for either a specified time period or until a specified point in time
 */

#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <mutex>
#include <algorithm>

std::mutex mtx;
double result;

void printResult(int denom)
{
    std::cout << "for denom = " << denom << ", the result is " << result << std::endl; 
}

void divideByNumber(double num, double denom)
{
    std::unique_lock<std::mutex> lck(mtx);
    try
    {
        // divide num ber denom but throw an exception if division by zero is attempted
        if (denom != 0)
        {
            result = num / denom;
            std::this_thread::sleep_for( std::chrono::milliseconds(100) );
            printResult(denom);
            lck.unlock();

            // do something outside of the lock
            std::this_thread::sleep_for( std::chrono::milliseconds(100) );

            lck.lock();
            // do something else under the lock
            std::this_thread::sleep_for( std::chrono::milliseconds(100) );
        }
        else 
        {
            throw std::invalid_argument("Exception from thread: Division by zero!");
        }
    }
    catch (const std::invalid_argument& e)
    {
        // notify the user about the exception and return
        std::cout << e.what() << std::endl;
        return;
    }
}

int main()
{
    // create a number of threads which execute the function "divideByNumber" with varying parameters
    std::vector<std::future<void>> futures;
    for (double i = -5; i <= +5; ++i)
    {
        futures.emplace_back( std::async(std::launch::async, divideByNumber, 50.0, i) );
    }

    // wait for the results
    std::for_each( futures.begin(), futures.end(), [](std::future<void>& ftr) {
        ftr.wait();
    } );

    return 0;
}

/**
 * [Output] (pops out slowly, as there's a sleep of 100 ms)
 * 
 * for denom = -5, the result is -10
 * for denom = -4, the result is -12.5
 * for denom = -3, the result is -16.6667
 * for denom = -2, the result is -25
 * for denom = -1, the result is -50
 * Exception from thread: Division by zero!
 * for denom = 1, the result is 50
 * for denom = 2, the result is 25
 * for denom = 3, the result is 16.6667
 * for denom = 4, the result is 12.5
 * for denom = 5, the result is 10
 *
 * */