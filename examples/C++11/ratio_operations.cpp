// CodeNebula - C++11 Example: Ratio Operations
// Compile: g++ -std=c++11 -Wall -Wextra -o example ratio_operations.cpp

// Demonstrates compile-time ratio arithmetic (ratio_add, ratio_subtract,
// ratio_multiply, ratio_divide) and comparisons (ratio_equal, ratio_less, etc.).

#include <iostream>
#include <ratio>

int main() {
    using one_third = std::ratio<1, 3>;
    using one_half  = std::ratio<1, 2>;

    // Arithmetic operations — all computed at compile time
    using sum  = std::ratio_add<one_third, one_half>;
    using diff = std::ratio_subtract<one_half, one_third>;
    using prod = std::ratio_multiply<one_third, one_half>;
    using quot = std::ratio_divide<one_third, one_half>;

    std::cout << "=== Arithmetic ===\n";
    std::cout << "1/3 + 1/2 = " << sum::num  << "/" << sum::den  << "\n";
    std::cout << "1/2 - 1/3 = " << diff::num << "/" << diff::den << "\n";
    std::cout << "1/3 * 1/2 = " << prod::num << "/" << prod::den << "\n";
    std::cout << "1/3 / 1/2 = " << quot::num << "/" << quot::den << "\n\n";

    // Chained operations: (2/3 + 1/4) * 3/5
    using step1 = std::ratio_add<std::ratio<2,3>, std::ratio<1,4>>;
    using result = std::ratio_multiply<step1, std::ratio<3,5>>;
    std::cout << "(2/3 + 1/4) * 3/5 = " << result::num << "/"
              << result::den << "\n\n";

    // Comparison predicates (compile-time boolean values)
    std::cout << "=== Comparisons ===\n";
    std::cout << std::boolalpha;
    std::cout << "1/3 == 2/6: " << std::ratio_equal<
        std::ratio<1,3>, std::ratio<2,6>>::value << "\n";
    std::cout << "1/3 != 1/2: " << std::ratio_not_equal<
        one_third, one_half>::value << "\n";
    std::cout << "1/3 <  1/2: " << std::ratio_less<
        one_third, one_half>::value << "\n";
    std::cout << "1/2 <= 1/2: " << std::ratio_less_equal<
        one_half, one_half>::value << "\n";
    std::cout << "1/2 >  1/3: " << std::ratio_greater<
        one_half, one_third>::value << "\n";
    std::cout << "1/3 >= 1/2: " << std::ratio_greater_equal<
        one_third, one_half>::value << "\n";

    return 0;
}

// Expected output:
// === Arithmetic ===
// 1/3 + 1/2 = 5/6
// 1/2 - 1/3 = 1/6
// 1/3 * 1/2 = 1/6
// 1/3 / 1/2 = 2/3
//
// (2/3 + 1/4) * 3/5 = 11/20
//
// === Comparisons ===
// 1/3 == 2/6: true
// 1/3 != 1/2: true
// 1/3 <  1/2: true
// 1/2 <= 1/2: true
// 1/2 >  1/3: true
// 1/3 >= 1/2: false
