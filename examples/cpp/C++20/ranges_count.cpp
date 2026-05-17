// CodeNebula - C++20 Example: ranges::count, count_if
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_count.cpp

#include <iostream>
#include <ranges>
#include <vector>
#include <string>
#include <algorithm>

struct Product {
    std::string name;
    double price;
    std::string category;
};

int main() {
    std::vector<int> numbers = {1, 2, 3, 2, 4, 2, 5, 2, 6, 7, 2};

    // ranges::count - count occurrences of a value
    std::cout << "Count of 2s: " << std::ranges::count(numbers, 2) << "\n";
    std::cout << "Count of 5s: " << std::ranges::count(numbers, 5) << "\n";
    std::cout << "Count of 9s: " << std::ranges::count(numbers, 9) << "\n";

    // ranges::count_if - count elements matching a predicate
    auto evens = std::ranges::count_if(numbers, [](int n) { return n % 2 == 0; });
    std::cout << "\nEven count: " << evens << "\n";

    auto gt4 = std::ranges::count_if(numbers, [](int n) { return n > 4; });
    std::cout << "Count > 4: " << gt4 << "\n";

    // Count with strings
    std::vector<std::string> words = {"apple", "banana", "apple", "cherry", "apple"};
    std::cout << "\nApple count: "
              << std::ranges::count(words, std::string("apple")) << "\n";
    std::cout << "Words > 5 chars: "
              << std::ranges::count_if(words, [](const auto& s) { return s.size() > 5; })
              << "\n";

    // Count with projection
    std::vector<Product> products = {
        {"Laptop", 999.99, "Electronics"}, {"Phone", 699.00, "Electronics"},
        {"Book", 29.99, "Books"}, {"Tablet", 449.00, "Electronics"}
    };

    auto electronics = std::ranges::count(products, std::string("Electronics"),
                                          &Product::category);
    std::cout << "\nElectronics: " << electronics << "\n";

    auto expensive = std::ranges::count_if(products,
        [](double p) { return p > 500.0; }, &Product::price);
    std::cout << "Expensive (>$500): " << expensive << "\n";

    // Count in a view
    auto even_count = std::ranges::count_if(
        std::views::iota(1, 101), [](int n) { return n % 2 == 0; });
    std::cout << "\nEven numbers in 1-100: " << even_count << "\n";

    // Count characters in a string
    std::string text = "mississippi";
    std::cout << "'" << text << "': s=" << std::ranges::count(text, 's')
              << " p=" << std::ranges::count(text, 'p') << "\n";
    return 0;
}
