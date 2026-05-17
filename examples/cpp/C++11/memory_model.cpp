// CodeNebula - C++11 Example: Memory Model and Memory Ordering
// Compile: g++ -std=c++11 -Wall -Wextra -pthread -o example memory_model.cpp
//
// This example demonstrates:
// - C++11 memory ordering options (relaxed, acquire, release, seq_cst)
// - Acquire-release semantics for producer-consumer patterns
// - Relaxed ordering for simple counters
// - Sequential consistency as the default and strongest guarantee
// - Practical examples of each ordering level

#include <iostream>
#include <atomic>
#include <thread>
#include <cassert>

// ============================================================
// 1. Sequential Consistency (default, strongest)
// ============================================================
// All threads observe the same order of operations.
// This is the default for std::atomic operations.
std::atomic<bool> seqFlag1(false);
std::atomic<bool> seqFlag2(false);
std::atomic<int> seqResult(0);

void seqWriter1() {
    seqFlag1.store(true);  // Default: memory_order_seq_cst
}

void seqWriter2() {
    seqFlag2.store(true);  // Default: memory_order_seq_cst
}

void seqReader() {
    // With seq_cst, if we see flag1==true then flag2==true,
    // every thread agrees on this ordering
    while (!seqFlag1.load() || !seqFlag2.load()) {}
    seqResult.store(42);
}

// ============================================================
// 2. Acquire-Release: producer-consumer synchronization
// ============================================================
std::atomic<bool> dataReady(false);
int sharedPayload = 0;  // Non-atomic, protected by acquire-release

void releaseProducer() {
    sharedPayload = 99;  // Write data (non-atomic is fine here)
    // Release: all writes before this are visible to the acquiring thread
    dataReady.store(true, std::memory_order_release);
}

void acquireConsumer() {
    // Acquire: sees all writes that happened before the release
    while (!dataReady.load(std::memory_order_acquire)) {}
    // sharedPayload is guaranteed to be 99 here
    std::cout << "  Acquire-Release consumer got: " << sharedPayload << std::endl;
}

// ============================================================
// 3. Relaxed ordering: no synchronization guarantees
// ============================================================
// Only guarantees atomicity, not ordering between threads.
// Good for simple counters where order doesn't matter.
std::atomic<int> relaxedCounter(0);

void relaxedIncrement(int count) {
    for (int i = 0; i < count; ++i) {
        // Relaxed: just atomic increment, no ordering constraints
        relaxedCounter.fetch_add(1, std::memory_order_relaxed);
    }
}

// ============================================================
// 4. Release-Consume (simplified concept)
// ============================================================
// memory_order_consume is intended for dependency chains.
// In practice, most compilers promote it to acquire.
// Shown here for completeness.
struct Data {
    int value;
    int extra;
};

std::atomic<Data*> atomicPtr(nullptr);

void publishData() {
    Data* d = new Data{42, 100};
    // Release ensures d's fields are visible
    atomicPtr.store(d, std::memory_order_release);
}

void readData() {
    Data* d = nullptr;
    while ((d = atomicPtr.load(std::memory_order_acquire)) == nullptr) {}
    // Safe to read d->value and d->extra
    std::cout << "  Published data: value=" << d->value
              << ", extra=" << d->extra << std::endl;
    delete d;
}

// ============================================================
// 5. Memory ordering comparison table
// ============================================================
void printOrderingTable() {
    std::cout << "\n--- Memory Ordering Summary ---" << std::endl;
    std::cout << "  Order             | Guarantee" << std::endl;
    std::cout << "  ------------------|-------------------------------------" << std::endl;
    std::cout << "  relaxed           | Atomicity only, no ordering" << std::endl;
    std::cout << "  acquire           | Reads after this see prior writes" << std::endl;
    std::cout << "  release           | Writes before this visible to acquire" << std::endl;
    std::cout << "  acq_rel           | Both acquire and release" << std::endl;
    std::cout << "  seq_cst (default) | Total global ordering" << std::endl;
}

int main() {
    std::cout << "=== Memory Model and Ordering ===" << std::endl;

    // Sequential consistency
    std::cout << "\n--- Sequential Consistency ---" << std::endl;
    std::thread sw1(seqWriter1);
    std::thread sw2(seqWriter2);
    std::thread sr(seqReader);
    sw1.join();
    sw2.join();
    sr.join();
    std::cout << "  seq_cst result: " << seqResult.load() << std::endl;

    // Acquire-Release
    std::cout << "\n--- Acquire-Release ---" << std::endl;
    std::thread prod(releaseProducer);
    std::thread cons(acquireConsumer);
    prod.join();
    cons.join();

    // Relaxed ordering for counters
    std::cout << "\n--- Relaxed Ordering ---" << std::endl;
    {
        std::thread t1(relaxedIncrement, 10000);
        std::thread t2(relaxedIncrement, 10000);
        t1.join();
        t2.join();
        std::cout << "  Relaxed counter: " << relaxedCounter.load() << std::endl;
    }

    // Publish-read pattern
    std::cout << "\n--- Publish/Read Pattern ---" << std::endl;
    std::thread pub(publishData);
    std::thread rd(readData);
    pub.join();
    rd.join();

    // Summary
    printOrderingTable();

    return 0;
}

// Expected output:
// === Memory Model and Ordering ===
//
// --- Sequential Consistency ---
//   seq_cst result: 42
//
// --- Acquire-Release ---
//   Acquire-Release consumer got: 99
//
// --- Relaxed Ordering ---
//   Relaxed counter: 20000
//
// --- Publish/Read Pattern ---
//   Published data: value=42, extra=100
//
// --- Memory Ordering Summary ---
//   Order             | Guarantee
//   ------------------|-------------------------------------
//   relaxed           | Atomicity only, no ordering
//   acquire           | Reads after this see prior writes
//   release           | Writes before this visible to acquire
//   acq_rel           | Both acquire and release
//   seq_cst (default) | Total global ordering
