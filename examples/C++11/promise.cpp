// CodeNebula - C++11 Example: std::promise
// Compile: g++ -std=c++11 -Wall -Wextra -pthread -o example promise.cpp
//
// This example demonstrates:
// - std::promise to set values for associated futures
// - set_value() for normal results
// - set_exception() for error propagation
// - Promise-future channel for thread communication
// - One-shot synchronization between threads

#include <iostream>
#include <future>
#include <thread>
#include <string>
#include <stdexcept>
#include <functional>
#include <numeric>
#include <vector>

// ============================================================
// 1. Basic promise: set_value
// ============================================================
void computeAndDeliver(std::promise<int> resultPromise, int a, int b) {
    std::cout << "  Worker: computing " << a << " + " << b << std::endl;
    int result = a + b;
    resultPromise.set_value(result);  // Deliver the result
    std::cout << "  Worker: value delivered" << std::endl;
}

// ============================================================
// 2. Promise with exception
// ============================================================
void divideSafely(std::promise<double> resultPromise, double a, double b) {
    if (b == 0.0) {
        // Deliver an exception instead of a value
        resultPromise.set_exception(
            std::make_exception_ptr(
                std::runtime_error("Division by zero")
            )
        );
    } else {
        resultPromise.set_value(a / b);
    }
}

// ============================================================
// 3. Promise as a synchronization signal (void promise)
// ============================================================
void workerWithSignal(std::promise<void> readySignal) {
    std::cout << "  Worker: initializing..." << std::endl;
    // Simulate initialization work
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "  Worker: ready!" << std::endl;
    readySignal.set_value();  // Signal that we're ready
}

// ============================================================
// 4. Chain of promises for pipeline processing
// ============================================================
void stage1(std::promise<int> output) {
    std::cout << "  Stage 1: generating data" << std::endl;
    output.set_value(10);
}

void stage2(std::future<int> input, std::promise<int> output) {
    int val = input.get();
    std::cout << "  Stage 2: received " << val << ", doubling" << std::endl;
    output.set_value(val * 2);
}

void stage3(std::future<int> input, std::promise<std::string> output) {
    int val = input.get();
    std::cout << "  Stage 3: received " << val << ", formatting" << std::endl;
    output.set_value("Final: " + std::to_string(val));
}

int main() {
    std::cout << "=== std::promise ===" << std::endl;

    // Basic set_value
    std::cout << "\n--- Basic promise ---" << std::endl;
    std::promise<int> sumPromise;
    std::future<int> sumFuture = sumPromise.get_future();

    std::thread t1(computeAndDeliver, std::move(sumPromise), 30, 12);
    std::cout << "  Main: waiting for result..." << std::endl;
    int result = sumFuture.get();
    std::cout << "  Main: got " << result << std::endl;
    t1.join();

    // Exception delivery
    std::cout << "\n--- Exception via promise ---" << std::endl;
    std::promise<double> divPromise1;
    std::future<double> divFuture1 = divPromise1.get_future();
    std::thread t2(divideSafely, std::move(divPromise1), 10.0, 3.0);
    std::cout << "  10 / 3 = " << divFuture1.get() << std::endl;
    t2.join();

    std::promise<double> divPromise2;
    std::future<double> divFuture2 = divPromise2.get_future();
    std::thread t3(divideSafely, std::move(divPromise2), 10.0, 0.0);
    try {
        divFuture2.get();
    } catch (const std::runtime_error& e) {
        std::cout << "  10 / 0 threw: " << e.what() << std::endl;
    }
    t3.join();

    // Void promise as signal
    std::cout << "\n--- Void promise (signal) ---" << std::endl;
    std::promise<void> readyPromise;
    std::future<void> readyFuture = readyPromise.get_future();
    std::thread t4(workerWithSignal, std::move(readyPromise));
    readyFuture.get();  // Blocks until worker signals ready
    std::cout << "  Main: worker is ready, proceeding" << std::endl;
    t4.join();

    // Pipeline
    std::cout << "\n--- Pipeline with promises ---" << std::endl;
    std::promise<int> p1;
    std::promise<int> p2;
    std::promise<std::string> p3;
    auto f1 = p1.get_future();
    auto f2 = p2.get_future();
    auto f3 = p3.get_future();

    std::thread s1(stage1, std::move(p1));
    std::thread s2(stage2, std::move(f1), std::move(p2));
    std::thread s3(stage3, std::move(f2), std::move(p3));

    std::cout << "  Pipeline result: " << f3.get() << std::endl;
    s1.join();
    s2.join();
    s3.join();

    return 0;
}

// Expected output:
// === std::promise ===
//
// --- Basic promise ---
//   Main: waiting for result...
//   Worker: computing 30 + 12
//   Worker: value delivered
//   Main: got 42
//
// --- Exception via promise ---
//   10 / 3 = 3.33333
//   10 / 0 threw: Division by zero
//
// --- Void promise (signal) ---
//   Worker: initializing...
//   Worker: ready!
//   Main: worker is ready, proceeding
//
// --- Pipeline with promises ---
//   Stage 1: generating data
//   Stage 2: received 10, doubling
//   Stage 3: received 20, formatting
//   Pipeline result: Final: 20
