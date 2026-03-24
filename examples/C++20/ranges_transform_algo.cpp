// CodeNebula - C++20 Example: ranges::transform (algorithm version)
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_transform_algo.cpp

#include <iostream>
#include <ranges>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

int main() {
    // Unary ranges::transform - transform one range to another
    std::vector<int> input = {1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int> output(input.size());

    std::ranges::transform(input, output.begin(), [](int x) { return x * x; });
    std::cout << "Squares: ";
    for (int n : output) std::cout << n << " ";
    std::cout << "\n";

    // Transform in-place
    std::vector<int> data = {10, 20, 30, 40, 50};
    std::ranges::transform(data, data.begin(), [](int x) { return x + 5; });
    std::cout << "In-place +5: ";
    for (int n : data) std::cout << n << " ";
    std::cout << "\n";

    // Transform strings to uppercase
    std::vector<std::string> words = {"hello", "world", "cpp", "ranges"};
    std::vector<std::string> upper(words.size());
    std::ranges::transform(words, upper.begin(), [](std::string s) {
        for (char& c : s) c = static_cast<char>(std::toupper(c));
        return s;
    });
    std::cout << "\nUppercased: ";
    for (const auto& w : upper) std::cout << w << " ";
    std::cout << "\n";

    // Binary ranges::transform - combine two ranges
    std::vector<int> a = {1, 2, 3, 4, 5};
    std::vector<int> b = {10, 20, 30, 40, 50};
    std::vector<int> sums(a.size());

    std::ranges::transform(a, b, sums.begin(), std::plus{});
    std::cout << "\nElement-wise sum: ";
    for (int n : sums) std::cout << n << " ";
    std::cout << "\n";

    // Binary transform: multiply corresponding elements
    std::vector<int> products(a.size());
    std::ranges::transform(a, b, products.begin(), std::multiplies{});
    std::cout << "Element-wise product: ";
    for (int n : products) std::cout << n << " ";
    std::cout << "\n";

    // Binary transform with pow
    std::vector<double> bases = {2.0, 3.0, 4.0, 5.0};
    std::vector<double> exponents = {3.0, 2.0, 1.5, 0.5};
    std::vector<double> powers(bases.size());
    std::ranges::transform(bases, exponents, powers.begin(),
                           [](double b, double e) { return std::pow(b, e); });
    std::cout << "\nPowers: ";
    for (double p : powers) std::cout << p << " ";
    std::cout << "\n";

    // Return value provides result iterator
    auto result = std::ranges::transform(a, output.begin(), std::negate{});
    std::cout << "Negated: ";
    for (auto it = output.begin(); it != result.out; ++it) std::cout << *it << " ";
    std::cout << "\n";
    return 0;
}
