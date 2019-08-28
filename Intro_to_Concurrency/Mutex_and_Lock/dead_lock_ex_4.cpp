/**
 * [Description]
 * A solved dead lock version of ex-3
 * 
 * */

#include <iostream>
#include <thread>
#include <mutex>

std::mutex mutex_1, mutex_2, mutex_3;

void ThreadA()
{
    // Creates deadlock problem
    mutex_1.lock();
    std::cout << "Thread A" << std::endl;
    mutex_2.lock();
    mutex_2.unlock();
    mutex_1.unlock();
}

void ThreadB()
{
    // Creates deadlock problem
    mutex_1.lock();
    std::cout << "Thread B" << std::endl;
    mutex_2.lock();
    mutex_1.unlock();
    mutex_2.unlock();
}

void ExecuteThreads()
{
    std::thread t1( ThreadA );
    std::thread t2( ThreadB );

    t1.join();
    t2.join();

    std::cout << "Finished" << std::endl;
}

int main()
{
    ExecuteThreads();

    return 0;
}

/**
 * [Output]
 * */