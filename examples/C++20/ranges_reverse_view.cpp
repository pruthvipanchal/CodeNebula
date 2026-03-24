// CodeNebula - C++20 Example: std::ranges::reverse_view
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_reverse_view.cpp

#include <iostream>
#include <ranges>
#include <vector>
#include <string>
#include <list>

int main() {
    // Basic reverse view over a vector
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8};

    std::cout << "Original: ";
    for (int n : numbers) std::cout << n << " ";
    std::cout << "\n";

    std::cout << "Reversed: ";
    for (int n : std::ranges::reverse_view(numbers)) std::cout << n << " ";
    std::cout << "\n";

    // Using views::reverse adaptor
    std::cout << "Via adaptor: ";
    for (int n : numbers | std::views::reverse) std::cout << n << " ";
    std::cout << "\n";

    // Reverse view over strings
    std::vector<std::string> words = {"alpha", "beta", "gamma", "delta"};
    std::cout << "\nWords reversed: ";
    for (const auto& w : words | std::views::reverse) std::cout << w << " ";
    std::cout << "\n";

    // Double reverse returns to original order
    std::cout << "Double reversed: ";
    for (int n : numbers | std::views::reverse | std::views::reverse)
        std::cout << n << " ";
    std::cout << "\n";

    // Combining reverse with other views
    std::cout << "\nLast 3 elements (reversed take): ";
    for (int n : numbers | std::views::reverse | std::views::take(3))
        std::cout << n << " ";
    std::cout << "\n";

    // Reverse view preserves bidirectional access
    auto rev = std::ranges::reverse_view(numbers);
    std::cout << "First in reverse: " << *rev.begin() << "\n";
    std::cout << "Size of reverse view: " << std::ranges::size(rev) << "\n";

    // Reverse view over a subrange
    std::cout << "Middle reversed: ";
    for (int n : std::ranges::subrange(numbers.begin() + 2, numbers.begin() + 6)
                 | std::views::reverse)
        std::cout << n << " ";
    std::cout << "\n";

    return 0;
}
