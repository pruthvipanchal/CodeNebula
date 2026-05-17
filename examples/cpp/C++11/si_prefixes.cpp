// CodeNebula - C++11 Example: SI Prefixes
// Compile: g++ -std=c++11 -Wall -Wextra -o example si_prefixes.cpp

// Demonstrates the predefined std::ratio SI prefix typedefs:
// atto (10^-18) through exa (10^18).

#include <iostream>
#include <ratio>
#include <iomanip>

// Helper to print a ratio's num/den
template <typename R>
void print_ratio(const char* name) {
    std::cout << std::setw(6) << name << ": "
              << R::num << " / " << R::den << "\n";
}

int main() {
    std::cout << "=== SI prefixes (small) ===\n";
    print_ratio<std::atto> ("atto");    // 10^-18
    print_ratio<std::femto>("femto");   // 10^-15
    print_ratio<std::pico> ("pico");    // 10^-12
    print_ratio<std::nano> ("nano");    // 10^-9
    print_ratio<std::micro>("micro");   // 10^-6
    print_ratio<std::milli>("milli");   // 10^-3
    print_ratio<std::centi>("centi");   // 10^-2
    print_ratio<std::deci> ("deci");    // 10^-1

    std::cout << "\n=== SI prefixes (large) ===\n";
    print_ratio<std::deca> ("deca");    // 10^1
    print_ratio<std::hecto>("hecto");   // 10^2
    print_ratio<std::kilo> ("kilo");    // 10^3
    print_ratio<std::mega> ("mega");    // 10^6
    print_ratio<std::giga> ("giga");    // 10^9
    print_ratio<std::tera> ("tera");    // 10^12
    print_ratio<std::peta> ("peta");    // 10^15
    print_ratio<std::exa>  ("exa");     // 10^18

    // Practical: convert 5 kilometers to meters using kilo
    double km = 5.0;
    double m = km * std::kilo::num / std::kilo::den;
    std::cout << "\n5 km = " << m << " m\n";

    // Convert 250 millivolts to volts using milli
    double mv = 250.0;
    double v = mv * static_cast<double>(std::milli::num) / std::milli::den;
    std::cout << "250 mV = " << v << " V\n";

    // Convert 3.2 gigahertz to hertz
    double ghz = 3.2;
    double hz = ghz * std::giga::num / std::giga::den;
    std::cout << std::fixed << std::setprecision(0);
    std::cout << "3.2 GHz = " << hz << " Hz\n";

    return 0;
}

// Expected output:
//  === SI prefixes (small) ===
//   atto: 1 / 1000000000000000000
//  femto: 1 / 1000000000000000
//   pico: 1 / 1000000000000
//   nano: 1 / 1000000000
//  micro: 1 / 1000000
//  milli: 1 / 1000
//  centi: 1 / 100
//   deci: 1 / 10
//
// === SI prefixes (large) ===
//   deca: 10 / 1
//  hecto: 100 / 1
//   kilo: 1000 / 1
//   mega: 1000000 / 1
//   giga: 1000000000 / 1
//   tera: 1000000000000 / 1
//   peta: 1000000000000000 / 1
//    exa: 1000000000000000000 / 1
//
// 5 km = 5000 m
// 250 mV = 0.25 V
// 3.2 GHz = 3200000000 Hz
