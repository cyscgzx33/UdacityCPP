/**
 * [Description]
 * 
 * In most cases, your code should only hold one lock on a mutex at a time. Occasionally you can nest your locks, 
 * for example by calling a subsystem that protects its internal data with a mutex while holding a lock on another mutex, but it is generally better to avoid locks on multiple mutexes at the same time, if possible. Sometimes, however, 
 * it is necessary to hold a lock on more than one mutex because you need to perform an operation on two different data elements, each protected by its own mutex.
 * In the unique_lock.cpp, we have seen that using several mutexes at once can lead to a deadlock, if the order of locking them is not carefully managed. 
 * To avoid this problem, the system must be told that both mutexes should be locked at the same time, so that one of the threads takes over both 
 * locks and blocking is avoided. That's what the std::lock() function is for - you provide a set of lock_guard or unique_lock objects and 
 * the system ensures that they are all locked when the function returns.
 * 
 */

#include <iostream>
#include <thread>
#include <mutex>

std::mutex mutex_1, mutex_2;

void ThreadA()
{
	// Ensures that locks are always executed in the same order
	std::lock(mutex_1, mutex_2);
	std::lock_guard<std::mutex> lock_2(mutex_2, std::adopt_lock);
	std::cout << "Thread A" << std::endl;
	std::lock_guard<std::mutex> lock_1(mutex_1, std::adopt_lock);
}

void ThreadB()
{
	std::lock_guard<std::mutex> lock_1(mutex_1, std::adopt_lock);
	std::cout << "Thread B" << std::endl;
	std::lock_guard<std::mutex> lock_2(mutex_2, std::adopt_lock);
}

void ExcuteThreads()
{
	std::thread t_1( ThreadA );
	std::thread t_2( ThreadB );

	t_1.join();
	t_2.join();

	std::cout << "Finished" << std::endl;
}

int main()
{
	ExcuteThreads();

	return 0;
}

/**
 * [Output]
 *
 * Thread A
 * Thread B
 * Finished
 */