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