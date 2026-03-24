// CodeNebula - C++20 Example: std::syncbuf and std::osyncstream
// Compile: g++ -std=c++20 -Wall -Wextra -pthread -o example syncstream.cpp

#include <iostream>
#include <syncstream>
#include <thread>
#include <vector>
#include <string>

void print_unsync(int id) {
    std::cout << "Thread " << id << ": unsynchronized line 1\n";
    std::cout << "Thread " << id << ": unsynchronized line 2\n";
}

void print_sync(int id) {
    // osyncstream buffers the entire output and flushes atomically
    std::osyncstream out(std::cout);
    out << "Thread " << id << ": Hello from synchronized output!\n";
    out << "Thread " << id << ": This will NOT interleave.\n";
    // Flushed atomically when 'out' is destroyed
}

int main() {
    const int num_threads = 4;

    // Demonstrate unsynchronized output (may interleave)
    std::cout << "=== Unsynchronized output ===\n";
    {
        std::vector<std::thread> threads;
        for (int i = 0; i < num_threads; ++i)
            threads.emplace_back(print_unsync, i);
        for (auto& t : threads) t.join();
    }

    std::cout << "\n=== Synchronized output ===\n";
    {
        std::vector<std::thread> threads;
        for (int i = 0; i < num_threads; ++i)
            threads.emplace_back(print_sync, i);
        for (auto& t : threads) t.join();
    }

    // Using osyncstream for formatted multi-line atomic output
    std::cout << "\n=== Formatted synchronized output ===\n";
    {
        std::vector<std::thread> threads;
        for (int i = 0; i < num_threads; ++i) {
            threads.emplace_back([i] {
                std::osyncstream sync_out(std::cout);
                sync_out << "--- Worker " << i << " Report ---\n";
                sync_out << "  Status: running\n";
                sync_out << "  Items processed: " << (i + 1) * 10 << "\n";
                sync_out << "--- End Worker " << i << " ---\n";
            });
        }
        for (auto& t : threads) t.join();
    }

    // Manual emit for explicit flush control
    std::cout << "\n=== Manual emit ===\n";
    {
        std::osyncstream sync_out(std::cout);
        sync_out << "First part... ";
        sync_out.emit();  // flush now
        sync_out << "Second part.\n";
        // remainder flushed on destruction
    }

    return 0;
}
