// CodeNebula - C++20 Example: make_shared_for_overwrite and make_unique_for_overwrite
// Compile: g++ -std=c++20 -Wall -Wextra -o example make_for_overwrite.cpp

#include <iostream>
#include <memory>
#include <cstring>

int main() {
    std::cout << "=== std::make_unique_for_overwrite ===\n";

    // make_unique<T>() value-initializes (zeros for built-in types)
    // make_unique_for_overwrite<T>() default-initializes (indeterminate for built-in)
    // Useful when you plan to overwrite the memory immediately

    // Single object
    auto p1 = std::make_unique_for_overwrite<int>();
    *p1 = 42;  // Overwrite immediately
    std::cout << "unique_ptr single: " << *p1 << "\n";

    // Array of objects - no zero-initialization overhead
    constexpr std::size_t N = 10;
    auto arr = std::make_unique_for_overwrite<int[]>(N);

    // Fill with data (the whole point: we write before reading)
    for (std::size_t i = 0; i < N; ++i) {
        arr[i] = static_cast<int>(i * i);
    }

    std::cout << "unique_ptr array: ";
    for (std::size_t i = 0; i < N; ++i) std::cout << arr[i] << " ";
    std::cout << "\n";

    std::cout << "\n=== std::make_shared_for_overwrite ===\n";

    // Single object
    auto sp1 = std::make_shared_for_overwrite<double>();
    *sp1 = 3.14;
    std::cout << "shared_ptr single: " << *sp1 << "\n";
    std::cout << "Use count: " << sp1.use_count() << "\n";

    // Array (C++20 shared_ptr supports arrays)
    auto sarr = std::make_shared_for_overwrite<char[]>(64);
    std::strcpy(sarr.get(), "Hello, C++20!");
    std::cout << "shared_ptr array: " << sarr.get() << "\n";

    std::cout << "\n=== Comparison with value-initialized versions ===\n";

    // make_unique<int>() guarantees zero-initialization
    auto zeroed = std::make_unique<int>();
    std::cout << "make_unique<int>(): " << *zeroed << " (guaranteed 0)\n";

    // make_unique_for_overwrite<int>() has indeterminate value
    auto uninitialized = std::make_unique_for_overwrite<int>();
    *uninitialized = 99;  // Must write before reading!
    std::cout << "make_unique_for_overwrite<int>(): " << *uninitialized
              << " (after assignment)\n";

    std::cout << "\n=== Performance benefit scenario ===\n";
    // Large buffer: skipping zero-init saves time
    constexpr std::size_t BUF_SIZE = 1024 * 1024;
    auto buffer = std::make_unique_for_overwrite<unsigned char[]>(BUF_SIZE);
    // Simulate filling from I/O (just memset here)
    std::memset(buffer.get(), 0xAB, BUF_SIZE);
    std::cout << "1MB buffer created without zero-init overhead\n";
    std::cout << "First byte: 0x" << std::hex
              << static_cast<int>(buffer[0]) << "\n";
    std::cout << "Last byte:  0x"
              << static_cast<int>(buffer[BUF_SIZE - 1]) << "\n";

    return 0;
}
