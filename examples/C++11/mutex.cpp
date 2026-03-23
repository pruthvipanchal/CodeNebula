// CodeNebula - C++11 Example: std::mutex
// Compile: g++ -std=c++11 -Wall -Wextra -pthread -o example mutex.cpp
//
// This example demonstrates:
// - std::mutex for mutual exclusion
// - lock() and unlock() basic usage
// - try_lock() for non-blocking lock attempts
// - std::recursive_mutex for reentrant locking
// - Data races without mutex vs. correct code with mutex

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <string>

// ============================================================
// 1. Shared counter without protection (data race)
// ============================================================
int unsafeCounter = 0;

void unsafeIncrement(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        ++unsafeCounter;  // DATA RACE!
    }
}

// ============================================================
// 2. Shared counter with std::mutex
// ============================================================
int safeCounter = 0;
std::mutex counterMutex;

void safeIncrement(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        counterMutex.lock();
        ++safeCounter;
        counterMutex.unlock();
    }
}

// ============================================================
// 3. try_lock() for non-blocking attempts
// ============================================================
std::mutex resourceMutex;

void tryAccessResource(const std::string& name) {
    if (resourceMutex.try_lock()) {
        std::cout << "  " << name << ": acquired lock, working..." << std::endl;
        // Simulate work
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        resourceMutex.unlock();
        std::cout << "  " << name << ": released lock" << std::endl;
    } else {
        std::cout << "  " << name << ": lock busy, doing other work" << std::endl;
    }
}

// ============================================================
// 4. std::recursive_mutex for reentrant locking
// ============================================================
class TreeNode {
    std::string name_;
    std::vector<TreeNode*> children_;
    mutable std::recursive_mutex mtx_;
public:
    TreeNode(const std::string& name) : name_(name) {}

    void addChild(TreeNode* child) {
        std::lock_guard<std::recursive_mutex> lock(mtx_);
        children_.push_back(child);
    }

    void print(int depth = 0) const {
        std::lock_guard<std::recursive_mutex> lock(mtx_);
        std::cout << std::string(depth * 2, ' ') << "  " << name_ << std::endl;
        for (const auto* child : children_) {
            child->print(depth + 1);  // Recursive: re-locks the mutex
        }
    }
};

int main() {
    std::cout << "=== std::mutex ===" << std::endl;

    // Unsafe (data race) demonstration
    std::cout << "\n--- Without mutex (data race) ---" << std::endl;
    {
        std::vector<std::thread> threads;
        for (int i = 0; i < 4; ++i) {
            threads.emplace_back(unsafeIncrement, 10000);
        }
        for (auto& t : threads) t.join();
        std::cout << "  Expected: 40000, Got: " << unsafeCounter
                  << (unsafeCounter != 40000 ? " (race detected!)" : "") << std::endl;
    }

    // Safe (mutex-protected) demonstration
    std::cout << "\n--- With std::mutex ---" << std::endl;
    {
        std::vector<std::thread> threads;
        for (int i = 0; i < 4; ++i) {
            threads.emplace_back(safeIncrement, 10000);
        }
        for (auto& t : threads) t.join();
        std::cout << "  Expected: 40000, Got: " << safeCounter << std::endl;
    }

    // try_lock demonstration
    std::cout << "\n--- try_lock() ---" << std::endl;
    {
        std::thread t1(tryAccessResource, "Thread-A");
        std::thread t2(tryAccessResource, "Thread-B");
        t1.join();
        t2.join();
    }

    // Recursive mutex demonstration
    std::cout << "\n--- recursive_mutex (tree) ---" << std::endl;
    {
        TreeNode root("root");
        TreeNode child1("child1");
        TreeNode child2("child2");
        TreeNode grandchild("grandchild");

        root.addChild(&child1);
        root.addChild(&child2);
        child1.addChild(&grandchild);

        root.print();
    }

    return 0;
}

// Expected output (thread interleaving and data race results may vary):
// === std::mutex ===
//
// --- Without mutex (data race) ---
//   Expected: 40000, Got: 38542 (race detected!)
//
// --- With std::mutex ---
//   Expected: 40000, Got: 40000
//
// --- try_lock() ---
//   Thread-A: acquired lock, working...
//   Thread-B: lock busy, doing other work
//   Thread-A: released lock
//
// --- recursive_mutex (tree) ---
//   root
//     child1
//       grandchild
//     child2
