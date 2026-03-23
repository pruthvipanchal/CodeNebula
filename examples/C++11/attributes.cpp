// CodeNebula - C++11 Example: Attributes
// Compile: g++ -std=c++11 -Wall -Wextra -o example attributes.cpp
//
// This example demonstrates:
// - [[noreturn]] attribute for functions that never return
// - [[carries_dependency]] attribute for dependency ordering
// - Standard attribute syntax [[...]] introduced in C++11
// - How attributes provide metadata to the compiler

#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>

// ============================================================
// 1. [[noreturn]] attribute
// ============================================================
// Tells the compiler this function never returns normally.
// This enables optimizations and suppresses warnings about
// missing return statements after calls to this function.

[[noreturn]] void throwError(const std::string& message) {
    throw std::runtime_error(message);
}

[[noreturn]] void fatalExit(const std::string& reason) {
    std::cerr << "FATAL: " << reason << std::endl;
    std::abort();
}

// ============================================================
// 2. Using [[noreturn]] in practice
// ============================================================
enum class ErrorCode { NONE, FILE_NOT_FOUND, PERMISSION_DENIED, UNKNOWN };

[[noreturn]] void handleFatalError(ErrorCode code) {
    switch (code) {
        case ErrorCode::FILE_NOT_FOUND:
            throw std::runtime_error("File not found");
        case ErrorCode::PERMISSION_DENIED:
            throw std::runtime_error("Permission denied");
        default:
            throw std::runtime_error("Unknown error");
    }
    // No return statement needed - compiler knows function never returns
}

int processFile(const std::string& filename) {
    if (filename.empty()) {
        handleFatalError(ErrorCode::FILE_NOT_FOUND);
        // Compiler knows code below this point is unreachable
    }
    return static_cast<int>(filename.length());
}

// ============================================================
// 3. [[carries_dependency]] attribute
// ============================================================
// Used in concurrent programming with memory ordering.
// Tells the compiler that a function carries a dependency
// chain, allowing it to avoid unnecessary memory fence
// instructions. Typically used with std::memory_order_consume.
//
// Note: In practice, most compilers treat memory_order_consume
// as memory_order_acquire, so this attribute is rarely needed.

// Example declaration (the attribute is on the parameter):
int processData([[carries_dependency]] int* data) {
    // The dependency chain from the pointer is preserved
    if (data != nullptr) {
        return *data + 1;
    }
    return 0;
}

// ============================================================
// 4. Attribute syntax overview
// ============================================================
class Calculator {
public:
    // Attributes can appear on declarations
    int add(int a, int b) { return a + b; }
    int subtract(int a, int b) { return a - b; }

    [[noreturn]] void unsupported() {
        throw std::logic_error("Operation not supported");
    }
};

int main() {
    std::cout << "=== C++11 Attributes ===" << std::endl;

    // Test [[noreturn]] with exception handling
    std::cout << "\n--- [[noreturn]] with exceptions ---" << std::endl;

    try {
        throwError("Test error message");
    } catch (const std::runtime_error& e) {
        std::cout << "  Caught: " << e.what() << std::endl;
    }

    try {
        handleFatalError(ErrorCode::FILE_NOT_FOUND);
    } catch (const std::runtime_error& e) {
        std::cout << "  Caught: " << e.what() << std::endl;
    }

    try {
        handleFatalError(ErrorCode::PERMISSION_DENIED);
    } catch (const std::runtime_error& e) {
        std::cout << "  Caught: " << e.what() << std::endl;
    }

    // processFile uses [[noreturn]] internally
    std::cout << "\n--- processFile ---" << std::endl;
    std::cout << "  processFile(\"data.txt\") = "
              << processFile("data.txt") << std::endl;
    try {
        processFile("");
    } catch (const std::runtime_error& e) {
        std::cout << "  processFile(\"\") threw: " << e.what() << std::endl;
    }

    // [[carries_dependency]]
    std::cout << "\n--- [[carries_dependency]] ---" << std::endl;
    int value = 42;
    std::cout << "  processData(&value) = " << processData(&value) << std::endl;
    std::cout << "  processData(nullptr) = " << processData(nullptr) << std::endl;

    // Calculator
    std::cout << "\n--- Calculator ---" << std::endl;
    Calculator calc;
    std::cout << "  add(5, 3) = " << calc.add(5, 3) << std::endl;
    try {
        calc.unsupported();
    } catch (const std::logic_error& e) {
        std::cout << "  unsupported() threw: " << e.what() << std::endl;
    }

    std::cout << "\nC++11 standard attributes: [[noreturn]], [[carries_dependency]]"
              << std::endl;

    return 0;
}

// Expected output:
// === C++11 Attributes ===
//
// --- [[noreturn]] with exceptions ---
//   Caught: Test error message
//   Caught: File not found
//   Caught: Permission denied
//
// --- processFile ---
//   processFile("data.txt") = 8
//   processFile("") threw: File not found
//
// --- [[carries_dependency]] ---
//   processData(&value) = 43
//   processData(nullptr) = 0
//
// --- Calculator ---
//   add(5, 3) = 8
//   unsupported() threw: Operation not supported
//
// C++11 standard attributes: [[noreturn]], [[carries_dependency]]
