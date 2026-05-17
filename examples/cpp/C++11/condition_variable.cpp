// CodeNebula - C++11 Example: std::condition_variable
// Compile: g++ -std=c++11 -Wall -Wextra -pthread -o example condition_variable.cpp
//
// This example demonstrates:
// - std::condition_variable for thread synchronization
// - wait() with predicate to avoid spurious wakeups
// - notify_one() and notify_all()
// - Producer-consumer pattern
// - Simple event signaling between threads

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <string>
#include <vector>
#include <chrono>

// ============================================================
// 1. Simple event signaling
// ============================================================
std::mutex eventMutex;
std::condition_variable eventCV;
bool eventReady = false;

void waitForEvent() {
    std::unique_lock<std::mutex> lock(eventMutex);
    std::cout << "  Waiter: waiting for event..." << std::endl;

    // wait() with predicate: only returns when predicate is true
    eventCV.wait(lock, [] { return eventReady; });

    std::cout << "  Waiter: event received!" << std::endl;
}

void signalEvent() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    {
        std::lock_guard<std::mutex> lock(eventMutex);
        eventReady = true;
        std::cout << "  Signaler: setting event" << std::endl;
    }
    eventCV.notify_one();  // Wake one waiting thread
}

// ============================================================
// 2. Producer-Consumer queue
// ============================================================
class MessageQueue {
    std::queue<std::string> queue_;
    std::mutex mutex_;
    std::condition_variable cv_;
    bool finished_ = false;

public:
    void produce(const std::string& msg) {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            queue_.push(msg);
            std::cout << "  Produced: " << msg << std::endl;
        }
        cv_.notify_one();
    }

    std::string consume() {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [this] { return !queue_.empty() || finished_; });

        if (queue_.empty()) return "";  // Finished, no more items

        std::string msg = queue_.front();
        queue_.pop();
        return msg;
    }

    void setFinished() {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            finished_ = true;
        }
        cv_.notify_all();  // Wake ALL waiting consumers
    }
};

// ============================================================
// 3. notify_all: barrier-like synchronization
// ============================================================
std::mutex barrierMutex;
std::condition_variable barrierCV;
bool startSignal = false;

void racerThread(int id) {
    {
        std::unique_lock<std::mutex> lock(barrierMutex);
        barrierCV.wait(lock, [] { return startSignal; });
    }
    std::cout << "  Racer " << id << " started!" << std::endl;
}

int main() {
    std::cout << "=== std::condition_variable ===" << std::endl;

    // Simple event
    std::cout << "\n--- Simple event signaling ---" << std::endl;
    std::thread waiter(waitForEvent);
    std::thread signaler(signalEvent);
    waiter.join();
    signaler.join();

    // Producer-Consumer
    std::cout << "\n--- Producer-Consumer ---" << std::endl;
    MessageQueue mq;

    std::thread producer([&mq]() {
        mq.produce("Message A");
        mq.produce("Message B");
        mq.produce("Message C");
        mq.setFinished();
    });

    std::thread consumer([&mq]() {
        while (true) {
            std::string msg = mq.consume();
            if (msg.empty()) break;
            std::cout << "  Consumed: " << msg << std::endl;
        }
        std::cout << "  Consumer: done" << std::endl;
    });

    producer.join();
    consumer.join();

    // notify_all barrier
    std::cout << "\n--- notify_all (start gate) ---" << std::endl;
    std::vector<std::thread> racers;
    for (int i = 0; i < 3; ++i) {
        racers.emplace_back(racerThread, i);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "  GO!" << std::endl;
    {
        std::lock_guard<std::mutex> lock(barrierMutex);
        startSignal = true;
    }
    barrierCV.notify_all();  // Release all racers

    for (auto& t : racers) t.join();

    return 0;
}

// Expected output (thread ordering may vary):
// === std::condition_variable ===
//
// --- Simple event signaling ---
//   Waiter: waiting for event...
//   Signaler: setting event
//   Waiter: event received!
//
// --- Producer-Consumer ---
//   Produced: Message A
//   Produced: Message B
//   Produced: Message C
//   Consumed: Message A
//   Consumed: Message B
//   Consumed: Message C
//   Consumer: done
//
// --- notify_all (start gate) ---
//   GO!
//   Racer 0 started!
//   Racer 1 started!
//   Racer 2 started!
