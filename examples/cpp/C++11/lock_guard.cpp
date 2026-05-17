// CodeNebula - C++11 Example: std::lock_guard
// Compile: g++ -std=c++11 -Wall -Wextra -pthread -o example lock_guard.cpp
//
// This example demonstrates:
// - std::lock_guard for RAII-based mutex locking
// - Automatic unlock on scope exit (even with exceptions)
// - Comparison with manual lock/unlock
// - Using lock_guard with different mutex types

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <string>
#include <stdexcept>

// ============================================================
// 1. Basic lock_guard usage
// ============================================================
class BankAccount {
    mutable std::mutex mtx_;
    std::string owner_;
    double balance_;

public:
    BankAccount(const std::string& owner, double balance)
        : owner_(owner), balance_(balance) {}

    void deposit(double amount) {
        std::lock_guard<std::mutex> lock(mtx_);  // Locks on construction
        balance_ += amount;
        std::cout << "  " << owner_ << ": deposited " << amount
                  << ", balance = " << balance_ << std::endl;
    }  // Automatically unlocks when lock goes out of scope

    bool withdraw(double amount) {
        std::lock_guard<std::mutex> lock(mtx_);
        if (balance_ >= amount) {
            balance_ -= amount;
            std::cout << "  " << owner_ << ": withdrew " << amount
                      << ", balance = " << balance_ << std::endl;
            return true;
        }
        std::cout << "  " << owner_ << ": insufficient funds" << std::endl;
        return false;
    }

    double getBalance() const {
        std::lock_guard<std::mutex> lock(mtx_);
        return balance_;
    }
};

// ============================================================
// 2. Exception safety with lock_guard
// ============================================================
std::mutex dataMutex;

void riskyOperation(int value) {
    std::lock_guard<std::mutex> lock(dataMutex);
    std::cout << "  Processing: " << value << std::endl;

    if (value < 0) {
        // lock_guard releases mutex even when exception is thrown
        throw std::runtime_error("Negative value not allowed");
    }

    std::cout << "  Completed: " << value << std::endl;
    // Mutex released here automatically
}

// ============================================================
// 3. Scoped locking for fine-grained control
// ============================================================
class ThreadSafeLog {
    std::mutex mtx_;
    std::vector<std::string> entries_;

public:
    void add(const std::string& entry) {
        // Only lock for the critical section
        {
            std::lock_guard<std::mutex> lock(mtx_);
            entries_.push_back(entry);
        }
        // Mutex already released; do non-critical work here
    }

    void printAll() const {
        // Cast away const for mutex (or use mutable)
        auto& self = const_cast<ThreadSafeLog&>(*this);
        std::lock_guard<std::mutex> lock(self.mtx_);
        std::cout << "  Log entries (" << entries_.size() << "):" << std::endl;
        for (const auto& e : entries_) {
            std::cout << "    - " << e << std::endl;
        }
    }
};

// ============================================================
// 4. adopt_lock: lock_guard with already-locked mutex
// ============================================================
std::mutex sharedMutex;

void adoptLockDemo() {
    sharedMutex.lock();  // Manually lock first
    // Tell lock_guard the mutex is already locked
    std::lock_guard<std::mutex> lock(sharedMutex, std::adopt_lock);
    std::cout << "  adopt_lock: mutex was pre-locked, guard manages unlock" << std::endl;
}  // Guard releases the mutex

int main() {
    std::cout << "=== std::lock_guard ===" << std::endl;

    // Bank account with thread-safe operations
    std::cout << "\n--- Thread-safe bank account ---" << std::endl;
    BankAccount account("Alice", 1000.0);

    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(&BankAccount::deposit, &account, 100.0);
    }
    for (auto& t : threads) t.join();
    std::cout << "  Final balance: " << account.getBalance() << std::endl;

    // Exception safety
    std::cout << "\n--- Exception safety ---" << std::endl;
    try {
        riskyOperation(10);
        riskyOperation(-1);   // Throws, but mutex is safely released
    } catch (const std::runtime_error& e) {
        std::cout << "  Caught: " << e.what() << std::endl;
    }
    // Mutex is available again after exception
    riskyOperation(20);

    // Thread-safe log
    std::cout << "\n--- Thread-safe log ---" << std::endl;
    ThreadSafeLog log;
    std::vector<std::thread> logThreads;
    for (int i = 0; i < 4; ++i) {
        logThreads.emplace_back([&log, i]() {
            log.add("Entry from thread " + std::to_string(i));
        });
    }
    for (auto& t : logThreads) t.join();
    log.printAll();

    // adopt_lock
    std::cout << "\n--- adopt_lock ---" << std::endl;
    adoptLockDemo();

    return 0;
}

// Expected output (thread ordering may vary):
// === std::lock_guard ===
//
// --- Thread-safe bank account ---
//   Alice: deposited 100, balance = 1100
//   Alice: deposited 100, balance = 1200
//   Alice: deposited 100, balance = 1300
//   Alice: deposited 100, balance = 1400
//   Alice: deposited 100, balance = 1500
//   Final balance: 1500
//
// --- Exception safety ---
//   Processing: 10
//   Completed: 10
//   Processing: -1
//   Caught: Negative value not allowed
//   Processing: 20
//   Completed: 20
//
// --- Thread-safe log ---
//   Log entries (4):
//     - Entry from thread 0
//     - Entry from thread 1
//     - Entry from thread 2
//     - Entry from thread 3
//
// --- adopt_lock ---
//   adopt_lock: mutex was pre-locked, guard manages unlock
