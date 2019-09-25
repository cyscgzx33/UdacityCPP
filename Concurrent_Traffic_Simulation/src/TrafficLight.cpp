#include <iostream>
#include <random>
#include <queue>
#include <future>

#include "TrafficLight.h"

/* Implementation of class "MessageQueue" */


template <typename T>
T MessageQueue<T>::receive()
{
    // FP.5a : The method receive should use std::unique_lock<std::mutex> and _condition.wait() 
    // to wait for and receive new messages and pull them from the queue using move semantics. 
    // The received object should then be returned by the receive function.
    std::unique_lock<std::mutex> u_lock(mutex_);
    cond_.wait( u_lock, [this] { return !queue_.empty(); } );

    T msg = std::move( queue.back() );
    queue_.pop_back();
    return msg;
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    // FP.4a : The method send should use the mechanisms std::lock_guard<std::mutex> 
    // as well as _condition.notify_one() to add a new message to the queue and afterwards send a notification.
    std::lock_guard<std::mutex> u_lock(mutex_);

    queue_.push_back( std::move(msg) );
    cond_.notify_one();
}


/* Implementation of class "TrafficLight" */


TrafficLight::TrafficLight()
{
    current_phase_ = TrafficLightPhase::kRed;
}

void TrafficLight::waitForGreen()
{
    // FP.5b : add the implementation of the method waitForGreen, in which an infinite while-loop 
    // runs and repeatedly calls the receive function on the message queue. 
    // Once it receives TrafficLightPhase::green, the method returns.
    while (1)
    {
        std::this_thread::sleep_for( std::chrono::milliseconds(1) );

        auto cur_phase = msg_queue_->receive();
        if (cur_phase == TrafficLightPhase::kGreen)
            return;
    }
}

TrafficLightPhase TrafficLight::getCurrentPhase() const
{
    return current_phase_;
}

void TrafficLight::setCurrentPhase(const TrafficLightPhase color)
{
    current_phase_ = color;
}

void TrafficLight::simulate()
{
    // FP.2b : Finally, the private method „cycleThroughPhases“ should be started in a thread when the public method „simulate“ is called. To do this, use the thread queue in the base class. 
    threads_.emplace_back( std::thread(&TrafficLight::cycleThroughPhases, this) );
}

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases()
{
    // FP.2a : Implement the function with an infinite loop that measures the time between two loop cycles 
    // and toggles the current phase of the traffic light between red and green and sends an update method 
    // to the message queue using move semantics. The cycle duration should be a random value between 4 and 6 seconds. 
    // Also, the while-loop should use std::this_thread::sleep_for to wait 1ms between two cycles. 
    std::random_device rd;
    std::mt19937 eng( rd() );
    std::uniform_int_distribution<> distribution(4, 6);

    std::unique_lock<std::mutex> lock(mtx_);
    std::cout << "Traffic Light #" << id_ << ": thread id = " << std::this_thread::get_id() << '\n';
    lock.unlock();

    // Init variables
    // randomly choose a single simulation cycle in seconds
    int cycle_duration = distribution(eng);

    auto last_update = std::chrono::system_clock::now();
    while (1)
    {
        // Time elapsed from last stop
        long time_elapsed = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - last_update).count();
        
        // Sleep every iter to reduce CPU load
        std::this_thread::sleep_for( std::chrono::milliseconds(1) );

        // Toggle traffic light phase
        if ( time_elapsed >= cycle_duration )
        {
            if (current_phase_ == TrafficLightPhase::kRed)
                current_phase_ = TrafficLightPhase::kGreen;
            else
                current_phase_ = TrafficLightPhase::kRed;
        }

        // Send update to the message queue and wait
        auto msg = current_phase_;
        auto is_sent = std::async( std::launch::async, &MessageQueue<TrafficLightPhase>::send, msg_queue_, std::move(msg) );
        is_sent.wait();

        // Reset stop watch for next cycle
        last_update = std::chrono::system_clock::now();

        // Randomly choose the cycle duration for the next cycle
        cycle_duration = distribution(eng);
    }
}