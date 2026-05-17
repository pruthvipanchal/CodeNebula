// CodeNebula - C++20 Example: std::equality_comparable Concept
// Compile: g++ -std=c++20 -Wall -Wextra -o example equality_comparable.cpp

// std::equality_comparable<T> is satisfied when T supports == and !=
// operators that return bool. std::equality_comparable_with<T, U>
// extends this to cross-type comparisons.

#include <concepts>
#include <iostream>
#include <string>
#include <vector>

struct Point {
    int x, y;
    bool operator==(const Point&) const = default;  // C++20 defaulted
};

struct Color {
    int r, g, b;
    // No operator== defined
};

// Find an element in a range (requires equality_comparable)
template <std::equality_comparable T>
int find_index(const std::vector<T>& vec, const T& target) {
    for (std::size_t i = 0; i < vec.size(); ++i) {
        if (vec[i] == target) return static_cast<int>(i);
    }
    return -1;
}

// Count occurrences
template <std::equality_comparable T>
int count(const std::vector<T>& vec, const T& target) {
    int result = 0;
    for (const auto& elem : vec) {
        if (elem == target) ++result;
    }
    return result;
}

// Check all elements are equal
template <std::equality_comparable T>
bool all_equal(const std::vector<T>& vec) {
    if (vec.empty()) return true;
    for (std::size_t i = 1; i < vec.size(); ++i) {
        if (!(vec[i] == vec[0])) return false;
    }
    return true;
}

int main() {
    // Find in vector of ints
    std::vector<int> nums = {10, 20, 30, 40, 50};
    std::cout << "Index of 30: " << find_index(nums, 30) << "\n";
    std::cout << "Index of 99: " << find_index(nums, 99) << "\n";

    // Find in vector of strings
    std::vector<std::string> words = {"apple", "banana", "cherry"};
    std::cout << "Index of banana: " << find_index(words, std::string("banana")) << "\n";

    // Count occurrences
    std::vector<int> data = {1, 2, 3, 2, 4, 2, 5};
    std::cout << "Count of 2: " << count(data, 2) << "\n";

    // Find with Points (uses defaulted ==)
    std::vector<Point> pts = {{0,0}, {1,2}, {3,4}};
    std::cout << "Index of (1,2): " << find_index(pts, Point{1, 2}) << "\n";

    // All equal check
    std::vector<int> same = {7, 7, 7, 7};
    std::vector<int> diff = {7, 7, 8, 7};
    std::cout << "All equal {7,7,7,7}: " << all_equal(same) << "\n";
    std::cout << "All equal {7,7,8,7}: " << all_equal(diff) << "\n";

    // Concept checks
    std::cout << "\nEquality comparable:\n";
    std::cout << "int: " << std::equality_comparable<int> << "\n";
    std::cout << "Point: " << std::equality_comparable<Point> << "\n";
    std::cout << "Color: " << std::equality_comparable<Color> << "\n";

    return 0;
}

// Expected output:
// Index of 30: 2
// Index of 99: -1
// Index of banana: 1
// Count of 2: 3
// Index of (1,2): 1
// All equal {7,7,7,7}: 1
// All equal {7,7,8,7}: 0
//
// Equality comparable:
// int: 1
// Point: 1
// Color: 0
