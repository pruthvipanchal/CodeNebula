// CodeNebula - C++17 Example: std::pmr::synchronized_pool_resource
// Compile: g++ -std=c++17 -Wall -Wextra -o example synchronized_pool_resource.cpp -lpthread

// Demonstrates std::pmr::synchronized_pool_resource, a thread-safe pool-based
// memory resource. Multiple threads can allocate and deallocate concurrently.
// It uses internal synchronization, making it safe without external locking.

#include <iostream>
#include <memory_resource>
#include <vector>
#include <thread>
#include <mutex>
#include <numeric>

std::mutex cout_mutex;

void worker(int id, std::pmr::memory_resource* pool, int count) {
    // Each thread allocates its own pmr::vector from the shared pool
    std::pmr::vector<int> data(pool);
    for (int i = 0; i < count; ++i) {
        data.push_back(id * 1000 + i);
    }

    int sum = std::accumulate(data.begin(), data.end(), 0);

    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << "  Thread " << id << ": " << data.size()
              << " elements, sum = " << sum << std::endl;
}

int main()
{
    // ------------------------------------------------------------------
    // 1. Basic thread-safe pool
    // ------------------------------------------------------------------
    std::cout << "=== Synchronized Pool (Multi-threaded) ===" << std::endl;
    std::pmr::synchronized_pool_resource pool;

    std::vector<std::thread> threads;
    for (int i = 0; i < 4; ++i) {
        threads.emplace_back(worker, i, &pool, 100);
    }
    for (auto& t : threads) t.join();

    // ------------------------------------------------------------------
    // 2. Custom pool options
    // ------------------------------------------------------------------
    std::cout << "\n=== Custom Options ===" << std::endl;
    std::pmr::pool_options opts;
    opts.max_blocks_per_chunk = 32;
    opts.largest_required_pool_block = 1024;

    std::pmr::synchronized_pool_resource custom_pool(opts);

    std::pmr::vector<int> v(&custom_pool);
    for (int i = 0; i < 200; ++i) v.push_back(i);

    std::cout << "  max_blocks_per_chunk       = 32" << std::endl;
    std::cout << "  largest_required_pool_block = 1024" << std::endl;
    std::cout << "  Stored " << v.size() << " elements" << std::endl;

    // ------------------------------------------------------------------
    // 3. Comparing synchronized vs unsynchronized
    // ------------------------------------------------------------------
    std::cout << "\n=== Synchronized vs Unsynchronized ===" << std::endl;
    std::cout << "  synchronized_pool_resource:" << std::endl;
    std::cout << "    - Thread-safe (internal locks)" << std::endl;
    std::cout << "    - Slightly slower due to synchronization" << std::endl;
    std::cout << "    - Use when multiple threads share a pool" << std::endl;
    std::cout << "  unsynchronized_pool_resource:" << std::endl;
    std::cout << "    - NOT thread-safe" << std::endl;
    std::cout << "    - Faster (no locking overhead)" << std::endl;
    std::cout << "    - Use for single-threaded or thread-local pools" << std::endl;

    // ------------------------------------------------------------------
    // 4. Multiple threads with concurrent alloc/dealloc
    // ------------------------------------------------------------------
    std::cout << "\n=== Concurrent Alloc/Dealloc ===" << std::endl;
    std::pmr::synchronized_pool_resource shared_pool;

    auto mixed_work = [&shared_pool](int id) {
        for (int round = 0; round < 5; ++round) {
            std::pmr::vector<int> temp(&shared_pool);
            for (int i = 0; i < 50; ++i) temp.push_back(i);
            // temp destroyed: memory returned to pool
        }
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "  Thread " << id << " completed 5 alloc/dealloc rounds" << std::endl;
    };

    std::vector<std::thread> workers;
    for (int i = 0; i < 4; ++i) {
        workers.emplace_back(mixed_work, i);
    }
    for (auto& t : workers) t.join();

    std::cout << "  All threads completed safely" << std::endl;

    return 0;
}

/*
Expected output (thread ordering may vary):

=== Synchronized Pool (Multi-threaded) ===
  Thread 0: 100 elements, sum = 4950
  Thread 1: 100 elements, sum = 104950
  Thread 2: 100 elements, sum = 204950
  Thread 3: 100 elements, sum = 304950

=== Custom Options ===
  max_blocks_per_chunk       = 32
  largest_required_pool_block = 1024
  Stored 200 elements

=== Synchronized vs Unsynchronized ===
  synchronized_pool_resource:
    - Thread-safe (internal locks)
    - Slightly slower due to synchronization
    - Use when multiple threads share a pool
  unsynchronized_pool_resource:
    - NOT thread-safe
    - Faster (no locking overhead)
    - Use for single-threaded or thread-local pools

=== Concurrent Alloc/Dealloc ===
  Thread 0 completed 5 alloc/dealloc rounds
  Thread 1 completed 5 alloc/dealloc rounds
  Thread 2 completed 5 alloc/dealloc rounds
  Thread 3 completed 5 alloc/dealloc rounds
  All threads completed safely
*/
