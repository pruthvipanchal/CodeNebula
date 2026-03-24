// CodeNebula - C++20 Example: std::relation Concept
// Compile: g++ -std=c++20 -Wall -Wextra -o example relation.cpp

// std::relation<R, T, U> is satisfied when R is a binary predicate that
// can be called with all combinations of T and U arguments. Relations
// are used for comparisons, orderings, and equivalence checks.

#include <concepts>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

// Custom relation: checks if two strings share the same first character
struct SameInitial {
    bool operator()(const std::string& a, const std::string& b) const {
        return !a.empty() && !b.empty() && a[0] == b[0];
    }
};

// Sort using any relation as comparator
template <typename T, std::relation<T, T> Comp>
void bubble_sort(std::vector<T>& vec, Comp comp) {
    for (std::size_t i = 0; i < vec.size(); ++i) {
        for (std::size_t j = i + 1; j < vec.size(); ++j) {
            if (comp(vec[j], vec[i])) {
                std::swap(vec[i], vec[j]);
            }
        }
    }
}

// Group elements that are equivalent under a relation
template <typename T, std::relation<T, T> Rel>
std::vector<std::vector<T>> group_by(const std::vector<T>& items, Rel rel) {
    std::vector<std::vector<T>> groups;
    std::vector<bool> used(items.size(), false);
    for (std::size_t i = 0; i < items.size(); ++i) {
        if (used[i]) continue;
        groups.push_back({items[i]});
        for (std::size_t j = i + 1; j < items.size(); ++j) {
            if (!used[j] && rel(items[i], items[j])) {
                groups.back().push_back(items[j]);
                used[j] = true;
            }
        }
    }
    return groups;
}

int main() {
    // Sort with std::less (a standard relation)
    std::vector<int> nums = {5, 2, 8, 1, 9, 3};
    bubble_sort(nums, std::less<>{});
    std::cout << "Sorted ascending: ";
    for (int n : nums) std::cout << n << " ";
    std::cout << "\n";

    // Sort with std::greater
    bubble_sort(nums, std::greater<>{});
    std::cout << "Sorted descending: ";
    for (int n : nums) std::cout << n << " ";
    std::cout << "\n";

    // Sort strings by length
    std::vector<std::string> words = {"cherry", "fig", "apple", "date", "banana"};
    bubble_sort(words, [](const std::string& a, const std::string& b) {
        return a.size() < b.size();
    });
    std::cout << "\nBy length: ";
    for (const auto& w : words) std::cout << w << " ";
    std::cout << "\n";

    // Group by same initial letter
    std::vector<std::string> names = {"Alice", "Bob", "Anna", "Ben", "Carol", "Amy"};
    auto groups = group_by(names, SameInitial{});
    std::cout << "\nGrouped by initial:\n";
    for (const auto& g : groups) {
        std::cout << "  [";
        for (std::size_t i = 0; i < g.size(); ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << g[i];
        }
        std::cout << "]\n";
    }

    // Concept checks
    std::cout << "\nRelation checks:\n";
    std::cout << "less<> on int: " << std::relation<std::less<>, int, int> << "\n";
    std::cout << "SameInitial on string: "
              << std::relation<SameInitial, std::string, std::string> << "\n";

    return 0;
}

// Expected output:
// Sorted ascending: 1 2 3 5 8 9
// Sorted descending: 9 8 5 3 2 1
//
// By length: fig date apple cherry banana
//
// Grouped by initial:
//   [Alice, Anna, Amy]
//   [Bob, Ben]
//   [Carol]
//
// Relation checks:
// less<> on int: 1
// SameInitial on string: 1
