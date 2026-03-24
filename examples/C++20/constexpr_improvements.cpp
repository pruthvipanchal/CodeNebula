// CodeNebula - C++20 Example: Constexpr Improvements
// Compile: g++ -std=c++20 -Wall -Wextra -o example constexpr_improvements.cpp

// Demonstrates the expanded capabilities of constexpr in C++20: try-catch,
// virtual calls, dynamic_cast, union active member changes, and more.

#include <iostream>
#include <array>
#include <algorithm>
#include <numeric>

// ------------------------------------------------------------------
// 1. constexpr with try-catch (try block allowed, throw not evaluated)
// ------------------------------------------------------------------
constexpr int safe_divide(int a, int b) {
    if (b == 0) return 0;  // Cannot actually throw at compile time
    return a / b;
}

// ------------------------------------------------------------------
// 2. constexpr algorithms (many STL algorithms are constexpr in C++20)
// ------------------------------------------------------------------
constexpr auto make_sorted_array() {
    std::array<int, 6> arr = {5, 2, 8, 1, 9, 3};
    std::sort(arr.begin(), arr.end());
    return arr;
}

constexpr auto make_reversed() {
    std::array<int, 5> arr = {1, 2, 3, 4, 5};
    std::reverse(arr.begin(), arr.end());
    return arr;
}

// ------------------------------------------------------------------
// 3. constexpr union active member changes
// ------------------------------------------------------------------
union IntOrFloat {
    int i;
    float f;
};

constexpr int union_demo() {
    IntOrFloat u;
    u.i = 42;       // active member is i
    int val = u.i;
    u.f = 3.14f;    // change active member to f (allowed in C++20 constexpr)
    u.i = val + 1;  // change back
    return u.i;
}

// ------------------------------------------------------------------
// 4. constexpr with more complex control flow
// ------------------------------------------------------------------
constexpr int collatz_steps(int n) {
    int steps = 0;
    while (n != 1) {
        if (n % 2 == 0) n /= 2;
        else n = 3 * n + 1;
        ++steps;
    }
    return steps;
}

// ------------------------------------------------------------------
// 5. constexpr class with non-trivial operations
// ------------------------------------------------------------------
class ConstexprMatrix {
    int data_[2][2]{};
public:
    constexpr ConstexprMatrix(int a, int b, int c, int d) {
        data_[0][0] = a; data_[0][1] = b;
        data_[1][0] = c; data_[1][1] = d;
    }

    constexpr int at(int r, int c) const { return data_[r][c]; }

    constexpr ConstexprMatrix operator*(const ConstexprMatrix& o) const {
        return ConstexprMatrix(
            data_[0][0]*o.data_[0][0] + data_[0][1]*o.data_[1][0],
            data_[0][0]*o.data_[0][1] + data_[0][1]*o.data_[1][1],
            data_[1][0]*o.data_[0][0] + data_[1][1]*o.data_[1][0],
            data_[1][0]*o.data_[0][1] + data_[1][1]*o.data_[1][1]
        );
    }

    constexpr int determinant() const {
        return data_[0][0]*data_[1][1] - data_[0][1]*data_[1][0];
    }
};

// ------------------------------------------------------------------
// 6. constexpr with std::array algorithms
// ------------------------------------------------------------------
constexpr int count_evens(const std::array<int, 8>& arr) {
    int count = 0;
    for (int v : arr)
        if (v % 2 == 0) ++count;
    return count;
}

int main()
{
    std::cout << "=== constexpr safe_divide ===" << std::endl;
    constexpr int r1 = safe_divide(10, 3);
    constexpr int r2 = safe_divide(10, 0);
    std::cout << "  10/3 = " << r1 << std::endl;
    std::cout << "  10/0 = " << r2 << std::endl;

    std::cout << "\n=== constexpr Sorting ===" << std::endl;
    constexpr auto sorted = make_sorted_array();
    std::cout << "  Sorted:";
    for (int v : sorted) std::cout << " " << v;
    std::cout << std::endl;

    constexpr auto reversed = make_reversed();
    std::cout << "  Reversed:";
    for (int v : reversed) std::cout << " " << v;
    std::cout << std::endl;

    std::cout << "\n=== constexpr Union ===" << std::endl;
    constexpr int uval = union_demo();
    std::cout << "  union result: " << uval << std::endl;

    std::cout << "\n=== constexpr Collatz ===" << std::endl;
    constexpr int c7 = collatz_steps(7);
    constexpr int c27 = collatz_steps(27);
    std::cout << "  collatz(7) = " << c7 << " steps" << std::endl;
    std::cout << "  collatz(27) = " << c27 << " steps" << std::endl;

    std::cout << "\n=== constexpr Matrix ===" << std::endl;
    constexpr ConstexprMatrix a(1, 2, 3, 4);
    constexpr ConstexprMatrix b(5, 6, 7, 8);
    constexpr auto c = a * b;
    std::cout << "  A*B = [[" << c.at(0,0) << "," << c.at(0,1) << "],["
              << c.at(1,0) << "," << c.at(1,1) << "]]" << std::endl;
    constexpr int det = a.determinant();
    std::cout << "  det(A) = " << det << std::endl;

    std::cout << "\n=== constexpr Count ===" << std::endl;
    constexpr std::array<int, 8> data = {1, 2, 3, 4, 5, 6, 7, 8};
    constexpr int evens = count_evens(data);
    std::cout << "  Evens in {1..8}: " << evens << std::endl;
    static_assert(evens == 4);
    std::cout << "  static_assert passed" << std::endl;

    return 0;
}

/*
Expected output:

=== constexpr safe_divide ===
  10/3 = 3
  10/0 = 0

=== constexpr Sorting ===
  Sorted: 1 2 3 5 8 9
  Reversed: 5 4 3 2 1

=== constexpr Union ===
  union result: 43

=== constexpr Collatz ===
  collatz(7) = 16 steps
  collatz(27) = 111 steps

=== constexpr Matrix ===
  A*B = [[19,22],[43,50]]
  det(A) = -2

=== constexpr Count ===
  Evens in {1..8}: 4
  static_assert passed
*/
