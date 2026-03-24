// CodeNebula - C++20 Example: [[likely]] and [[unlikely]] Attributes
// Compile: g++ -std=c++20 -Wall -Wextra -o example likely_unlikely.cpp

// [[likely]] and [[unlikely]] are branch prediction hints for the compiler.
// They indicate which branch of an if/switch is expected to be taken most
// often, allowing the compiler to optimize code layout accordingly.

#include <iostream>
#include <vector>
#include <random>
#include <chrono>

// Error handling with [[unlikely]] — errors are rare
int safe_divide(int a, int b) {
    if (b == 0) [[unlikely]] {
        std::cout << "  Error: division by zero!\n";
        return 0;
    }
    return a / b;
}

// Cache lookup with [[likely]] — cache hits are common
struct SimpleCache {
    int cached_key = -1;
    int cached_value = 0;

    int lookup(int key) {
        if (key == cached_key) [[likely]] {
            return cached_value;  // cache hit (expected common path)
        } else [[unlikely]] {
            // cache miss — expensive computation
            cached_key = key;
            cached_value = key * key + 1;
            return cached_value;
        }
    }
};

// Switch statement with likely/unlikely branches
const char* classify_http_status(int code) {
    switch (code) {
        case 200: [[likely]]   return "OK";
        case 301:              return "Moved Permanently";
        case 404: [[unlikely]] return "Not Found";
        case 500: [[unlikely]] return "Internal Server Error";
        default:               return "Unknown";
    }
}

// Loop with rare break condition
int find_first_negative(const std::vector<int>& data) {
    for (std::size_t i = 0; i < data.size(); ++i) {
        if (data[i] < 0) [[unlikely]] {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// Validation with [[likely]] success path
bool process_value(int value) {
    if (value >= 0 && value <= 1000) [[likely]] {
        // Normal processing path
        return true;
    } else [[unlikely]] {
        // Out-of-range error path
        std::cout << "  Value " << value << " out of range!\n";
        return false;
    }
}

int main() {
    std::cout << "=== [[likely]] and [[unlikely]] Attributes ===\n\n";

    // Safe divide: normal case and error case
    std::cout << "safe_divide(100, 7) = " << safe_divide(100, 7) << "\n";
    std::cout << "safe_divide(42, 0)  = " << safe_divide(42, 0) << "\n\n";

    // Cache lookups
    SimpleCache cache;
    std::cout << "Cache lookups:\n";
    std::cout << "  lookup(5) = " << cache.lookup(5) << " (miss)\n";
    std::cout << "  lookup(5) = " << cache.lookup(5) << " (hit)\n";
    std::cout << "  lookup(3) = " << cache.lookup(3) << " (miss)\n\n";

    // HTTP status classification
    std::cout << "HTTP status codes:\n";
    int codes[] = {200, 301, 404, 500, 418};
    for (int code : codes) {
        std::cout << "  " << code << " -> " << classify_http_status(code) << "\n";
    }
    std::cout << "\n";

    // Find negative in mostly-positive data
    std::vector<int> data = {5, 10, 20, 30, 40, -3, 60};
    int idx = find_first_negative(data);
    std::cout << "First negative at index: " << idx << "\n\n";

    // Validation
    std::cout << "Validation:\n";
    process_value(42);
    process_value(999);
    process_value(5000);

    return 0;
}

// Expected output:
// === [[likely]] and [[unlikely]] Attributes ===
//
// safe_divide(100, 7) = 14
// safe_divide(42, 0)  =   Error: division by zero!
// 0
//
// Cache lookups:
//   lookup(5) = 26 (miss)
//   lookup(5) = 26 (hit)
//   lookup(3) = 10 (miss)
//
// HTTP status codes:
//   200 -> OK
//   301 -> Moved Permanently
//   404 -> Not Found
//   500 -> Internal Server Error
//   418 -> Unknown
//
// First negative at index: 5
//
// Validation:
//   Value 5000 out of range!
