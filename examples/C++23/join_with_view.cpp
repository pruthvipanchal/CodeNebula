// CodeNebula - C++23 Example: std::ranges::join_with_view
// Compile: g++ -std=c++23 -Wall -Wextra -o example join_with_view.cpp
// Note: Requires GCC 13+ / Clang 17+

// std::ranges::join_with_view flattens a range of ranges, inserting a
// delimiter (element or pattern) between each inner range. It extends
// join_view by adding separator support, similar to string join operations.

#include <iostream>
#include <ranges>
#include <vector>
#include <string>
#include <string_view>

int main() {
    // Join strings with a character delimiter
    std::vector<std::string> words = {"Hello", "World", "from", "C++23"};
    std::cout << "=== Join words with space ===" << std::endl;
    std::cout << "  ";
    for (char c : words | std::views::join_with(' ')) {
        std::cout << c;
    }
    std::cout << std::endl;

    // Join with a string delimiter
    std::cout << "\n=== Join words with ' - ' ===" << std::endl;
    std::string_view sep = " - ";
    std::cout << "  ";
    for (char c : words | std::views::join_with(sep)) {
        std::cout << c;
    }
    std::cout << std::endl;

    // Join number groups with a separator element
    std::vector<std::vector<int>> groups = {{1, 2, 3}, {4, 5}, {6, 7, 8, 9}};
    std::cout << "\n=== Join number groups with 0 ===" << std::endl;
    std::cout << "  ";
    for (auto val : groups | std::views::join_with(0)) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Join with a multi-element separator
    std::vector<int> separator = {-1, -1};
    std::cout << "\n=== Join groups with [-1, -1] separator ===" << std::endl;
    std::cout << "  ";
    for (auto val : groups | std::views::join_with(separator)) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Practical: build a CSV-like line
    std::vector<std::string> fields = {"Alice", "30", "Engineer", "NYC"};
    std::cout << "\n=== CSV line ===" << std::endl;
    std::cout << "  ";
    for (char c : fields | std::views::join_with(',')) {
        std::cout << c;
    }
    std::cout << std::endl;

    // Join path components
    std::vector<std::string> path_parts = {"usr", "local", "bin", "app"};
    std::cout << "\n=== Unix path ===" << std::endl;
    std::cout << "  /";
    for (char c : path_parts | std::views::join_with('/')) {
        std::cout << c;
    }
    std::cout << std::endl;

    return 0;
}

// Expected output:
// === Join words with space ===
//   Hello World from C++23
//
// === Join words with ' - ' ===
//   Hello - World - from - C++23
//
// === Join number groups with 0 ===
//   1 2 3 0 4 5 0 6 7 8 9
//
// === Join groups with [-1, -1] separator ===
//   1 2 3 -1 -1 4 5 -1 -1 6 7 8 9
//
// === CSV line ===
//   Alice,30,Engineer,NYC
//
// === Unix path ===
//   /usr/local/bin/app
