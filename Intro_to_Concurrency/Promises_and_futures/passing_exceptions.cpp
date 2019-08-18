/* [Description]
 * 
 * he future-promise communication channel may also be used for passing exceptions. 
 * To do this, the worker thread simply sets an exception rather than a value in the promise. 
 * In the parent thread, the exception is then re-thrown once get() is called on the future.
 * Let us take a look at the following example to see how this mechanism works:
 *
 * */

#include <iostream>
#include <thread>
#include <future>
#include <cmath>
#include <memory>

void divideByNumber(std::promise<double>&& promise, double num, double denom)
{
    std::this_thread::sleep_for( std::chrono::microseconds(500) ); // simulate work
    try
    {
        if (denom == 0)
            throw std::runtime_error("Exception from thread: Division by zero!");
        else
            promise.set_value(num / denom);
    }
    catch (...)
    {
        promise.set_exception( std::current_exception() );
    }
}

int main()
{
    // create promise and future
    std::promise<double> prms;
    std::future<double> ftr = prms.get_future();

    // start thread and pass promise as argument
    double num = 42.0, denom = 0.0;
    std::thread t(divideByNumber, std::move(prms), num, denom);

    // retrieve result within try-catch-block
    try
    {
        double result = ftr.get();
        std::cout << "Result = " << result << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    // thread barrier
    t.join();
    
    return 0;
}

/* [Output]
 * 
 * Exception from thread: Division by zero!
 * 
 * */