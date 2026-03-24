// CodeNebula - C++20 Example: Uniform Container Erasure
// Compile: g++ -std=c++20 -Wall -Wextra -o example erase.cpp

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <string>
#include <set>
#include <map>

int main() {
    // std::erase - remove all occurrences of a value from a vector
    std::vector<int> nums = {1, 2, 3, 2, 5, 2, 7, 2};
    std::cout << "Original: ";
    for (int n : nums) std::cout << n << ' ';
    std::cout << '\n';

    auto removed = std::erase(nums, 2);
    std::cout << "After erase(2): ";
    for (int n : nums) std::cout << n << ' ';
    std::cout << " (removed " << removed << " elements)\n";

    // std::erase_if - remove elements matching a predicate
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto erased = std::erase_if(data, [](int x) { return x % 2 == 0; });
    std::cout << "\nAfter erase_if(even): ";
    for (int d : data) std::cout << d << ' ';
    std::cout << " (removed " << erased << ")\n";

    // Works uniformly across container types - list
    std::list<int> lst = {5, 10, 15, 10, 20, 10};
    std::erase(lst, 10);
    std::cout << "\nList after erase(10): ";
    for (int l : lst) std::cout << l << ' ';
    std::cout << '\n';

    // Deque
    std::deque<int> dq = {3, 1, 4, 1, 5, 9, 2, 6};
    std::erase_if(dq, [](int x) { return x < 4; });
    std::cout << "Deque after erase_if(<4): ";
    for (int d : dq) std::cout << d << ' ';
    std::cout << '\n';

    // String
    std::string text = "Hello, World!";
    std::erase(text, 'l');
    std::cout << "\nString after erase('l'): " << text << '\n';

    std::string sentence = "C++ is a great language!";
    std::erase_if(sentence, [](char c) { return c == ' '; });
    std::cout << "After erase_if(spaces): " << sentence << '\n';

    // Associative containers only support erase_if
    std::set<int> s = {1, 2, 3, 4, 5, 6, 7, 8};
    std::erase_if(s, [](int x) { return x % 3 == 0; });
    std::cout << "\nSet after erase_if(%%3==0): ";
    for (int x : s) std::cout << x << ' ';
    std::cout << '\n';

    std::map<std::string, int> scores = {
        {"Alice", 85}, {"Bob", 42}, {"Carol", 91}, {"Dave", 38}
    };
    std::erase_if(scores, [](const auto& pair) { return pair.second < 50; });
    std::cout << "Map after erase_if(score<50):\n";
    for (const auto& [name, score] : scores)
        std::cout << "  " << name << ": " << score << '\n';

    return 0;
}
