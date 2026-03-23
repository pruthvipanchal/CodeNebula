// CodeNebula - C++11 Example: system_error
// Compile: g++ -std=c++11 -Wall -Wextra -o example system_error.cpp

// Demonstrates std::system_error with std::error_code for portable
// system error handling. Replaces raw errno checking with type-safe errors.

#include <iostream>
#include <system_error>
#include <cerrno>
#include <fstream>
#include <string>

// Function that uses error_code for non-throwing error reporting
bool open_file(const std::string& path, std::error_code& ec) {
    std::ifstream file(path);
    if (!file.is_open()) {
        ec = std::make_error_code(std::errc::no_such_file_or_directory);
        return false;
    }
    ec.clear();
    return true;
}

int main() {
    std::cout << "=== std::system_error ===" << std::endl;

    // Create error codes from errc enum
    std::error_code ec1 = std::make_error_code(std::errc::permission_denied);
    std::error_code ec2 = std::make_error_code(std::errc::no_such_file_or_directory);
    std::error_code ec_ok;  // default is "no error"

    std::cout << "permission_denied:  " << ec1.message() << " (" << ec1.value() << ")" << std::endl;
    std::cout << "no_such_file:       " << ec2.message() << " (" << ec2.value() << ")" << std::endl;
    std::cout << "no error:           " << ec_ok.message() << " (" << ec_ok.value() << ")" << std::endl;
    std::cout << "ec_ok is false:     " << (!ec_ok ? "yes" : "no") << std::endl;

    // Using error_code with a function
    std::error_code ec;
    bool ok = open_file("/nonexistent/file.txt", ec);
    std::cout << "\nopen_file result: " << (ok ? "success" : "failed") << std::endl;
    if (ec) {
        std::cout << "Error: " << ec.message() << std::endl;
        std::cout << "Category: " << ec.category().name() << std::endl;
    }

    // Throwing system_error
    try {
        throw std::system_error(ec2, "Failed to open config");
    } catch (const std::system_error& e) {
        std::cout << "\nCaught system_error:" << std::endl;
        std::cout << "  what(): " << e.what() << std::endl;
        std::cout << "  code:   " << e.code().value() << std::endl;
    }

    std::cout << "\nAll checks passed!" << std::endl;
    return 0;
}

// Expected output (messages are platform-dependent):
// === std::system_error ===
// permission_denied:  Permission denied (13)
// no_such_file:       No such file or directory (2)
// no error:           No error (0)
// ec_ok is false:     yes
//
// open_file result: failed
// Error: No such file or directory
// Category: generic
//
// Caught system_error:
//   what(): Failed to open config: No such file or directory
//   code:   2
//
// All checks passed!
