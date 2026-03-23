// CodeNebula - C++11 Example: Duration Typedefs
// Compile: g++ -std=c++11 -Wall -Wextra -o example duration_typedefs.cpp

// Demonstrates the predefined duration typedefs: nanoseconds, microseconds,
// milliseconds, seconds, minutes, hours — and conversions between them.

#include <iostream>
#include <chrono>

int main() {
    using namespace std::chrono;

    // Construct durations from each typedef
    nanoseconds  ns(1500000000LL);   // 1.5 billion nanoseconds
    microseconds us(1500000);         // 1.5 million microseconds
    milliseconds ms(1500);            // 1500 milliseconds
    seconds      s(90);               // 90 seconds
    minutes      m(3);                // 3 minutes
    hours        h(2);                // 2 hours

    std::cout << "=== Raw counts ===\n";
    std::cout << "nanoseconds:  " << ns.count() << " ns\n";
    std::cout << "microseconds: " << us.count() << " us\n";
    std::cout << "milliseconds: " << ms.count() << " ms\n";
    std::cout << "seconds:      " << s.count()  << " s\n";
    std::cout << "minutes:      " << m.count()  << " min\n";
    std::cout << "hours:        " << h.count()  << " h\n\n";

    // duration_cast: narrowing (truncates toward zero)
    std::cout << "=== Conversions (duration_cast) ===\n";
    auto ns_to_ms = duration_cast<milliseconds>(ns);
    std::cout << ns.count() << " ns = " << ns_to_ms.count() << " ms\n";

    auto s_to_min = duration_cast<minutes>(s);
    std::cout << s.count() << " s  = " << s_to_min.count() << " min\n";

    auto h_to_s = duration_cast<seconds>(h);
    std::cout << h.count() << " h  = " << h_to_s.count() << " s\n\n";

    // Widening conversion is implicit (no cast needed)
    nanoseconds widened = ms;  // milliseconds -> nanoseconds
    std::cout << "1500 ms = " << widened.count() << " ns (implicit)\n\n";

    // Arithmetic on durations
    auto total = h + m + s;
    auto total_s = duration_cast<seconds>(total);
    std::cout << "2h + 3min + 90s = " << total_s.count() << " s\n";

    // Comparison
    std::cout << "90s == 1min? " << std::boolalpha << (seconds(90) == minutes(1))
              << "\n";
    std::cout << "90s >  1min? " << (seconds(90) > minutes(1)) << "\n";

    return 0;
}

// Expected output:
// === Raw counts ===
// nanoseconds:  1500000000 ns
// microseconds: 1500000 us
// milliseconds: 1500 ms
// seconds:      90 s
// minutes:      3 min
// hours:        2 h
//
// === Conversions (duration_cast) ===
// 1500000000 ns = 1500 ms
// 90 s  = 1 min
// 2 h  = 7200 s
//
// 1500 ms = 1500000000 ns (implicit)
//
// 2h + 3min + 90s = 7470 s
// 90s == 1min? false
// 90s >  1min? true
