// CodeNebula - C++11 Example: std::ratio
// Compile: g++ -std=c++11 -Wall -Wextra -o example ratio.cpp

// Demonstrates std::ratio: compile-time rational number arithmetic.
// A ratio<Num, Den> represents the fraction Num/Den reduced to lowest terms.

#include <iostream>
#include <ratio>

int main() {
    // Basic ratio creation — automatically reduced
    using two_thirds  = std::ratio<2, 3>;
    using four_sixths = std::ratio<4, 6>;   // reduced to 2/3

    std::cout << "=== Basic ratios ===\n";
    std::cout << "ratio<2,3>: " << two_thirds::num << "/"
              << two_thirds::den << "\n";
    std::cout << "ratio<4,6>: " << four_sixths::num << "/"
              << four_sixths::den << " (auto-reduced)\n";

    // Negative ratios — sign is always in the numerator
    using neg = std::ratio<-5, 10>;
    std::cout << "ratio<-5,10>: " << neg::num << "/" << neg::den << "\n";

    using neg2 = std::ratio<7, -14>;
    std::cout << "ratio<7,-14>: " << neg2::num << "/" << neg2::den << "\n\n";

    // Large values
    using big = std::ratio<1000000, 3>;
    std::cout << "ratio<1000000,3>: " << big::num << "/" << big::den << "\n\n";

    // Unit ratios (identity and zero)
    using one  = std::ratio<1, 1>;
    using zero = std::ratio<0, 1>;
    std::cout << "ratio<1,1>: " << one::num  << "/" << one::den  << "\n";
    std::cout << "ratio<0,1>: " << zero::num << "/" << zero::den << "\n\n";

    // Practical use: defining conversion factors
    using km_to_m  = std::ratio<1000, 1>;    // 1 km = 1000 m
    using mi_to_ft = std::ratio<5280, 1>;    // 1 mile = 5280 feet
    using inch_to_cm = std::ratio<254, 100>; // 1 inch = 2.54 cm

    std::cout << "=== Conversion factors ===\n";
    std::cout << "km->m:   " << km_to_m::num  << "/" << km_to_m::den  << "\n";
    std::cout << "mi->ft:  " << mi_to_ft::num << "/" << mi_to_ft::den << "\n";
    std::cout << "in->cm:  " << inch_to_cm::num << "/"
              << inch_to_cm::den << "\n";

    return 0;
}

// Expected output:
// === Basic ratios ===
// ratio<2,3>: 2/3
// ratio<4,6>: 2/3 (auto-reduced)
// ratio<-5,10>: -1/2
// ratio<7,-14>: -1/2
//
// ratio<1000000,3>: 1000000/3
//
// ratio<1,1>: 1/1
// ratio<0,1>: 0/1
//
// === Conversion factors ===
// km->m:   1000/1
// mi->ft:  5280/1
// in->cm:  127/50
