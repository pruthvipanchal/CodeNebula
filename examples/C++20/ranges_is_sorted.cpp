// CodeNebula - C++20 Example: Ranges Is Sorted
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_is_sorted.cpp

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
#include <string>

int main() {
    // ranges::is_sorted - check if a range is sorted in non-descending order
    std::vector<int> sorted = {1, 2, 3, 4, 5};
    std::vector<int> unsorted = {1, 3, 2, 5, 4};

    std::cout << "{1,2,3,4,5} is sorted? "
              << (std::ranges::is_sorted(sorted) ? "yes" : "no") << '\n';
    std::cout << "{1,3,2,5,4} is sorted? "
              << (std::ranges::is_sorted(unsorted) ? "yes" : "no") << '\n';

    // Check descending order with greater comparator
    std::vector<int> desc = {5, 4, 3, 2, 1};
    bool desc_sorted = std::ranges::is_sorted(desc, std::ranges::greater{});
    std::cout << "{5,4,3,2,1} sorted descending? "
              << (desc_sorted ? "yes" : "no") << '\n';

    // ranges::is_sorted_until - find where the sorted order breaks
    std::vector<int> data = {1, 3, 5, 4, 7, 9};
    auto boundary = std::ranges::is_sorted_until(data);
    std::cout << "\n{1,3,5,4,7,9} sorted until index "
              << (boundary - data.begin()) << " (value " << *boundary << ")\n";

    // Fully sorted range returns end iterator
    auto end_it = std::ranges::is_sorted_until(sorted);
    std::cout << "{1,2,3,4,5} sorted until end? "
              << (end_it == sorted.end() ? "yes" : "no") << '\n';

    // With projection - check if sorted by string length
    std::vector<std::string> words = {"a", "bb", "ccc", "dddd"};
    bool by_len = std::ranges::is_sorted(words, {}, &std::string::size);
    std::cout << "\nSorted by length? " << (by_len ? "yes" : "no") << '\n';

    std::vector<std::string> mixed = {"apple", "fig", "cherry"};
    bool mixed_len = std::ranges::is_sorted(mixed, {}, &std::string::size);
    std::cout << "{apple,fig,cherry} sorted by length? "
              << (mixed_len ? "yes" : "no") << '\n';

    auto until = std::ranges::is_sorted_until(mixed, {}, &std::string::size);
    std::cout << "Sorted by length until: \"" << *until << "\"\n";

    // Equal elements are considered sorted
    std::vector<int> equal = {3, 3, 3, 3};
    std::cout << "\n{3,3,3,3} is sorted? "
              << (std::ranges::is_sorted(equal) ? "yes" : "no") << '\n';

    return 0;
}
