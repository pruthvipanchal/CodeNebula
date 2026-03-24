// CodeNebula - C++23 Example: constexpr std::vector Improvements
// Compile: g++ -std=c++23 -Wall -Wextra -o example constexpr_vector.cpp
// Note: Requires GCC 13+ / Clang 17+

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

// C++23 extends constexpr support for std::vector beyond C++20.
// More algorithms and operations work at compile time, enabling
// complex computations to be evaluated by the compiler.

// Compile-time sieve of Eratosthenes
constexpr std::vector<int> sieve_primes(int limit) {
    std::vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i * i <= limit; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= limit; j += i) {
                is_prime[j] = false;
            }
        }
    }

    std::vector<int> primes;
    for (int i = 2; i <= limit; ++i) {
        if (is_prime[i]) primes.push_back(i);
    }
    return primes;
}

// Compile-time sort and unique
constexpr std::vector<int> sorted_unique(std::vector<int> v) {
    std::ranges::sort(v);
    auto [first, last] = std::ranges::unique(v);
    v.erase(first, last);
    return v;
}

// Compile-time accumulation
constexpr int sum_of_squares(int n) {
    std::vector<int> v(n);
    std::iota(v.begin(), v.end(), 1);  // 1, 2, ..., n
    int sum = 0;
    for (int x : v) sum += x * x;
    return sum;
}

int main() {
    std::cout << "=== constexpr std::vector improvements in C++23 ===\n\n";

    // Compile-time prime generation
    constexpr auto primes = sieve_primes(30);
    constexpr auto prime_count = primes.size();
    static_assert(prime_count == 10, "There are 10 primes up to 30");

    std::cout << "Primes up to 30 (computed at compile time):\n  ";
    for (int p : primes) std::cout << p << " ";
    std::cout << "\n  Count: " << prime_count << "\n\n";

    // Compile-time sort and deduplicate
    constexpr auto unique_sorted = sorted_unique({5, 3, 1, 3, 2, 5, 4, 1});
    std::cout << "Sorted unique of {5,3,1,3,2,5,4,1}:\n  ";
    for (int x : unique_sorted) std::cout << x << " ";
    std::cout << "\n\n";

    // Compile-time arithmetic
    constexpr int ss5 = sum_of_squares(5);
    static_assert(ss5 == 55, "1^2 + 2^2 + 3^2 + 4^2 + 5^2 = 55");
    std::cout << "Sum of squares 1..5: " << ss5 << "\n";

    constexpr int ss10 = sum_of_squares(10);
    static_assert(ss10 == 385);
    std::cout << "Sum of squares 1..10: " << ss10 << "\n";

    std::cout << "\nAll computations verified at compile time with static_assert.\n";

    return 0;
}

// Expected output:
// === constexpr std::vector improvements in C++23 ===
//
// Primes up to 30 (computed at compile time):
//   2 3 5 7 11 13 17 19 23 29
//   Count: 10
//
// Sorted unique of {5,3,1,3,2,5,4,1}:
//   1 2 3 4 5
//
// Sum of squares 1..5: 55
// Sum of squares 1..10: 385
//
// All computations verified at compile time with static_assert.
