// CodeNebula - C++11 Example: system_clock
// Compile: g++ -std=c++11 -Wall -Wextra -o example system_clock.cpp

// Demonstrates std::chrono::system_clock: the wall-clock that can be
// converted to calendar time via to_time_t / from_time_t.

#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>

int main() {
    using namespace std::chrono;

    // Get the current time point
    system_clock::time_point now = system_clock::now();

    // Convert to time_t for human-readable display
    std::time_t now_t = system_clock::to_time_t(now);
    std::cout << "Current time: " << std::ctime(&now_t);

    // Convert back from time_t to time_point
    system_clock::time_point roundtrip = system_clock::from_time_t(now_t);
    std::time_t roundtrip_t = system_clock::to_time_t(roundtrip);
    std::cout << "Round-trip:   " << std::ctime(&roundtrip_t);

    // Epoch (time_t = 0)
    system_clock::time_point epoch = system_clock::from_time_t(0);
    std::time_t epoch_t = system_clock::to_time_t(epoch);
    std::cout << "Epoch:        " << std::ctime(&epoch_t);

    // Duration since epoch in seconds
    auto since_epoch = duration_cast<seconds>(now.time_since_epoch());
    std::cout << "Seconds since epoch: " << since_epoch.count() << "\n";

    // system_clock is not necessarily steady
    std::cout << "system_clock is_steady: "
              << std::boolalpha << system_clock::is_steady << "\n";

    // Resolution: the tick period of the clock
    using period = system_clock::period;
    std::cout << "Tick period: " << period::num << "/" << period::den
              << " seconds\n";

    return 0;
}

// Expected output (times will vary):
// Current time: Mon Mar 23 10:30:00 2026
// Round-trip:   Mon Mar 23 10:30:00 2026
// Epoch:        Thu Jan  1 00:00:00 1970
// Seconds since epoch: 1774500600
// system_clock is_steady: false
// Tick period: 1/1000000000 seconds
