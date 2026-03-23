// CodeNebula - C++11 Example: std::chrono::time_point
// Compile: g++ -std=c++11 -Wall -Wextra -o example chrono_time_point.cpp

// std::chrono::time_point represents a point in time relative to a clock's
// epoch. It supports arithmetic with durations and comparison. The three
// standard clocks are system_clock, steady_clock, and high_resolution_clock.

#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>
#include <iomanip>

int main() {
    using namespace std::chrono;

    // === system_clock: wall-clock time (can convert to time_t) ===
    std::cout << "=== system_clock ===" << std::endl;
    auto now = system_clock::now();

    // Convert to time_t for human-readable output
    std::time_t now_t = system_clock::to_time_t(now);
    std::cout << "Current time: " << std::ctime(&now_t);

    // Time since epoch
    auto since_epoch = now.time_since_epoch();
    auto sec = duration_cast<seconds>(since_epoch);
    std::cout << "Seconds since epoch: " << sec.count() << std::endl;

    // Create a time_point from time_t
    std::time_t some_time = 1000000000;  // Sep 9, 2001
    auto tp = system_clock::from_time_t(some_time);
    std::time_t check = system_clock::to_time_t(tp);
    std::cout << "Unix 1000000000: " << std::ctime(&check);

    // === steady_clock: monotonic, for measuring intervals ===
    std::cout << "\n=== steady_clock ===" << std::endl;
    std::cout << "is_steady: " << (steady_clock::is_steady ? "true" : "false") << std::endl;

    auto start = steady_clock::now();
    std::this_thread::sleep_for(milliseconds(150));
    auto end = steady_clock::now();

    auto elapsed = end - start;  // duration
    auto ms = duration_cast<milliseconds>(elapsed);
    auto us = duration_cast<microseconds>(elapsed);
    std::cout << "Sleep(150ms) measured:" << std::endl;
    std::cout << "  " << ms.count() << " ms" << std::endl;
    std::cout << "  " << us.count() << " us" << std::endl;

    // === time_point arithmetic ===
    std::cout << "\n=== time_point arithmetic ===" << std::endl;

    // Add duration to time_point
    auto future = now + hours(24);
    std::time_t future_t = system_clock::to_time_t(future);
    std::cout << "24 hours from now: " << std::ctime(&future_t);

    auto past = now - hours(48);
    std::time_t past_t = system_clock::to_time_t(past);
    std::cout << "48 hours ago:      " << std::ctime(&past_t);

    // Subtract two time_points to get duration
    auto diff = future - past;
    auto diff_hours = duration_cast<hours>(diff);
    std::cout << "Difference: " << diff_hours.count() << " hours" << std::endl;

    // === Comparison ===
    std::cout << "\n=== Comparisons ===" << std::endl;
    auto t1 = steady_clock::now();
    auto t2 = t1 + seconds(1);
    std::cout << "t1 < t2:  " << (t1 < t2 ? "true" : "false") << std::endl;
    std::cout << "t1 == t1: " << (t1 == t1 ? "true" : "false") << std::endl;

    // === Practical: simple timer ===
    std::cout << "\n=== Timer ===" << std::endl;
    auto timer_start = steady_clock::now();
    long long sum = 0;
    for (int i = 0; i < 1000000; ++i) sum += i;
    auto timer_end = steady_clock::now();
    auto timer_us = duration_cast<microseconds>(timer_end - timer_start);
    std::cout << "Sum 0..999999 = " << sum << std::endl;
    std::cout << "Took: " << timer_us.count() << " us" << std::endl;

    return 0;
}

// Expected output (times will vary):
// === system_clock ===
// Current time: <current date and time>
// Seconds since epoch: <large number>
// Unix 1000000000: Sun Sep  9 01:46:40 2001
//
// === steady_clock ===
// is_steady: true
// Sleep(150ms) measured:
//   ~150 ms
//   ~150000 us
//
// === time_point arithmetic ===
// 24 hours from now: <tomorrow>
// 48 hours ago:      <two days ago>
// Difference: 72 hours
//
// === Comparisons ===
// t1 < t2:  true
// t1 == t1: true
//
// === Timer ===
// Sum 0..999999 = 499999500000
// Took: <some microseconds>
