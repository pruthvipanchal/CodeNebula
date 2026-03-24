// CodeNebula - C++20 Example: ranges::fill, fill_n, generate, generate_n
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_fill_generate.cpp

#include <iostream>
#include <ranges>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    // ranges::fill - fill entire range with a value
    std::vector<int> nums(8);
    std::ranges::fill(nums, 42);
    std::cout << "Filled with 42: ";
    for (int n : nums) std::cout << n << " ";
    std::cout << "\n";

    // Fill a subrange
    std::ranges::fill(nums.begin() + 2, nums.begin() + 6, 99);
    std::cout << "Partial fill with 99: ";
    for (int n : nums) std::cout << n << " ";
    std::cout << "\n";

    // ranges::fill_n - fill N elements starting from iterator
    std::vector<int> data(10, 0);
    std::ranges::fill_n(data.begin(), 5, 7);
    std::cout << "Fill_n (5 sevens): ";
    for (int n : data) std::cout << n << " ";
    std::cout << "\n";

    // ranges::generate - fill with values from a generator function
    std::vector<int> squares(8);
    int counter = 1;
    std::ranges::generate(squares, [&counter]() { return counter * counter++; });
    std::cout << "\nGenerated squares: ";
    for (int n : squares) std::cout << n << " ";
    std::cout << "\n";

    // Generate Fibonacci sequence
    std::vector<int> fib(10);
    int a = 0, b = 1;
    std::ranges::generate(fib, [&a, &b]() {
        int result = a;
        a = b;
        b = result + b;
        return result;
    });
    std::cout << "Fibonacci: ";
    for (int n : fib) std::cout << n << " ";
    std::cout << "\n";

    // ranges::generate_n - generate N values
    std::vector<int> powers;
    int base = 1;
    std::ranges::generate_n(std::back_inserter(powers), 8,
                            [&base]() { return base *= 2; });
    std::cout << "Powers of 2: ";
    for (int n : powers) std::cout << n << " ";
    std::cout << "\n";

    // generate_n with counting labels
    std::vector<std::string> labels;
    int id = 0;
    std::ranges::generate_n(std::back_inserter(labels), 5,
                            [&id]() { return "item_" + std::to_string(++id); });
    std::cout << "\nLabels: ";
    for (const auto& l : labels) std::cout << l << " ";
    std::cout << "\n";
    return 0;
}
