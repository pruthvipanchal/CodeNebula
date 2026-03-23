// CodeNebula - C++11 Example: steady_clock
// Compile: g++ -std=c++11 -Wall -Wextra -o example steady_clock.cpp

// Demonstrates std::chrono::steady_clock: a monotonic clock ideal for
// measuring elapsed time and benchmarking.

#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    using namespace std::chrono;

    // steady_clock is guaranteed to be monotonic
    std::cout << "steady_clock is_steady: "
              << std::boolalpha << steady_clock::is_steady << "\n";

    // Benchmark: sorting a vector
    const int N = 100000;
    std::vector<int> data(N);
    std::iota(data.begin(), data.end(), 0);
    std::reverse(data.begin(), data.end());

    steady_clock::time_point start = steady_clock::now();
    std::sort(data.begin(), data.end());
    steady_clock::time_point end = steady_clock::now();

    auto elapsed_us = duration_cast<microseconds>(end - start).count();
    auto elapsed_ms = duration_cast<milliseconds>(end - start).count();

    std::cout << "Sorted " << N << " integers\n";
    std::cout << "Elapsed: " << elapsed_us << " microseconds ("
              << elapsed_ms << " ms)\n";

    // Measure a tight loop
    start = steady_clock::now();
    volatile long sum = 0;
    for (int i = 0; i < 1000000; ++i) {
        sum += i;
    }
    end = steady_clock::now();

    auto loop_ns = duration_cast<nanoseconds>(end - start).count();
    std::cout << "Loop sum: " << sum << "\n";
    std::cout << "Loop elapsed: " << loop_ns << " nanoseconds\n";

    // Two successive calls — monotonic guarantee
    auto t1 = steady_clock::now();
    auto t2 = steady_clock::now();
    std::cout << "t2 >= t1: " << std::boolalpha << (t2 >= t1) << "\n";

    return 0;
}

// Expected output (timings will vary):
// steady_clock is_steady: true
// Sorted 100000 integers
// Elapsed: 8500 microseconds (8 ms)
// Loop sum: 499999500000
// Loop elapsed: 2500000 nanoseconds
// t2 >= t1: true
