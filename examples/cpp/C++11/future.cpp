// CodeNebula - C++11 Example: std::future
// Compile: g++ -std=c++11 -Wall -Wextra -pthread -o example future.cpp
//
// This example demonstrates:
// - std::future to retrieve results from asynchronous operations
// - get() to block and obtain the result
// - wait(), wait_for(), wait_until() for checking readiness
// - Futures from std::async, std::packaged_task, and std::promise
// - Exception propagation through futures

#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <string>
#include <stdexcept>
#include <cmath>

// ============================================================
// 1. Future from std::async
// ============================================================
int computeSum(int n) {
    int sum = 0;
    for (int i = 1; i <= n; ++i) {
        sum += i;
    }
    return sum;
}

double computeSqrt(double x) {
    if (x < 0) throw std::invalid_argument("Cannot sqrt negative");
    return std::sqrt(x);
}

// ============================================================
// 2. Future from std::packaged_task
// ============================================================
std::string formatResult(int value) {
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    return "Result is: " + std::to_string(value);
}

// ============================================================
// 3. Checking future status
// ============================================================
int slowComputation() {
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    return 42;
}

int main() {
    std::cout << "=== std::future ===" << std::endl;

    // Future from async
    std::cout << "\n--- Future from std::async ---" << std::endl;
    std::future<int> sumFuture = std::async(std::launch::async, computeSum, 100);
    std::future<double> sqrtFuture = std::async(std::launch::async, computeSqrt, 144.0);

    // Do other work while computation runs...
    std::cout << "  Waiting for results..." << std::endl;

    int sumResult = sumFuture.get();       // Blocks until ready
    double sqrtResult = sqrtFuture.get();

    std::cout << "  Sum(1..100) = " << sumResult << std::endl;
    std::cout << "  Sqrt(144) = " << sqrtResult << std::endl;

    // Exception through future
    std::cout << "\n--- Exception propagation ---" << std::endl;
    std::future<double> badFuture = std::async(std::launch::async, computeSqrt, -1.0);
    try {
        badFuture.get();  // Re-throws the exception
    } catch (const std::invalid_argument& e) {
        std::cout << "  Caught from future: " << e.what() << std::endl;
    }

    // Future from packaged_task
    std::cout << "\n--- Future from packaged_task ---" << std::endl;
    std::packaged_task<std::string(int)> task(formatResult);
    std::future<std::string> taskFuture = task.get_future();

    std::thread taskThread(std::move(task), 99);
    std::string formatted = taskFuture.get();
    std::cout << "  " << formatted << std::endl;
    taskThread.join();

    // Checking status with wait_for
    std::cout << "\n--- wait_for status check ---" << std::endl;
    std::future<int> slowFuture = std::async(std::launch::async, slowComputation);

    auto status = slowFuture.wait_for(std::chrono::milliseconds(50));
    if (status == std::future_status::timeout) {
        std::cout << "  After 50ms: not ready yet (timeout)" << std::endl;
    } else if (status == std::future_status::ready) {
        std::cout << "  After 50ms: ready" << std::endl;
    }

    int slowResult = slowFuture.get();
    std::cout << "  Final result: " << slowResult << std::endl;

    // Multiple futures
    std::cout << "\n--- Multiple async futures ---" << std::endl;
    std::vector<std::future<int>> futures;
    for (int i = 1; i <= 5; ++i) {
        futures.push_back(std::async(std::launch::async, computeSum, i * 10));
    }

    for (size_t i = 0; i < futures.size(); ++i) {
        std::cout << "  Sum(1.." << ((i + 1) * 10) << ") = "
                  << futures[i].get() << std::endl;
    }

    return 0;
}

// Expected output:
// === std::future ===
//
// --- Future from std::async ---
//   Waiting for results...
//   Sum(1..100) = 5050
//   Sqrt(144) = 12
//
// --- Exception propagation ---
//   Caught from future: Cannot sqrt negative
//
// --- Future from packaged_task ---
//   Result is: 99
//
// --- wait_for status check ---
//   After 50ms: not ready yet (timeout)
//   Final result: 42
//
// --- Multiple async futures ---
//   Sum(1..10) = 55
//   Sum(1..20) = 210
//   Sum(1..30) = 465
//   Sum(1..40) = 820
//   Sum(1..50) = 1275
