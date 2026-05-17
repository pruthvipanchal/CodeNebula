// CodeNebula - C++20 Example: views::transform
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_adaptor_transform.cpp

#include <iostream>
#include <ranges>
#include <vector>
#include <string>
#include <cmath>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8};

    // Basic transform: square each element
    std::cout << "Squares: ";
    for (int n : numbers | std::views::transform([](int x) { return x * x; }))
        std::cout << n << " ";
    std::cout << "\n";

    // Transform to different type
    std::cout << "As doubles (halved): ";
    for (double d : numbers | std::views::transform([](int x) { return x / 2.0; }))
        std::cout << d << " ";
    std::cout << "\n";

    // Transform strings
    std::vector<std::string> words = {"hello", "world", "cpp", "twenty"};
    std::cout << "\nUppercased: ";
    for (const auto& s : words | std::views::transform([](std::string s) {
             for (char& c : s) c = static_cast<char>(std::toupper(c));
             return s;
         }))
        std::cout << s << " ";
    std::cout << "\n";

    // Transform to extract string lengths
    std::cout << "Lengths: ";
    for (auto len : words | std::views::transform(&std::string::size))
        std::cout << len << " ";
    std::cout << "\n";

    // Chain transform with filter
    std::cout << "\nEven squares: ";
    for (int n : numbers | std::views::transform([](int x) { return x * x; })
                         | std::views::filter([](int x) { return x % 2 == 0; }))
        std::cout << n << " ";
    std::cout << "\n";

    // Mathematical transforms
    std::vector<double> angles = {0.0, 0.5, 1.0, 1.5, 2.0};
    std::cout << "sin(x): ";
    for (double s : angles | std::views::transform([](double x) { return std::sin(x); }))
        std::cout << s << " ";
    std::cout << "\n";

    // Transform with index simulation using iota
    std::cout << "\nIndexed words:\n";
    for (auto idx : std::views::iota(0, static_cast<int>(words.size()))
                    | std::views::transform([&](int i) {
                          return std::to_string(i) + ": " + words[i];
                      }))
        std::cout << "  " << idx << "\n";

    // Multiple transforms chained
    std::cout << "Cubed mod 10: ";
    for (int n : numbers | std::views::transform([](int x) { return x * x * x; })
                         | std::views::transform([](int x) { return x % 10; }))
        std::cout << n << " ";
    std::cout << "\n";
    return 0;
}
