// CodeNebula - C++20 Example: std::totally_ordered Concept
// Compile: g++ -std=c++20 -Wall -Wextra -o example totally_ordered.cpp

// std::totally_ordered<T> requires ==, !=, <, >, <=, >= operators that
// establish a strict total order. This is essential for sorting and
// ordered containers.

#include <algorithm>
#include <concepts>
#include <iostream>
#include <string>
#include <vector>

struct Temperature {
    double celsius;
    auto operator<=>(const Temperature&) const = default;  // C++20 spaceship
};

// Clamp a value to a range (requires total ordering)
template <std::totally_ordered T>
T clamp_value(const T& val, const T& low, const T& high) {
    if (val < low) return low;
    if (val > high) return high;
    return val;
}

// Find min and max in a range
template <std::totally_ordered T>
std::pair<T, T> min_max(const std::vector<T>& vec) {
    T lo = vec[0], hi = vec[0];
    for (const auto& v : vec) {
        if (v < lo) lo = v;
        if (v > hi) hi = v;
    }
    return {lo, hi};
}

// Insertion sort (requires totally_ordered)
template <std::totally_ordered T>
void insertion_sort(std::vector<T>& vec) {
    for (std::size_t i = 1; i < vec.size(); ++i) {
        T key = vec[i];
        int j = static_cast<int>(i) - 1;
        while (j >= 0 && vec[j] > key) {
            vec[j + 1] = vec[j];
            --j;
        }
        vec[j + 1] = key;
    }
}

int main() {
    // Clamp values
    std::cout << "clamp(15, 0, 10): " << clamp_value(15, 0, 10) << "\n";
    std::cout << "clamp(-5, 0, 10): " << clamp_value(-5, 0, 10) << "\n";
    std::cout << "clamp(5, 0, 10): " << clamp_value(5, 0, 10) << "\n";

    // Min/max
    std::vector<int> nums = {38, 12, 95, 7, 63};
    auto [lo, hi] = min_max(nums);
    std::cout << "\nMin: " << lo << ", Max: " << hi << "\n";

    // Sort integers
    insertion_sort(nums);
    std::cout << "Sorted: ";
    for (int n : nums) std::cout << n << " ";
    std::cout << "\n";

    // Sort strings (lexicographic total order)
    std::vector<std::string> words = {"cherry", "apple", "banana"};
    insertion_sort(words);
    std::cout << "Sorted: ";
    for (const auto& w : words) std::cout << w << " ";
    std::cout << "\n";

    // Temperature with defaulted <=>
    Temperature t1{36.6}, t2{37.5}, t3{35.0};
    std::cout << "\n36.6 < 37.5: " << (t1 < t2) << "\n";
    std::cout << "totally_ordered<Temperature>: "
              << std::totally_ordered<Temperature> << "\n";

    return 0;
}

// Expected output:
// clamp(15, 0, 10): 10
// clamp(-5, 0, 10): 0
// clamp(5, 0, 10): 5
//
// Min: 7, Max: 95
// Sorted: 7 12 38 63 95
// Sorted: apple banana cherry
//
// 36.6 < 37.5: 1
// totally_ordered<Temperature>: 1
