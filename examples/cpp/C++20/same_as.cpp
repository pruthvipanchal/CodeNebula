// CodeNebula - C++20 Example: std::same_as Concept
// Compile: g++ -std=c++20 -Wall -Wextra -o example same_as.cpp

// std::same_as checks whether two types are exactly the same type.
// It is a symmetric concept: same_as<T, U> implies same_as<U, T>.

#include <concepts>
#include <iostream>
#include <string>

// Function constrained to accept only int parameters
template <std::same_as<int> T>
void process_int(T value) {
    std::cout << "Processing int: " << value << "\n";
}

// Overloaded function using same_as to distinguish types
template <typename T>
    requires std::same_as<T, std::string>
void describe(const T& s) {
    std::cout << "String with length " << s.size() << ": " << s << "\n";
}

template <typename T>
    requires std::same_as<T, double>
void describe(T d) {
    std::cout << "Double value: " << d << "\n";
}

// Compile-time type checking with same_as
template <typename T>
void check_type(T) {
    if constexpr (std::same_as<T, int>) {
        std::cout << "Type is exactly int\n";
    } else if constexpr (std::same_as<T, long>) {
        std::cout << "Type is exactly long\n";
    } else {
        std::cout << "Type is something else\n";
    }
}

int main() {
    // Demonstrate same_as constraint
    process_int(42);

    // Demonstrate overloaded describe
    describe(std::string("hello"));
    describe(3.14);

    // Demonstrate compile-time checks
    check_type(10);
    check_type(10L);
    check_type(10.0f);

    // Symmetry: same_as<int, int> and same_as<const int, const int>
    std::cout << "same_as<int, int>: " << std::same_as<int, int> << "\n";
    std::cout << "same_as<int, long>: " << std::same_as<int, long> << "\n";
    std::cout << "same_as<int, const int>: " << std::same_as<int, const int> << "\n";

    return 0;
}

// Expected output:
// Processing int: 42
// String with length 5: hello
// Double value: 3.14
// Type is exactly int
// Type is exactly long
// Type is something else
// same_as<int, int>: 1
// same_as<int, long>: 0
// same_as<int, const int>: 0
