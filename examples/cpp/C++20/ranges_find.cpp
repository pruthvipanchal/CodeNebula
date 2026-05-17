// CodeNebula - C++20 Example: ranges::find, find_if, find_if_not
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_find.cpp

#include <iostream>
#include <ranges>
#include <vector>
#include <string>
#include <algorithm>

struct Person {
    std::string name;
    int age;
};

int main() {
    std::vector<int> numbers = {10, 25, 30, 45, 50, 65, 70, 85};

    // ranges::find - find exact value
    auto it = std::ranges::find(numbers, 45);
    if (it != numbers.end())
        std::cout << "Found 45 at index " << (it - numbers.begin()) << "\n";

    it = std::ranges::find(numbers, 99);
    std::cout << "Found 99: " << std::boolalpha << (it != numbers.end()) << "\n";

    // ranges::find_if - find by predicate
    auto it2 = std::ranges::find_if(numbers, [](int n) { return n > 60; });
    if (it2 != numbers.end())
        std::cout << "First > 60: " << *it2 << "\n";

    // ranges::find_if_not - find first that doesn't match
    auto it3 = std::ranges::find_if_not(numbers, [](int n) { return n < 50; });
    if (it3 != numbers.end())
        std::cout << "First not < 50: " << *it3 << "\n";

    // Find with projection
    std::vector<Person> people = {
        {"Alice", 30}, {"Bob", 25}, {"Charlie", 35}, {"Diana", 28}
    };
    auto person = std::ranges::find(people, "Charlie", &Person::name);
    if (person != people.end())
        std::cout << "\nFound " << person->name << ", age " << person->age << "\n";

    // find_if with projection
    auto young = std::ranges::find_if(people, [](int age) { return age < 28; },
                                      &Person::age);
    if (young != people.end())
        std::cout << "Youngest under 28: " << young->name << "\n";

    // Find in strings
    std::vector<std::string> words = {"apple", "banana", "cherry", "date"};
    auto long_word = std::ranges::find_if(words,
        [](const std::string& s) { return s.size() > 5; });
    if (long_word != words.end())
        std::cout << "\nFirst word > 5 chars: " << *long_word << "\n";

    // find_if_not with projection
    auto not_short = std::ranges::find_if_not(words,
        [](size_t len) { return len <= 5; }, &std::string::size);
    if (not_short != words.end())
        std::cout << "First word not short: " << *not_short << "\n";

    return 0;
}
