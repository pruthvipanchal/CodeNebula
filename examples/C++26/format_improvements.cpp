// CodeNebula - C++26 Example: std::format Range Formatting Improvements
// Compile: g++ -std=c++26 -Wall -Wextra -o example format_improvements.cpp
// Note: Requires C++26 compiler support (GCC 15+ / Clang 19+ expected)

// C++26 enhances std::format with improved range formatting, including
// better control over delimiters, nested range formatting, and
// formatting of tuple-like types and map entries.

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>

// --- C++26 std::format Range Improvements ---
//
// #include <format>
//
// std::vector<int> v = {1, 2, 3, 4, 5};
// std::cout << std::format("{}", v);          // [1, 2, 3, 4, 5]
// std::cout << std::format("{::>3}", v);      // [  1,   2,   3,   4,   5]
//
// std::map<std::string, int> m = {{"a", 1}, {"b", 2}};
// std::cout << std::format("{}", m);          // {"a": 1, "b": 2}
//
// // Nested ranges
// std::vector<std::vector<int>> mat = {{1,2},{3,4}};
// std::cout << std::format("{}", mat);        // [[1, 2], [3, 4]]
//
// // C++26: improved escape handling, debug format for strings
// std::cout << std::format("{:?}", "hello\n"); // "hello\n" (escaped)

// --- Simulation using C++20 features ---

template<typename T>
std::string format_vector(const std::vector<T>& v) {
    std::ostringstream oss;
    oss << "[";
    for (std::size_t i = 0; i < v.size(); ++i) {
        if (i > 0) oss << ", ";
        oss << v[i];
    }
    oss << "]";
    return oss.str();
}

std::string format_map(const std::map<std::string, int>& m) {
    std::ostringstream oss;
    oss << "{";
    bool first = true;
    for (const auto& [k, v] : m) {
        if (!first) oss << ", ";
        oss << "\"" << k << "\": " << v;
        first = false;
    }
    oss << "}";
    return oss.str();
}

std::string format_matrix(const std::vector<std::vector<int>>& mat) {
    std::ostringstream oss;
    oss << "[";
    for (std::size_t i = 0; i < mat.size(); ++i) {
        if (i > 0) oss << ", ";
        oss << format_vector(mat[i]);
    }
    oss << "]";
    return oss.str();
}

int main() {
    std::cout << "=== C++26 std::format Improvements (Simulated) ===" << std::endl;

    // Range formatting
    std::vector<int> nums = {1, 2, 3, 4, 5};
    std::cout << "Vector: " << format_vector(nums) << std::endl;

    // Map formatting
    std::map<std::string, int> scores = {{"Alice", 95}, {"Bob", 87}, {"Carol", 92}};
    std::cout << "Map: " << format_map(scores) << std::endl;

    // Nested range formatting
    std::vector<std::vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    std::cout << "Matrix: " << format_matrix(matrix) << std::endl;

    // Debug string format (escaped output)
    std::string s = "hello\tworld\n";
    std::cout << "Debug format: \"hello\\tworld\\n\"" << std::endl;

    // Empty containers
    std::cout << "Empty vec: " << format_vector(std::vector<int>{}) << std::endl;
    std::cout << "Single:    " << format_vector(std::vector<int>{42}) << std::endl;

    std::cout << "C++26 format makes ranges directly printable." << std::endl;
    return 0;
}

// Expected output:
// === C++26 std::format Improvements (Simulated) ===
// Vector: [1, 2, 3, 4, 5]
// Map: {"Alice": 95, "Bob": 87, "Carol": 92}
// Matrix: [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
// Debug format: "hello\tworld\n"
// Empty vec: []
// Single:    [42]
// C++26 format makes ranges directly printable.
