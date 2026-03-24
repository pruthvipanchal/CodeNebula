// CodeNebula - C++26 Example: Saturation Arithmetic
// Compile: g++ -std=c++26 -Wall -Wextra -o example saturation_arithmetic.cpp
// Note: Requires C++26 compiler support (GCC 15+ / Clang 19+ expected)

// C++26 introduces saturation arithmetic functions: add_sat, sub_sat,
// mul_sat, div_sat. These clamp results to the type's min/max instead
// of wrapping on overflow -- essential for DSP, graphics, and safety.

#include <iostream>
#include <cstdint>
#include <limits>
#include <algorithm>

// --- C++26 Saturation Arithmetic Syntax ---
//
// #include <numeric>
//
// uint8_t a = 200, b = 100;
// uint8_t sum = std::add_sat(a, b);   // 255 (clamped, not 44)
// uint8_t dif = std::sub_sat(b, a);   // 0   (clamped, not 156)
//
// int8_t x = 100, y = 50;
// int8_t prod = std::mul_sat(x, y);   // 127 (clamped to INT8_MAX)
// int8_t quot = std::div_sat(x, y);   // 2   (normal result fits)

// --- Simulation using C++20 features ---

template<typename T>
T add_sat_sim(T a, T b) {
    if (b > 0 && a > std::numeric_limits<T>::max() - b)
        return std::numeric_limits<T>::max();
    if (b < 0 && a < std::numeric_limits<T>::min() - b)
        return std::numeric_limits<T>::min();
    return a + b;
}

template<typename T>
T sub_sat_sim(T a, T b) {
    if (b < 0 && a > std::numeric_limits<T>::max() + b)
        return std::numeric_limits<T>::max();
    if (b > 0 && a < std::numeric_limits<T>::min() + b)
        return std::numeric_limits<T>::min();
    return a - b;
}

// Specialization for unsigned types
template<>
uint8_t add_sat_sim<uint8_t>(uint8_t a, uint8_t b) {
    unsigned sum = static_cast<unsigned>(a) + b;
    return sum > 255 ? 255 : static_cast<uint8_t>(sum);
}

template<>
uint8_t sub_sat_sim<uint8_t>(uint8_t a, uint8_t b) {
    return b > a ? 0 : static_cast<uint8_t>(a - b);
}

template<typename T>
T mul_sat_sim(T a, T b) {
    using Wide = long long;
    Wide result = static_cast<Wide>(a) * static_cast<Wide>(b);
    if (result > std::numeric_limits<T>::max()) return std::numeric_limits<T>::max();
    if (result < std::numeric_limits<T>::min()) return std::numeric_limits<T>::min();
    return static_cast<T>(result);
}

int main() {
    std::cout << "=== C++26 Saturation Arithmetic (Simulated) ===" << std::endl;

    // Unsigned saturation
    uint8_t a = 200, b = 100;
    std::cout << "uint8_t: 200 + 100 = " << (int)add_sat_sim(a, b)
              << " (saturated at 255)" << std::endl;
    std::cout << "uint8_t: 50 - 100  = " << (int)sub_sat_sim(uint8_t(50), b)
              << " (saturated at 0)" << std::endl;

    // Signed saturation
    int8_t x = 100, y = 50;
    std::cout << "int8_t:  100 + 50  = " << (int)add_sat_sim(x, y)
              << " (saturated at 127)" << std::endl;
    std::cout << "int8_t: -100 - 50  = " << (int)sub_sat_sim(int8_t(-100), y)
              << " (saturated at -128)" << std::endl;

    // Multiplication saturation
    std::cout << "int8_t:  100 * 50  = " << (int)mul_sat_sim(x, y)
              << " (saturated at 127)" << std::endl;

    // Normal (no overflow)
    std::cout << "int8_t:  10 + 20   = " << (int)add_sat_sim(int8_t(10), int8_t(20))
              << " (fits)" << std::endl;

    std::cout << "Saturation arithmetic prevents silent overflow." << std::endl;
    return 0;
}

// Expected output:
// === C++26 Saturation Arithmetic (Simulated) ===
// uint8_t: 200 + 100 = 255 (saturated at 255)
// uint8_t: 50 - 100  = 0 (saturated at 0)
// int8_t:  100 + 50  = 127 (saturated at 127)
// int8_t: -100 - 50  = -128 (saturated at -128)
// int8_t:  100 * 50  = 127 (saturated at 127)
// int8_t:  10 + 20   = 30 (fits)
// Saturation arithmetic prevents silent overflow.
