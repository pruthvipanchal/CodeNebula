// CodeNebula - C++11 Example: std::unordered_multiset
// Compile: g++ -std=c++11 -Wall -Wextra -o example unordered_multiset.cpp

// std::unordered_multiset is a hash-based container that allows duplicate
// elements. Unlike std::unordered_set, the same value can appear multiple
// times. It provides O(1) average-case insertion and lookup.

#include <iostream>
#include <unordered_set>
#include <string>

int main() {
    // Create with initializer list (note duplicates are allowed)
    std::unordered_multiset<std::string> words = {
        "hello", "world", "hello", "foo", "world", "hello"
    };

    std::cout << "Size: " << words.size() << std::endl;

    // Count occurrences of each element
    std::cout << "Count 'hello': " << words.count("hello") << std::endl;
    std::cout << "Count 'world': " << words.count("world") << std::endl;
    std::cout << "Count 'foo': " << words.count("foo") << std::endl;
    std::cout << "Count 'bar': " << words.count("bar") << std::endl;

    // Insert more duplicates
    words.insert("foo");
    words.insert("foo");
    std::cout << "After adding 2 more 'foo', count: " << words.count("foo") << std::endl;

    // equal_range returns all elements with a given key
    auto range = words.equal_range("hello");
    std::cout << "All 'hello' entries: ";
    for (auto it = range.first; it != range.second; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Erase one instance vs all instances
    // erase(iterator) removes one; erase(key) removes all
    auto it = words.find("hello");
    if (it != words.end()) {
        words.erase(it);  // removes only one "hello"
    }
    std::cout << "After erasing one 'hello', count: " << words.count("hello") << std::endl;

    words.erase("foo");  // removes ALL "foo" entries
    std::cout << "After erasing all 'foo', count: " << words.count("foo") << std::endl;

    std::cout << "Final size: " << words.size() << std::endl;

    // Iterate all remaining elements
    std::cout << "Remaining: ";
    for (const auto& w : words) {
        std::cout << w << " ";
    }
    std::cout << std::endl;

    return 0;
}

// Expected output:
// Size: 6
// Count 'hello': 3
// Count 'world': 2
// Count 'foo': 1
// Count 'bar': 0
// After adding 2 more 'foo', count: 3
// All 'hello' entries: hello hello hello
// After erasing one 'hello', count: 2
// After erasing all 'foo', count: 0
// Final size: 4
// Remaining: <unordered - varies by implementation>
