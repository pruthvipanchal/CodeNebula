// CodeNebula - C++20 Example: std::ranges::filter_view
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_filter_view.cpp

#include <ranges>
#include <vector>
#include <string>
#include <iostream>

// std::ranges::filter_view / std::views::filter creates a lazy view
// that includes only elements satisfying a predicate.

struct Employee {
    std::string name;
    int age;
    double salary;
};

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Filter even numbers
    auto evens = numbers | std::views::filter([](int n) { return n % 2 == 0; });
    std::cout << "Evens: ";
    for (int n : evens) std::cout << n << " ";
    std::cout << "\n";

    // Filter and chain with transform
    auto even_squares = numbers
        | std::views::filter([](int n) { return n % 2 == 0; })
        | std::views::transform([](int n) { return n * n; });
    std::cout << "Even squares: ";
    for (int n : even_squares) std::cout << n << " ";
    std::cout << "\n";

    // Filter with complex predicate on structs
    std::vector<Employee> team = {
        {"Alice", 35, 90000}, {"Bob", 28, 65000},
        {"Carol", 42, 110000}, {"Dave", 31, 75000},
        {"Eve", 45, 120000}
    };

    auto senior_high_earners = team
        | std::views::filter([](const Employee& e) {
            return e.age >= 35 && e.salary >= 100000;
        });
    std::cout << "\nSenior high earners:\n";
    for (const auto& e : senior_high_earners) {
        std::cout << "  " << e.name << " (age " << e.age
                  << ", $" << e.salary << ")\n";
    }

    // Filter is lazy - predicate called only during iteration
    int call_count = 0;
    auto tracked = numbers | std::views::filter([&](int n) {
        ++call_count;
        return n > 7;
    });
    std::cout << "\nBefore iteration, calls: " << call_count << "\n";
    for ([[maybe_unused]] int n : tracked) {}
    std::cout << "After iteration, calls: " << call_count << "\n";

    // Multiple filters can be composed
    auto result = numbers
        | std::views::filter([](int n) { return n > 3; })
        | std::views::filter([](int n) { return n < 8; });
    std::cout << "3 < x < 8: ";
    for (int n : result) std::cout << n << " ";
    std::cout << "\n";
    return 0;
}
