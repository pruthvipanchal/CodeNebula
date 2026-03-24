// CodeNebula - C++20 Example: Chrono Time Zones
// Compile: g++ -std=c++20 -Wall -Wextra -o example chrono_timezones.cpp

#include <chrono>
#include <iostream>

int main() {
    using namespace std::chrono;

    std::cout << "=== sys_time (system clock) ===\n";

    auto now = system_clock::now();
    auto now_s = floor<seconds>(now);
    std::cout << "System time (UTC): " << now_s << "\n";

    // Convert to year_month_day
    auto today = floor<days>(now);
    year_month_day ymd{today};
    std::cout << "Today's date: " << ymd << "\n";

    std::cout << "\n=== Time zones ===\n";

    // Get the local time zone
    const auto* local_tz = current_zone();
    std::cout << "Local timezone: " << local_tz->name() << "\n";

    // Look up specific time zones
    const auto* ny_tz = locate_zone("America/New_York");
    const auto* tokyo_tz = locate_zone("Asia/Tokyo");
    const auto* london_tz = locate_zone("Europe/London");
    std::cout << "Found zones: " << ny_tz->name() << ", "
              << tokyo_tz->name() << ", " << london_tz->name() << "\n";

    std::cout << "\n=== zoned_time ===\n";

    // Create zoned times from system time
    zoned_time zt_local{current_zone(), now_s};
    zoned_time zt_ny{"America/New_York", now_s};
    zoned_time zt_tokyo{"Asia/Tokyo", now_s};
    zoned_time zt_london{"Europe/London", now_s};

    std::cout << "Local:  " << zt_local << "\n";
    std::cout << "NYC:    " << zt_ny << "\n";
    std::cout << "Tokyo:  " << zt_tokyo << "\n";
    std::cout << "London: " << zt_london << "\n";

    std::cout << "\n=== Converting between zones ===\n";

    // Create a specific local time in New York
    auto ny_local = local_days{2024y / July / 4d} + 12h + 0min;
    zoned_time ny_noon{"America/New_York", ny_local};
    std::cout << "NY noon: " << ny_noon << "\n";

    // Convert to Tokyo time
    zoned_time tokyo_time{"Asia/Tokyo", ny_noon.get_sys_time()};
    std::cout << "In Tokyo: " << tokyo_time << "\n";

    std::cout << "\n=== UTC offset info ===\n";

    auto info = ny_tz->get_info(now_s);
    std::cout << "NY offset: " << info.offset << "\n";
    std::cout << "NY abbrev: " << info.abbrev << "\n";
    std::cout << "NY DST: " << (info.save != 0min ? "yes" : "no") << "\n";

    std::cout << "\n=== utc_clock ===\n";

    auto utc_now = utc_clock::now();
    auto utc_s = floor<seconds>(utc_now);
    std::cout << "UTC clock: " << utc_s << "\n";

    // Convert between clocks
    auto sys_from_utc = utc_clock::to_sys(utc_s);
    std::cout << "As sys_time: " << floor<seconds>(sys_from_utc) << "\n";

    return 0;
}
