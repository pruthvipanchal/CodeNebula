// CodeNebula - C++11 Example: high_resolution_clock
// Compile: g++ -std=c++11 -Wall -Wextra -o example high_resolution_clock.cpp

// Demonstrates std::chrono::high_resolution_clock: the clock with the
// shortest tick period available on the platform.

#include <iostream>
#include <chrono>
#include <cmath>

int main() {
    using namespace std::chrono;
    using hrc = high_resolution_clock;

    // Check if it is steady (implementation-defined)
    std::cout << "high_resolution_clock is_steady: "
              << std::boolalpha << hrc::is_steady << "\n";

    // Display tick period (resolution)
    using period = hrc::period;
    std::cout << "Tick period: " << period::num << "/" << period::den
              << " seconds\n";
    double resolution_ns = (1e9 * period::num) / period::den;
    std::cout << "Resolution:  ~" << resolution_ns << " nanoseconds\n\n";

    // Measure a small computation with nanosecond precision
    auto start = hrc::now();
    double result = 0.0;
    for (int i = 1; i <= 10000; ++i) {
        result += std::sin(static_cast<double>(i));
    }
    auto end = hrc::now();

    auto ns = duration_cast<nanoseconds>(end - start).count();
    auto us = duration_cast<microseconds>(end - start).count();
    std::cout << "sin() sum for 10000 iterations: " << result << "\n";
    std::cout << "Elapsed: " << ns << " ns (" << us << " us)\n\n";

    // Measure overhead of now() itself
    auto t1 = hrc::now();
    auto t2 = hrc::now();
    auto overhead = duration_cast<nanoseconds>(t2 - t1).count();
    std::cout << "Clock call overhead: ~" << overhead << " ns\n";

    // Check whether it is an alias for steady_clock or system_clock
    bool same_as_steady = std::is_same<hrc, steady_clock>::value;
    bool same_as_system = std::is_same<hrc, system_clock>::value;
    std::cout << "Same as steady_clock: " << same_as_steady << "\n";
    std::cout << "Same as system_clock: " << same_as_system << "\n";

    return 0;
}

// Expected output (timings and aliases are platform-dependent):
// high_resolution_clock is_steady: true
// Tick period: 1/1000000000 seconds
// Resolution:  ~1 nanoseconds
//
// sin() sum for 10000 iterations: -0.305614
// Elapsed: 125000 ns (125 us)
//
// Clock call overhead: ~30 ns
// Same as steady_clock: true
// Same as system_clock: false
