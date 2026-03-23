// CodeNebula - C++11 Example: std::thread
// Compile: g++ -std=c++11 -Wall -Wextra -pthread -o example thread.cpp
//
// This example demonstrates:
// - Creating threads with free functions, lambdas, and member functions
// - join() to wait for thread completion
// - detach() to run threads independently
// - Passing arguments to threads
// - std::this_thread utilities (get_id, sleep_for)

#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <mutex>
#include <vector>

std::mutex printMutex;

// ============================================================
// 1. Thread from a free function
// ============================================================
void printMessage(const std::string& msg, int count) {
    for (int i = 0; i < count; ++i) {
        std::lock_guard<std::mutex> lock(printMutex);
        std::cout << "  [" << std::this_thread::get_id() << "] "
                  << msg << " #" << (i + 1) << std::endl;
    }
}

// ============================================================
// 2. Thread from a member function
// ============================================================
class Worker {
    std::string name_;
public:
    Worker(const std::string& name) : name_(name) {}

    void doWork(int iterations) {
        for (int i = 0; i < iterations; ++i) {
            std::lock_guard<std::mutex> lock(printMutex);
            std::cout << "  " << name_ << " working: step " << (i + 1) << std::endl;
        }
    }
};

int main() {
    std::cout << "=== std::thread ===" << std::endl;
    std::cout << "  Main thread ID: " << std::this_thread::get_id() << std::endl;

    // Thread from free function
    std::cout << "\n--- Free function thread ---" << std::endl;
    std::thread t1(printMessage, "Hello", 3);
    t1.join();  // Wait for t1 to finish

    // Thread from lambda
    std::cout << "\n--- Lambda thread ---" << std::endl;
    int result = 0;
    std::thread t2([&result]() {
        std::lock_guard<std::mutex> lock(printMutex);
        std::cout << "  Lambda thread ID: " << std::this_thread::get_id() << std::endl;
        result = 42;
    });
    t2.join();
    std::cout << "  Result from lambda: " << result << std::endl;

    // Thread from member function
    std::cout << "\n--- Member function thread ---" << std::endl;
    Worker worker("Builder");
    std::thread t3(&Worker::doWork, &worker, 3);
    t3.join();

    // Multiple threads
    std::cout << "\n--- Multiple threads ---" << std::endl;
    std::vector<std::thread> threads;
    for (int i = 0; i < 4; ++i) {
        threads.emplace_back([i]() {
            std::lock_guard<std::mutex> lock(printMutex);
            std::cout << "  Thread " << i << " (ID: "
                      << std::this_thread::get_id() << ")" << std::endl;
        });
    }
    for (auto& t : threads) {
        t.join();
    }

    // Hardware concurrency
    std::cout << "\n--- Thread info ---" << std::endl;
    std::cout << "  Hardware concurrency: "
              << std::thread::hardware_concurrency() << std::endl;

    // Check joinable state
    std::cout << "\n--- Joinable state ---" << std::endl;
    std::thread t4([]() {});
    std::cout << "  Before join, joinable: " << t4.joinable() << std::endl;
    t4.join();
    std::cout << "  After join, joinable: " << t4.joinable() << std::endl;

    return 0;
}

// Expected output (thread IDs and order may vary):
// === std::thread ===
//   Main thread ID: 140234...
//
// --- Free function thread ---
//   [140234...] Hello #1
//   [140234...] Hello #2
//   [140234...] Hello #3
//
// --- Lambda thread ---
//   Lambda thread ID: 140234...
//   Result from lambda: 42
//
// --- Member function thread ---
//   Builder working: step 1
//   Builder working: step 2
//   Builder working: step 3
//
// --- Multiple threads ---
//   Thread 0 (ID: 140234...)
//   Thread 1 (ID: 140234...)
//   Thread 2 (ID: 140234...)
//   Thread 3 (ID: 140234...)
//
// --- Thread info ---
//   Hardware concurrency: 8
//
// --- Joinable state ---
//   Before join, joinable: 1
//   After join, joinable: 0
