// CodeNebula - C++23 Example: Static operator[]
// Compile: g++ -std=c++23 -Wall -Wextra -o example static_operator_subscript.cpp
// Note: Requires GCC 13+ / Clang 16+ / MSVC 19.34+

// C++23 allows operator[] to be declared static, similar to static operator().
// Useful for stateless index-mapping objects and compile-time accessors.

#include <iostream>
#include <array>
#include <cmath>

// Stateless lookup table accessor
struct FibTable {
    static constexpr std::array<int, 10> table = {0,1,1,2,3,5,8,13,21,34};

    static int operator[](std::size_t i) {
        return (i < table.size()) ? table[i] : -1;
    }
};

// Stateless mathematical mapping: maps index to computed value
struct SquareMap {
    static int operator[](int i) {
        return i * i;
    }
};

// Stateless string table
struct DayName {
    static constexpr const char* days[] = {
        "Sunday", "Monday", "Tuesday", "Wednesday",
        "Thursday", "Friday", "Saturday"
    };

    static const char* operator[](int i) {
        return (i >= 0 && i < 7) ? days[i] : "Invalid";
    }
};

// Combining static operator[] with multidimensional subscript (C++23)
struct IdentityMatrix {
    static int operator[](int i, int j) {
        return (i == j) ? 1 : 0;
    }
};

int main() {
    std::cout << "=== Static operator[] ===" << std::endl;

    std::cout << "Fibonacci lookup:" << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << "  fib[" << i << "] = " << FibTable{}[i] << std::endl;
    }

    std::cout << "\n=== Stateless math mapping ===" << std::endl;
    for (int i = 1; i <= 5; ++i) {
        std::cout << "  square[" << i << "] = " << SquareMap{}[i] << std::endl;
    }

    std::cout << "\n=== Day name lookup ===" << std::endl;
    std::cout << "  day[0] = " << DayName{}[0] << std::endl;
    std::cout << "  day[4] = " << DayName{}[4] << std::endl;

    std::cout << "\n=== Static multidim subscript (identity matrix) ===" << std::endl;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j)
            std::cout << IdentityMatrix{}[i, j] << " ";
        std::cout << std::endl;
    }

    return 0;
}

/*
Expected output:
=== Static operator[] ===
Fibonacci lookup:
  fib[0] = 0
  fib[1] = 1
  fib[2] = 1
  fib[3] = 2
  fib[4] = 3
  fib[5] = 5
  fib[6] = 8
  fib[7] = 13
  fib[8] = 21
  fib[9] = 34

=== Stateless math mapping ===
  square[1] = 1
  square[2] = 4
  square[3] = 9
  square[4] = 16
  square[5] = 25

=== Day name lookup ===
  day[0] = Sunday
  day[4] = Thursday

=== Static multidim subscript (identity matrix) ===
1 0 0
0 1 0
0 0 1
*/
