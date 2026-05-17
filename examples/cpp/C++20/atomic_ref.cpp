// CodeNebula - C++20 Example: std::atomic_ref
// Compile: g++ -std=c++20 -Wall -Wextra -pthread -o example atomic_ref.cpp

#include <atomic>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

struct Counters {
    int reads = 0;
    int writes = 0;
    int errors = 0;
};

int main() {
    std::cout << "=== std::atomic_ref - atomic access to non-atomic variables ===\n\n";

    // atomic_ref provides atomic operations on an existing non-atomic variable
    // Useful when you cannot change the type (e.g., in a struct or library)

    int counter = 0;
    constexpr int iterations = 10000;
    constexpr int num_threads = 4;

    std::cout << "--- Without atomic_ref (data race) ---\n";
    {
        int unsafe_counter = 0;
        std::vector<std::jthread> threads;
        for (int i = 0; i < num_threads; ++i) {
            threads.emplace_back([&unsafe_counter] {
                for (int j = 0; j < iterations; ++j) {
                    ++unsafe_counter;  // DATA RACE!
                }
            });
        }
        for (auto& t : threads) t.join();
        std::cout << "Expected: " << (num_threads * iterations)
                  << ", Got: " << unsafe_counter << " (may differ due to race)\n";
    }

    std::cout << "\n--- With atomic_ref (safe) ---\n";
    {
        counter = 0;
        std::vector<std::jthread> threads;
        for (int i = 0; i < num_threads; ++i) {
            threads.emplace_back([&counter] {
                std::atomic_ref<int> ref(counter);
                for (int j = 0; j < iterations; ++j) {
                    ref.fetch_add(1, std::memory_order_relaxed);
                }
            });
        }
        for (auto& t : threads) t.join();
        std::cout << "Expected: " << (num_threads * iterations)
                  << ", Got: " << counter << " (always correct)\n";
    }

    std::cout << "\n=== atomic_ref with struct members ===\n";
    {
        Counters c;
        std::vector<std::jthread> threads;
        for (int i = 0; i < 4; ++i) {
            threads.emplace_back([&c] {
                std::atomic_ref<int> reads(c.reads);
                std::atomic_ref<int> writes(c.writes);
                for (int j = 0; j < 1000; ++j) {
                    reads.fetch_add(1, std::memory_order_relaxed);
                    writes.fetch_add(1, std::memory_order_relaxed);
                }
            });
        }
        for (auto& t : threads) t.join();
        std::cout << "Reads: " << c.reads << ", Writes: " << c.writes << "\n";
    }

    std::cout << "\n=== atomic_ref properties ===\n";
    std::cout << "is_always_lock_free (int): "
              << std::atomic_ref<int>::is_always_lock_free << "\n";
    std::cout << "is_always_lock_free (double): "
              << std::atomic_ref<double>::is_always_lock_free << "\n";
    std::cout << "required_alignment (int): "
              << std::atomic_ref<int>::required_alignment << "\n";

    std::cout << "\n=== compare_exchange with atomic_ref ===\n";
    int value = 10;
    std::atomic_ref<int> ref(value);
    int expected = 10;
    bool success = ref.compare_exchange_strong(expected, 20);
    std::cout << "CAS(10 -> 20): " << (success ? "success" : "failed")
              << ", value = " << value << "\n";

    return 0;
}
