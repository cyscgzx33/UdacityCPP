/**
 * [Description]
 * Using mutexes can significantly reduce the risk of data races as seen in the example above. 
 * But imagine what would happen if an exception was thrown while executing code in the 
 * critical section, i.e. between lock and unlock. In such a case, the mutex would remain 
 * locked indefinitely and no other thread could unlock it - the program would most likely freeze.
 * */

#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <algorithm>

double result;

void printResult(int denom)
{
    std::cout << "for denom = " << denom << ", the result is " << result << std::endl;
}

void divideByNumber(double num, double denom)
{
    try
    {
        // devide num by denom but throw an exception if division by zero is attempted
        if (denom != 0)
        {
            result = num / denom;
            std::this_thread::sleep_for( std::chrono::milliseconds(1) );
            printResult(denom);
        }
        else
        {
            throw std::invalid_argument("Execption from thread: Division by zero!");
        }
    }
    catch(const std::invalid_argument& e)
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
    for (double i = -5; i <= +5; i++)
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
 * [Output]
 * 
 * Execption from thread: Division by zero!
 * for denom = -5, the result is 10
 * for denom = -4, the result is for denom = -3, the result is 10
 * for denom = -2, the result is for denom = -1, the result is 10
 * 10
 * for denom = 1, the result is 10
 * for denom = 2, the result is 10
 * for denom = 3, the result is 10
 * for denom = 4, the result is 10
 * 10
 * for denom = 5, the result is 10 
 * 
 * [Explain]
 * As can easily be seen, the console output is totally mixed up and some results appear multiple times. 
 * There are several issues with this program, so let us look at them in turn:
 *   1. The thread function writes its result to a global variable which is passed to it by reference. 
 *      This will cause a data race as illustrated in the last section. The sleep_for function exposes the data race clearly.
 *   2. The result is printed to the console by several threads at the same time, causing the chaotic output.
 */