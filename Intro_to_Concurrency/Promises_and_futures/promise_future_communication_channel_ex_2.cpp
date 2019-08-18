/* [Description]
 *
 * In the following example:
 * we want to declare a promise which allows for transmitting a string 
 * between two threads and modifying it in the process.
 */

#include <iostream>
#include <thread>
#include <future>

void modifyMessage(std::promise<std::string>&& promises, std::string message) {
    std::this_thread::sleep_for( std::chrono::milliseconds(4000) ); // simulate work
    std::string modifiedMessage = message + " has been modified";
    promises.set_value(modifiedMessage);
}

int main() {
    // define message
    std::string messageToThread = "My Message";

    // create promise and future
    std::promise<std::string> prms;
    std::future<std::string> ftr = prms.get_future();

    // start thread and pass promise as argument
    std::thread t(modifyMessage, std::move(prms), messageToThread);

    // print original message to console
    std::cout << "Original message from main(): " << messageToThread << std::endl;

    // retrieve modified message via future and print to console
    std::string messageFromThread = ftr.get();   // If the result is movable (which is the case for std::string), it will be moved; 
                                                 // otherwise it will be copied instead.
    std::cout << "Modified message from thread(): " << messageFromThread << std::endl;

    // thread barrier
    t.join();

    return 0;
}

/* [Output]
 * Original message from main(): My Message
 * Modified message from thread(): My Message has been modified
 * 
 * [Explain]
 * Back in the main thread, after starting the thread, the original message is printed to the console. 
 * Then, we start listening on the other end of the communication channel by calling the function get() on the future. 
 * This method will block until data is available - which happens as soon as set_value has been called on the promise (from the thread). 
 * If the result is movable (which is the case for std::string), it will be moved - otherwise it will be copied instead. 
 * After the data has been received (with a considerable delay), the modified message is printed to the console.
 */