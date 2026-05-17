// CodeNebula - C++20 Example: std::predicate Concept
// Compile: g++ -std=c++20 -Wall -Wextra -o example predicate.cpp

// std::predicate<F, Args...> refines std::regular_invocable by requiring
// that the callable returns a boolean-testable value. Predicates are the
// foundation of algorithms like filter, find_if, and count_if.

#include <concepts>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

// Filter elements matching a predicate
template <typename T, std::predicate<T> Pred>
std::vector<T> filter(const std::vector<T>& items, Pred pred) {
    std::vector<T> result;
    for (const auto& item : items) {
        if (std::invoke(pred, item)) {
            result.push_back(item);
        }
    }
    return result;
}

// Count elements matching a predicate
template <typename T, std::predicate<T> Pred>
std::size_t count_if(const std::vector<T>& items, Pred pred) {
    std::size_t count = 0;
    for (const auto& item : items)
        if (std::invoke(pred, item)) ++count;
    return count;
}

// Check if any element matches
template <typename T, std::predicate<T> Pred>
bool any_of(const std::vector<T>& items, Pred pred) {
    for (const auto& item : items)
        if (std::invoke(pred, item)) return true;
    return false;
}

// Named predicates
bool is_positive(int x) { return x > 0; }

struct IsLongerThan {
    std::size_t min_len;
    bool operator()(const std::string& s) const { return s.size() > min_len; }
};

int main() {
    // Filter integers
    std::vector<int> nums = {-3, -1, 0, 2, 5, -4, 8, 1};

    auto positives = filter(nums, is_positive);
    std::cout << "Positives: ";
    for (int n : positives) std::cout << n << " ";
    std::cout << "\n";

    auto evens = filter(nums, [](int x) { return x % 2 == 0; });
    std::cout << "Evens: ";
    for (int n : evens) std::cout << n << " ";
    std::cout << "\n";

    // Count with predicate
    std::cout << "Count positive: " << count_if(nums, is_positive) << "\n";
    std::cout << "Count negative: "
              << count_if(nums, [](int x) { return x < 0; }) << "\n";

    // Filter strings with function object predicate
    std::vector<std::string> words = {"hi", "hello", "hey", "greetings", "yo"};
    auto long_words = filter(words, IsLongerThan{3});
    std::cout << "\nWords longer than 3: ";
    for (const auto& w : long_words) std::cout << w << " ";
    std::cout << "\n";

    // any_of
    std::cout << "Any negative? " << any_of(nums, [](int x) { return x < 0; }) << "\n";
    std::cout << "Any > 100? " << any_of(nums, [](int x) { return x > 100; }) << "\n";

    return 0;
}

// Expected output:
// Positives: 2 5 8 1
// Evens: 0 2 -4 8
// Count positive: 4
// Count negative: 3
//
// Words longer than 3: hello greetings
//
// Any negative? 1
// Any > 100? 0
