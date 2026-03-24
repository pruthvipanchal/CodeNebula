// CodeNebula - C++23 Example: constexpr Improvements
// Compile: g++ -std=c++23 -Wall -Wextra -o example constexpr_improvements.cpp
// Note: Requires GCC 13+ / Clang 17+ / MSVC 19.35+

// C++23 relaxes constexpr further:
//   - constexpr functions can use goto (non-trivial control flow)
//   - constexpr functions can have non-literal type local variables
//     (if not evaluated at compile time)
//   - static and thread_local variables in constexpr functions (with limits)
//   - constexpr casts from void*

#include <iostream>
#include <string>
#include <cmath>
#include <optional>
#include <memory>

// C++23: constexpr unique_ptr (dynamic allocation in constexpr)
constexpr int heap_computation() {
    auto ptr = std::make_unique<int>(42);
    *ptr += 8;
    return *ptr;  // Memory freed before constexpr evaluation ends
}

// C++23: more constexpr math functions (some implementations)
constexpr double constexpr_abs(double x) {
    return x < 0 ? -x : x;
}

// C++23: constexpr optional operations
constexpr std::optional<int> safe_divide(int a, int b) {
    if (b == 0) return std::nullopt;
    return a / b;
}

// C++23: constexpr with more complex control flow
constexpr int collatz_steps(int n) {
    int steps = 0;
    while (n != 1) {
        if (n % 2 == 0)
            n /= 2;
        else
            n = 3 * n + 1;
        ++steps;
    }
    return steps;
}

// constexpr with void* casts (new in C++23)
constexpr int round_trip_cast() {
    int value = 99;
    void* vp = &value;
    int* ip = static_cast<int*>(vp);  // C++23: allowed in constexpr
    return *ip;
}

// constexpr string-like operations
constexpr int count_vowels(const char* s) {
    int count = 0;
    while (*s) {
        char c = *s;
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
            ++count;
        ++s;
    }
    return count;
}

int main() {
    std::cout << "=== constexpr Improvements in C++23 ===" << std::endl;

    constexpr int heap_val = heap_computation();
    std::cout << "constexpr heap computation: " << heap_val << std::endl;

    constexpr auto div_result = safe_divide(42, 5);
    std::cout << "constexpr 42/5 = " << div_result.value() << std::endl;
    constexpr auto div_zero = safe_divide(42, 0);
    std::cout << "constexpr 42/0 has value? " << div_zero.has_value() << std::endl;

    std::cout << "\n=== constexpr complex control flow ===" << std::endl;
    constexpr int steps = collatz_steps(27);
    std::cout << "Collatz steps for 27: " << steps << std::endl;

    std::cout << "\n=== constexpr void* casts ===" << std::endl;
    constexpr int rt = round_trip_cast();
    std::cout << "Round-trip cast result: " << rt << std::endl;

    std::cout << "\n=== constexpr string operations ===" << std::endl;
    constexpr int vowels = count_vowels("Hello C++23 World");
    std::cout << "Vowels in 'Hello C++23 World': " << vowels << std::endl;

    // Verify compile-time evaluation
    static_assert(heap_val == 50);
    static_assert(collatz_steps(1) == 0);
    static_assert(count_vowels("aeiou") == 5);
    std::cout << "\nAll static_asserts passed!" << std::endl;

    return 0;
}

/*
Expected output:
=== constexpr Improvements in C++23 ===
constexpr heap computation: 50
constexpr 42/5 = 8
constexpr 42/0 has value? 0

=== constexpr complex control flow ===
Collatz steps for 27: 111

=== constexpr void* casts ===
Round-trip cast result: 99

=== constexpr string operations ===
Vowels in 'Hello C++23 World': 4

All static_asserts passed!
*/
