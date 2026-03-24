// CodeNebula - C++23 Example: chrono::zoned_traits, choose, leap_second
// Compile: g++ -std=c++23 -Wall -Wextra -o example chrono_zoned_leap.cpp
// Note: Requires GCC 13+ / Clang 17+

#include <chrono>
#include <iostream>
#include <string>

// C++23 improves chrono timezone and leap second support:
// - zoned_time with choose::earliest / choose::latest for ambiguous times
// - leap_second_info and get_leap_second_info()
// - Enhanced zoned_traits for custom time zone handling

int main() {
    using namespace std::chrono;
    using namespace std::chrono_literals;

    std::cout << "=== chrono::zoned_traits, choose, leap_second ===\n\n";

    // --- Basic zoned_time ---
    std::cout << "--- Zoned time ---\n";
    auto now = system_clock::now();
    auto utc_now = floor<seconds>(now);

    try {
        zoned_time zt_utc{"UTC", utc_now};
        std::cout << "UTC:      " << zt_utc << "\n";

        zoned_time zt_ny{"America/New_York", utc_now};
        std::cout << "New York: " << zt_ny << "\n";

        zoned_time zt_tok{"Asia/Tokyo", utc_now};
        std::cout << "Tokyo:    " << zt_tok << "\n";

        zoned_time zt_lon{"Europe/London", utc_now};
        std::cout << "London:   " << zt_lon << "\n\n";
    } catch (const std::runtime_error& e) {
        std::cout << "Timezone error: " << e.what() << "\n\n";
    }

    // --- choose::earliest / choose::latest for ambiguous times ---
    // During DST fall-back, a local time can occur twice.
    std::cout << "--- choose for ambiguous times ---\n";
    try {
        // Nov 3, 2024, 1:30 AM ET is ambiguous (DST fall-back)
        auto ambiguous_local = local_days{2024y / November / 3d} + 1h + 30min;

        auto zt_early = zoned_time{"America/New_York",
            ambiguous_local, choose::earliest};
        auto zt_late = zoned_time{"America/New_York",
            ambiguous_local, choose::latest};

        std::cout << "Ambiguous time 2024-11-03 01:30 ET:\n";
        std::cout << "  choose::earliest -> " << zt_early << "\n";
        std::cout << "  choose::latest   -> " << zt_late << "\n\n";
    } catch (const std::runtime_error& e) {
        std::cout << "  (Timezone data unavailable: " << e.what() << ")\n\n";
    }

    // --- Leap second information ---
    std::cout << "--- Leap second info ---\n";
    auto utc_time = utc_clock::now();
    auto info = get_leap_second_info(utc_time);
    std::cout << "Current leap second offset: "
              << info.elapsed.count() << "s\n";
    std::cout << "Is during leap second insertion: "
              << (info.is_leap_second ? "yes" : "no") << "\n\n";

    // --- Enumerate known leap seconds ---
    std::cout << "--- Known leap seconds (last 5) ---\n";
    auto& leaps = get_tzdb().leap_seconds;
    int count = 0;
    for (auto it = leaps.rbegin(); it != leaps.rend() && count < 5; ++it, ++count) {
        std::cout << "  " << it->date() << " ("
                  << (it->value().count() > 0 ? "+" : "")
                  << it->value().count() << "s)\n";
    }
    std::cout << "Total leap seconds in database: " << leaps.size() << "\n\n";

    // --- Time zone database info ---
    std::cout << "--- Time zone database ---\n";
    const auto& db = get_tzdb();
    std::cout << "Database version: " << db.version << "\n";
    std::cout << "Number of zones: " << db.zones.size() << "\n";

    return 0;
}

// Expected output (varies by system time and tzdb):
// === chrono::zoned_traits, choose, leap_second ===
//
// --- Zoned time ---
// UTC:      2026-03-24 12:00:00 UTC
// New York: 2026-03-24 08:00:00 EDT
// Tokyo:    2026-03-24 21:00:00 JST
// London:   2026-03-24 12:00:00 GMT
//
// --- choose for ambiguous times ---
// Ambiguous time 2024-11-03 01:30 ET:
//   choose::earliest -> 2024-11-03 01:30:00 EDT
//   choose::latest   -> 2024-11-03 01:30:00 EST
//
// --- Leap second info ---
// Current leap second offset: 27s
// Is during leap second insertion: no
//
// --- Known leap seconds (last 5) ---
//   2017-01-01 (+1s)
//   2015-07-01 (+1s)
//   2012-07-01 (+1s)
//   2009-01-01 (+1s)
//   2006-01-01 (+1s)
// Total leap seconds in database: 27
//
// --- Time zone database ---
// Database version: 2024a
// Number of zones: 596
