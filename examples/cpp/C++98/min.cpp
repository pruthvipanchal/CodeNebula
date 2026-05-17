// CodeNebula - C++98 Example: min
// Compile: g++ -std=c++98 -Wall -Wextra -o example min.cpp

// std::min returns the smaller of two values. With a custom
// comparator, it can define "smaller" in different ways.

#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>

bool by_abs(int a, int b) {
    return std::abs(a) < std::abs(b);
}

bool shorter(const std::string& a, const std::string& b) {
    return a.size() < b.size();
}

int main() {
    // Basic min of integers
    std::cout << "min(3, 7): " << std::min(3, 7) << std::endl;
    std::cout << "min(10, 2): " << std::min(10, 2) << std::endl;
    std::cout << "min(-5, -3): " << std::min(-5, -3) << std::endl;

    // Equal values -- returns the first argument
    std::cout << "min(4, 4): " << std::min(4, 4) << std::endl;

    // With doubles
    std::cout << "min(3.14, 2.72): " << std::min(3.14, 2.72) << std::endl;

    // Custom comparator: min by absolute value
    std::cout << "min(-10, 3) by abs: "
              << std::min(-10, 3, by_abs) << std::endl;

    // Strings (lexicographic by default)
    std::string a = "banana";
    std::string b = "apple";
    std::cout << "min(banana, apple): " << std::min(a, b) << std::endl;

    // Strings by length
    std::cout << "min by length(banana, apple): "
              << std::min(a, b, shorter) << std::endl;

    return 0;
}

// Expected output:
// min(3, 7): 3
// min(10, 2): 2
// min(-5, -3): -5
// min(4, 4): 4
// min(3.14, 2.72): 2.72
// min(-10, 3) by abs: 3
// min(banana, apple): apple
// min by length(banana, apple): apple
