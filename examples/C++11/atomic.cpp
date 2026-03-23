// CodeNebula - C++11 Example: std::atomic
// Compile: g++ -std=c++11 -Wall -Wextra -pthread -o example atomic.cpp
//
// This example demonstrates:
// - std::atomic for lock-free thread-safe operations
// - load(), store(), exchange(), compare_exchange
// - Atomic arithmetic: fetch_add, fetch_sub, ++, --
// - std::atomic_flag as a spinlock
// - Comparison with non-atomic operations

#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

// ============================================================
// 1. Basic atomic operations
// ============================================================
std::atomic<int> atomicCounter(0);
int regularCounter = 0;

void incrementAtomic(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        atomicCounter.fetch_add(1);  // Atomic increment
    }
}

void incrementRegular(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        ++regularCounter;  // Data race!
    }
}

// ============================================================
// 2. Atomic load, store, exchange
// ============================================================
std::atomic<bool> ready(false);
std::atomic<int> payload(0);

void producer() {
    payload.store(42);           // Store value
    ready.store(true);           // Signal ready
}

void consumer() {
    while (!ready.load()) {}     // Spin until ready
    int val = payload.load();    // Read value
    std::cout << "  Consumer got: " << val << std::endl;
}

// ============================================================
// 3. compare_exchange (CAS operation)
// ============================================================
std::atomic<int> casValue(100);

bool tryUpdate(int expected, int desired) {
    // Only updates if current value equals expected
    return casValue.compare_exchange_strong(expected, desired);
}

// ============================================================
// 4. atomic_flag spinlock
// ============================================================
class SpinLock {
    std::atomic_flag flag_ = ATOMIC_FLAG_INIT;
public:
    void lock() {
        while (flag_.test_and_set(std::memory_order_acquire)) {
            // Spin until we acquire the lock
        }
    }

    void unlock() {
        flag_.clear(std::memory_order_release);
    }
};

SpinLock spinlock;
int protectedData = 0;

void spinlockWorker(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        spinlock.lock();
        ++protectedData;
        spinlock.unlock();
    }
}

int main() {
    std::cout << "=== std::atomic ===" << std::endl;

    // Atomic vs regular counter
    std::cout << "\n--- Atomic vs regular counter ---" << std::endl;
    {
        std::vector<std::thread> threads;
        for (int i = 0; i < 4; ++i) {
            threads.emplace_back(incrementAtomic, 10000);
            threads.emplace_back(incrementRegular, 10000);
        }
        for (auto& t : threads) t.join();

        std::cout << "  Atomic counter:  " << atomicCounter.load()
                  << " (expected: 40000)" << std::endl;
        std::cout << "  Regular counter: " << regularCounter
                  << " (may be wrong due to race)" << std::endl;
    }

    // Load, store, exchange
    std::cout << "\n--- load/store/exchange ---" << std::endl;
    std::thread prod(producer);
    std::thread cons(consumer);
    prod.join();
    cons.join();

    std::atomic<int> val(10);
    int old = val.exchange(20);  // Atomically set to 20, return old
    std::cout << "  exchange: old=" << old << ", new=" << val.load() << std::endl;

    // CAS
    std::cout << "\n--- compare_exchange ---" << std::endl;
    std::cout << "  Current value: " << casValue.load() << std::endl;
    bool success1 = tryUpdate(100, 200);
    std::cout << "  CAS(100->200): " << (success1 ? "success" : "failed")
              << ", value=" << casValue.load() << std::endl;
    bool success2 = tryUpdate(100, 300);  // Fails: value is now 200
    std::cout << "  CAS(100->300): " << (success2 ? "success" : "failed")
              << ", value=" << casValue.load() << std::endl;

    // Atomic arithmetic
    std::cout << "\n--- Atomic arithmetic ---" << std::endl;
    std::atomic<int> num(10);
    std::cout << "  Initial: " << num.load() << std::endl;
    num.fetch_add(5);
    std::cout << "  After fetch_add(5): " << num.load() << std::endl;
    num.fetch_sub(3);
    std::cout << "  After fetch_sub(3): " << num.load() << std::endl;
    ++num;
    std::cout << "  After ++: " << num.load() << std::endl;

    // Spinlock
    std::cout << "\n--- atomic_flag spinlock ---" << std::endl;
    {
        std::vector<std::thread> threads;
        for (int i = 0; i < 4; ++i) {
            threads.emplace_back(spinlockWorker, 10000);
        }
        for (auto& t : threads) t.join();
        std::cout << "  Protected data: " << protectedData
                  << " (expected: 40000)" << std::endl;
    }

    // Properties
    std::cout << "\n--- Atomic properties ---" << std::endl;
    std::cout << "  atomic<int> is lock-free: "
              << atomicCounter.is_lock_free() << std::endl;

    return 0;
}

// Expected output (regular counter may vary due to race):
// === std::atomic ===
//
// --- Atomic vs regular counter ---
//   Atomic counter:  40000 (expected: 40000)
//   Regular counter: 38756 (may be wrong due to race)
//
// --- load/store/exchange ---
//   Consumer got: 42
//   exchange: old=10, new=20
//
// --- compare_exchange ---
//   Current value: 100
//   CAS(100->200): success, value=200
//   CAS(100->300): failed, value=200
//
// --- Atomic arithmetic ---
//   Initial: 10
//   After fetch_add(5): 15
//   After fetch_sub(3): 12
//   After ++: 13
//
// --- atomic_flag spinlock ---
//   Protected data: 40000 (expected: 40000)
//
// --- Atomic properties ---
//   atomic<int> is lock-free: 1
