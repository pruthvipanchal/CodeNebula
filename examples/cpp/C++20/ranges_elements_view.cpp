// CodeNebula - C++20 Example: std::ranges::elements_view
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_elements_view.cpp

#include <iostream>
#include <ranges>
#include <vector>
#include <tuple>
#include <string>

int main() {
    // Elements view extracts the Nth element from tuple-like ranges
    std::vector<std::tuple<int, std::string, double>> records = {
        {1, "Alice",   95.5},
        {2, "Bob",     87.3},
        {3, "Charlie", 92.1},
        {4, "Diana",   78.9},
        {5, "Eve",     99.0}
    };

    // Extract element 0 (IDs)
    std::cout << "IDs (element 0): ";
    for (int id : std::ranges::elements_view<decltype(std::views::all(records)), 0>(records))
        std::cout << id << " ";
    std::cout << "\n";

    // Using views::elements adaptor for element 1 (names)
    std::cout << "Names (element 1): ";
    for (const auto& name : records | std::views::elements<1>)
        std::cout << name << " ";
    std::cout << "\n";

    // Extract element 2 (scores)
    std::cout << "Scores (element 2): ";
    for (double score : records | std::views::elements<2>)
        std::cout << score << " ";
    std::cout << "\n";

    // Works with pairs too
    std::vector<std::pair<std::string, int>> inventory = {
        {"sword", 1}, {"potion", 5}, {"shield", 2}, {"arrow", 50}
    };

    std::cout << "\nItem names: ";
    for (const auto& item : inventory | std::views::elements<0>)
        std::cout << item << " ";
    std::cout << "\n";

    std::cout << "Quantities: ";
    for (int qty : inventory | std::views::elements<1>)
        std::cout << qty << " ";
    std::cout << "\n";

    // Combine elements_view with other views
    std::cout << "\nHigh scores (>90): ";
    for (const auto& [id, name, score] : records) {
        if (score > 90.0)
            std::cout << name << "(" << score << ") ";
    }
    std::cout << "\n";

    // Elements view with take
    std::cout << "First 3 names: ";
    for (const auto& name : records | std::views::elements<1> | std::views::take(3))
        std::cout << name << " ";
    std::cout << "\n";

    return 0;
}
