// CodeNebula - C++20 Example: std::midpoint
// Compile: g++ -std=c++20 -Wall -Wextra -o example midpoint.cpp

#include <cstdint>
#include <iostream>
#include <numeric>

int main() {
    std::cout << "=== std::midpoint for integers ===\n";

    // Basic integer midpoint (rounds toward first argument)
    std::cout << "midpoint(1, 5)   = " << std::midpoint(1, 5) << "\n";
    std::cout << "midpoint(0, 10)  = " << std::midpoint(0, 10) << "\n";
    std::cout << "midpoint(3, 4)   = " << std::midpoint(3, 4) << "\n";   // 3 (rounds to a)
    std::cout << "midpoint(4, 3)   = " << std::midpoint(4, 3) << "\n";   // 4 (rounds to a)

    // Negative values
    std::cout << "midpoint(-5, 5)  = " << std::midpoint(-5, 5) << "\n";
    std::cout << "midpoint(-10, -2)= " << std::midpoint(-10, -2) << "\n";

    // No overflow: safe even near integer limits
    int a = std::numeric_limits<int>::max() - 1;
    int b = std::numeric_limits<int>::max();
    std::cout << "midpoint(MAX-1, MAX) = " << std::midpoint(a, b) << "\n";

    // Works with unsigned types too
    unsigned u1 = 0, u2 = 100;
    std::cout << "midpoint(0u, 100u)   = " << std::midpoint(u1, u2) << "\n";

    std::cout << "\n=== std::midpoint for floating-point ===\n";

    std::cout << "midpoint(1.0, 3.0)   = " << std::midpoint(1.0, 3.0) << "\n";
    std::cout << "midpoint(0.0, 1.0)   = " << std::midpoint(0.0, 1.0) << "\n";
    std::cout << "midpoint(-1.5, 1.5)  = " << std::midpoint(-1.5, 1.5) << "\n";

    // Float precision
    float f1 = 1.0e20f, f2 = 1.0f;
    std::cout << "midpoint(1e20f, 1f)  = " << std::midpoint(f1, f2) << "\n";

    std::cout << "\n=== std::midpoint for pointers ===\n";

    int arr[] = {10, 20, 30, 40, 50, 60, 70};
    int* p1 = &arr[1];
    int* p2 = &arr[5];
    int* mid = std::midpoint(p1, p2);
    std::cout << "Array:   ";
    for (int v : arr) std::cout << v << " ";
    std::cout << "\n";
    std::cout << "p1 -> " << *p1 << ", p2 -> " << *p2 << "\n";
    std::cout << "midpoint(p1, p2) -> " << *mid << "\n";

    std::cout << "\n=== Binary search using midpoint ===\n";

    int sorted[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int target = 23;
    int* lo = sorted;
    int* hi = sorted + 9;
    while (lo <= hi) {
        int* m = std::midpoint(lo, hi);
        if (*m == target) { std::cout << "Found " << target << " at index " << (m - sorted) << "\n"; break; }
        else if (*m < target) lo = m + 1;
        else hi = m - 1;
    }

    return 0;
}
