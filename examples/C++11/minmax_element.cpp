// CodeNebula - C++11 Example: std::minmax_element in Range
// Compile: g++ -std=c++11 -Wall -Wextra -o example minmax_element.cpp

// std::minmax_element finds both the minimum and maximum elements in a range
// in a single pass, returning a pair of iterators. It is more efficient than
// calling std::min_element and std::max_element separately.

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>

int main() {
    // Find min and max in a vector of integers
    std::vector<int> nums = {5, 2, 8, 1, 9, 3, 7};

    auto result = std::minmax_element(nums.begin(), nums.end());
    std::cout << "Min: " << *result.first << " at index "
              << std::distance(nums.begin(), result.first) << std::endl;
    std::cout << "Max: " << *result.second << " at index "
              << std::distance(nums.begin(), result.second) << std::endl;

    // Find min and max string by length
    std::vector<std::string> words = {"cat", "elephant", "hi", "dog", "giraffe"};

    auto str_result = std::minmax_element(words.begin(), words.end(),
        [](const std::string& a, const std::string& b) {
            return a.size() < b.size();
        });
    std::cout << "Shortest word: " << *str_result.first << std::endl;
    std::cout << "Longest word: " << *str_result.second << std::endl;

    // Works with arrays
    int arr[] = {42, 17, 93, 5, 68};
    auto arr_result = std::minmax_element(std::begin(arr), std::end(arr));
    std::cout << "Array min: " << *arr_result.first << std::endl;
    std::cout << "Array max: " << *arr_result.second << std::endl;

    // Calculate the range (max - min)
    std::vector<double> temps = {22.5, 18.3, 31.7, 15.0, 27.8};
    auto temp_result = std::minmax_element(temps.begin(), temps.end());
    double range = *temp_result.second - *temp_result.first;
    std::cout << "Temperature range: " << *temp_result.first << " to "
              << *temp_result.second << " (span: " << range << ")" << std::endl;

    // Single element
    std::vector<int> single = {42};
    auto s = std::minmax_element(single.begin(), single.end());
    std::cout << "Single element: min=" << *s.first
              << ", max=" << *s.second << std::endl;

    // With duplicate min/max values
    std::vector<int> dups = {3, 1, 4, 1, 5, 9, 5};
    auto d = std::minmax_element(dups.begin(), dups.end());
    std::cout << "With duplicates: min=" << *d.first
              << ", max=" << *d.second << std::endl;

    return 0;
}

// Expected output:
// Min: 1 at index 3
// Max: 9 at index 4
// Shortest word: hi
// Longest word: elephant
// Array min: 5
// Array max: 93
// Temperature range: 15 to 31.7 (span: 16.7)
// Single element: min=42, max=42
// With duplicates: min=1, max=9
