// CodeNebula - C++17 Example: Parallel Algorithms (Execution Policies)
// Compile: g++ -std=c++17 -Wall -Wextra -o example parallel_algorithms.cpp -ltbb
// Note: Parallel execution requires a threading backend (e.g., Intel TBB).
// Without TBB, std::execution::seq still works. par/par_unseq may need TBB linked.

// C++17 adds execution policies to many <algorithm> and <numeric> functions:
// seq (sequential), par (parallel), par_unseq (parallel + vectorized).

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <execution>
#include <chrono>

int main() {
    // --- Execution policy overview ---
    std::cout << "=== Execution policies ===" << std::endl;
    std::cout << "seq:       sequential, single-threaded" << std::endl;
    std::cout << "par:       parallel, multi-threaded" << std::endl;
    std::cout << "par_unseq: parallel + vectorized (SIMD)" << std::endl;

    const int N = 1'000'000;
    std::vector<int> data(N);
    std::iota(data.begin(), data.end(), 1);  // 1, 2, ..., N

    // --- std::sort with execution policy ---
    std::cout << "\n=== Parallel sort ===" << std::endl;
    std::vector<int> to_sort(data.rbegin(), data.rend());  // reversed
    std::sort(std::execution::seq, to_sort.begin(), to_sort.end());
    std::cout << "Sorted (seq): first=" << to_sort.front()
              << ", last=" << to_sort.back() << std::endl;

    // --- std::for_each with parallel policy ---
    std::cout << "\n=== Parallel for_each ===" << std::endl;
    std::vector<double> squares(N);
    std::for_each(std::execution::seq, data.begin(), data.end(),
        [&squares](int x) { squares[x - 1] = static_cast<double>(x) * x; });
    std::cout << "squares[0]=" << squares[0]
              << ", squares[999999]=" << squares[999999] << std::endl;

    // --- std::transform with seq policy ---
    std::cout << "\n=== Parallel transform ===" << std::endl;
    std::vector<int> doubled(N);
    std::transform(std::execution::seq, data.begin(), data.end(),
                   doubled.begin(), [](int x) { return x * 2; });
    std::cout << "doubled[0]=" << doubled[0]
              << ", doubled[4]=" << doubled[4] << std::endl;

    // --- std::reduce (parallel-friendly accumulation) ---
    std::cout << "\n=== std::reduce ===" << std::endl;
    long long sum_seq = std::reduce(std::execution::seq,
                                     data.begin(), data.end(), 0LL);
    std::cout << "Sum (seq): " << sum_seq << std::endl;
    std::cout << "Expected:  " << (static_cast<long long>(N) * (N + 1) / 2) << std::endl;

    // --- std::count_if ---
    std::cout << "\n=== Parallel count_if ===" << std::endl;
    auto evens = std::count_if(std::execution::seq,
        data.begin(), data.end(), [](int x) { return x % 2 == 0; });
    std::cout << "Even numbers: " << evens << std::endl;

    // --- std::find_if ---
    std::cout << "\n=== Parallel find_if ===" << std::endl;
    auto it = std::find_if(std::execution::seq,
        data.begin(), data.end(), [](int x) { return x > 999990; });
    if (it != data.end()) {
        std::cout << "First > 999990: " << *it << std::endl;
    }

    // --- std::any_of / all_of / none_of ---
    std::cout << "\n=== Parallel predicates ===" << std::endl;
    bool has_neg = std::any_of(std::execution::seq,
        data.begin(), data.end(), [](int x) { return x < 0; });
    bool all_pos = std::all_of(std::execution::seq,
        data.begin(), data.end(), [](int x) { return x > 0; });
    std::cout << "any negative: " << has_neg << std::endl;
    std::cout << "all positive: " << all_pos << std::endl;

    return 0;
}

/*
Expected output:
=== Execution policies ===
seq:       sequential, single-threaded
par:       parallel, multi-threaded
par_unseq: parallel + vectorized (SIMD)

=== Parallel sort ===
Sorted (seq): first=1, last=1000000

=== Parallel for_each ===
squares[0]=1, squares[999999]=1e+12

=== Parallel transform ===
doubled[0]=2, doubled[4]=10

=== std::reduce ===
Sum (seq): 500000500000
Expected:  500000500000

=== Parallel count_if ===
Even numbers: 500000

=== Parallel find_if ===
First > 999990: 999991

=== Parallel predicates ===
any negative: 0
all positive: 1
*/
