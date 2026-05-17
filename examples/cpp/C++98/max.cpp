// CodeNebula - C++98 Example: max
// Compile: g++ -std=c++98 -Wall -Wextra -o example max.cpp

// std::max returns the larger of two values. With a custom
// comparator, it can define "larger" in different ways.

#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>

bool by_abs(int a, int b) {
    return std::abs(a) < std::abs(b);
}

int main() {
    // Basic max of integers
    std::cout << "max(3, 7): " << std::max(3, 7) << std::endl;
    std::cout << "max(10, 2): " << std::max(10, 2) << std::endl;
    std::cout << "max(-5, -3): " << std::max(-5, -3) << std::endl;

    // Equal values -- returns the first argument
    std::cout << "max(4, 4): " << std::max(4, 4) << std::endl;

    // With doubles
    std::cout << "max(3.14, 2.72): " << std::max(3.14, 2.72) << std::endl;

    // Custom comparator: max by absolute value
    std::cout << "max(-10, 3) by abs: "
              << std::max(-10, 3, by_abs) << std::endl;

    // Strings (lexicographic by default)
    std::string a = "banana";
    std::string b = "apple";
    std::cout << "max(banana, apple): " << std::max(a, b) << std::endl;

    // Practical use: clamping a value
    int value = 150;
    int lo = 0;
    int hi = 100;
    int clamped = std::min(std::max(value, lo), hi);
    std::cout << "Clamp 150 to [0,100]: " << clamped << std::endl;

    return 0;
}

// Expected output:
// max(3, 7): 7
// max(10, 2): 10
// max(-5, -3): -3
// max(4, 4): 4
// max(3.14, 2.72): 3.14
// max(-10, 3) by abs: -10
// max(banana, apple): banana
// Clamp 150 to [0,100]: 100
