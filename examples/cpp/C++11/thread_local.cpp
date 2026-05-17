// CodeNebula - C++11 Example: Thread Local Storage
// Compile: g++ -std=c++11 -Wall -Wextra -pthread -o example thread_local.cpp
//
// This example demonstrates:
// - thread_local storage duration for variables
// - Each thread gets its own independent copy
// - thread_local with static, function-local, and class-static variables
// - Practical use cases: per-thread counters, caches, error codes

#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <vector>

std::mutex coutMutex;

// ============================================================
// 1. Global thread_local variable
// ============================================================
thread_local int threadCounter = 0;
thread_local std::string threadName = "unnamed";

// ============================================================
// 2. Function with thread_local static
// ============================================================
int getCallCount() {
    thread_local int callCount = 0;  // Each thread starts at 0
    return ++callCount;
}

// ============================================================
// 3. Class with thread_local static member
// ============================================================
class Logger {
public:
    static thread_local int logCount;

    static void log(const std::string& msg) {
        ++logCount;
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << "  [" << msg << "] log #" << logCount << std::endl;
    }
};

thread_local int Logger::logCount = 0;

// ============================================================
// 4. Worker function demonstrating independence
// ============================================================
void workerFunction(const std::string& name, int iterations) {
    threadName = name;
    threadCounter = 0;

    for (int i = 0; i < iterations; ++i) {
        ++threadCounter;
        getCallCount();
        Logger::log(name);
    }

    std::lock_guard<std::mutex> lock(coutMutex);
    std::cout << "  " << threadName
              << ": counter=" << threadCounter
              << ", calls=" << getCallCount() - 1
              << ", logs=" << Logger::logCount << std::endl;
}

int main() {
    std::cout << "=== Thread Local Storage ===" << std::endl;

    // Main thread usage
    std::cout << "\n--- Main thread ---" << std::endl;
    threadName = "main";
    threadCounter = 100;
    std::cout << "  Main threadName: " << threadName << std::endl;
    std::cout << "  Main threadCounter: " << threadCounter << std::endl;

    // Spawn worker threads
    std::cout << "\n--- Worker threads ---" << std::endl;
    std::thread t1(workerFunction, "Alpha", 3);
    std::thread t2(workerFunction, "Beta", 2);

    t1.join();
    t2.join();

    // Main thread values are unchanged
    std::cout << "\n--- After threads finish ---" << std::endl;
    std::cout << "  Main threadName: " << threadName << std::endl;
    std::cout << "  Main threadCounter: " << threadCounter << std::endl;
    std::cout << "  Main Logger::logCount: " << Logger::logCount << std::endl;

    std::cout << "\nKey insight: each thread had independent copies" << std::endl;

    return 0;
}

// Expected output (thread interleaving may vary):
// === Thread Local Storage ===
//
// --- Main thread ---
//   Main threadName: main
//   Main threadCounter: 100
//
// --- Worker threads ---
//   [Alpha] log #1
//   [Alpha] log #2
//   [Alpha] log #3
//   Alpha: counter=3, calls=3, logs=3
//   [Beta] log #1
//   [Beta] log #2
//   Beta: counter=2, calls=2, logs=2
//
// --- After threads finish ---
//   Main threadName: main
//   Main threadCounter: 100
//   Main Logger::logCount: 0
//
// Key insight: each thread had independent copies
