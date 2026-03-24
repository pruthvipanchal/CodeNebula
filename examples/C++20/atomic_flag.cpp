// CodeNebula - C++20 Example: std::atomic_flag Enhancements (test, wait/notify)
// Compile: g++ -std=c++20 -Wall -Wextra -pthread -o example atomic_flag.cpp

#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

int main() {
    std::cout << "=== std::atomic_flag C++20 enhancements ===\n\n";

    // C++20: atomic_flag is default-initialized to clear state
    std::atomic_flag flag;

    // C++20 addition: test() - read the flag without modifying it
    std::cout << "--- test() (non-modifying read) ---\n";
    std::cout << "Initial state: " << flag.test() << " (0 = clear)\n";

    flag.test_and_set();
    std::cout << "After test_and_set(): " << flag.test() << " (1 = set)\n";

    flag.clear();
    std::cout << "After clear(): " << flag.test() << " (0 = clear)\n";

    std::cout << "\n=== atomic_flag::wait/notify ===\n";
    std::cout << "(Efficient blocking until flag changes)\n\n";

    // Spinlock using atomic_flag
    std::cout << "--- Spinlock example ---\n";
    std::atomic_flag lock = ATOMIC_FLAG_INIT;
    int shared_data = 0;

    auto critical_section = [&](int id) {
        for (int i = 0; i < 1000; ++i) {
            while (lock.test_and_set(std::memory_order_acquire)) {
                // Spin (in real code, use wait() for efficiency)
            }
            ++shared_data;  // Protected by spinlock
            lock.clear(std::memory_order_release);
        }
        std::cout << "Thread " << id << " done\n";
    };

    {
        std::jthread t1(critical_section, 1);
        std::jthread t2(critical_section, 2);
    }
    std::cout << "Shared data: " << shared_data << " (expected 2000)\n";

    std::cout << "\n--- wait/notify signaling ---\n";

    std::atomic_flag ready;
    ready.clear();

    std::jthread producer([&ready] {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        std::cout << "Producer: data is ready\n";
        ready.test_and_set();
        ready.notify_one();  // Wake up one waiting thread
    });

    std::jthread consumer([&ready] {
        std::cout << "Consumer: waiting for data...\n";
        ready.wait(false);  // Block until flag != false (i.e., until set)
        std::cout << "Consumer: got the signal, processing!\n";
    });

    producer.join();
    consumer.join();

    std::cout << "\n--- notify_all example ---\n";

    std::atomic_flag start_signal;
    start_signal.clear();

    auto racer = [&start_signal](int id) {
        start_signal.wait(false);  // Wait until flag is set
        std::cout << "Racer " << id << " started!\n";
    };

    std::vector<std::jthread> racers;
    for (int i = 0; i < 4; ++i) {
        racers.emplace_back(racer, i);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(30));
    std::cout << "GO!\n";
    start_signal.test_and_set();
    start_signal.notify_all();  // Wake ALL waiting threads

    for (auto& r : racers) r.join();

    std::cout << "\n=== Properties ===\n";
    std::cout << "is_always_lock_free: " << std::atomic_flag::is_always_lock_free << "\n";

    return 0;
}
