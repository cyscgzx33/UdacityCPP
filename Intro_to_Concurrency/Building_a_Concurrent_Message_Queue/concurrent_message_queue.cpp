#include <iostream>
#include <thread>
#include <queue>
#include <future>
#include <mutex>
#include <algorithm>

template <class T>
class MessageQueue
{
  public:
    T receive()
    {
        // perform queue modification under the lock
        std::unique_lock<std::mutex> u_lock(mutex_);

        // pass unique lock to condition variable
        cond_.wait( u_lock, [this] { return !messages_.empty(); } ); 

        // remove last vector element from queue
        T msg = std::move( messages_.back() );
        messages_.pop_back();

        return msg; // will not be copied due to return value optimization (RVO) in C++
    }

    void send(T&& msg)
    {
        // simulate some work
        std::this_thread::sleep_for( std::chrono::milliseconds(100) );

        // perform vector modification under the lock
        std::lock_guard<std::mutex> u_lock(mutex_);

        // add vector to queue
        std::cout << "  Message " << msg << " has been sent to the queue" << std::endl;
        messages_.push_back( std::move(msg) );
    }

  private:
    std::mutex mutex_;
    std::condition_variable cond_;
    std::deque<T> messages_;
};

int main()
{
    // create monitor object as a shared pointer to enable access by multiple threads
    std::shared_ptr<MessageQueue<int>> queue( new MessageQueue<int> );

    std::cout << "Spawning threads..." << std::endl;
    std::vector<std::future<void>> futures;
    for (int i = 0; i < 10; i++)
    {
        int message = i;
        futures.emplace_back( std::async( std::launch::async, &MessageQueue<int>::send, queue, std::move(message) ) );
    }

    std::cout << "Collecting results..." << std::endl;
    while (true)
    {
        int message = queue->receive();
        std::cout << "  Message #" << message << " has been removed from the queue" << std::endl;
    }

    std::for_each( futures.begin(), futures.end(), [](std::future<void>& ftr) { ftr.wait(); } );

    std::cout << "Finished!" << std::endl;

    return 0;
}