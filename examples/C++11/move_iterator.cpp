// CodeNebula - C++11 Example: std::move_iterator for Move Semantics
// Compile: g++ -std=c++11 -Wall -Wextra -o example move_iterator.cpp

// std::move_iterator wraps an iterator so that dereferencing yields an
// rvalue reference, enabling move semantics instead of copying. This is
// useful when you want to transfer ownership of elements between containers.

#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>

int main() {
    // Source vector of strings
    std::vector<std::string> source = {"Hello", "World", "Move", "Semantics"};

    std::cout << "Source before move: ";
    for (const auto& s : source) {
        std::cout << "'" << s << "' ";
    }
    std::cout << std::endl;

    // Move elements from source to destination using move_iterator
    std::vector<std::string> dest(
        std::make_move_iterator(source.begin()),
        std::make_move_iterator(source.end())
    );

    std::cout << "Destination after move: ";
    for (const auto& s : dest) {
        std::cout << "'" << s << "' ";
    }
    std::cout << std::endl;

    // Source strings are now in a moved-from state (valid but unspecified)
    std::cout << "Source after move (size=" << source.size() << "): ";
    for (const auto& s : source) {
        std::cout << "'" << s << "' ";
    }
    std::cout << std::endl;

    // Use move_iterator with std::copy
    std::vector<std::string> words = {"alpha", "beta", "gamma"};
    std::vector<std::string> target;
    target.resize(words.size());

    std::copy(std::make_move_iterator(words.begin()),
              std::make_move_iterator(words.end()),
              target.begin());

    std::cout << "Target after copy-move: ";
    for (const auto& s : target) {
        std::cout << "'" << s << "' ";
    }
    std::cout << std::endl;

    // Partial move using move_iterator
    std::vector<std::string> partial_src = {"one", "two", "three", "four"};
    auto mid = partial_src.begin() + 2;
    std::vector<std::string> first_half(
        std::make_move_iterator(partial_src.begin()),
        std::make_move_iterator(mid)
    );

    std::cout << "First half moved: ";
    for (const auto& s : first_half) {
        std::cout << "'" << s << "' ";
    }
    std::cout << std::endl;

    return 0;
}

// Expected output:
// Source before move: 'Hello' 'World' 'Move' 'Semantics'
// Destination after move: 'Hello' 'World' 'Move' 'Semantics'
// Source after move (size=4): '' '' '' ''
// Target after copy-move: 'alpha' 'beta' 'gamma'
// First half moved: 'one' 'two'
