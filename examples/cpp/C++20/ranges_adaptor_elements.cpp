// CodeNebula - C++20 Example: views::elements, views::keys, views::values
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_adaptor_elements.cpp

#include <iostream>
#include <ranges>
#include <vector>
#include <map>
#include <tuple>
#include <string>

int main() {
    // views::keys - extract first element of pair-like types
    std::map<std::string, int> population = {
        {"Tokyo", 37400}, {"Delhi", 30290}, {"Shanghai", 27058},
        {"Beijing", 20463}, {"Mumbai", 20411}
    };

    std::cout << "Cities (keys): ";
    for (const auto& city : population | std::views::keys)
        std::cout << city << " ";
    std::cout << "\n";

    // views::values - extract second element
    std::cout << "Populations (values): ";
    for (int pop : population | std::views::values) std::cout << pop << " ";
    std::cout << "\n";

    // views::elements<N> - extract Nth element from tuple-like
    std::vector<std::tuple<int, std::string, double>> students = {
        {1, "Alice", 3.9}, {2, "Bob", 3.5},
        {3, "Charlie", 3.7}, {4, "Diana", 3.95}
    };

    std::cout << "\nStudent IDs: ";
    for (int id : students | std::views::elements<0>) std::cout << id << " ";
    std::cout << "\nStudent names: ";
    for (const auto& name : students | std::views::elements<1>)
        std::cout << name << " ";
    std::cout << "\nStudent GPAs: ";
    for (double gpa : students | std::views::elements<2>) std::cout << gpa << " ";
    std::cout << "\n";

    // Combine with filter: high-population cities
    std::cout << "\nLarge cities (>25000): ";
    for (const auto& city : population
             | std::views::filter([](const auto& p) { return p.second > 25000; })
             | std::views::keys)
        std::cout << city << " ";
    std::cout << "\n";

    // Combine values with transform
    std::cout << "Populations in millions: ";
    for (double pop : population | std::views::values
                                 | std::views::transform([](int p) { return p / 1000.0; }))
        std::cout << pop << "M ";
    std::cout << "\n";

    // keys/values on vector of pairs
    std::vector<std::pair<char, int>> letter_scores = {
        {'a', 1}, {'b', 3}, {'c', 3}, {'d', 2}, {'e', 1}
    };
    std::cout << "\nLetters: ";
    for (char c : letter_scores | std::views::keys) std::cout << c << " ";
    std::cout << "\nScores: ";
    for (int s : letter_scores | std::views::values) std::cout << s << " ";
    std::cout << "\n";

    return 0;
}
