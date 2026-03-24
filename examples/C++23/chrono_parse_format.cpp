// CodeNebula - C++23 Example: std::chrono::parse and format
// Compile: g++ -std=c++23 -Wall -Wextra -o example chrono_parse_format.cpp
// Note: Requires GCC 13+ / Clang 17+

#include <chrono>
#include <format>
#include <iostream>
#include <sstream>
#include <string>

// C++23 adds std::chrono::parse for parsing time strings, complementing
// std::format for formatting. Together they provide a complete
// type-safe date/time formatting and parsing system.

int main() {
    using namespace std::chrono;
    using namespace std::chrono_literals;

    std::cout << "=== std::chrono::parse and format ===\n\n";

    // --- Formatting durations ---
    std::cout << "--- Formatting durations ---\n";
    auto dur = 3h + 25min + 10s;
    std::cout << "Duration: " << dur << "\n";

    auto ms_dur = 1500ms;
    std::cout << "Milliseconds: " << ms_dur << "\n\n";

    // --- Formatting time points ---
    std::cout << "--- Formatting time points ---\n";
    auto now = system_clock::now();
    auto today = floor<days>(now);

    // year_month_day from time point
    year_month_day ymd{today};
    std::cout << "Today: " << ymd << "\n";
    std::cout << "Year: " << (int)ymd.year()
              << ", Month: " << (unsigned)ymd.month()
              << ", Day: " << (unsigned)ymd.day() << "\n\n";

    // --- Parsing dates with chrono::parse ---
    std::cout << "--- Parsing with chrono::parse ---\n";

    // Parse a date string
    sys_seconds tp1;
    std::istringstream iss1("2024-06-15 14:30:00");
    iss1 >> parse("%Y-%m-%d %H:%M:%S", tp1);
    if (!iss1.fail()) {
        auto parsed_ymd = year_month_day{floor<days>(tp1)};
        auto tod = hh_mm_ss{tp1 - floor<days>(tp1)};
        std::cout << "Parsed: " << parsed_ymd
                  << " " << tod.hours().count()
                  << ":" << tod.minutes().count()
                  << ":" << tod.seconds().count() << "\n";
    }

    // Parse different format
    sys_seconds tp2;
    std::istringstream iss2("15/06/2024");
    iss2 >> parse("%d/%m/%Y", tp2);
    if (!iss2.fail()) {
        auto parsed = year_month_day{floor<days>(tp2)};
        std::cout << "Parsed DD/MM/YYYY: " << parsed << "\n";
    }

    // Parse time only
    seconds time_of_day;
    std::istringstream iss3("09:45:30");
    iss3 >> parse("%H:%M:%S", time_of_day);
    if (!iss3.fail()) {
        hh_mm_ss hms{time_of_day};
        std::cout << "Parsed time: " << hms.hours().count() << "h "
                  << hms.minutes().count() << "m "
                  << hms.seconds().count() << "s\n";
    }

    // --- Date arithmetic ---
    std::cout << "\n--- Date arithmetic ---\n";
    auto date = 2024y / March / 15d;
    auto next_month = date.year() / (date.month() + months{1}) / date.day();
    std::cout << "Date: " << date << "\n";
    std::cout << "Next month: " << next_month << "\n";

    auto weekday_today = weekday{today};
    std::cout << "Today is weekday index: " << weekday_today.c_encoding() << "\n";

    return 0;
}

// Expected output (dates vary based on current date):
// === std::chrono::parse and format ===
//
// --- Formatting durations ---
// Duration: 12310s
// Milliseconds: 1500ms
//
// --- Formatting time points ---
// Today: 2026-03-24
// Year: 2026, Month: 3, Day: 24
//
// --- Parsing with chrono::parse ---
// Parsed: 2024-06-15 14:30:0
// Parsed DD/MM/YYYY: 2024-06-15
// Parsed time: 9h 45m 30s
//
// --- Date arithmetic ---
// Date: 2024-03-15
// Next month: 2024-04-15
// Today is weekday index: 2
