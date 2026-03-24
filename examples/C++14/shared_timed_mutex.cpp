// CodeNebula - C++14 Example: std::shared_timed_mutex
// Compile: g++ -std=c++14 -Wall -Wextra -pthread -o example shared_timed_mutex.cpp

// Demonstrates std::shared_timed_mutex for reader-writer locking with timeout
// support. Multiple threads can hold shared (read) locks simultaneously, but
// exclusive (write) locks are solitary. Real-world use: caches, configuration
// stores, and any data structure with many readers and few writers.

#include <iostream>
#include <shared_mutex>
#include <thread>
#include <vector>
#include <chrono>
#include <string>
#include <sstream>
#include <mutex>

// ------------------------------------------------------------------
// Thread-safe print helper (avoid interleaved output)
// ------------------------------------------------------------------
std::mutex cout_mutex;

void safe_print(const std::string& msg)
{
    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << msg << std::endl;
}

// ------------------------------------------------------------------
// Shared cache protected by shared_timed_mutex
// ------------------------------------------------------------------
class ThreadSafeCache
{
    mutable std::shared_timed_mutex mutex_;
    std::string data_ = "(empty)";
    int version_ = 0;

public:
    // Read operation: shared lock (multiple readers OK)
    std::string read(const std::string& reader_name) const
    {
        std::shared_lock<std::shared_timed_mutex> lock(mutex_);
        std::ostringstream oss;
        oss << "  [" << reader_name << "] READ v" << version_
            << ": " << data_;
        return oss.str();
    }

    // Write operation: exclusive lock (single writer)
    void write(const std::string& writer_name, const std::string& value)
    {
        std::unique_lock<std::shared_timed_mutex> lock(mutex_);
        ++version_;
        data_ = value;
        std::ostringstream oss;
        oss << "  [" << writer_name << "] WRITE v" << version_
            << ": " << data_;
        safe_print(oss.str());
    }

    // Timed read: try to acquire shared lock with timeout
    bool try_read_for(const std::string& reader_name,
                      std::chrono::milliseconds timeout) const
    {
        std::shared_lock<std::shared_timed_mutex> lock(mutex_, timeout);
        if (lock.owns_lock())
        {
            std::ostringstream oss;
            oss << "  [" << reader_name << "] TIMED READ v" << version_
                << ": " << data_;
            safe_print(oss.str());
            return true;
        }
        safe_print("  [" + reader_name + "] TIMED READ: timeout!");
        return false;
    }

    // Timed write: try to acquire exclusive lock with timeout
    bool try_write_for(const std::string& writer_name,
                       const std::string& value,
                       std::chrono::milliseconds timeout)
    {
        std::unique_lock<std::shared_timed_mutex> lock(mutex_, timeout);
        if (lock.owns_lock())
        {
            ++version_;
            data_ = value;
            std::ostringstream oss;
            oss << "  [" << writer_name << "] TIMED WRITE v" << version_
                << ": " << data_;
            safe_print(oss.str());
            return true;
        }
        safe_print("  [" + writer_name + "] TIMED WRITE: timeout!");
        return false;
    }
};

int main()
{
    ThreadSafeCache cache;

    // ------------------------------------------------------------------
    // 1. Single-threaded demonstration
    // ------------------------------------------------------------------
    std::cout << "=== Single-Threaded Read/Write ===" << std::endl;
    cache.write("main", "initial data");
    safe_print(cache.read("main"));
    cache.write("main", "updated data");
    safe_print(cache.read("main"));
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. Multiple concurrent readers
    // ------------------------------------------------------------------
    std::cout << "=== Concurrent Readers ===" << std::endl;
    cache.write("main", "shared value");

    std::vector<std::thread> readers;
    for (int i = 0; i < 4; ++i)
    {
        readers.emplace_back([&cache, i]() {
            std::string name = "reader" + std::to_string(i);
            safe_print(cache.read(name));
        });
    }
    for (auto& t : readers) t.join();
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. Timed lock attempts
    // ------------------------------------------------------------------
    std::cout << "=== Timed Lock Operations ===" << std::endl;
    cache.try_read_for("timed_reader", std::chrono::milliseconds(100));
    cache.try_write_for("timed_writer", "timed value",
                        std::chrono::milliseconds(100));
    cache.try_read_for("timed_reader2", std::chrono::milliseconds(100));
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. Writer-reader interaction
    // ------------------------------------------------------------------
    std::cout << "=== Writer-Reader Interaction ===" << std::endl;
    std::thread writer([&cache]() {
        for (int i = 1; i <= 3; ++i)
        {
            cache.write("writer", "data_v" + std::to_string(i));
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    });

    std::thread reader([&cache]() {
        for (int i = 0; i < 3; ++i)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            safe_print(cache.read("reader"));
        }
    });

    writer.join();
    reader.join();

    return 0;
}

/*
Expected output (thread ordering may vary):

=== Single-Threaded Read/Write ===
  [main] WRITE v1: initial data
  [main] READ v1: initial data
  [main] WRITE v2: updated data
  [main] READ v2: updated data

=== Concurrent Readers ===
  [main] WRITE v3: shared value
  [reader0] READ v3: shared value
  [reader1] READ v3: shared value
  [reader2] READ v3: shared value
  [reader3] READ v3: shared value

=== Timed Lock Operations ===
  [timed_reader] TIMED READ v3: shared value
  [timed_writer] TIMED WRITE v4: timed value
  [timed_reader2] TIMED READ v4: timed value

=== Writer-Reader Interaction ===
  [writer] WRITE v5: data_v1
  [reader] READ v5: data_v1
  [writer] WRITE v6: data_v2
  [reader] READ v6: data_v2
  [writer] WRITE v7: data_v3
  [reader] READ v7: data_v3
*/
