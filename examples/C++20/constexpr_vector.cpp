// CodeNebula - C++20 Example: Constexpr std::vector
// Compile: g++ -std=c++20 -Wall -Wextra -o example constexpr_vector.cpp

// Demonstrates constexpr std::vector in C++20: dynamic containers at compile
// time using transient allocation. Vectors must not persist past constexpr.

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <array>

// ------------------------------------------------------------------
// 1. constexpr vector sum
// ------------------------------------------------------------------
constexpr int vector_sum(int n) {
    std::vector<int> v;
    for (int i = 1; i <= n; ++i)
        v.push_back(i);
    return std::accumulate(v.begin(), v.end(), 0);
}

// ------------------------------------------------------------------
// 2. constexpr vector sorting
// ------------------------------------------------------------------
constexpr auto sort_and_extract() {
    std::vector<int> v = {9, 3, 7, 1, 5, 2, 8, 4, 6};
    std::sort(v.begin(), v.end());

    struct Result {
        int data[9]{};
        int size = 0;
    };
    Result r;
    r.size = static_cast<int>(v.size());
    for (int i = 0; i < r.size; ++i)
        r.data[i] = v[i];
    return r;
}

// ------------------------------------------------------------------
// 3. constexpr Sieve of Eratosthenes using vector<bool>
// ------------------------------------------------------------------
constexpr int count_primes(int limit) {
    std::vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= limit; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= limit; j += i)
                is_prime[j] = false;
        }
    }
    int count = 0;
    for (int i = 0; i <= limit; ++i)
        if (is_prime[i]) ++count;
    return count;
}

// ------------------------------------------------------------------
// 4. constexpr vector with remove/erase
// ------------------------------------------------------------------
constexpr int count_after_filter(int max, int divisor) {
    std::vector<int> v;
    for (int i = 1; i <= max; ++i)
        v.push_back(i);

    // Remove multiples of divisor
    auto it = std::remove_if(v.begin(), v.end(),
        [divisor](int x) { return x % divisor == 0; });
    v.erase(it, v.end());

    return static_cast<int>(v.size());
}

// ------------------------------------------------------------------
// 5. constexpr vector of vectors (nested)
// ------------------------------------------------------------------
constexpr int nested_vector_sum() {
    std::vector<std::vector<int>> matrix;
    for (int i = 0; i < 3; ++i) {
        std::vector<int> row;
        for (int j = 0; j < 3; ++j)
            row.push_back(i * 3 + j + 1);
        matrix.push_back(std::move(row));
    }

    int total = 0;
    for (const auto& row : matrix)
        for (int val : row)
            total += val;
    return total;
}

// ------------------------------------------------------------------
// 6. constexpr unique elements
// ------------------------------------------------------------------
constexpr int count_unique() {
    std::vector<int> v = {1, 3, 2, 3, 1, 4, 2, 5, 4, 5};
    std::sort(v.begin(), v.end());
    auto it = std::unique(v.begin(), v.end());
    v.erase(it, v.end());
    return static_cast<int>(v.size());
}

// ------------------------------------------------------------------
// 7. constexpr min/max from vector
// ------------------------------------------------------------------
constexpr auto find_stats() {
    std::vector<int> v = {42, 17, 93, 8, 55, 31, 76};
    struct Stats {
        int min_val, max_val, sum;
    };
    auto [mn, mx] = std::minmax_element(v.begin(), v.end());
    int s = std::accumulate(v.begin(), v.end(), 0);
    return Stats{*mn, *mx, s};
}

int main()
{
    std::cout << "=== constexpr Vector Sum ===" << std::endl;
    constexpr int s10 = vector_sum(10);
    constexpr int s100 = vector_sum(100);
    std::cout << "  sum(1..10) = " << s10 << std::endl;
    std::cout << "  sum(1..100) = " << s100 << std::endl;
    static_assert(s10 == 55);
    static_assert(s100 == 5050);

    std::cout << "\n=== constexpr Vector Sort ===" << std::endl;
    constexpr auto sorted = sort_and_extract();
    std::cout << "  Sorted:";
    for (int i = 0; i < sorted.size; ++i)
        std::cout << " " << sorted.data[i];
    std::cout << std::endl;

    std::cout << "\n=== constexpr Sieve of Eratosthenes ===" << std::endl;
    constexpr int p100 = count_primes(100);
    constexpr int p1000 = count_primes(1000);
    std::cout << "  Primes up to 100: " << p100 << std::endl;
    std::cout << "  Primes up to 1000: " << p1000 << std::endl;
    static_assert(p100 == 25);

    std::cout << "\n=== constexpr Filter ===" << std::endl;
    constexpr int remaining = count_after_filter(20, 3);
    std::cout << "  1..20 without multiples of 3: " << remaining << std::endl;

    std::cout << "\n=== constexpr Nested Vectors ===" << std::endl;
    constexpr int mat_sum = nested_vector_sum();
    std::cout << "  3x3 matrix sum (1..9): " << mat_sum << std::endl;
    static_assert(mat_sum == 45);

    std::cout << "\n=== constexpr Unique Count ===" << std::endl;
    constexpr int uniq = count_unique();
    std::cout << "  Unique values in {1,3,2,3,1,4,2,5,4,5}: " << uniq << std::endl;
    static_assert(uniq == 5);

    std::cout << "\n=== constexpr Min/Max/Sum ===" << std::endl;
    constexpr auto stats = find_stats();
    std::cout << "  Min: " << stats.min_val << std::endl;
    std::cout << "  Max: " << stats.max_val << std::endl;
    std::cout << "  Sum: " << stats.sum << std::endl;

    std::cout << "\n  All static_asserts passed" << std::endl;

    return 0;
}

/*
Expected output:

=== constexpr Vector Sum ===
  sum(1..10) = 55
  sum(1..100) = 5050

=== constexpr Vector Sort ===
  Sorted: 1 2 3 4 5 6 7 8 9

=== constexpr Sieve of Eratosthenes ===
  Primes up to 100: 25
  Primes up to 1000: 168

=== constexpr Filter ===
  1..20 without multiples of 3: 14

=== constexpr Nested Vectors ===
  3x3 matrix sum (1..9): 45

=== constexpr Unique Count ===
  Unique values in {1,3,2,3,1,4,2,5,4,5}: 5

=== constexpr Min/Max/Sum ===
  Min: 8
  Max: 93
  Sum: 322

  All static_asserts passed
*/
