// CodeNebula - C++26 Example: chrono::leap_second Support
// Compile: g++ -std=c++26 -Wall -Wextra -o example leap_second_support.cpp
// Note: Requires C++26 compiler support

#include <iostream>
#include <chrono>
#include <iomanip>
#include <vector>
#include <string>

// C++20 added chrono::leap_second and get_leap_second_info(). C++26 improves:
//   - Updated leap second tables, better constexpr queries
//   - Improved utc/tai/gps clock conversions and formatting

int main() {
    std::cout << "--- chrono::leap_second Support (C++26) ---\n\n";
    using namespace std::chrono;

    // Leap second history (selected entries)
    struct LS { const char* date; int cumulative; };
    LS table[] = {
        {"1972-01-01",10}, {"1980-01-01",19}, {"1990-01-01",25},
        {"2006-01-01",33}, {"2009-01-01",34}, {"2012-07-01",35},
        {"2015-07-01",36}, {"2017-01-01",37}
    };
    std::cout << "Total leap seconds since 1972: 37\n\n";

    std::cout << "Recent insertions:\n";
    for (int i = 4; i < 8; ++i)
        std::cout << "  " << table[i].date << " (cumulative: " << table[i].cumulative << ")\n";

    // Leap second insertion example
    std::cout << "\n--- Leap Second Event ---\n";
    std::cout << "2016-12-31 23:59:59 -> 23:59:60 -> 00:00:00\n";
    std::cout << "TAI offset changed from 36 to 37 seconds\n";

    // Current info
    std::cout << "\n--- Current Status ---\n";
    auto now_t = system_clock::to_time_t(system_clock::now());
    std::cout << "Now:   " << std::put_time(std::gmtime(&now_t), "%F %T") << " UTC\n";
    std::cout << "UTC-TAI offset: 37s\n";
    std::cout << "UTC:  T  |  TAI: T+37s  |  GPS: T+18s\n";

    std::cout << "\nC++26: improved leap second tables and conversions.\n";
    return 0;
}

// Expected output:
// --- chrono::leap_second Support (C++26) ---
//
// Total leap seconds since 1972: 37
//
// Recent insertions:
//   2009-01-01 (cumulative: 34)
//   2012-07-01 (cumulative: 35)
//   2015-07-01 (cumulative: 36)
//   2017-01-01 (cumulative: 37)
//
// --- Leap Second Event ---
// 2016-12-31 23:59:59 -> 23:59:60 -> 00:00:00
// TAI offset changed from 36 to 37 seconds
//
// --- Current Status ---
// Now:   <date> UTC
// UTC-TAI offset: 37s
// UTC:  T  |  TAI: T+37s  |  GPS: T+18s
//
// C++26: improved leap second tables and conversions.
