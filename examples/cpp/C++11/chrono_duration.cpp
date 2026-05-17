// CodeNebula - C++11 Example: std::chrono::duration Arithmetic
// Compile: g++ -std=c++11 -Wall -Wextra -o example chrono_duration.cpp

// std::chrono::duration represents a time span. It's a type-safe wrapper
// around a count of ticks with a specified period (ratio). Arithmetic
// operations automatically handle unit conversions.

#include <iostream>
#include <chrono>
#include <thread>

int main() {
    using namespace std::chrono;

    // Predefined duration types
    hours        h(2);
    minutes      m(30);
    seconds      s(45);
    milliseconds ms(500);
    microseconds us(1234);
    nanoseconds  ns(5678);

    std::cout << "Duration values:" << std::endl;
    std::cout << "  " << h.count() << " hours" << std::endl;
    std::cout << "  " << m.count() << " minutes" << std::endl;
    std::cout << "  " << s.count() << " seconds" << std::endl;
    std::cout << "  " << ms.count() << " milliseconds" << std::endl;
    std::cout << "  " << us.count() << " microseconds" << std::endl;
    std::cout << "  " << ns.count() << " nanoseconds" << std::endl;

    // Arithmetic: addition and subtraction
    auto total = h + m + s;  // result is in seconds (common type)
    std::cout << "\n2h + 30m + 45s = " << total.count() << " seconds" << std::endl;

    auto diff = hours(3) - minutes(90);
    std::cout << "3h - 90m = " << diff.count() << " seconds" << std::endl;

    // Scalar multiplication and division
    auto doubled = s * 2;
    auto halved = m / 2;
    std::cout << "\n45s * 2 = " << doubled.count() << " seconds" << std::endl;
    std::cout << "30m / 2 = " << halved.count() << " minutes" << std::endl;

    // Duration cast (convert between types)
    auto total_min = duration_cast<minutes>(total);
    auto total_ms = duration_cast<milliseconds>(total);
    std::cout << "\n" << total.count() << " seconds = " << total_min.count()
              << " minutes (truncated)" << std::endl;
    std::cout << total.count() << " seconds = " << total_ms.count()
              << " milliseconds" << std::endl;

    // Implicit conversion (fine-to-coarse needs cast, coarse-to-fine is implicit)
    nanoseconds fine = seconds(1);  // implicit: 1s -> 1000000000ns
    std::cout << "\n1 second = " << fine.count() << " nanoseconds" << std::endl;

    // Comparison operators
    std::cout << "\nComparisons:" << std::endl;
    std::cout << "  1h == 60m:  " << (hours(1) == minutes(60) ? "true" : "false") << std::endl;
    std::cout << "  1h > 59m:   " << (hours(1) > minutes(59) ? "true" : "false") << std::endl;
    std::cout << "  500ms < 1s: " << (milliseconds(500) < seconds(1) ? "true" : "false") << std::endl;

    // Practical: measure execution time
    auto start = steady_clock::now();
    std::this_thread::sleep_for(milliseconds(100));
    auto end = steady_clock::now();
    auto elapsed = duration_cast<milliseconds>(end - start);
    std::cout << "\nSleep(100ms) took: " << elapsed.count() << "ms" << std::endl;

    // Modulo operation
    auto remainder = seconds(125) % minutes(1);
    std::cout << "\n125s % 1m = " << remainder.count() << " seconds" << std::endl;

    return 0;
}

// Expected output:
// Duration values:
//   2 hours
//   30 minutes
//   45 seconds
//   500 milliseconds
//   1234 microseconds
//   5678 nanoseconds
//
// 2h + 30m + 45s = 9045 seconds
// 3h - 90m = 5400 seconds
//
// 45s * 2 = 90 seconds
// 30m / 2 = 15 minutes
//
// 9045 seconds = 150 minutes (truncated)
// 9045 seconds = 9045000 milliseconds
//
// 1 second = 1000000000 nanoseconds
//
// Comparisons:
//   1h == 60m:  true
//   1h > 59m:   true
//   500ms < 1s: true
//
// Sleep(100ms) took: ~100ms
//
// 125s % 1m = 5 seconds
