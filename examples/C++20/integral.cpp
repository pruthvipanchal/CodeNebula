// CodeNebula - C++20 Example: std::integral Concept
// Compile: g++ -std=c++20 -Wall -Wextra -o example integral.cpp

// std::integral is satisfied by any type for which std::is_integral_v
// is true: bool, char, int, long, short, and their signed/unsigned variants.

#include <concepts>
#include <iostream>

// Function that only accepts integral types
template <std::integral T>
T safe_add(T a, T b) {
    std::cout << "Adding integral values: " << a << " + " << b << "\n";
    return a + b;
}

// Bit counting for integral types only
template <std::integral T>
int count_set_bits(T value) {
    int count = 0;
    auto v = static_cast<std::make_unsigned_t<T>>(value);
    while (v) {
        count += v & 1;
        v >>= 1;
    }
    return count;
}

// Check if a type is integral at compile time
template <typename T>
void report_integral(const char* name) {
    std::cout << name << " is integral: " << std::integral<T> << "\n";
}

int main() {
    // Use with various integral types
    auto sum_int = safe_add(10, 20);
    std::cout << "Result: " << sum_int << "\n";

    auto sum_long = safe_add(100L, 200L);
    std::cout << "Result: " << sum_long << "\n";

    // safe_add(1.0, 2.0);  // Compile error: double is not integral

    // Bit counting
    std::cout << "Set bits in 255: " << count_set_bits(255) << "\n";
    std::cout << "Set bits in 7: " << count_set_bits(7) << "\n";

    // Type checks
    std::cout << "\nType checks:\n";
    report_integral<int>("int");
    report_integral<char>("char");
    report_integral<bool>("bool");
    report_integral<unsigned long>("unsigned long");
    report_integral<double>("double");
    report_integral<float>("float");

    return 0;
}

// Expected output:
// Adding integral values: 10 + 20
// Result: 30
// Adding integral values: 100 + 200
// Result: 300
// Set bits in 255: 8
// Set bits in 7: 3
//
// Type checks:
// int is integral: 1
// char is integral: 1
// bool is integral: 1
// unsigned long is integral: 1
// double is integral: 0
// float is integral: 0
