// CodeNebula - C++11 Example: std::unique_lock
// Compile: g++ -std=c++11 -Wall -Wextra -pthread -o example unique_lock.cpp
//
// This example demonstrates:
// - std::unique_lock for flexible mutex ownership
// - Deferred locking, try-locking, and timed locking
// - Moving lock ownership between scopes
// - Comparison with std::lock_guard
// - Using unique_lock with std::condition_variable

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include <string>

std::mutex printMtx;

void safePrint(const std::string& msg) {
    std::lock_guard<std::mutex> lock(printMtx);
    std::cout << msg << std::endl;
}

// ============================================================
// 1. Basic unique_lock usage
// ============================================================
std::mutex dataMutex;
int sharedData = 0;

void basicUsage() {
    std::unique_lock<std::mutex> lock(dataMutex);  // Locks immediately
    sharedData += 10;
    safePrint("  Basic: sharedData = " + std::to_string(sharedData));
    // Unlocks automatically at end of scope
}

// ============================================================
// 2. Deferred locking
// ============================================================
void deferredLocking() {
    std::unique_lock<std::mutex> lock(dataMutex, std::defer_lock);
    // Mutex NOT locked yet

    safePrint("  Deferred: doing prep work (unlocked)");

    lock.lock();  // Now lock it explicitly
    sharedData += 5;
    safePrint("  Deferred: sharedData = " + std::to_string(sharedData));
    lock.unlock();  // Can unlock early

    safePrint("  Deferred: doing cleanup (unlocked)");
}

// ============================================================
// 3. try_lock with unique_lock
// ============================================================
std::mutex tryMutex;

void tryLockDemo(const std::string& name) {
    std::unique_lock<std::mutex> lock(tryMutex, std::try_to_lock);

    if (lock.owns_lock()) {
        safePrint("  " + name + ": acquired lock");
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    } else {
        safePrint("  " + name + ": could not acquire lock");
    }
}

// ============================================================
// 4. Timed locking with std::timed_mutex
// ============================================================
std::timed_mutex timedMutex;

void timedLockDemo(const std::string& name) {
    std::unique_lock<std::timed_mutex> lock(timedMutex, std::defer_lock);

    if (lock.try_lock_for(std::chrono::milliseconds(100))) {
        safePrint("  " + name + ": got timed lock");
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    } else {
        safePrint("  " + name + ": timed out waiting for lock");
    }
}

// ============================================================
// 5. Moving lock ownership
// ============================================================
std::unique_lock<std::mutex> acquireLock(std::mutex& mtx) {
    std::unique_lock<std::mutex> lock(mtx);
    safePrint("  Lock acquired in function");
    return lock;  // Move ownership to caller
}

// ============================================================
// 6. Manual lock/unlock control
// ============================================================
void manualControl() {
    std::unique_lock<std::mutex> lock(dataMutex);
    sharedData += 1;
    safePrint("  Manual: locked, sharedData = " + std::to_string(sharedData));

    lock.unlock();
    safePrint("  Manual: unlocked for non-critical section");

    lock.lock();
    sharedData += 1;
    safePrint("  Manual: re-locked, sharedData = " + std::to_string(sharedData));
}

int main() {
    std::cout << "=== std::unique_lock ===" << std::endl;

    // Basic
    std::cout << "\n--- Basic usage ---" << std::endl;
    basicUsage();

    // Deferred
    std::cout << "\n--- Deferred locking ---" << std::endl;
    deferredLocking();

    // try_to_lock
    std::cout << "\n--- try_to_lock ---" << std::endl;
    std::thread t1(tryLockDemo, "Alpha");
    std::thread t2(tryLockDemo, "Beta");
    t1.join();
    t2.join();

    // Timed lock
    std::cout << "\n--- Timed locking ---" << std::endl;
    std::thread t3(timedLockDemo, "Fast");
    std::thread t4(timedLockDemo, "Slow");
    t3.join();
    t4.join();

    // Move ownership
    std::cout << "\n--- Moving lock ownership ---" << std::endl;
    {
        auto lock = acquireLock(dataMutex);
        sharedData += 100;
        safePrint("  Caller holds lock, sharedData = " + std::to_string(sharedData));
    }
    safePrint("  Lock released by caller's scope exit");

    // Manual control
    std::cout << "\n--- Manual lock/unlock ---" << std::endl;
    manualControl();

    // Query lock state
    std::cout << "\n--- Lock state queries ---" << std::endl;
    std::unique_lock<std::mutex> lock(dataMutex, std::defer_lock);
    std::cout << "  owns_lock (deferred): " << lock.owns_lock() << std::endl;
    lock.lock();
    std::cout << "  owns_lock (locked):   " << lock.owns_lock() << std::endl;
    lock.unlock();
    std::cout << "  owns_lock (unlocked): " << lock.owns_lock() << std::endl;

    return 0;
}

// Expected output (thread ordering may vary):
// === std::unique_lock ===
//
// --- Basic usage ---
//   Basic: sharedData = 10
//
// --- Deferred locking ---
//   Deferred: doing prep work (unlocked)
//   Deferred: sharedData = 15
//   Deferred: doing cleanup (unlocked)
//
// --- try_to_lock ---
//   Alpha: acquired lock
//   Beta: could not acquire lock
//
// --- Timed locking ---
//   Fast: got timed lock
//   Slow: got timed lock
//
// --- Moving lock ownership ---
//   Lock acquired in function
//   Caller holds lock, sharedData = 116
//   Lock released by caller's scope exit
//
// --- Manual lock/unlock ---
//   Manual: locked, sharedData = 117
//   Manual: unlocked for non-critical section
//   Manual: re-locked, sharedData = 118
//
// --- Lock state queries ---
//   owns_lock (deferred): 0
//   owns_lock (locked):   1
//   owns_lock (unlocked): 0
