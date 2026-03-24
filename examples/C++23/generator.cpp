// CodeNebula - C++23 Example: std::generator
// Compile: g++ -std=c++23 -Wall -Wextra -o example generator.cpp
// Note: Requires GCC 14+ / Clang 18+ / MSVC 19.37+

// std::generator<T> is a coroutine-based range type that lazily produces
// values using co_yield. It integrates with range-based for loops and
// the ranges library.

#include <iostream>
#include <generator>
#include <string>
#include <cstdint>

// Simple counting generator
std::generator<int> iota(int start, int end) {
    for (int i = start; i < end; ++i) {
        co_yield i;
    }
}

// Fibonacci sequence (infinite, lazy)
std::generator<std::uint64_t> fibonacci() {
    std::uint64_t a = 0, b = 1;
    while (true) {
        co_yield a;
        auto next = a + b;
        a = b;
        b = next;
    }
}

// String tokenizer generator
std::generator<std::string> split(std::string str, char delim) {
    std::string token;
    for (char c : str) {
        if (c == delim) {
            if (!token.empty()) {
                co_yield token;
                token.clear();
            }
        } else {
            token += c;
        }
    }
    if (!token.empty()) co_yield token;
}

// Filtered range: yield only even numbers
std::generator<int> evens(int limit) {
    for (int i = 0; i <= limit; i += 2) {
        co_yield i;
    }
}

int main() {
    std::cout << "=== std::generator - Lazy Sequences ===" << std::endl;

    std::cout << "iota(1, 6): ";
    for (int val : iota(1, 6)) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    std::cout << "\n=== Fibonacci (first 15) ===" << std::endl;
    int count = 0;
    for (auto val : fibonacci()) {
        std::cout << val << " ";
        if (++count >= 15) break;
    }
    std::cout << std::endl;

    std::cout << "\n=== String splitting ===" << std::endl;
    for (const auto& token : split("Hello,World,C++23,Generator", ',')) {
        std::cout << "  '" << token << "'" << std::endl;
    }

    std::cout << "\n=== Even numbers up to 10 ===" << std::endl;
    for (int val : evens(10)) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}

/*
Expected output:
=== std::generator - Lazy Sequences ===
iota(1, 6): 1 2 3 4 5

=== Fibonacci (first 15) ===
0 1 1 2 3 5 8 13 21 34 55 89 144 233 377

=== String splitting ===
  'Hello'
  'World'
  'C++23'
  'Generator'

=== Even numbers up to 10 ===
0 2 4 6 8 10
*/
