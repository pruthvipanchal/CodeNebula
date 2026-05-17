// CodeNebula - C++20 Example: Ranges Reverse
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_reverse_algo.cpp

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

int main() {
    // ranges::reverse - reverse elements in place
    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7};
    std::cout << "Original: ";
    for (int n : nums) std::cout << n << ' ';
    std::cout << '\n';

    std::ranges::reverse(nums);
    std::cout << "Reversed: ";
    for (int n : nums) std::cout << n << ' ';
    std::cout << '\n';

    // Reverse a subrange using iterators
    std::vector<int> data = {10, 20, 30, 40, 50, 60};
    std::ranges::reverse(data.begin() + 1, data.begin() + 5);
    std::cout << "\nPartial reverse [1,5): ";
    for (int d : data) std::cout << d << ' ';
    std::cout << '\n';

    // ranges::reverse_copy - copy in reverse order
    std::vector<int> src = {1, 2, 3, 4, 5};
    std::vector<int> dst(src.size());

    std::ranges::reverse_copy(src, dst.begin());
    std::cout << "\nSource:        ";
    for (int s : src) std::cout << s << ' ';
    std::cout << '\n';
    std::cout << "Reverse copy:  ";
    for (int d : dst) std::cout << d << ' ';
    std::cout << '\n';

    // Reverse a string
    std::string word = "CodeNebula";
    std::cout << "\nOriginal string: " << word << '\n';
    std::ranges::reverse(word);
    std::cout << "Reversed string: " << word << '\n';

    // reverse_copy into a new string
    std::string greeting = "Hello";
    std::string reversed(greeting.size(), ' ');
    std::ranges::reverse_copy(greeting, reversed.begin());
    std::cout << "\n\"" << greeting << "\" reversed: \"" << reversed << "\"\n";

    return 0;
}
