// CodeNebula - C++11 Example: std::error_code
// Compile: g++ -std=c++11 -Wall -Wextra -o example error_code.cpp

// std::error_code holds a platform-dependent error value and a pointer
// to an error_category. It provides a portable way to represent and
// transport error conditions from the OS or library level.

#include <iostream>
#include <system_error>
#include <cerrno>
#include <fstream>
#include <string>

// Simulate an operation that can fail
std::error_code open_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return std::error_code(ENOENT, std::generic_category());
    }
    return std::error_code();  // success (no error)
}

int main() {
    // Default construction: no error
    std::error_code ec;
    std::cout << "Default error_code: " << ec.value()
              << " (" << ec.message() << ")" << std::endl;
    std::cout << "Bool check: " << (ec ? "error" : "no error") << std::endl;

    // Create from errno values using generic_category
    std::error_code perm_denied(EACCES, std::generic_category());
    std::cout << "\nPermission denied:" << std::endl;
    std::cout << "  Value: " << perm_denied.value() << std::endl;
    std::cout << "  Message: " << perm_denied.message() << std::endl;
    std::cout << "  Category: " << perm_denied.category().name() << std::endl;

    // Create from errc enum (portable error codes)
    auto no_mem = std::make_error_code(std::errc::not_enough_memory);
    std::cout << "\nOut of memory:" << std::endl;
    std::cout << "  Value: " << no_mem.value() << std::endl;
    std::cout << "  Message: " << no_mem.message() << std::endl;

    // Use in a function
    auto result = open_file("nonexistent_file.txt");
    if (result) {
        std::cout << "\nFile open failed: " << result.message() << std::endl;
    }

    // Compare error codes
    auto err1 = std::make_error_code(std::errc::no_such_file_or_directory);
    auto err2 = std::make_error_code(std::errc::no_such_file_or_directory);
    std::cout << "\nerr1 == err2: " << (err1 == err2 ? "true" : "false") << std::endl;

    // Clear an error code
    std::error_code clearable = err1;
    std::cout << "Before clear: " << clearable.message() << std::endl;
    clearable.clear();
    std::cout << "After clear: " << clearable.message() << std::endl;
    std::cout << "Is cleared: " << (!clearable ? "yes" : "no") << std::endl;

    return 0;
}

// Expected output (messages vary by platform):
// Default error_code: 0 (No error)
// Bool check: no error
//
// Permission denied:
//   Value: 13
//   Message: Permission denied
//   Category: generic
//
// Out of memory:
//   Value: 12
//   Message: Not enough space
//
// File open failed: No such file or directory
//
// err1 == err2: true
// Before clear: No such file or directory
// After clear: No error
// Is cleared: yes
