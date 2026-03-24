// CodeNebula - C++23 Example: std::flat_multimap
// Compile: g++ -std=c++23 -Wall -Wextra -o example flat_multimap.cpp
// Note: Requires GCC 14+ / Clang 18+ / MSVC 19.37+

// std::flat_multimap is like std::flat_map but allows duplicate keys.
// Elements with equal keys maintain insertion order among themselves.

#include <iostream>
#include <flat_map>
#include <string>

int main() {
    std::cout << "=== std::flat_multimap ===" << std::endl;

    // Construction: duplicate keys are allowed
    std::flat_multimap<std::string, int> grades;
    grades.insert({"Alice", 90});
    grades.insert({"Bob", 85});
    grades.insert({"Alice", 95});  // duplicate key OK
    grades.insert({"Bob", 88});
    grades.insert({"Alice", 92});
    grades.insert({"Charlie", 77});

    std::cout << "All entries (sorted by key):" << std::endl;
    for (const auto& [name, grade] : grades) {
        std::cout << "  " << name << ": " << grade << std::endl;
    }

    // Count entries per key
    std::cout << "\n=== Count per key ===" << std::endl;
    std::cout << "Alice entries:   " << grades.count("Alice") << std::endl;
    std::cout << "Bob entries:     " << grades.count("Bob") << std::endl;
    std::cout << "Charlie entries: " << grades.count("Charlie") << std::endl;

    // equal_range: get all values for a key
    std::cout << "\n=== equal_range for Alice ===" << std::endl;
    auto [begin, end] = grades.equal_range("Alice");
    std::cout << "Alice's grades: ";
    for (auto it = begin; it != end; ++it) {
        std::cout << it->second << " ";
    }
    std::cout << std::endl;

    // Find returns iterator to first matching element
    std::cout << "\n=== find ===" << std::endl;
    auto it = grades.find("Bob");
    if (it != grades.end()) {
        std::cout << "First Bob entry: " << it->second << std::endl;
    }

    // Contains
    std::cout << "Contains 'Diana': " << grades.contains("Diana") << std::endl;

    // Erase all entries for a key
    auto erased = grades.erase("Alice");
    std::cout << "\nErased " << erased << " Alice entries" << std::endl;
    std::cout << "Remaining size: " << grades.size() << std::endl;

    // Initializer list construction
    std::cout << "\n=== Initializer list ===" << std::endl;
    std::flat_multimap<int, std::string> events = {
        {2023, "Conference"}, {2023, "Workshop"}, {2024, "Summit"},
        {2023, "Hackathon"}, {2024, "Meetup"}
    };
    for (const auto& [year, event] : events) {
        std::cout << "  " << year << ": " << event << std::endl;
    }

    return 0;
}

/*
Expected output:
=== std::flat_multimap ===
All entries (sorted by key):
  Alice: 90
  Alice: 95
  Alice: 92
  Bob: 85
  Bob: 88
  Charlie: 77

=== Count per key ===
Alice entries:   3
Bob entries:     2
Charlie entries: 1

=== equal_range for Alice ===
Alice's grades: 90 95 92

=== find ===
First Bob entry: 85
Contains 'Diana': 0

Erased 3 Alice entries
Remaining size: 3

=== Initializer list ===
  2023: Conference
  2023: Workshop
  2023: Hackathon
  2024: Summit
  2024: Meetup
*/
