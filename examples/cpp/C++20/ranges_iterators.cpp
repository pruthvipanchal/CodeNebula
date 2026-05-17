// CodeNebula - C++20 Example: Range Iterators (ranges::begin/end/cbegin/cend/rbegin/rend)
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_iterators.cpp

#include <ranges>
#include <vector>
#include <list>
#include <array>
#include <iostream>

// std::ranges provides CPOs for obtaining iterators: begin, end,
// cbegin, cend, rbegin, rend. These work uniformly with all ranges.

template <std::ranges::range R>
void print_forward(const R& r) {
    std::cout << "Forward:  ";
    for (auto it = std::ranges::begin(r); it != std::ranges::end(r); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
}

template <std::ranges::bidirectional_range R>
void print_reverse(const R& r) {
    std::cout << "Reverse:  ";
    for (auto it = std::ranges::rbegin(r); it != std::ranges::rend(r); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
}

int main() {
    std::vector<int> vec = {10, 20, 30, 40, 50};

    // ranges::begin / ranges::end
    std::cout << "=== Vector ===\n";
    print_forward(vec);
    print_reverse(vec);

    // ranges::cbegin / ranges::cend provide const iterators
    auto cit = std::ranges::cbegin(vec);
    std::cout << "First (const): " << *cit << "\n";

    // Works uniformly with C arrays
    int arr[] = {1, 2, 3, 4, 5};
    std::cout << "\n=== C Array ===\n";
    print_forward(arr);
    print_reverse(arr);

    // Works with std::array
    std::array<std::string, 3> strs = {"hello", "world", "test"};
    std::cout << "\n=== std::array<string> ===\n";
    print_forward(strs);
    print_reverse(strs);

    // Works with list
    std::list<int> lst = {5, 10, 15};
    std::cout << "\n=== List ===\n";
    print_forward(lst);
    print_reverse(lst);

    // ranges::begin works on views
    auto view = vec | std::views::take(3);
    auto vit = std::ranges::begin(view);
    std::cout << "\nFirst of take(3) view: " << *vit << "\n";

    // Demonstrate iterator distance
    auto dist = std::ranges::distance(std::ranges::begin(vec), std::ranges::end(vec));
    std::cout << "Vector distance: " << dist << "\n";
    return 0;
}
