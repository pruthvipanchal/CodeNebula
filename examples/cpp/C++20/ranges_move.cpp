// CodeNebula - C++20 Example: ranges::move, move_backward
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_move.cpp

#include <iostream>
#include <ranges>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>

int main() {
    // ranges::move - move elements from source to destination
    std::vector<std::string> source = {"alpha", "beta", "gamma", "delta", "epsilon"};
    std::cout << "Before move - Source: ";
    for (const auto& s : source) std::cout << "'" << s << "' ";
    std::cout << "\n";

    std::vector<std::string> dest(source.size());
    std::ranges::move(source, dest.begin());
    std::cout << "After move - Source: ";
    for (const auto& s : source) std::cout << "'" << s << "' ";
    std::cout << "\nAfter move - Dest: ";
    for (const auto& s : dest) std::cout << "'" << s << "' ";
    std::cout << "\n";

    // ranges::move with integers (move == copy for trivial types)
    std::vector<int> nums = {10, 20, 30, 40, 50};
    std::vector<int> num_dest(nums.size());
    auto [in_end, out_end] = std::ranges::move(nums, num_dest.begin());
    std::cout << "\nMoved integers: ";
    for (int n : num_dest) std::cout << n << " ";
    std::cout << "\nInput fully consumed: " << std::boolalpha
              << (in_end == nums.end()) << "\n";

    // ranges::move_backward - move elements backward
    std::vector<std::string> data = {"one", "two", "three", "four", "five", "", "", ""};
    std::ranges::move_backward(data.begin(), data.begin() + 5, data.end());
    std::cout << "\nShifted right by 3: ";
    for (const auto& s : data) std::cout << "'" << s << "' ";
    std::cout << "\n";

    // Move from a subrange
    std::vector<std::string> words = {"hello", "beautiful", "world", "out", "there"};
    std::vector<std::string> selected(2);
    std::ranges::move(words.begin() + 1, words.begin() + 3, selected.begin());
    std::cout << "\nMoved subrange: ";
    for (const auto& s : selected) std::cout << "'" << s << "' ";
    std::cout << "\n";

    // Move unique_ptr (non-copyable types)
    std::vector<std::unique_ptr<int>> ptrs;
    ptrs.push_back(std::make_unique<int>(100));
    ptrs.push_back(std::make_unique<int>(200));
    ptrs.push_back(std::make_unique<int>(300));

    std::vector<std::unique_ptr<int>> ptr_dest(ptrs.size());
    std::ranges::move(ptrs, ptr_dest.begin());
    std::cout << "\nMoved unique_ptrs: ";
    for (const auto& p : ptr_dest)
        if (p) std::cout << *p << " ";
    std::cout << "\n";
    return 0;
}
