// CodeNebula - C++20 Example: ranges::for_each, for_each_n
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_for_each.cpp

#include <iostream>
#include <ranges>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8};

    // ranges::for_each with a lambda
    std::cout << "Doubled: ";
    std::ranges::for_each(numbers, [](int n) { std::cout << n * 2 << " "; });
    std::cout << "\n";

    // for_each with side effects (accumulate a sum)
    int sum = 0;
    std::ranges::for_each(numbers, [&sum](int n) { sum += n; });
    std::cout << "Sum: " << sum << "\n";

    // for_each with projection
    std::vector<std::string> words = {"hello", "world", "cpp", "twenty"};
    std::cout << "\nWord lengths: ";
    std::ranges::for_each(words, [](size_t len) { std::cout << len << " "; },
                          &std::string::size);
    std::cout << "\n";

    // Modify elements in-place
    std::ranges::for_each(numbers, [](int& n) { n *= 10; });
    std::cout << "After x10: ";
    std::ranges::for_each(numbers, [](int n) { std::cout << n << " "; });
    std::cout << "\n";

    // for_each on a view (filtered range)
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << "\nEven numbers: ";
    std::ranges::for_each(data | std::views::filter([](int x) { return x % 2 == 0; }),
                          [](int n) { std::cout << n << " "; });
    std::cout << "\n";

    // ranges::for_each_n - apply to first N elements
    std::vector<int> vals = {10, 20, 30, 40, 50, 60, 70};
    std::cout << "First 4 elements: ";
    std::ranges::for_each_n(vals.begin(), 4, [](int n) { std::cout << n << " "; });
    std::cout << "\n";

    // for_each_n with modification
    std::ranges::for_each_n(vals.begin(), 3, [](int& n) { n += 100; });
    std::cout << "After adding 100 to first 3: ";
    std::ranges::for_each(vals, [](int n) { std::cout << n << " "; });
    std::cout << "\n";

    // for_each_n with projection
    std::cout << "\nFirst 2 word lengths: ";
    std::ranges::for_each_n(words.begin(), 2,
                            [](size_t len) { std::cout << len << " "; },
                            &std::string::size);
    std::cout << "\n";

    // Return value of for_each contains the function object
    auto result = std::ranges::for_each(data, [count = 0](int) mutable { ++count; });
    std::cout << "for_each returned iterator at end: "
              << (result.in == data.end()) << "\n";

    return 0;
}
