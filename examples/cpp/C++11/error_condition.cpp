// CodeNebula - C++11 Example: std::error_condition
// Compile: g++ -std=c++11 -Wall -Wextra -o example error_condition.cpp

// std::error_condition represents a portable error condition, as opposed
// to std::error_code which is platform-specific. Use error_condition to
// compare against platform-independent error meanings.

#include <iostream>
#include <system_error>
#include <cerrno>

// Simulate a function returning platform-specific error_code
std::error_code try_operation(bool should_fail) {
    if (should_fail) {
        return std::error_code(EACCES, std::system_category());
    }
    return std::error_code();  // success
}

int main() {
    // error_condition from errc enum (portable)
    std::error_condition cond = std::errc::permission_denied;
    std::cout << "Condition: " << cond.message() << std::endl;
    std::cout << "Category:  " << cond.category().name() << std::endl;
    std::cout << "Value:     " << cond.value() << std::endl;

    // Compare error_code with error_condition (cross-platform)
    auto ec = try_operation(true);
    std::cout << "\nOperation returned: " << ec.message() << std::endl;

    // The key feature: compare platform error_code to portable condition
    if (ec == std::errc::permission_denied) {
        std::cout << "Matched: permission_denied (portable check)" << std::endl;
    }

    // Default condition is "no error"
    std::error_condition no_err;
    std::cout << "\nDefault condition: " << no_err.message() << std::endl;
    std::cout << "Is error: " << (no_err ? "yes" : "no") << std::endl;

    // Create from make_error_condition
    auto cond2 = std::make_error_condition(std::errc::no_such_file_or_directory);
    std::cout << "\nFile not found condition:" << std::endl;
    std::cout << "  Message: " << cond2.message() << std::endl;
    std::cout << "  Value:   " << cond2.value() << std::endl;

    // Demonstrate the error_code to error_condition mapping
    std::error_code platform_err(ENOENT, std::generic_category());
    std::error_condition default_cond = platform_err.default_error_condition();
    std::cout << "\nPlatform code -> condition:" << std::endl;
    std::cout << "  Code:      " << platform_err.message() << std::endl;
    std::cout << "  Condition: " << default_cond.message() << std::endl;
    std::cout << "  Match: " << (platform_err == cond2 ? "yes" : "no") << std::endl;

    // Multiple errc values for common checks
    std::cout << "\nCommon portable conditions:" << std::endl;
    auto conditions = {
        std::errc::file_exists,
        std::errc::is_a_directory,
        std::errc::timed_out,
        std::errc::resource_unavailable_try_again
    };
    for (auto e : conditions) {
        auto c = std::make_error_condition(e);
        std::cout << "  [" << c.value() << "] " << c.message() << std::endl;
    }

    return 0;
}

// Expected output (messages vary by platform):
// Condition: Permission denied
// Category:  generic
// Value:     13
//
// Operation returned: Permission denied
// Matched: permission_denied (portable check)
//
// Default condition: No error
// Is error: no
//
// File not found condition:
//   Message: No such file or directory
//   Value:   2
//
// Platform code -> condition:
//   Code:      No such file or directory
//   Condition: No such file or directory
//   Match: yes
//
// Common portable conditions:
//   [17] File exists
//   [21] Is a directory
//   [110] Connection timed out
//   [11] Resource temporarily unavailable
