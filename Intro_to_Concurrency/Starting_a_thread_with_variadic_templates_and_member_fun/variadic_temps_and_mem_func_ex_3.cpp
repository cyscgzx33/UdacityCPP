/* [Description]
 * In this example, the signature of the thread function is modified to 
 * take a non-const reference to the string instead.
 * When passing the string variable name to the thread function, 
 * we need to explicitly mark it as a reference, 
 * so the compiler will treat it as such. This can be done by using the std::ref function. 
 * In the console output it becomes clear that the string has been successfully 
 * modified within the thread function before being passed to main.
 * 
 * Even though the code works, we are now sharing mutable data between threads - 
 * which will be something we discuss in later sections of this course as a primary source for 
 * concurrency bugs.
 */

#include <iostream>
#include <thread>
#include <string>

void printName(std::string& name, int wait_time) { // non-const reference, as a potential of a primary source for concurrency bugs
    std::this_thread::sleep_for( std::chrono::microseconds(wait_time) );
    name += " (from Thread)";
    std::cout << name << std::endl;
}

int main() {
    std::string name("MyThread");

    // starting thread
    std::thread t(printName, std::ref(name), 50);

    // wait for thread before returning
    t.join();

    // print name from main
    name += " (from Main)";
    std::cout << name << std::endl;

    return 0;
}

/* [Output]
 * 
 * MyThread (from Thread)
 * MyThread (from Thread) (from Main)
 * 
 * [Explain]
 * The console output shows how using copy-by-value and 
 * std::move affect the string parameters:
 */