// CodeNebula - C++20 Example: Ranges Set Operations
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_set_operations.cpp

#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>

int main() {
    std::vector<int> a = {1, 2, 3, 4, 5, 6};
    std::vector<int> b = {2, 4, 6, 8, 10};

    std::cout << "A: ";
    for (int x : a) std::cout << x << ' ';
    std::cout << "\nB: ";
    for (int x : b) std::cout << x << ' ';
    std::cout << '\n';

    // ranges::includes - check if A contains all elements of a subset
    std::vector<int> subset = {2, 4, 6};
    bool inc = std::ranges::includes(a, subset);
    std::cout << "\nA includes {2,4,6}? " << (inc ? "yes" : "no") << '\n';

    // ranges::set_union - elements in A or B (or both)
    std::vector<int> result;
    std::ranges::set_union(a, b, std::back_inserter(result));
    std::cout << "\nUnion: ";
    for (int x : result) std::cout << x << ' ';
    std::cout << '\n';

    // ranges::set_intersection - elements in both A and B
    result.clear();
    std::ranges::set_intersection(a, b, std::back_inserter(result));
    std::cout << "Intersection: ";
    for (int x : result) std::cout << x << ' ';
    std::cout << '\n';

    // ranges::set_difference - elements in A but not in B
    result.clear();
    std::ranges::set_difference(a, b, std::back_inserter(result));
    std::cout << "Difference (A-B): ";
    for (int x : result) std::cout << x << ' ';
    std::cout << '\n';

    // ranges::set_symmetric_difference - elements in A or B but not both
    result.clear();
    std::ranges::set_symmetric_difference(a, b, std::back_inserter(result));
    std::cout << "Symmetric difference: ";
    for (int x : result) std::cout << x << ' ';
    std::cout << '\n';

    // All operations require sorted inputs
    std::vector<int> x = {5, 1, 3};
    std::vector<int> y = {4, 2};
    std::ranges::sort(x);
    std::ranges::sort(y);
    result.clear();
    std::ranges::set_union(x, y, std::back_inserter(result));
    std::cout << "\nSorted then union: ";
    for (int v : result) std::cout << v << ' ';
    std::cout << '\n';

    return 0;
}
