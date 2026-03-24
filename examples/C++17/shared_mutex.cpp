// CodeNebula - C++17 Example: std::shared_mutex
// Compile: g++ -std=c++17 -Wall -Wextra -o example shared_mutex.cpp -lpthread

// Demonstrates std::shared_mutex, a reader-writer lock that allows multiple
// concurrent readers OR one exclusive writer. Use std::shared_lock for read
// access and std::unique_lock (or std::lock_guard) for write access.

#include <iostream>
#include <shared_mutex>
#include <thread>
#include <vector>
#include <string>
#include <map>
#include <mutex>
#include <chrono>

// ------------------------------------------------------------------
// Thread-safe cache using shared_mutex
// ------------------------------------------------------------------
class ThreadSafeCache {
    mutable std::shared_mutex mutex_;
    std::map<std::string, int> data_;
    std::mutex cout_mutex_;

    void log(const std::string& msg) {
        std::lock_guard<std::mutex> lock(cout_mutex_);
        std::cout << "  " << msg << std::endl;
    }

public:
    // Read operation: multiple threads can read concurrently
    int get(const std::string& key) const {
        std::shared_lock lock(mutex_);  // Shared (read) lock
        auto it = data_.find(key);
        return (it != data_.end()) ? it->second : -1;
    }

    // Write operation: exclusive access required
    void set(const std::string& key, int value) {
        std::unique_lock lock(mutex_);  // Exclusive (write) lock
        data_[key] = value;
    }

    // Read: check if key exists
    bool contains(const std::string& key) const {
        std::shared_lock lock(mutex_);
        return data_.find(key) != data_.end();
    }

    // Read: get size
    std::size_t size() const {
        std::shared_lock lock(mutex_);
        return data_.size();
    }
};

int main()
{
    ThreadSafeCache cache;

    // ------------------------------------------------------------------
    // 1. Writer threads populate the cache
    // ------------------------------------------------------------------
    std::cout << "=== Writers ===" << std::endl;
    std::vector<std::thread> writers;
    for (int i = 0; i < 4; ++i) {
        writers.emplace_back([&cache, i]() {
            std::string key = "key_" + std::to_string(i);
            cache.set(key, i * 100);
        });
    }
    for (auto& t : writers) t.join();
    std::cout << "  Written " << cache.size() << " entries" << std::endl;

    // ------------------------------------------------------------------
    // 2. Multiple reader threads read concurrently
    // ------------------------------------------------------------------
    std::cout << "\n=== Concurrent Readers ===" << std::endl;
    std::mutex print_mutex;
    std::vector<std::thread> readers;

    for (int i = 0; i < 4; ++i) {
        readers.emplace_back([&cache, &print_mutex, i]() {
            std::string key = "key_" + std::to_string(i);
            int val = cache.get(key);
            std::lock_guard<std::mutex> lock(print_mutex);
            std::cout << "  Reader " << i << ": " << key << " = " << val << std::endl;
        });
    }
    for (auto& t : readers) t.join();

    // ------------------------------------------------------------------
    // 3. Mixed readers and writers
    // ------------------------------------------------------------------
    std::cout << "\n=== Mixed Read/Write ===" << std::endl;
    std::vector<std::thread> mixed;

    // Writer adds new entry
    mixed.emplace_back([&cache]() {
        cache.set("key_new", 999);
    });

    // Readers check for existing data
    for (int i = 0; i < 3; ++i) {
        mixed.emplace_back([&cache, &print_mutex, i]() {
            bool exists = cache.contains("key_" + std::to_string(i));
            std::lock_guard<std::mutex> lock(print_mutex);
            std::cout << "  Reader: key_" << i << " exists=" << exists << std::endl;
        });
    }
    for (auto& t : mixed) t.join();

    std::cout << "\n  Final cache size: " << cache.size() << std::endl;

    // ------------------------------------------------------------------
    // 4. Lock types summary
    // ------------------------------------------------------------------
    std::cout << "\n=== Lock Summary ===" << std::endl;
    std::cout << "  shared_lock  -> shared (read) access, multiple allowed" << std::endl;
    std::cout << "  unique_lock  -> exclusive (write) access, one at a time" << std::endl;
    std::cout << "  lock_guard   -> exclusive access (simpler, non-movable)" << std::endl;

    return 0;
}

/*
Expected output (thread order may vary):

=== Writers ===
  Written 4 entries

=== Concurrent Readers ===
  Reader 0: key_0 = 0
  Reader 1: key_1 = 100
  Reader 2: key_2 = 200
  Reader 3: key_3 = 300

=== Mixed Read/Write ===
  Reader: key_0 exists=1
  Reader: key_1 exists=1
  Reader: key_2 exists=1

  Final cache size: 5

=== Lock Summary ===
  shared_lock  -> shared (read) access, multiple allowed
  unique_lock  -> exclusive (write) access, one at a time
  lock_guard   -> exclusive access (simpler, non-movable)
*/
