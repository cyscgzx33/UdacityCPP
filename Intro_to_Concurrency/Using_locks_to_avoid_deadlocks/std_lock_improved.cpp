/**
 * [Description]
 * 
 * In the following deadlock-free code, std::lock is used to ensure that the mutexes are always 
 * locked in the same order, regardless of the order of the arguments. 
 * Note that std::adopt_lock option allows us to use std::lock_guard on an already locked mutex.
 * 
 * As a rule of thumb, programmers should try to avoid using several mutexes at once. 
 * Practice shows that this can be achieved in the majority of cases. 
 * For the remaining cases though, using std::lock is a safe way to avoid a deadlock situation.
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