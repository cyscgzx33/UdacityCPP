#include <iostream>
#include <thread>
#include <string>

void printName(std::string name, int wait_time) {
    std::this_thread::sleep_for( std::chrono::milliseconds(wait_time) );
    std::cout << "Name (from Thread) = " << name << std::endl;
}

int main() {
    std::string name_1 = "MyThread1";
    std::string name_2 = "MyThread2";

    // starting threads using value-copy and move semantics
    std::thread t1(printName, name_1, 50);
    std::thread t2(printName, std::move(name_2), 100); // 

    // wait for threads before returning
    t1.join();
    t2.join();

    // print name from main
    std::cout << "Name (from Main) = " << name_1 << std::endl;
    std::cout << "Name (from Main) = " << name_2 << std::endl;

    return 0;
}

/* [Output]
 * 
 * Name (from Thread) = MyThread1
 * Name (from Thread) = MyThread2
 * Name (from Main) = MyThread1
 * Name (from Main) = 
 * 
 * [Explain]
 * With t1, the string name1 is copied by value, which allows us to print name1 even after join has been called. 
 * The second string name2 is passed to the thread function using move semantics, 
 * which means that it is not available any more after join has been called on t2
 * The console output shows how using copy-by-value and 
 * std::move affect the string parameters:
 */
