// CodeNebula - C++11 Example: std::unordered_multimap
// Compile: g++ -std=c++11 -Wall -Wextra -o example unordered_multimap.cpp

// std::unordered_multimap is a hash-based associative container that allows
// multiple key-value pairs with the same key. It provides O(1) average-case
// insertion and lookup, useful for one-to-many mappings.

#include <iostream>
#include <unordered_map>
#include <string>

int main() {
    // Create with initializer list (duplicate keys allowed)
    std::unordered_multimap<std::string, std::string> courses = {
        {"Alice", "Math"}, {"Bob", "Physics"},
        {"Alice", "History"}, {"Bob", "Chemistry"},
        {"Alice", "Art"}
    };

    std::cout << "Total entries: " << courses.size() << std::endl;

    // Count entries for a given key
    std::cout << "Alice's courses: " << courses.count("Alice") << std::endl;
    std::cout << "Bob's courses: " << courses.count("Bob") << std::endl;

    // Use equal_range to get all values for a key
    std::cout << "Alice is enrolled in: ";
    auto range = courses.equal_range("Alice");
    for (auto it = range.first; it != range.second; ++it) {
        std::cout << it->second << " ";
    }
    std::cout << std::endl;

    // Insert additional entries
    courses.emplace("Charlie", "Biology");
    courses.emplace("Charlie", "Math");
    std::cout << "Charlie's courses: " << courses.count("Charlie") << std::endl;

    // Erase one entry for Bob (using iterator)
    auto it = courses.find("Bob");
    if (it != courses.end()) {
        std::cout << "Removing Bob's course: " << it->second << std::endl;
        courses.erase(it);
    }
    std::cout << "Bob's remaining courses: " << courses.count("Bob") << std::endl;

    // Erase all entries for Alice
    courses.erase("Alice");
    std::cout << "After removing all Alice entries, size: " << courses.size() << std::endl;

    // Iterate over all remaining entries
    std::cout << "Remaining entries:" << std::endl;
    for (const auto& pair : courses) {
        std::cout << "  " << pair.first << " -> " << pair.second << std::endl;
    }

    return 0;
}

// Expected output:
// Total entries: 5
// Alice's courses: 3
// Bob's courses: 2
// Alice is enrolled in: Art History Math (order may vary)
// Charlie's courses: 2
// Removing Bob's course: <one of Bob's courses>
// Bob's remaining courses: 1
// After removing all Alice entries, size: 4
// Remaining entries:
//   <unordered - varies by implementation>
