// CodeNebula - C++26 Example: std::print Improvements
// Compile: g++ -std=c++26 -Wall -Wextra -o example print_improvements.cpp
// Note: Requires C++26 compiler support (GCC 15+ / Clang 19+ expected)

// C++26 improves std::print (introduced in C++23) with better range
// support, improved Unicode handling, and std::println enhancements.
// std::print writes formatted output directly without stream overhead.

#include <iostream>
#include <string>
#include <vector>
#include <map>

// --- C++26 std::print Improvements ---
//
// #include <print>
//
// std::print("Hello, {}!\n", "world");           // Direct formatted output
// std::println("Value: {}", 42);                  // With automatic newline
//
// // C++26: print ranges directly
// std::vector<int> v = {1, 2, 3};
// std::println("{}", v);                           // [1, 2, 3]
//
// // C++26: print to any output stream
// std::print(std::cerr, "Error: {}\n", msg);
//
// // C++26: improved Unicode support
// std::println("Unicode: {} {} {}", "\u2603", "\u2764", "\u2605");
//
// // C++26: print with fill and alignment
// std::println("{:*>10}", "hi");                   // ********hi
// std::println("{:*<10}", "hi");                   // hi********

// --- Simulation using C++20 features ---

// Simple print simulation (C++23 std::print would handle this)
template<typename T>
void sim_println(const std::string& label, const T& value) {
    std::cout << label << value << std::endl;
}

void sim_print_vec(const std::vector<int>& v) {
    std::cout << "[";
    for (std::size_t i = 0; i < v.size(); ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << v[i];
    }
    std::cout << "]" << std::endl;
}

int main() {
    std::cout << "=== C++26 std::print Improvements (Simulated) ===" << std::endl;

    // Basic formatted output
    std::cout << "Hello, world!" << std::endl;
    std::cout << "Value: " << 42 << std::endl;
    std::cout << "Pi: " << 3.14159 << std::endl;

    // Range printing (C++26: std::println("{}", v))
    std::vector<int> nums = {10, 20, 30, 40, 50};
    std::cout << "Vector: ";
    sim_print_vec(nums);

    // Multiple arguments (C++26: std::println("{} + {} = {}", a, b, a+b))
    int a = 3, b = 7;
    std::cout << a << " + " << b << " = " << (a + b) << std::endl;

    // Alignment simulation (C++26: std::println("{:*>10}", "hi"))
    std::cout << "Right-aligned: ";
    for (int i = 0; i < 8; ++i) std::cout << '*';
    std::cout << "hi" << std::endl;

    std::cout << "Left-aligned:  hi";
    for (int i = 0; i < 8; ++i) std::cout << '*';
    std::cout << std::endl;

    // Centered
    std::cout << "Centered:  ";
    for (int i = 0; i < 4; ++i) std::cout << '*';
    std::cout << "hi";
    for (int i = 0; i < 4; ++i) std::cout << '*';
    std::cout << std::endl;

    std::cout << "std::print/println: clean, type-safe formatted I/O." << std::endl;
    return 0;
}

// Expected output:
// === C++26 std::print Improvements (Simulated) ===
// Hello, world!
// Value: 42
// Pi: 3.14159
// Vector: [10, 20, 30, 40, 50]
// 3 + 7 = 10
// Right-aligned: ********hi
// Left-aligned:  hi********
// Centered:  ****hi****
// std::print/println: clean, type-safe formatted I/O.
