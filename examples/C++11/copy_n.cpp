// CodeNebula - C++11 Example: std::copy_n First N Elements
// Compile: g++ -std=c++11 -Wall -Wextra -o example copy_n.cpp

// std::copy_n copies exactly N elements from a source starting at a given
// iterator. Unlike std::copy, you specify a count instead of an end iterator,
// which is convenient when working with input iterators or known counts.

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>

int main() {
    std::vector<int> source = {10, 20, 30, 40, 50, 60, 70, 80};

    // Copy first 3 elements
    std::vector<int> first_three(3);
    std::copy_n(source.begin(), 3, first_three.begin());

    std::cout << "First 3: ";
    for (const auto& n : first_three) std::cout << n << " ";
    std::cout << std::endl;

    // Copy 4 elements starting from index 2
    std::vector<int> middle(4);
    std::copy_n(source.begin() + 2, 4, middle.begin());

    std::cout << "4 from index 2: ";
    for (const auto& n : middle) std::cout << n << " ";
    std::cout << std::endl;

    // Copy N elements into a growing container
    std::vector<int> growing;
    std::copy_n(source.begin(), 5, std::back_inserter(growing));

    std::cout << "First 5 (back_inserter): ";
    for (const auto& n : growing) std::cout << n << " ";
    std::cout << std::endl;

    // Copy N elements directly to output stream
    std::cout << "First 4 to stream: ";
    std::copy_n(source.begin(), 4, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    // Copy N strings
    std::vector<std::string> names = {"Alice", "Bob", "Charlie", "Dave", "Eve"};
    std::vector<std::string> top_three;
    std::copy_n(names.begin(), 3, std::back_inserter(top_three));

    std::cout << "Top 3 names: ";
    for (const auto& n : top_three) std::cout << n << " ";
    std::cout << std::endl;

    // Copy 0 elements (no-op)
    std::vector<int> empty;
    std::copy_n(source.begin(), 0, std::back_inserter(empty));
    std::cout << "Copy 0 elements, size: " << empty.size() << std::endl;

    return 0;
}

// Expected output:
// First 3: 10 20 30
// 4 from index 2: 30 40 50 60
// First 5 (back_inserter): 10 20 30 40 50
// First 4 to stream: 10 20 30 40
// Top 3 names: Alice Bob Charlie
// Copy 0 elements, size: 0
