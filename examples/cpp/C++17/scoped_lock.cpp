// CodeNebula - C++17 Example: std::scoped_lock
// Compile: g++ -std=c++17 -Wall -Wextra -o example scoped_lock.cpp -lpthread

// Demonstrates std::scoped_lock, a C++17 RAII lock guard that can lock
// multiple mutexes simultaneously without deadlock (using a deadlock-avoidance
// algorithm). It replaces the error-prone pattern of manually calling
// std::lock() followed by std::lock_guard with std::adopt_lock.

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <string>

// ------------------------------------------------------------------
// Bank account with mutex for thread-safe operations
// ------------------------------------------------------------------
struct Account {
    std::string name;
    double balance;
    std::mutex mutex;

    Account(std::string n, double b) : name(std::move(n)), balance(b) {}
};

// Transfer money between accounts: locks BOTH mutexes to avoid deadlock
void transfer(Account& from, Account& to, double amount) {
    // scoped_lock acquires both mutexes atomically, preventing deadlock
    // even if another thread calls transfer(to, from, ...) simultaneously
    std::scoped_lock lock(from.mutex, to.mutex);

    if (from.balance >= amount) {
        from.balance -= amount;
        to.balance += amount;
    }
}

// ------------------------------------------------------------------
// Logging system with multiple protection levels
// ------------------------------------------------------------------
class Logger {
    std::mutex data_mutex_;
    std::mutex format_mutex_;
    std::vector<std::string> logs_;
    std::string prefix_ = "[LOG] ";

public:
    // Needs both mutexes to safely format and store
    void log(const std::string& msg) {
        std::scoped_lock lock(data_mutex_, format_mutex_);
        logs_.push_back(prefix_ + msg);
    }

    void set_prefix(const std::string& p) {
        std::scoped_lock lock(format_mutex_);
        prefix_ = p;
    }

    void print_all() {
        std::scoped_lock lock(data_mutex_);
        for (const auto& entry : logs_) {
            std::cout << "  " << entry << std::endl;
        }
    }
};

int main()
{
    // ------------------------------------------------------------------
    // 1. Single mutex (replaces lock_guard)
    // ------------------------------------------------------------------
    std::cout << "=== Single Mutex ===" << std::endl;
    std::mutex m;
    {
        std::scoped_lock lock(m);  // Locks one mutex, just like lock_guard
        std::cout << "  Locked single mutex" << std::endl;
    }
    std::cout << "  Unlocked on scope exit" << std::endl;

    // ------------------------------------------------------------------
    // 2. Deadlock-free bank transfers
    // ------------------------------------------------------------------
    std::cout << "\n=== Bank Transfers ===" << std::endl;
    Account alice("Alice", 1000.0);
    Account bob("Bob", 1000.0);

    std::cout << "  Before: Alice=" << alice.balance << " Bob=" << bob.balance << std::endl;

    std::vector<std::thread> threads;
    // Multiple threads transferring in both directions simultaneously
    for (int i = 0; i < 100; ++i) {
        threads.emplace_back(transfer, std::ref(alice), std::ref(bob), 10.0);
        threads.emplace_back(transfer, std::ref(bob), std::ref(alice), 10.0);
    }
    for (auto& t : threads) t.join();

    std::cout << "  After:  Alice=" << alice.balance << " Bob=" << bob.balance << std::endl;
    std::cout << "  Total:  " << (alice.balance + bob.balance)
              << " (should be 2000)" << std::endl;

    // ------------------------------------------------------------------
    // 3. Multi-resource logger
    // ------------------------------------------------------------------
    std::cout << "\n=== Multi-Resource Logger ===" << std::endl;
    Logger logger;

    std::vector<std::thread> log_threads;
    for (int i = 0; i < 5; ++i) {
        log_threads.emplace_back([&logger, i]() {
            logger.log("message from thread " + std::to_string(i));
        });
    }
    for (auto& t : log_threads) t.join();
    logger.print_all();

    // ------------------------------------------------------------------
    // 4. Zero mutexes (no-op, but valid)
    // ------------------------------------------------------------------
    std::cout << "\n=== Zero Mutexes ===" << std::endl;
    {
        std::scoped_lock lock;  // Locks nothing -- valid and useful in templates
        std::cout << "  scoped_lock with no mutexes: valid no-op" << std::endl;
    }

    return 0;
}

/*
Expected output (thread message order may vary):

=== Single Mutex ===
  Locked single mutex
  Unlocked on scope exit

=== Bank Transfers ===
  Before: Alice=1000 Bob=1000
  After:  Alice=1000 Bob=1000
  Total:  2000 (should be 2000)

=== Multi-Resource Logger ===
  [LOG] message from thread 0
  [LOG] message from thread 1
  [LOG] message from thread 2
  [LOG] message from thread 3
  [LOG] message from thread 4

=== Zero Mutexes ===
  scoped_lock with no mutexes: valid no-op
*/
