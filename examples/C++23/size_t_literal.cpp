// CodeNebula - C++23 Example: size_t Literal Suffix
// Compile: g++ -std=c++23 -Wall -Wextra -o example size_t_literal.cpp
// Note: Requires GCC 13+ / Clang 15+ / MSVC 19.34+

// C++23 introduces the 'uz' and 'zu' literal suffixes for std::size_t.
// This eliminates signed/unsigned comparison warnings and awkward casts.

#include <iostream>
#include <vector>
#include <type_traits>

int main() {
    std::cout << "=== size_t Literal Suffix (uz/zu) ===" << std::endl;

    // The new literal suffix
    auto a = 42uz;   // std::size_t
    auto b = 100zu;  // std::size_t (zu is also valid)

    std::cout << "42uz  = " << a << " (size_t: "
              << std::is_same_v<decltype(a), std::size_t> << ")" << std::endl;
    std::cout << "100zu = " << b << " (size_t: "
              << std::is_same_v<decltype(b), std::size_t> << ")" << std::endl;

    // Before C++23: signed/unsigned mismatch warnings
    std::cout << "\n=== Avoiding signed/unsigned warnings ===" << std::endl;
    std::vector<int> vec = {10, 20, 30, 40, 50};

    // OLD way (warning: comparing int with size_t)
    // for (int i = 0; i < vec.size(); ++i) { ... }

    // C++23 way: clean, no warnings
    for (auto i = 0uz; i < vec.size(); ++i) {
        std::cout << "  vec[" << i << "] = " << vec[i] << std::endl;
    }

    // Useful in expressions
    std::cout << "\n=== Arithmetic with size_t literals ===" << std::endl;
    auto half = vec.size() / 2uz;
    auto last = vec.size() - 1uz;
    std::cout << "Vector size:   " << vec.size() << std::endl;
    std::cout << "Half index:    " << half << std::endl;
    std::cout << "Last index:    " << last << std::endl;

    // Comparison of literal types
    std::cout << "\n=== Type verification ===" << std::endl;
    auto x = 0uz;
    std::cout << "0uz is size_t:          "
              << std::is_same_v<decltype(x), std::size_t> << std::endl;
    std::cout << "0uz is unsigned:        "
              << std::is_unsigned_v<decltype(x)> << std::endl;

    // Also: 'z' suffix for signed std::ptrdiff_t / std::ssize_t
    auto signed_val = 42z;  // signed counterpart (ptrdiff_t)
    std::cout << "42z  is signed:         "
              << std::is_signed_v<decltype(signed_val)> << std::endl;

    return 0;
}

/*
Expected output:
=== size_t Literal Suffix (uz/zu) ===
42uz  = 42 (size_t: 1)
100zu = 100 (size_t: 1)

=== Avoiding signed/unsigned warnings ===
  vec[0] = 10
  vec[1] = 20
  vec[2] = 30
  vec[3] = 40
  vec[4] = 50

=== Arithmetic with size_t literals ===
Vector size:   5
Half index:    2
Last index:    4

=== Type verification ===
0uz is size_t:          1
0uz is unsigned:        1
42z  is signed:         1
*/
