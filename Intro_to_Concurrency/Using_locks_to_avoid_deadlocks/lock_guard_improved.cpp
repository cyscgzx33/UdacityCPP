/**
 * [Description]
 * 
 * It's an improved version compared to lock_guard.cpp:
 * it limits the scope of the mutex to the section which accesses the critical resource,
 * such that the mutex is only locked for the time when result is modified and the result is printed.
 * i.e., the "std::lock_guard<std::mutex> lck(mtx)" will ONLY be called when i != 0.
 * */


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
    try
    {
        // divide num by denom but throw an exception if division by zero is attempted
        if (denom != 0)
        {
            std::lock_guard<std::mutex> lck(mtx);
            result = num / denom;
            std::this_thread::sleep_for( std::chrono::milliseconds(10) );
            printResult(denom);
        }
        else
        {
            throw std::invalid_argument("Exeception from thread: Division by zero!");
        }
    }
    catch (const std::invalid_argument& e)
    {
        // notify the user about the exeception and return
        std::cout << e.what() << std::endl;
        return;
    }
}

int main()
{
    // create a number of threads which execute the function "divideByNumber" with varying parameters
    std::vector<std::future<void>> futures;
    for (double i = -5; i <= +5; i++)
    {
        futures.emplace_back( std::async(std::launch::async, divideByNumber, 50.0, i) );
    }

    // wait for the results
    std::for_each(futures.begin(), futures.end(), [](std::future<void>& ftr) {
        ftr.wait();
    });

    return 0;
}

/**
 * [Output]
 * 
 * for denom = -5, the result is -10
 * for denom = -4, the result is -12.5
 * for denom = -2, the result is -25
 * for denom = -3, the result is -16.6667
 * for denom = -1, the result is -50
 * Exeception from thread: Division by zero!
 * for denom = 1, the result is 10
 * for denom = 2, the result is 12.5
 * for denom = 3, the result is 16.6667
 * for denom = 4, the result is 25
 * for denom = 5, the result is 50
 * 
 * */