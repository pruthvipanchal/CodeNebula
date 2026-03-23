// CodeNebula - C++11 Example: aligned_storage
// Compile: g++ -std=c++11 -Wall -Wextra -o example aligned_storage.cpp

// Demonstrates std::aligned_storage to create raw storage with proper
// alignment for a given type. Useful for manual object lifetime management,
// variant types, and memory pools.

#include <iostream>
#include <type_traits>
#include <new>       // placement new
#include <string>

// Simple optional using aligned_storage
template<typename T>
class SimpleOptional {
    typename std::aligned_storage<sizeof(T), alignof(T)>::type storage;
    bool has_value;

public:
    SimpleOptional() : has_value(false) {}

    void set(const T& val) {
        if (has_value) reinterpret_cast<T*>(&storage)->~T();
        new (&storage) T(val);
        has_value = true;
    }

    T& get() { return *reinterpret_cast<T*>(&storage); }
    bool empty() const { return !has_value; }

    ~SimpleOptional() {
        if (has_value) reinterpret_cast<T*>(&storage)->~T();
    }
};

int main() {
    std::cout << "=== std::aligned_storage ===" << std::endl;

    // Basic aligned_storage properties
    using Storage = std::aligned_storage<sizeof(double), alignof(double)>::type;
    std::cout << "sizeof(double):  " << sizeof(double) << std::endl;
    std::cout << "sizeof(Storage): " << sizeof(Storage) << std::endl;
    std::cout << "alignof(double): " << alignof(double) << std::endl;
    std::cout << "alignof(Storage):" << alignof(Storage) << std::endl;

    static_assert(sizeof(Storage) >= sizeof(double), "storage big enough");
    static_assert(alignof(Storage) >= alignof(double), "storage aligned");

    // Use SimpleOptional with different types
    SimpleOptional<int> opt_int;
    std::cout << "\nopt_int empty: " << opt_int.empty() << std::endl;
    opt_int.set(42);
    std::cout << "opt_int value: " << opt_int.get() << std::endl;

    SimpleOptional<std::string> opt_str;
    opt_str.set("Hello, aligned_storage!");
    std::cout << "opt_str value: " << opt_str.get() << std::endl;

    std::cout << "\nAll checks passed!" << std::endl;
    return 0;
}

// Expected output:
// === std::aligned_storage ===
// sizeof(double):  8
// sizeof(Storage): 8
// alignof(double): 8
// alignof(Storage):8
//
// opt_int empty: 1
// opt_int value: 42
// opt_str value: Hello, aligned_storage!
//
// All checks passed!
