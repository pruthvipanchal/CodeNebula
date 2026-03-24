// CodeNebula - C++20 Example: views::filter
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_adaptor_filter.cpp

#include <iostream>
#include <ranges>
#include <vector>
#include <string>

struct Employee {
    std::string name;
    int age;
    double salary;
};

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    // Basic filter for even numbers
    std::cout << "Even numbers: ";
    for (int n : numbers | std::views::filter([](int x) { return x % 2 == 0; }))
        std::cout << n << " ";
    std::cout << "\n";

    // Filter with named predicate
    auto is_prime = [](int n) {
        if (n < 2) return false;
        for (int i = 2; i * i <= n; ++i)
            if (n % i == 0) return false;
        return true;
    };
    std::cout << "Primes: ";
    for (int n : numbers | std::views::filter(is_prime)) std::cout << n << " ";
    std::cout << "\n";

    // Filter strings by length
    std::vector<std::string> words = {"hi", "hello", "hey", "greetings", "yo"};
    std::cout << "\nLong words (>3 chars): ";
    for (const auto& w : words | std::views::filter(
             [](const std::string& s) { return s.size() > 3; }))
        std::cout << w << " ";
    std::cout << "\n";

    // Filter structs
    std::vector<Employee> team = {
        {"Alice", 30, 75000}, {"Bob", 45, 95000},
        {"Charlie", 28, 65000}, {"Diana", 35, 85000}
    };
    std::cout << "\nHigh earners (>80k):\n";
    for (const auto& e : team | std::views::filter(
             [](const Employee& e) { return e.salary > 80000; }))
        std::cout << "  " << e.name << " - $" << e.salary << "\n";

    // Chaining multiple filters
    std::cout << "Even and divisible by 3: ";
    for (int n : numbers | std::views::filter([](int x) { return x % 2 == 0; })
                         | std::views::filter([](int x) { return x % 3 == 0; }))
        std::cout << n << " ";
    std::cout << "\n";

    // Filter preserves laziness - no intermediate containers
    std::cout << "First 3 odd: ";
    for (int n : numbers | std::views::filter([](int x) { return x % 2 != 0; })
                         | std::views::take(3))
        std::cout << n << " ";
    std::cout << "\n";
    return 0;
}
