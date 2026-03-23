// CodeNebula - C++11 Example: std::error_category
// Compile: g++ -std=c++11 -Wall -Wextra -o example error_category.cpp

// std::error_category is the base class for error category types.
// Each category defines a domain of error codes. You can create
// custom categories for your own library's error codes.

#include <iostream>
#include <system_error>
#include <string>

// Define custom error codes for a network library
enum class NetworkError {
    ok = 0,
    connection_refused = 1,
    timeout = 2,
    dns_failure = 3,
    ssl_error = 4
};

// Custom error category
class NetworkCategory : public std::error_category {
public:
    const char* name() const noexcept override {
        return "network";
    }

    std::string message(int ev) const override {
        switch (static_cast<NetworkError>(ev)) {
            case NetworkError::ok:                return "Success";
            case NetworkError::connection_refused: return "Connection refused";
            case NetworkError::timeout:            return "Connection timed out";
            case NetworkError::dns_failure:        return "DNS resolution failed";
            case NetworkError::ssl_error:          return "SSL/TLS error";
            default:                               return "Unknown network error";
        }
    }
};

// Singleton accessor for the category
const NetworkCategory& network_category() {
    static NetworkCategory instance;
    return instance;
}

// Helper to make error_code from our enum
std::error_code make_error_code(NetworkError e) {
    return {static_cast<int>(e), network_category()};
}

int main() {
    // Built-in categories
    std::cout << "Built-in categories:" << std::endl;
    std::cout << "  generic_category:  " << std::generic_category().name() << std::endl;
    std::cout << "  system_category:   " << std::system_category().name() << std::endl;

    // Categories are singletons -- identity comparison works
    const auto& g1 = std::generic_category();
    const auto& g2 = std::generic_category();
    std::cout << "  Same instance: " << (&g1 == &g2 ? "yes" : "no") << std::endl;

    // Custom category usage
    std::cout << "\nCustom network errors:" << std::endl;
    auto err1 = make_error_code(NetworkError::timeout);
    auto err2 = make_error_code(NetworkError::dns_failure);
    auto err3 = make_error_code(NetworkError::ok);

    std::cout << "  err1: [" << err1.category().name() << ":"
              << err1.value() << "] " << err1.message() << std::endl;
    std::cout << "  err2: [" << err2.category().name() << ":"
              << err2.value() << "] " << err2.message() << std::endl;
    std::cout << "  err3 is error: " << (err3 ? "yes" : "no") << std::endl;

    // Compare errors from different categories
    auto sys_err = std::error_code(2, std::generic_category());
    std::cout << "\nCross-category comparison:" << std::endl;
    std::cout << "  network:2 == generic:2 ? "
              << (err1 == sys_err ? "yes" : "no") << std::endl;

    return 0;
}

// Expected output:
// Built-in categories:
//   generic_category:  generic
//   system_category:   system
//   Same instance: yes
//
// Custom network errors:
//   err1: [network:2] Connection timed out
//   err2: [network:3] DNS resolution failed
//   err3 is error: no
//
// Cross-category comparison:
//   network:2 == generic:2 ? no
