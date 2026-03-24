// CodeNebula - C++20 Example: pipe operator | chaining
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_adaptor_compose.cpp

#include <iostream>
#include <ranges>
#include <vector>
#include <string>

int main() {
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

    // Simple two-step pipeline
    std::cout << "Even numbers doubled: ";
    for (int n : data | std::views::filter([](int x) { return x % 2 == 0; })
                      | std::views::transform([](int x) { return x * 2; }))
        std::cout << n << " ";
    std::cout << "\n";

    // Three-step pipeline: filter -> transform -> take
    std::cout << "First 4 odd squares: ";
    for (int n : data | std::views::filter([](int x) { return x % 2 != 0; })
                      | std::views::transform([](int x) { return x * x; })
                      | std::views::take(4))
        std::cout << n << " ";
    std::cout << "\n";

    // Complex pipeline with multiple operations
    std::cout << "Drop 2, filter >5, x10, take 3: ";
    for (int n : data | std::views::drop(2)
                      | std::views::filter([](int x) { return x > 5; })
                      | std::views::transform([](int x) { return x * 10; })
                      | std::views::take(3))
        std::cout << n << " ";
    std::cout << "\n";

    // String processing pipeline
    std::vector<std::string> words = {
        "the", "quick", "brown", "fox", "jumps", "over", "the", "lazy"
    };
    std::cout << "\nLong words uppercased (first 3):\n";
    for (const auto& w : words
             | std::views::filter([](const std::string& s) { return s.size() > 3; })
             | std::views::transform([](std::string s) {
                   for (char& c : s) c = static_cast<char>(std::toupper(c));
                   return s;
               })
             | std::views::take(3))
        std::cout << "  " << w << "\n";

    // Composing with iota as source - FizzBuzz
    std::cout << "Fizzbuzz (1-15): ";
    for (const auto& s : std::views::iota(1, 16)
             | std::views::transform([](int n) -> std::string {
                   if (n % 15 == 0) return "FizzBuzz";
                   if (n % 3 == 0) return "Fizz";
                   if (n % 5 == 0) return "Buzz";
                   return std::to_string(n);
               }))
        std::cout << s << " ";
    std::cout << "\n";

    // Reverse then take vs take then reverse - order matters
    std::cout << "\nLast 5 (reverse|take): ";
    for (int n : data | std::views::reverse | std::views::take(5))
        std::cout << n << " ";
    std::cout << "\nFirst 5 reversed (take|reverse): ";
    for (int n : data | std::views::take(5) | std::views::reverse)
        std::cout << n << " ";
    std::cout << "\n";
    return 0;
}
