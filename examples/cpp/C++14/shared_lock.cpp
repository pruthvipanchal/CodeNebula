// CodeNebula - C++14 Example: std::shared_lock
// Compile: g++ -std=c++14 -Wall -Wextra -pthread -o example shared_lock.cpp

// Demonstrates std::shared_lock for acquiring shared (read) ownership of a
// shared_timed_mutex. While unique_lock provides exclusive access, shared_lock
// allows multiple threads to read concurrently. Real-world use: thread-safe
// read-heavy data structures, DNS caches, routing tables, and config stores.

#include <iostream>
#include <shared_mutex>
#include <thread>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <mutex>
#include <chrono>

// ------------------------------------------------------------------
// Thread-safe print helper
// ------------------------------------------------------------------
std::mutex print_mutex;

template<typename... Args>
void safe_print(Args&&... args)
{
    std::lock_guard<std::mutex> lock(print_mutex);
    // Initializer list trick for expansion
    using swallow = int[];
    (void)swallow{0, (void(std::cout << std::forward<Args>(args)), 0)...};
    std::cout << std::endl;
}

// ------------------------------------------------------------------
// Thread-safe DNS cache using shared_lock (readers) / unique_lock (writers)
// ------------------------------------------------------------------
class DnsCache
{
    mutable std::shared_timed_mutex mutex_;
    std::map<std::string, std::string> entries_;

public:
    // Read: multiple threads can resolve simultaneously
    std::string resolve(const std::string& hostname) const
    {
        std::shared_lock<std::shared_timed_mutex> lock(mutex_);
        auto it = entries_.find(hostname);
        if (it != entries_.end())
            return it->second;
        return "(not found)";
    }

    // Write: exclusive access to update an entry
    void update(const std::string& hostname, const std::string& ip)
    {
        std::unique_lock<std::shared_timed_mutex> lock(mutex_);
        entries_[hostname] = ip;
    }

    // Read: get current size
    std::size_t size() const
    {
        std::shared_lock<std::shared_timed_mutex> lock(mutex_);
        return entries_.size();
    }

    // Read: dump all entries
    std::string dump() const
    {
        std::shared_lock<std::shared_timed_mutex> lock(mutex_);
        std::ostringstream oss;
        for (const auto& e : entries_)
            oss << "    " << e.first << " -> " << e.second << "\n";
        return oss.str();
    }
};

int main()
{
    DnsCache cache;

    // ------------------------------------------------------------------
    // 1. Populate the cache (single-threaded setup)
    // ------------------------------------------------------------------
    std::cout << "=== Populating DNS Cache ===" << std::endl;
    cache.update("example.com", "93.184.216.34");
    cache.update("google.com", "142.250.80.46");
    cache.update("github.com", "140.82.121.4");
    std::cout << "  Entries: " << cache.size() << std::endl;
    std::cout << cache.dump() << std::endl;

    // ------------------------------------------------------------------
    // 2. Multiple concurrent readers (shared_lock allows parallel reads)
    // ------------------------------------------------------------------
    std::cout << "=== Concurrent DNS Lookups ===" << std::endl;
    std::vector<std::thread> readers;
    std::vector<std::string> hosts = {"example.com", "google.com", "github.com", "unknown.org"};

    for (const auto& host : hosts)
    {
        readers.emplace_back([&cache, host]() {
            std::string ip = cache.resolve(host);
            safe_print("  resolve(", host, ") = ", ip);
        });
    }
    for (auto& t : readers) t.join();
    readers.clear();
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. shared_lock features: deferred locking
    // ------------------------------------------------------------------
    std::cout << "=== Deferred Locking ===" << std::endl;
    {
        std::shared_timed_mutex mtx;

        std::shared_lock<std::shared_timed_mutex> lock(mtx, std::defer_lock);
        std::cout << "  Lock created (deferred): owns_lock = "
                  << std::boolalpha << lock.owns_lock() << std::endl;

        lock.lock();
        std::cout << "  After lock():            owns_lock = "
                  << lock.owns_lock() << std::endl;

        lock.unlock();
        std::cout << "  After unlock():          owns_lock = "
                  << lock.owns_lock() << std::endl;
    }
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. Readers and writers working together
    // ------------------------------------------------------------------
    std::cout << "=== Readers + Writer Concurrency ===" << std::endl;

    // Writer thread adds new entries
    std::thread writer([&cache]() {
        cache.update("rust-lang.org", "13.225.255.27");
        safe_print("  [writer] Added rust-lang.org");
        cache.update("cppreference.com", "104.26.1.93");
        safe_print("  [writer] Added cppreference.com");
    });

    // Reader threads perform lookups concurrently
    std::vector<std::thread> lookup_threads;
    for (int i = 0; i < 3; ++i)
    {
        lookup_threads.emplace_back([&cache, i]() {
            // Small delay so some reads happen after writes
            std::this_thread::sleep_for(std::chrono::milliseconds(i * 5));
            std::string id = "reader" + std::to_string(i);
            safe_print("  [", id, "] google.com -> ", cache.resolve("google.com"));
        });
    }

    writer.join();
    for (auto& t : lookup_threads) t.join();
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 5. Final state
    // ------------------------------------------------------------------
    std::cout << "=== Final Cache State ===" << std::endl;
    std::cout << "  Total entries: " << cache.size() << std::endl;
    std::cout << cache.dump();

    return 0;
}

/*
Expected output (thread ordering may vary):

=== Populating DNS Cache ===
  Entries: 3
    example.com -> 93.184.216.34
    github.com -> 140.82.121.4
    google.com -> 142.250.80.46

=== Concurrent DNS Lookups ===
  resolve(example.com) = 93.184.216.34
  resolve(google.com) = 142.250.80.46
  resolve(github.com) = 140.82.121.4
  resolve(unknown.org) = (not found)

=== Deferred Locking ===
  Lock created (deferred): owns_lock = false
  After lock():            owns_lock = true
  After unlock():          owns_lock = false

=== Readers + Writer Concurrency ===
  [writer] Added rust-lang.org
  [writer] Added cppreference.com
  [reader0] google.com -> 142.250.80.46
  [reader1] google.com -> 142.250.80.46
  [reader2] google.com -> 142.250.80.46

=== Final Cache State ===
  Total entries: 5
    cppreference.com -> 104.26.1.93
    example.com -> 93.184.216.34
    github.com -> 140.82.121.4
    google.com -> 142.250.80.46
    rust-lang.org -> 13.225.255.27
*/
