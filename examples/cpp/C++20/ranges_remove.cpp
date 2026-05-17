// CodeNebula - C++20 Example: ranges::remove, remove_if
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_remove.cpp

#include <iostream>
#include <ranges>
#include <vector>
#include <string>
#include <algorithm>

struct Task {
    std::string name;
    bool completed;
    int priority;
};

int main() {
    // ranges::remove - move matching elements to end, return subrange
    std::vector<int> numbers = {1, 2, 3, 2, 4, 2, 5, 2, 6};
    std::cout << "Before remove 2: ";
    for (int n : numbers) std::cout << n << " ";
    std::cout << "\n";

    auto [rem_begin, rem_end] = std::ranges::remove(numbers, 2);
    numbers.erase(rem_begin, rem_end);
    std::cout << "After erase-remove: ";
    for (int n : numbers) std::cout << n << " ";
    std::cout << "\n";

    // ranges::remove_if - remove by predicate
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto ret = std::ranges::remove_if(data, [](int n) { return n % 2 != 0; });
    data.erase(ret.begin(), ret.end());
    std::cout << "\nAfter removing odds: ";
    for (int n : data) std::cout << n << " ";
    std::cout << "\n";

    // Remove with strings
    std::vector<std::string> words = {"apple", "bad", "cherry", "bad", "date"};
    auto ret2 = std::ranges::remove(words, std::string("bad"));
    words.erase(ret2.begin(), ret2.end());
    std::cout << "After removing 'bad': ";
    for (const auto& w : words) std::cout << w << " ";
    std::cout << "\n";

    // remove_if with projection
    std::vector<Task> tasks = {
        {"Write code", true, 3}, {"Review PR", false, 2},
        {"Fix bug", true, 1}, {"Deploy", false, 3}, {"Test", true, 2}
    };
    auto completed = std::ranges::remove_if(tasks,
        [](bool done) { return done; }, &Task::completed);
    tasks.erase(completed.begin(), completed.end());
    std::cout << "\nRemaining tasks (" << tasks.size() << "):\n";
    for (const auto& t : tasks)
        std::cout << "  " << t.name << " (priority: " << t.priority << ")\n";

    // Remove characters from a string
    std::string text = "H e l l o   W o r l d";
    auto spaces = std::ranges::remove(text, ' ');
    text.erase(spaces.begin(), spaces.end());
    std::cout << "\nSpaces removed: " << text << "\n";

    // remove_if on string (remove vowels)
    std::string msg = "Programming is fun";
    auto vowels = std::ranges::remove_if(msg,
        [](char c) { return std::string("aeiouAEIOU").find(c) != std::string::npos; });
    msg.erase(vowels.begin(), vowels.end());
    std::cout << "Vowels removed: " << msg << "\n";
    return 0;
}
