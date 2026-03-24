// CodeNebula - C++20 Example: ranges::copy, copy_if, copy_n, copy_backward
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_copy.cpp

#include <iostream>
#include <ranges>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

int main() {
    std::vector<int> source = {1, 2, 3, 4, 5, 6, 7, 8};

    // ranges::copy - copy entire range
    std::vector<int> dest(source.size());
    std::ranges::copy(source, dest.begin());
    std::cout << "Copied: ";
    for (int n : dest) std::cout << n << " ";
    std::cout << "\n";

    // Copy to output stream
    std::cout << "To stdout: ";
    std::ranges::copy(source, std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";

    // ranges::copy_if - copy elements matching a predicate
    std::vector<int> evens;
    std::ranges::copy_if(source, std::back_inserter(evens),
                         [](int n) { return n % 2 == 0; });
    std::cout << "\nEvens: ";
    for (int n : evens) std::cout << n << " ";
    std::cout << "\n";

    // copy_if with strings
    std::vector<std::string> words = {"apple", "bat", "cherry", "do", "elderberry"};
    std::vector<std::string> long_words;
    std::ranges::copy_if(words, std::back_inserter(long_words),
                         [](const std::string& s) { return s.size() > 3; });
    std::cout << "Long words: ";
    for (const auto& w : long_words) std::cout << w << " ";
    std::cout << "\n";

    // ranges::copy_n - copy exactly N elements
    std::vector<int> first_four(4);
    std::ranges::copy_n(source.begin(), 4, first_four.begin());
    std::cout << "\nFirst 4: ";
    for (int n : first_four) std::cout << n << " ";
    std::cout << "\n";

    // ranges::copy_backward - copy preserving order, placed at end of buffer
    std::vector<int> buf(10, 0);
    std::ranges::copy_backward(source, buf.end());
    std::cout << "Copy backward into size-10: ";
    for (int n : buf) std::cout << n << " ";
    std::cout << "\n";

    // Copy from a view
    std::vector<int> squares;
    std::ranges::copy(source | std::views::transform([](int x) { return x * x; }),
                      std::back_inserter(squares));
    std::cout << "\nSquares: ";
    for (int n : squares) std::cout << n << " ";
    std::cout << "\n";
    return 0;
}
