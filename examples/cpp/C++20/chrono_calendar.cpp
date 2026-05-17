// CodeNebula - C++20 Example: Chrono Calendar Types
// Compile: g++ -std=c++20 -Wall -Wextra -o example chrono_calendar.cpp

#include <chrono>
#include <iostream>

int main() {
    using namespace std::chrono;

    std::cout << "=== Basic calendar types ===\n";

    // day, month, year
    day d{15};
    month m{March};
    year y{2024};
    std::cout << "Day: " << unsigned(d) << ", Month: " << unsigned(m)
              << ", Year: " << int(y) << "\n";

    // year_month_day - the primary calendar date type
    year_month_day ymd{2024y / March / 15d};
    std::cout << "Date: " << ymd << "\n";
    std::cout << "Valid: " << ymd.ok() << "\n";

    // Alternative construction syntaxes
    auto date2 = 2024y / 3 / 15;
    auto date3 = March / 15d / 2024y;
    std::cout << "Same date: " << date2 << " == " << date3 << "\n";

    std::cout << "\n=== Weekday ===\n";

    weekday wd{Saturday};
    std::cout << "Saturday iso_encoding: " << wd.iso_encoding() << "\n";

    // Get weekday from a date
    year_month_day today_ymd{2024y / July / 4d};
    weekday today_wd{sys_days{today_ymd}};
    std::cout << "July 4, 2024 is weekday: " << today_wd << "\n";

    std::cout << "\n=== month_day, month_weekday ===\n";

    month_day christmas{December / 25d};
    std::cout << "Christmas: " << christmas << "\n";

    // Third Monday of January (MLK Day)
    month_weekday mlk{January / Monday[3]};
    std::cout << "MLK Day pattern: " << mlk << "\n";

    std::cout << "\n=== year_month_day_last ===\n";

    // Last day of February in leap/non-leap years
    year_month_day_last feb_last_2024{2024y / February / last};
    year_month_day_last feb_last_2023{2023y / February / last};
    std::cout << "Last day Feb 2024: " << year_month_day{feb_last_2024} << "\n";
    std::cout << "Last day Feb 2023: " << year_month_day{feb_last_2023} << "\n";

    std::cout << "\n=== Date arithmetic ===\n";

    year_month_day start{2024y / January / 31d};
    auto plus_one_month = start.year() / (start.month() + months{1}) / start.day();
    std::cout << start << " + 1 month = " << plus_one_month
              << " (valid: " << plus_one_month.ok() << ")\n";

    // Convert to sys_days for day-level arithmetic
    sys_days sd = sys_days{start} + days{45};
    year_month_day result{sd};
    std::cout << start << " + 45 days = " << result << "\n";

    // Difference between dates
    auto diff = sys_days{2024y / December / 31d} - sys_days{2024y / January / 1d};
    std::cout << "Days in 2024: " << diff.count() + 1 << "\n";

    std::cout << "\n=== Leap year check ===\n";
    for (int yr : {2020, 2023, 2024, 2100}) {
        std::cout << yr << " is leap: " << year{yr}.is_leap() << "\n";
    }

    return 0;
}
