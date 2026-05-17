// CodeNebula - C++11 Example: std::move Algorithm (Range)
// Compile: g++ -std=c++11 -Wall -Wextra -o example move_algorithm.cpp

// std::move (the algorithm in <algorithm>, not std::move from <utility>)
// moves elements from a source range to a destination range. After the
// operation, source elements are in a valid but unspecified state.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    // Move strings from one vector to another
    std::vector<std::string> source = {"Alpha", "Beta", "Gamma", "Delta"};

    std::cout << "Source before: ";
    for (const auto& s : source) std::cout << "'" << s << "' ";
    std::cout << std::endl;

    std::vector<std::string> dest(source.size());
    std::move(source.begin(), source.end(), dest.begin());

    std::cout << "Dest after move: ";
    for (const auto& s : dest) std::cout << "'" << s << "' ";
    std::cout << std::endl;

    // Source strings are moved-from (empty for most implementations)
    std::cout << "Source after move (size=" << source.size() << "): ";
    for (const auto& s : source) std::cout << "'" << s << "' ";
    std::cout << std::endl;

    // Move a subset of elements
    std::vector<std::string> words = {"one", "two", "three", "four", "five"};
    std::vector<std::string> partial(2);
    std::move(words.begin(), words.begin() + 2, partial.begin());

    std::cout << "Partial move result: ";
    for (const auto& s : partial) std::cout << "'" << s << "' ";
    std::cout << std::endl;

    // Move into back of existing vector
    std::vector<std::string> items = {"X", "Y", "Z"};
    std::vector<std::string> combined = {"A", "B"};
    combined.resize(combined.size() + items.size());
    std::move(items.begin(), items.end(), combined.begin() + 2);

    std::cout << "Combined: ";
    for (const auto& s : combined) std::cout << "'" << s << "' ";
    std::cout << std::endl;

    // Integers are trivially moved (same as copy)
    std::vector<int> int_src = {10, 20, 30};
    std::vector<int> int_dst(3);
    std::move(int_src.begin(), int_src.end(), int_dst.begin());

    std::cout << "Int move: ";
    for (const auto& n : int_dst) std::cout << n << " ";
    std::cout << std::endl;

    return 0;
}

// Expected output:
// Source before: 'Alpha' 'Beta' 'Gamma' 'Delta'
// Dest after move: 'Alpha' 'Beta' 'Gamma' 'Delta'
// Source after move (size=4): '' '' '' ''
// Partial move result: 'one' 'two'
// Combined: 'A' 'B' 'X' 'Y' 'Z'
// Int move: 10 20 30
