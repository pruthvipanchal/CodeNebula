// CodeNebula - C++20 Example: std::ranges::iota_view
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_iota_view.cpp

#include <iostream>
#include <ranges>
#include <vector>
#include <algorithm>

int main() {
    // iota_view generates a sequence of incrementing values
    // Bounded iota: [start, end)
    std::cout << "Numbers 1 to 10: ";
    for (int n : std::ranges::iota_view(1, 11))
        std::cout << n << " ";
    std::cout << "\n";

    // Using views::iota adaptor
    std::cout << "Numbers 0 to 4: ";
    for (int n : std::views::iota(0, 5))
        std::cout << n << " ";
    std::cout << "\n";

    // Unbounded iota with take
    std::cout << "First 8 from 100: ";
    for (int n : std::views::iota(100) | std::views::take(8))
        std::cout << n << " ";
    std::cout << "\n";

    // Generate even numbers using iota + transform
    std::cout << "\nFirst 10 even numbers: ";
    for (int n : std::views::iota(1) | std::views::transform([](int i) { return i * 2; })
                                      | std::views::take(10))
        std::cout << n << " ";
    std::cout << "\n";

    // Generate squares using iota
    std::cout << "Squares 1-8: ";
    for (int n : std::views::iota(1, 9)
                 | std::views::transform([](int i) { return i * i; }))
        std::cout << n << " ";
    std::cout << "\n";

    // Use iota for indexing
    std::vector<std::string> names = {"Alice", "Bob", "Charlie", "Diana"};
    std::cout << "\nIndexed list:\n";
    for (int i : std::views::iota(0, static_cast<int>(names.size())))
        std::cout << "  [" << i << "] " << names[i] << "\n";

    // Filter iota for specific values
    std::cout << "Multiples of 3 up to 30: ";
    for (int n : std::views::iota(1, 31)
                 | std::views::filter([](int i) { return i % 3 == 0; }))
        std::cout << n << " ";
    std::cout << "\n";

    // Iota with characters
    std::cout << "Alphabet: ";
    for (char c : std::views::iota('a', static_cast<char>('z' + 1)))
        std::cout << c;
    std::cout << "\n";

    return 0;
}
