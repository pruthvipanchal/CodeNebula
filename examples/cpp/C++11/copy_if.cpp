// CodeNebula - C++11 Example: std::copy_if Conditional Copy
// Compile: g++ -std=c++11 -Wall -Wextra -o example copy_if.cpp

// std::copy_if copies elements from a source range to a destination only
// if they satisfy a predicate. It replaces the common pattern of using
// std::remove_copy_if with a negated predicate, improving readability.

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Copy only even numbers
    std::vector<int> evens;
    std::copy_if(numbers.begin(), numbers.end(), std::back_inserter(evens),
                 [](int n) { return n % 2 == 0; });

    std::cout << "Even numbers: ";
    for (const auto& n : evens) std::cout << n << " ";
    std::cout << std::endl;

    // Copy numbers greater than 5
    std::vector<int> large;
    std::copy_if(numbers.begin(), numbers.end(), std::back_inserter(large),
                 [](int n) { return n > 5; });

    std::cout << "Numbers > 5: ";
    for (const auto& n : large) std::cout << n << " ";
    std::cout << std::endl;

    // Filter strings by length
    std::vector<std::string> words = {"hi", "hello", "hey", "greetings", "yo"};
    std::vector<std::string> long_words;
    std::copy_if(words.begin(), words.end(), std::back_inserter(long_words),
                 [](const std::string& s) { return s.size() > 3; });

    std::cout << "Words > 3 chars: ";
    for (const auto& w : long_words) std::cout << w << " ";
    std::cout << std::endl;

    // Copy to output stream directly
    std::cout << "Odd numbers: ";
    std::copy_if(numbers.begin(), numbers.end(),
                 std::ostream_iterator<int>(std::cout, " "),
                 [](int n) { return n % 2 != 0; });
    std::cout << std::endl;

    // Copy non-negative values from mixed data
    std::vector<int> mixed = {-3, 5, -1, 8, 0, -7, 4};
    std::vector<int> non_negative;
    std::copy_if(mixed.begin(), mixed.end(), std::back_inserter(non_negative),
                 [](int n) { return n >= 0; });

    std::cout << "Non-negative: ";
    for (const auto& n : non_negative) std::cout << n << " ";
    std::cout << std::endl;

    return 0;
}

// Expected output:
// Even numbers: 2 4 6 8 10
// Numbers > 5: 6 7 8 9 10
// Words > 3 chars: hello greetings
// Odd numbers: 1 3 5 7 9
// Non-negative: 5 8 0 4
