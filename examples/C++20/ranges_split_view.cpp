// CodeNebula - C++20 Example: std::ranges::split_view
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_split_view.cpp

#include <ranges>
#include <string>
#include <string_view>
#include <vector>
#include <iostream>

// std::ranges::split_view / std::views::split splits a range into
// subranges using a delimiter (element or pattern). Each subrange
// is a view over the original data.

// Helper to print a split view's subranges
void print_parts(auto view, const char* label) {
    std::cout << label << ": ";
    for (auto part : view) {
        std::cout << "[";
        for (auto ch : part) std::cout << ch;
        std::cout << "] ";
    }
    std::cout << "\n";
}

int main() {
    using namespace std::string_view_literals;

    // Split a string by a single character
    std::string csv = "apple,banana,cherry,date";
    auto by_comma = csv | std::views::split(',');
    print_parts(by_comma, "Split by ','");

    // Split by a string pattern
    std::string text = "one--two--three--four";
    auto by_dashes = text | std::views::split("--"sv);
    print_parts(by_dashes, "Split by '--'");

    // Split and collect into vector of strings
    std::string data = "10:20:30:40:50";
    std::vector<std::string> tokens;
    for (auto part : data | std::views::split(':')) {
        tokens.emplace_back(part.begin(), part.end());
    }
    std::cout << "Tokens: ";
    for (const auto& t : tokens) std::cout << "[" << t << "] ";
    std::cout << "\n";

    // Split with empty parts (consecutive delimiters)
    std::string with_empty = "a,,b,,c";
    auto parts = with_empty | std::views::split(',');
    std::cout << "With empties: ";
    for (auto part : parts) {
        std::cout << "[";
        for (char c : part) std::cout << c;
        std::cout << "] ";
    }
    std::cout << "\n";

    // Split integers in a range by a sentinel value
    std::vector<int> nums = {1, 2, 0, 3, 4, 0, 5};
    auto groups = nums | std::views::split(0);
    std::cout << "Int groups: ";
    for (auto group : groups) {
        std::cout << "{ ";
        for (int n : group) std::cout << n << " ";
        std::cout << "} ";
    }
    std::cout << "\n";
    return 0;
}
