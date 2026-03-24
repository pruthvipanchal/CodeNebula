// CodeNebula - C++23 Example: [[assume]] Attribute
// Compile: g++ -std=c++23 -Wall -Wextra -o example assume_attribute.cpp
// Note: Requires GCC 13+ / Clang 17+ / MSVC 19.35+

// [[assume(expr)]] tells the compiler that 'expr' is true at that point.
// The compiler may use this for optimization. The expression is never evaluated.

#include <iostream>

// The compiler can optimize division knowing x > 0
int fast_divide(int x, int y) {
    [[assume(y > 0)]];
    [[assume(x >= 0)]];
    // Compiler may omit checks for negative values / division by zero
    return x / y;
}

// Assume can help with loop optimization
void process_array(int* data, int size) {
    [[assume(size > 0)]];
    [[assume(size % 4 == 0)]];  // Hint: size is always a multiple of 4

    // Compiler can vectorize this loop more aggressively
    for (int i = 0; i < size; ++i) {
        data[i] *= 2;
    }
}

// Demonstrate with enum-like constraints
enum class Color { Red = 0, Green = 1, Blue = 2 };

const char* color_name(Color c) {
    [[assume(static_cast<int>(c) >= 0 && static_cast<int>(c) <= 2)]];
    switch (c) {
        case Color::Red:   return "Red";
        case Color::Green: return "Green";
        case Color::Blue:  return "Blue";
    }
    return "Unknown";  // Compiler may remove this as unreachable
}

int main() {
    std::cout << "=== [[assume]] Attribute ===" << std::endl;

    std::cout << "fast_divide(100, 7) = " << fast_divide(100, 7) << std::endl;
    std::cout << "fast_divide(42, 6)  = " << fast_divide(42, 6) << std::endl;

    std::cout << "\n=== Array processing with assume ===" << std::endl;
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    process_array(arr, 8);
    std::cout << "After doubling: ";
    for (int v : arr) std::cout << v << " ";
    std::cout << std::endl;

    std::cout << "\n=== Enum with assume ===" << std::endl;
    std::cout << "Color(0) = " << color_name(Color::Red) << std::endl;
    std::cout << "Color(1) = " << color_name(Color::Green) << std::endl;
    std::cout << "Color(2) = " << color_name(Color::Blue) << std::endl;

    // Note: [[assume]] is purely an optimization hint.
    // Violating the assumption is undefined behavior.
    std::cout << "\nNote: [[assume]] is UB if the condition is false!" << std::endl;

    return 0;
}

/*
Expected output:
=== [[assume]] Attribute ===
fast_divide(100, 7) = 14
fast_divide(42, 6)  = 7

=== Array processing with assume ===
After doubling: 2 4 6 8 10 12 14 16

=== Enum with assume ===
Color(0) = Red
Color(1) = Green
Color(2) = Blue

Note: [[assume]] is UB if the condition is false!
*/
