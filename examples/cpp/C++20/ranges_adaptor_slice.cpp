// CodeNebula - C++20 Example: views::take, views::drop
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_adaptor_slice.cpp

#include <iostream>
#include <ranges>
#include <vector>
#include <string>

int main() {
    std::vector<int> numbers = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    // views::take - take the first N elements
    std::cout << "First 4: ";
    for (int n : numbers | std::views::take(4)) std::cout << n << " ";
    std::cout << "\n";

    // views::drop - skip the first N elements
    std::cout << "Drop first 6: ";
    for (int n : numbers | std::views::drop(6)) std::cout << n << " ";
    std::cout << "\n";

    // Combine take and drop for slicing
    std::cout << "Middle (drop 3, take 4): ";
    for (int n : numbers | std::views::drop(3) | std::views::take(4))
        std::cout << n << " ";
    std::cout << "\n";

    // Take more than available is safe; drop more gives empty
    std::cout << "Take 100 (safe): ";
    for (int n : numbers | std::views::take(100)) std::cout << n << " ";
    std::cout << "\nDrop 100: [";
    for (int n : numbers | std::views::drop(100)) std::cout << n;
    std::cout << "]\n";

    // Pagination pattern
    std::vector<std::string> items = {"a","b","c","d","e","f","g","h","i","j"};
    int page_size = 3;
    std::cout << "\nPaginated output:\n";
    for (int page = 0; page * page_size < static_cast<int>(items.size()); ++page) {
        std::cout << "  Page " << page << ": ";
        for (const auto& item : items | std::views::drop(page * page_size)
                                       | std::views::take(page_size))
            std::cout << item << " ";
        std::cout << "\n";
    }

    // Combine with filter and take
    std::cout << "\nFirst 3 multiples of 20: ";
    for (int n : numbers | std::views::filter([](int x) { return x % 20 == 0; })
                         | std::views::take(3))
        std::cout << n << " ";
    std::cout << "\n";

    // Take from an infinite range
    std::cout << "First 5 from iota(1): ";
    for (int n : std::views::iota(1) | std::views::take(5))
        std::cout << n << " ";
    std::cout << "\n";
    return 0;
}
