// CodeNebula - C++98 Example: <ctime> time functions
// Compile: g++ -std=c++98 -Wall -Wextra -o example ctime.cpp

#include <iostream>
#include <ctime>
#include <iomanip>

int main() {
    // Get current calendar time
    std::time_t now = std::time(NULL);
    std::cout << "time_t value: " << now << std::endl;

    // Convert to local time struct
    std::tm* local = std::localtime(&now);
    std::cout << "Local time: "
              << (1900 + local->tm_year) << "-"
              << std::setw(2) << std::setfill('0') << (1 + local->tm_mon) << "-"
              << std::setw(2) << local->tm_mday << " "
              << std::setw(2) << local->tm_hour << ":"
              << std::setw(2) << local->tm_min << ":"
              << std::setw(2) << local->tm_sec << std::endl;

    // Convert to UTC
    std::tm* utc = std::gmtime(&now);
    std::cout << "UTC time:   "
              << (1900 + utc->tm_year) << "-"
              << std::setw(2) << (1 + utc->tm_mon) << "-"
              << std::setw(2) << utc->tm_mday << " "
              << std::setw(2) << utc->tm_hour << ":"
              << std::setw(2) << utc->tm_min << ":"
              << std::setw(2) << utc->tm_sec << std::endl;

    // Formatted string with strftime
    char buf[80];
    std::strftime(buf, sizeof(buf), "%A, %B %d, %Y %I:%M %p", local);
    std::cout << "Formatted: " << buf << std::endl;

    // asctime - human readable
    std::cout << "asctime: " << std::asctime(local); // includes newline

    // clock - processor time
    std::clock_t start = std::clock();
    volatile long sum = 0; // volatile prevents optimization
    for (long i = 0; i < 1000000L; ++i) sum += i;
    std::clock_t end = std::clock();

    double elapsed = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    std::cout << "CPU time for loop: " << elapsed << " seconds" << std::endl;

    // difftime
    std::time_t later = now + 3600; // 1 hour later
    std::cout << "difftime (1 hour): " << std::difftime(later, now) << " sec" << std::endl;

    return 0;
}

// Expected output (time values vary):
// time_t value: <current epoch>
// Local time: <current date and time>
// UTC time:   <current UTC date and time>
// Formatted: <day>, <month> <dd>, <yyyy> <hh>:<mm> <AM/PM>
// asctime: <human-readable time>
// CPU time for loop: <small number> seconds
// difftime (1 hour): 3600 sec
