// CodeNebula - C++17 Example: std::reduce
// Compile: g++ -std=c++17 -Wall -Wextra -o example reduce.cpp

// Demonstrates std::reduce, a parallel-friendly alternative to std::accumulate.
// Unlike accumulate (which is strictly left-to-right), reduce allows the
// operation to be applied in any order, enabling parallel execution.
// The operation must be associative and commutative for correct results.

#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <functional>

int main()
{
    // ------------------------------------------------------------------
    // 1. Basic sum (like accumulate, but parallelizable)
    // ------------------------------------------------------------------
    std::cout << "=== basic sum ===" << std::endl;
    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    int sum = std::reduce(nums.begin(), nums.end());  // default: 0 + addition
    std::cout << "  reduce(1..10) = " << sum << std::endl;

    // ------------------------------------------------------------------
    // 2. Sum with explicit initial value
    // ------------------------------------------------------------------
    std::cout << "\n=== sum with init ===" << std::endl;
    int sum_from_100 = std::reduce(nums.begin(), nums.end(), 100);
    std::cout << "  reduce(1..10, init=100) = " << sum_from_100 << std::endl;

    // ------------------------------------------------------------------
    // 3. Product using custom operation
    // ------------------------------------------------------------------
    std::cout << "\n=== product ===" << std::endl;
    std::vector<int> factors = {1, 2, 3, 4, 5};
    int product = std::reduce(factors.begin(), factors.end(), 1, std::multiplies<>{});
    std::cout << "  reduce(1..5, init=1, multiply) = " << product << std::endl;

    // ------------------------------------------------------------------
    // 4. Max element via reduce
    // ------------------------------------------------------------------
    std::cout << "\n=== max element ===" << std::endl;
    std::vector<int> data = {42, 17, 93, 5, 68, 31};
    int max_val = std::reduce(data.begin(), data.end(), data.front(),
        [](int a, int b) { return a > b ? a : b; });
    std::cout << "  max of {42,17,93,5,68,31} = " << max_val << std::endl;

    // ------------------------------------------------------------------
    // 5. Sum of doubles (floating-point reduction)
    // ------------------------------------------------------------------
    std::cout << "\n=== floating-point sum ===" << std::endl;
    std::vector<double> prices = {19.99, 5.49, 12.00, 3.75, 8.25};
    double total = std::reduce(prices.begin(), prices.end(), 0.0);
    std::cout << "  total price = " << total << std::endl;

    // ------------------------------------------------------------------
    // 6. Comparison: reduce vs accumulate
    // ------------------------------------------------------------------
    std::cout << "\n=== reduce vs accumulate ===" << std::endl;
    // For associative+commutative ops, results match
    int acc_sum = std::accumulate(nums.begin(), nums.end(), 0);
    int red_sum = std::reduce(nums.begin(), nums.end(), 0);
    std::cout << "  accumulate: " << acc_sum << std::endl;
    std::cout << "  reduce    : " << red_sum << std::endl;
    std::cout << "  equal     : " << std::boolalpha << (acc_sum == red_sum) << std::endl;

    // ------------------------------------------------------------------
    // 7. Counting even numbers via reduce
    // ------------------------------------------------------------------
    std::cout << "\n=== count evens via reduce ===" << std::endl;
    std::vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int even_count = std::reduce(values.begin(), values.end(), 0,
        [](int count, int val) { return count + (val % 2 == 0 ? 1 : 0); });
    // Note: this only works correctly with sequential execution since
    // the lambda is not commutative. For parallel, use transform_reduce.
    std::cout << "  even numbers in 1..10: " << even_count << std::endl;

    return 0;
}

/*
Expected output:

=== basic sum ===
  reduce(1..10) = 55

=== sum with init ===
  reduce(1..10, init=100) = 155

=== product ===
  reduce(1..5, init=1, multiply) = 120

=== max element ===
  max of {42,17,93,5,68,31} = 93

=== floating-point sum ===
  total price = 49.48

=== reduce vs accumulate ===
  accumulate: 55
  reduce    : 55
  equal     : true

=== count evens via reduce ===
  even numbers in 1..10: 5
*/
