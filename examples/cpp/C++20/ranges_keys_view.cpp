// CodeNebula - C++20 Example: std::ranges::keys_view
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_keys_view.cpp

#include <iostream>
#include <ranges>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

int main() {
    // keys_view extracts the first element from pair-like ranges
    std::map<std::string, int> scores = {
        {"Alice", 95}, {"Bob", 87}, {"Charlie", 92},
        {"Diana", 78}, {"Eve", 99}
    };

    // Extract all keys from a map
    std::cout << "Student names (keys): ";
    for (const auto& name : std::views::keys(scores))
        std::cout << name << " ";
    std::cout << "\n";

    // Using pipe syntax
    std::cout << "Names via pipe: ";
    for (const auto& name : scores | std::views::keys)
        std::cout << name << " ";
    std::cout << "\n";

    // Works with vector of pairs
    std::vector<std::pair<int, std::string>> id_names = {
        {101, "Engineering"}, {102, "Marketing"},
        {103, "Finance"},     {104, "Research"}
    };
    std::cout << "\nDepartment IDs: ";
    for (int id : id_names | std::views::keys)
        std::cout << id << " ";
    std::cout << "\n";

    // Combine keys_view with algorithms
    auto keys = scores | std::views::keys;
    auto it = std::ranges::find(keys, "Charlie");
    if (it != keys.end())
        std::cout << "\nFound key: " << *it << "\n";

    // Count keys matching a condition
    auto long_names = std::ranges::count_if(
        scores | std::views::keys,
        [](const std::string& name) { return name.size() > 3; }
    );
    std::cout << "Keys longer than 3 chars: " << long_names << "\n";

    // Chain keys_view with take
    std::cout << "\nFirst 3 keys: ";
    for (const auto& name : scores | std::views::keys | std::views::take(3))
        std::cout << name << " ";
    std::cout << "\n";

    // keys_view with multimap
    std::multimap<char, int> grades = {
        {'A', 95}, {'B', 85}, {'A', 92}, {'C', 75}, {'B', 88}
    };
    std::cout << "Grade letters: ";
    for (char g : grades | std::views::keys) std::cout << g << " ";
    std::cout << "\n";
    return 0;
}
