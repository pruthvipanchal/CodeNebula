// CodeNebula - C++11 Example: std::unordered_map Hash Map
// Compile: g++ -std=c++11 -Wall -Wextra -o example unordered_map.cpp

// std::unordered_map is a hash-based associative container storing key-value
// pairs with unique keys. It provides O(1) average-case lookup, insertion,
// and deletion, making it faster than std::map for most use cases.

#include <iostream>
#include <unordered_map>
#include <string>

int main() {
    // Create with initializer list
    std::unordered_map<std::string, int> ages = {
        {"Alice", 30}, {"Bob", 25}, {"Charlie", 35}
    };

    // Insert using different methods
    ages["Dave"] = 28;                        // operator[]
    ages.insert({"Eve", 22});                 // insert with pair
    ages.emplace("Frank", 40);                // emplace in-place

    std::cout << "Size: " << ages.size() << std::endl;

    // Access elements
    std::cout << "Alice's age: " << ages["Alice"] << std::endl;
    std::cout << "Bob's age: " << ages.at("Bob") << std::endl;

    // Find an element
    auto it = ages.find("Charlie");
    if (it != ages.end()) {
        std::cout << "Found " << it->first << " -> " << it->second << std::endl;
    }

    // Check existence
    std::cout << "Contains 'Eve': " << (ages.count("Eve") ? "yes" : "no") << std::endl;
    std::cout << "Contains 'Zoe': " << (ages.count("Zoe") ? "yes" : "no") << std::endl;

    // Erase by key
    ages.erase("Dave");
    std::cout << "After erasing Dave, size: " << ages.size() << std::endl;

    // Iterate over all key-value pairs (order not guaranteed)
    std::cout << "All entries:" << std::endl;
    for (const auto& pair : ages) {
        std::cout << "  " << pair.first << ": " << pair.second << std::endl;
    }

    // Bucket information
    std::cout << "Bucket count: " << ages.bucket_count() << std::endl;

    return 0;
}

// Expected output:
// Size: 6
// Alice's age: 30
// Bob's age: 25
// Found Charlie -> 35
// Contains 'Eve': yes
// Contains 'Zoe': no
// After erasing Dave, size: 5
// All entries:
//   <unordered - entries in implementation-defined order>
// Bucket count: <implementation-defined>
