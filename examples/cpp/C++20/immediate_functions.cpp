// CodeNebula - C++20 Example: Immediate Functions (consteval)
// Compile: g++ -std=c++20 -Wall -Wextra -o example immediate_functions.cpp

// consteval functions MUST be evaluated at compile time.
// Unlike constexpr (which CAN run at compile time), consteval
// guarantees compile-time evaluation — calling one at runtime is an error.

#include <iostream>
#include <array>

// A consteval function: always evaluated at compile time
consteval int square(int n) {
    return n * n;
}

// consteval can enforce compile-time string length
consteval int string_length(const char* s) {
    int len = 0;
    while (s[len] != '\0') ++len;
    return len;
}

// consteval factorial — recursion works just fine
consteval long long factorial(int n) {
    long long result = 1;
    for (int i = 2; i <= n; ++i)
        result *= i;
    return result;
}

// consteval used to build a lookup table at compile time
consteval std::array<int, 10> make_squares_table() {
    std::array<int, 10> table{};
    for (int i = 0; i < 10; ++i)
        table[i] = i * i;
    return table;
}

int main() {
    // All of these are computed at compile time
    constexpr int val = square(7);
    std::cout << "square(7) = " << val << "\n";

    constexpr int len = string_length("Hello, C++20!");
    std::cout << "string_length(\"Hello, C++20!\") = " << len << "\n";

    constexpr long long fact10 = factorial(10);
    std::cout << "factorial(10) = " << fact10 << "\n";

    // Compile-time lookup table
    constexpr auto table = make_squares_table();
    std::cout << "Squares table: ";
    for (int i = 0; i < 10; ++i)
        std::cout << table[i] << " ";
    std::cout << "\n";

    // This would NOT compile — consteval requires a compile-time argument:
    // int x = 5;
    // int bad = square(x);  // ERROR: x is not a constant expression

    // But this works because n is constexpr
    constexpr int n = 5;
    constexpr int good = square(n);
    std::cout << "square(5) = " << good << "\n";

    return 0;
}

// Expected output:
// square(7) = 49
// string_length("Hello, C++20!") = 13
// factorial(10) = 3628800
// Squares table: 0 1 4 9 16 25 36 49 64 81
// square(5) = 25
