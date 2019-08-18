/* [Description]
 * 
 * There are some situations where it might be interesting to separate the waiting for the content from the actual retrieving. 
 * Futures allow us to do that using the wait() function. This method will block until the future is ready. 
 * Once it returns, it is guaranteed that data is available and we can use get() to retrieve it without delay.
 * 
 * In addition to wait, the C++ standard also offers the method wait_for, 
 * which takes a time duration as an input and also waits for a result to become available. 
 * The method wait_for() will block either until the specified timeout duration has elapsed or 
 * the result becomes available - whichever comes first. 
 * The return value identifies the state of the result.
 * 
 * In the following example, we use the wait_for method to wait for the availability of a result for one second. 
 * After the time has passed (or the result is available) print the result to the console. 
 * Should the time be up without the result being available, print an error message to the console instead.
 */

#include <iostream>
#include <thread>
#include <future>
#include <cmath>

void computeSqrt(std::promise<double>&& promises, double input) {
    std::this_thread::sleep_for( std::chrono::milliseconds(2000) );
    double output = sqrt(input);
    promises.set_value(output);
}

int main() {
    // define input data
    double input_data = 42.0;

    // create promise and future
    std::promise<double> prms;
    std::future<double> ftr = prms.get_future();

    // start thread and pass promise as argument
    std::thread t(computeSqrt, std::move(prms), input_data);

    // wait for result to become available
    auto status = ftr.wait_for( std::chrono::milliseconds(1000) ); // if < 2000, unavailable; > 2000, good to show.
    if (status == std::future_status::ready) { // result is ready
        std::cout << "Result = " << ftr.get() << std::endl;
    }
    else if (status == std::future_status::timeout || status == std::future_status::deferred) {
        std::cout << "Result unavailable" << std::endl;
    } 

    // thread barrier
    t.join();

    return 0;
}

/* [Output]
 *
 * Result unavailable
 * 
 * [Explain]
 * 
 * Bevause we only wait_for 1000 ms, in the computeSqrt() the sleep time is 2000;
 * Thus, if we set wait_for time larger than 2000, as an example, 3000, it will show the result. 
 *
 */