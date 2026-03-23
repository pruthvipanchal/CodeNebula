// CodeNebula - C++11 Example: std::unordered_set Hash Set
// Compile: g++ -std=c++11 -Wall -Wextra -o example unordered_set.cpp

// std::unordered_set is a hash-based container that stores unique elements.
// It provides O(1) average-case lookup, insertion, and deletion.
// Elements are not stored in any particular order.

#include <iostream>
#include <unordered_set>
#include <string>

int main() {
    // Create an unordered_set with initializer list
    std::unordered_set<std::string> fruits = {"apple", "banana", "cherry"};

    // Insert elements
    fruits.insert("date");
    auto result = fruits.insert("apple");  // duplicate - won't be inserted
    std::cout << "Insert 'apple' again: "
              << (result.second ? "success" : "already exists") << std::endl;

    // Size and bucket info
    std::cout << "Size: " << fruits.size() << std::endl;
    std::cout << "Bucket count: " << fruits.bucket_count() << std::endl;
    std::cout << "Load factor: " << fruits.load_factor() << std::endl;

    // Find an element - O(1) average
    auto it = fruits.find("banana");
    if (it != fruits.end()) {
        std::cout << "Found: " << *it << std::endl;
    }

    // Count occurrences (0 or 1 for set)
    std::cout << "Count 'cherry': " << fruits.count("cherry") << std::endl;
    std::cout << "Count 'grape': " << fruits.count("grape") << std::endl;

    // Erase an element
    fruits.erase("banana");
    std::cout << "After erasing 'banana', size: " << fruits.size() << std::endl;

    // Iterate (order is not guaranteed)
    std::cout << "All fruits: ";
    for (const auto& f : fruits) {
        std::cout << f << " ";
    }
    std::cout << std::endl;

    // Emplace constructs element in-place
    fruits.emplace("elderberry");
    std::cout << "After emplace, size: " << fruits.size() << std::endl;

    return 0;
}

// Expected output:
// Insert 'apple' again: already exists
// Size: 4
// Bucket count: <implementation-defined>
// Load factor: <implementation-defined>
// Found: banana
// Count 'cherry': 1
// Count 'grape': 0
// After erasing 'banana', size: 3
// All fruits: <unordered - varies by implementation>
// After emplace, size: 4
