// CodeNebula - C++20 Example: std::ranges::values_view
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_values_view.cpp

#include <iostream>
#include <ranges>
#include <vector>
#include <map>
#include <string>

int main() {
    // values_view extracts the second element from pair-like ranges
    std::map<std::string, int> scores = {
        {"Alice", 95}, {"Bob", 87}, {"Charlie", 92},
        {"Diana", 78}, {"Eve", 99}
    };

    // Extract all values from a map
    std::cout << "Scores (values): ";
    for (int score : std::views::values(scores))
        std::cout << score << " ";
    std::cout << "\n";

    // Using pipe syntax
    std::cout << "Scores via pipe: ";
    for (int score : scores | std::views::values)
        std::cout << score << " ";
    std::cout << "\n";

    // Compute statistics using values_view
    int total = 0, count = 0;
    for (int v : scores | std::views::values) { total += v; ++count; }
    std::cout << "\nAverage score: " << static_cast<double>(total) / count << "\n";

    // Works with vector of pairs
    std::vector<std::pair<std::string, double>> products = {
        {"Laptop", 999.99}, {"Phone", 699.50},
        {"Tablet", 449.00}, {"Watch", 299.95}
    };
    std::cout << "\nPrices: ";
    for (double price : products | std::views::values)
        std::cout << "$" << price << " ";
    std::cout << "\n";

    // Combine values_view with filter
    std::cout << "High scores (>90): ";
    for (int score : scores | std::views::values
                            | std::views::filter([](int s) { return s > 90; }))
        std::cout << score << " ";
    std::cout << "\n";

    // Chain with transform
    std::cout << "Discounted prices: ";
    for (double price : products | std::views::values
                                 | std::views::transform([](double p) { return p * 0.9; }))
        std::cout << "$" << price << " ";
    std::cout << "\n";

    // Count values matching a predicate
    auto high_count = std::ranges::count_if(
        scores | std::views::values, [](int s) { return s >= 90; });
    std::cout << "\nStudents scoring 90+: " << high_count << "\n";
    return 0;
}
