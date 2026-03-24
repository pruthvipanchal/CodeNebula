// CodeNebula - C++26 Example: chrono::gps_clock Improvements
// Compile: g++ -std=c++26 -Wall -Wextra -o example gps_clock_improvements.cpp
// Note: Requires C++26 compiler support

#include <iostream>
#include <chrono>
#include <iomanip>

// C++20 introduced chrono::gps_clock. C++26 improves with:
//   - Better UTC<->GPS conversion with leap second tables
//   - Improved constexpr and formatting support
// GPS epoch: 1980-01-06 00:00:00 UTC. GPS = TAI - 19s = UTC + 18s.

int main() {
    std::cout << "--- chrono::gps_clock (C++26) ---\n\n";
    using namespace std::chrono;

    auto gps_epoch = sys_days{1980y / January / 6};
    auto gps_epoch_t = system_clock::to_time_t(gps_epoch);
    std::cout << "GPS epoch: " << std::put_time(std::gmtime(&gps_epoch_t), "%F %T") << " UTC\n";

    auto utc_now = system_clock::now();
    auto utc_t = system_clock::to_time_t(utc_now);
    std::cout << "UTC now:   " << std::put_time(std::gmtime(&utc_t), "%F %T") << "\n";

    constexpr int gps_utc_offset = 18;
    auto gps_now = utc_now + seconds(gps_utc_offset);
    auto gps_t = system_clock::to_time_t(gps_now);
    std::cout << "GPS now:   " << std::put_time(std::gmtime(&gps_t), "%F %T")
              << " (UTC+" << gps_utc_offset << "s)\n";

    // GPS week number
    auto hrs = duration_cast<hours>(utc_now - gps_epoch);
    int gps_week = static_cast<int>(hrs.count() / (24 * 7));
    std::cout << "\nGPS week: " << gps_week << "\n";

    // Time scale relationships
    std::cout << "\n--- Relationships ---\n";
    std::cout << "TAI = UTC + 37s\n";
    std::cout << "GPS = TAI - 19s = UTC + 18s\n";

    auto total_days = duration_cast<days>(utc_now - gps_epoch);
    std::cout << "\nDays since GPS epoch: " << total_days.count() << "\n";
    std::cout << "\nC++26: gps_clock has improved leap second conversions.\n";
    return 0;
}

// Expected output:
// --- chrono::gps_clock (C++26) ---
//
// GPS epoch: 1980-01-06 00:00:00 UTC
// UTC now:   <current date time>
// GPS now:   <current + 18s> (UTC+18s)
//
// GPS week: <number>
//
// --- Relationships ---
// TAI = UTC + 37s
// GPS = TAI - 19s = UTC + 18s
//
// Days since GPS epoch: <number>
//
// C++26: gps_clock has improved leap second conversions.
