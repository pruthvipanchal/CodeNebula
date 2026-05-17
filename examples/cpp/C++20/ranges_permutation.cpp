// CodeNebula - C++20 Example: Ranges Permutation
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_permutation.cpp

#include <algorithm>
#include <iostream>
#include <vector>

void print(const char* label, const std::vector<int>& v) {
    std::cout << label;
    for (int x : v) std::cout << x << ' ';
    std::cout << '\n';
}

int main() {
    // ranges::next_permutation - rearrange into the next lexicographic permutation
    std::vector<int> perm = {1, 2, 3};
    std::cout << "All permutations of {1, 2, 3}:\n";

    do {
        std::cout << "  ";
        for (int x : perm) std::cout << x << ' ';
        std::cout << '\n';
    } while (std::ranges::next_permutation(perm).found);

    // ranges::prev_permutation - rearrange into the previous permutation
    std::vector<int> desc = {3, 2, 1};
    std::cout << "\nReverse permutations of {3, 2, 1}:\n";

    do {
        std::cout << "  ";
        for (int x : desc) std::cout << x << ' ';
        std::cout << '\n';
    } while (std::ranges::prev_permutation(desc).found);

    // next_permutation returns a struct with .found and .in (end iterator)
    std::vector<int> data = {1, 3, 2};
    print("\nStarting: ", data);
    auto result = std::ranges::next_permutation(data);
    print("Next perm: ", data);
    std::cout << "Found next? " << (result.found ? "yes" : "no") << '\n';

    // When at the last permutation, it wraps to the first
    std::vector<int> last = {3, 2, 1};
    print("\nLast perm: ", last);
    auto wrap = std::ranges::next_permutation(last);
    print("Wrapped:   ", last);
    std::cout << "Found next? " << (wrap.found ? "yes" : "no") << '\n';

    // Count permutations of 4 elements
    std::vector<int> four = {1, 2, 3, 4};
    int count = 0;
    do { ++count; } while (std::ranges::next_permutation(four).found);
    std::cout << "\nNumber of permutations of 4 elements: " << count << '\n';

    return 0;
}
