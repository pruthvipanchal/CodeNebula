// CodeNebula - C++17 Example: std::pmr::monotonic_buffer_resource
// Compile: g++ -std=c++17 -Wall -Wextra -o example monotonic_buffer_resource.cpp

// Demonstrates std::pmr::monotonic_buffer_resource, a fast memory resource
// that allocates by bumping a pointer forward. It never reuses freed memory
// until the entire resource is destroyed or release() is called. Ideal for
// short-lived, allocation-heavy workloads.

#include <iostream>
#include <memory_resource>
#include <vector>
#include <string>
#include <array>
#include <chrono>

int main()
{
    // ------------------------------------------------------------------
    // 1. Stack-based monotonic buffer (no heap at all)
    // ------------------------------------------------------------------
    std::cout << "=== Stack-Based Buffer ===" << std::endl;
    std::array<std::byte, 512> stack_buf{};
    std::pmr::monotonic_buffer_resource stack_pool(
        stack_buf.data(), stack_buf.size(),
        std::pmr::null_memory_resource()  // No fallback: fail if exhausted
    );

    std::pmr::vector<int> v1(&stack_pool);
    for (int i = 1; i <= 10; ++i) v1.push_back(i);

    std::cout << "  Elements: ";
    for (int x : v1) std::cout << x << " ";
    std::cout << std::endl;
    std::cout << "  All from stack buffer (no heap allocation)" << std::endl;

    // ------------------------------------------------------------------
    // 2. Heap-backed with upstream fallback
    // ------------------------------------------------------------------
    std::cout << "\n=== Heap-Backed with Fallback ===" << std::endl;
    std::array<std::byte, 32> tiny_buf{};
    std::pmr::monotonic_buffer_resource fallback_pool(
        tiny_buf.data(), tiny_buf.size(),
        std::pmr::get_default_resource()  // Falls back to heap
    );

    std::pmr::vector<int> v2(&fallback_pool);
    for (int i = 0; i < 100; ++i) v2.push_back(i);

    std::cout << "  Stored " << v2.size() << " elements" << std::endl;
    std::cout << "  Started in 32-byte buffer, overflowed to heap" << std::endl;

    // ------------------------------------------------------------------
    // 3. release() resets the buffer for reuse
    // ------------------------------------------------------------------
    std::cout << "\n=== release() ===" << std::endl;
    std::array<std::byte, 256> buf{};
    std::pmr::monotonic_buffer_resource reusable(
        buf.data(), buf.size(), std::pmr::null_memory_resource()
    );

    for (int round = 1; round <= 3; ++round) {
        std::pmr::vector<int> temp(&reusable);
        for (int i = 0; i < 5; ++i) temp.push_back(round * 10 + i);

        std::cout << "  Round " << round << ": ";
        for (int x : temp) std::cout << x << " ";
        std::cout << std::endl;

        // temp destructor runs, but memory not reclaimed until release()
        reusable.release();  // Reset: buffer available again
    }

    // ------------------------------------------------------------------
    // 4. Performance comparison: monotonic vs default
    // ------------------------------------------------------------------
    std::cout << "\n=== Performance Comparison ===" << std::endl;
    constexpr int N = 100000;

    auto bench = [&](const char* label, std::pmr::memory_resource* mr) {
        auto start = std::chrono::steady_clock::now();
        for (int trial = 0; trial < 10; ++trial) {
            std::pmr::vector<int> v(mr);
            for (int i = 0; i < N; ++i) v.push_back(i);
        }
        auto end = std::chrono::steady_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "  " << label << ": " << ms << " us" << std::endl;
    };

    bench("default (heap)", std::pmr::get_default_resource());

    std::pmr::monotonic_buffer_resource fast_pool(N * sizeof(int) * 2);
    bench("monotonic     ", &fast_pool);

    return 0;
}

/*
Expected output (timings vary):

=== Stack-Based Buffer ===
  Elements: 1 2 3 4 5 6 7 8 9 10
  All from stack buffer (no heap allocation)

=== Heap-Backed with Fallback ===
  Stored 100 elements
  Started in 32-byte buffer, overflowed to heap

=== release() ===
  Round 1: 10 11 12 13 14
  Round 2: 20 21 22 23 24
  Round 3: 30 31 32 33 34

=== Performance Comparison ===
  default (heap): 12345 us
  monotonic     : 6789 us
*/
