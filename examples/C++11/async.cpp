// CodeNebula - C++11 Example: std::async
// Compile: g++ -std=c++11 -Wall -Wextra -pthread -o example async.cpp
//
// This example demonstrates:
// - std::async for launching asynchronous tasks
// - std::launch::async (new thread) vs std::launch::deferred (lazy)
// - Default launch policy (implementation-defined)
// - Collecting results from multiple async tasks
// - Practical use: parallel computation

#include <iostream>
#include <future>
#include <vector>
#include <string>
#include <chrono>
#include <numeric>
#include <cmath>

// ============================================================
// 1. Basic async usage
// ============================================================
int heavyComputation(int n) {
    int sum = 0;
    for (int i = 1; i <= n; ++i) {
        sum += i * i;
    }
    return sum;
}

std::string fetchData(const std::string& source) {
    // Simulate network delay
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    return "Data from " + source;
}

// ============================================================
// 2. Launch policies
// ============================================================
void demonstratePolicies() {
    std::cout << "--- Launch policies ---" << std::endl;

    // std::launch::async: guaranteed new thread
    auto asyncResult = std::async(std::launch::async, []() {
        std::cout << "  async policy: thread "
                  << std::this_thread::get_id() << std::endl;
        return 1;
    });

    // std::launch::deferred: lazy evaluation (runs on get())
    auto deferredResult = std::async(std::launch::deferred, []() {
        std::cout << "  deferred policy: thread "
                  << std::this_thread::get_id() << std::endl;
        return 2;
    });

    std::cout << "  Main thread: " << std::this_thread::get_id() << std::endl;
    std::cout << "  (deferred not yet executed)" << std::endl;

    asyncResult.get();
    std::cout << "  Calling deferred.get() now..." << std::endl;
    deferredResult.get();  // Executes HERE, on the calling thread
}

// ============================================================
// 3. Parallel computation
// ============================================================
double partialSum(const std::vector<double>& data, size_t start, size_t end) {
    double sum = 0.0;
    for (size_t i = start; i < end; ++i) {
        sum += data[i];
    }
    return sum;
}

double parallelSum(const std::vector<double>& data, int numTasks) {
    size_t chunkSize = data.size() / static_cast<size_t>(numTasks);
    std::vector<std::future<double>> futures;

    for (int i = 0; i < numTasks; ++i) {
        size_t start = static_cast<size_t>(i) * chunkSize;
        size_t end = (i == numTasks - 1) ? data.size() : start + chunkSize;
        futures.push_back(
            std::async(std::launch::async, partialSum,
                       std::cref(data), start, end)
        );
    }

    double total = 0.0;
    for (auto& f : futures) {
        total += f.get();
    }
    return total;
}

// ============================================================
// 4. Multiple independent tasks
// ============================================================
struct TaskResult {
    std::string name;
    int value;
};

int main() {
    std::cout << "=== std::async ===" << std::endl;

    // Basic async
    std::cout << "\n--- Basic async ---" << std::endl;
    auto f1 = std::async(std::launch::async, heavyComputation, 100);
    auto f2 = std::async(std::launch::async, fetchData, "server-1");
    auto f3 = std::async(std::launch::async, fetchData, "server-2");

    std::cout << "  Tasks launched, doing other work..." << std::endl;
    std::cout << "  Sum of squares(1..100) = " << f1.get() << std::endl;
    std::cout << "  " << f2.get() << std::endl;
    std::cout << "  " << f3.get() << std::endl;

    // Launch policies
    std::cout << std::endl;
    demonstratePolicies();

    // Parallel sum
    std::cout << "\n--- Parallel computation ---" << std::endl;
    std::vector<double> data(10000);
    for (size_t i = 0; i < data.size(); ++i) {
        data[i] = static_cast<double>(i + 1);
    }

    auto start = std::chrono::steady_clock::now();
    double pSum = parallelSum(data, 4);
    auto end = std::chrono::steady_clock::now();
    auto dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    double expected = 10000.0 * 10001.0 / 2.0;
    std::cout << "  Parallel sum: " << pSum << std::endl;
    std::cout << "  Expected:     " << expected << std::endl;
    std::cout << "  Time: " << dur.count() << " us" << std::endl;

    // Collecting multiple results
    std::cout << "\n--- Multiple async results ---" << std::endl;
    std::vector<std::future<int>> futures;
    for (int i = 1; i <= 5; ++i) {
        futures.push_back(std::async(std::launch::async, [i]() {
            return i * i;
        }));
    }
    for (int i = 0; i < 5; ++i) {
        std::cout << "  " << (i + 1) << "^2 = " << futures[i].get() << std::endl;
    }

    return 0;
}

// Expected output:
// === std::async ===
//
// --- Basic async ---
//   Tasks launched, doing other work...
//   Sum of squares(1..100) = 338350
//   Data from server-1
//   Data from server-2
//
// --- Launch policies ---
//   Main thread: 140...
//   async policy: thread 140...
//   (deferred not yet executed)
//   Calling deferred.get() now...
//   deferred policy: thread 140... (same as main)
//
// --- Parallel computation ---
//   Parallel sum: 5.0005e+07
//   Expected:     5.0005e+07
//   Time: ... us
//
// --- Multiple async results ---
//   1^2 = 1
//   2^2 = 4
//   3^2 = 9
//   4^2 = 16
//   5^2 = 25
