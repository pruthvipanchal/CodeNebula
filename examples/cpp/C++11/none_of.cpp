// CodeNebula - C++11 Example: std::none_of Predicate Check
// Compile: g++ -std=c++11 -Wall -Wextra -o example none_of.cpp

// std::none_of returns true if a predicate holds for no element in a range.
// It is the logical complement of std::any_of and short-circuits on the
// first element that satisfies the predicate. Returns true for empty ranges.

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1, 3, 5, 7, 9};

    // Check if no elements are even
    bool no_even = std::none_of(numbers.begin(), numbers.end(),
                                [](int n) { return n % 2 == 0; });
    std::cout << "None even (odd list): " << std::boolalpha << no_even << std::endl;

    // Check if no elements are negative
    bool no_negative = std::none_of(numbers.begin(), numbers.end(),
                                    [](int n) { return n < 0; });
    std::cout << "None negative: " << no_negative << std::endl;

    // Add a negative number
    numbers.push_back(-2);
    no_negative = std::none_of(numbers.begin(), numbers.end(),
                               [](int n) { return n < 0; });
    std::cout << "None negative after adding -2: " << no_negative << std::endl;

    // Check if no elements are zero
    std::vector<int> data = {4, 7, 2, 9, 1};
    bool no_zeros = std::none_of(data.begin(), data.end(),
                                 [](int n) { return n == 0; });
    std::cout << "No zeros in data: " << no_zeros << std::endl;

    // Empty range returns true
    std::vector<int> empty;
    bool empty_result = std::none_of(empty.begin(), empty.end(),
                                     [](int n) { return n == 42; });
    std::cout << "None of empty range: " << empty_result << std::endl;

    // Practical: verify no duplicates exceed a limit
    std::vector<double> temps = {36.5, 37.0, 36.8, 37.2, 36.9};
    double fever_limit = 38.0;
    bool no_fever = std::none_of(temps.begin(), temps.end(),
                                 [fever_limit](double t) { return t >= fever_limit; });
    std::cout << "No fever readings (< " << fever_limit << "): " << no_fever << std::endl;

    return 0;
}

// Expected output:
// None even (odd list): true
// None negative: true
// None negative after adding -2: false
// No zeros in data: true
// None of empty range: true
// No fever readings (< 38): true
