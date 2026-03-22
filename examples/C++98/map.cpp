// CodeNebula - C++98 Example: map
// Compile: g++ -std=c++98 -Wall -Wextra -o example map.cpp

// std::map is an ordered associative container that stores key-value pairs
// with unique keys. Elements are sorted by key. O(log n) lookup, insertion, removal.

#include <iostream>
#include <map>
#include <string>

void print_map(const std::string& label, const std::map<std::string, int>& m) {
    std::cout << label << ":" << std::endl;
    for (std::map<std::string, int>::const_iterator it = m.begin(); it != m.end(); ++it) {
        std::cout << "  [" << it->first << "] = " << it->second << std::endl;
    }
    std::cout << "  (size=" << m.size() << ")" << std::endl;
}

int main() {
    // --- Insert with std::pair and make_pair ---
    std::cout << "=== insert ===" << std::endl;
    std::map<std::string, int> ages;

    // Method 1: insert with std::pair constructor
    ages.insert(std::pair<std::string, int>("Alice", 30));

    // Method 2: insert with std::make_pair
    ages.insert(std::make_pair(std::string("Bob"), 25));
    ages.insert(std::make_pair(std::string("Charlie"), 35));

    print_map("After inserts", ages);

    // Insert returns pair<iterator, bool> - duplicate key fails
    std::pair<std::map<std::string, int>::iterator, bool> result;
    result = ages.insert(std::make_pair(std::string("Alice"), 99));
    std::cout << "Insert duplicate 'Alice': success="
              << (result.second ? "true" : "false")
              << ", value=" << result.first->second << std::endl;

    // --- operator[] ---
    std::cout << "\n=== operator[] ===" << std::endl;

    // operator[] inserts if key doesn't exist (default-constructs value)
    ages["Diana"] = 28;
    ages["Eve"] = 22;
    std::cout << "ages[\"Alice\"] = " << ages["Alice"] << std::endl;
    std::cout << "ages[\"Diana\"] = " << ages["Diana"] << std::endl;

    // Modifying with []
    ages["Bob"] = 26;
    std::cout << "After ages[\"Bob\"] = 26: " << ages["Bob"] << std::endl;

    // Warning: accessing non-existent key with [] creates it!
    std::cout << "ages[\"Unknown\"] = " << ages["Unknown"]
              << " (created with default value)" << std::endl;
    print_map("Current map", ages);

    // --- find ---
    std::cout << "\n=== find ===" << std::endl;
    std::map<std::string, int>::iterator it = ages.find("Charlie");
    if (it != ages.end()) {
        std::cout << "Found Charlie: " << it->second << std::endl;
    }

    it = ages.find("Zara");
    if (it == ages.end()) {
        std::cout << "Zara not found" << std::endl;
    }

    // --- count ---
    std::cout << "\n=== count ===" << std::endl;
    std::cout << "count(\"Alice\") = " << ages.count("Alice") << std::endl;
    std::cout << "count(\"Nobody\") = " << ages.count("Nobody") << std::endl;

    // --- erase ---
    std::cout << "\n=== erase ===" << std::endl;
    // Erase the default-created "Unknown" entry
    ages.erase("Unknown");
    std::cout << "After erasing 'Unknown': size=" << ages.size() << std::endl;

    // Erase by iterator
    it = ages.find("Eve");
    if (it != ages.end()) {
        ages.erase(it);
    }
    std::cout << "After erasing 'Eve': size=" << ages.size() << std::endl;

    // --- Iteration (ordered by key) ---
    std::cout << "\n=== Iteration (ordered by key) ===" << std::endl;
    std::cout << "Forward:" << std::endl;
    for (std::map<std::string, int>::iterator it2 = ages.begin();
         it2 != ages.end(); ++it2) {
        std::cout << "  " << it2->first << " => " << it2->second << std::endl;
    }

    std::cout << "Reverse:" << std::endl;
    for (std::map<std::string, int>::reverse_iterator rit = ages.rbegin();
         rit != ages.rend(); ++rit) {
        std::cout << "  " << rit->first << " => " << rit->second << std::endl;
    }

    // --- lower_bound, upper_bound ---
    std::cout << "\n=== lower_bound and upper_bound ===" << std::endl;
    std::map<std::string, int>::iterator lb = ages.lower_bound("Bob");
    std::cout << "lower_bound(\"Bob\"): " << lb->first << " => " << lb->second << std::endl;

    std::map<std::string, int>::iterator ub = ages.upper_bound("Bob");
    std::cout << "upper_bound(\"Bob\"): " << ub->first << " => " << ub->second << std::endl;

    // --- Map with int keys ---
    std::cout << "\n=== Map with int keys ===" << std::endl;
    std::map<int, std::string> id_names;
    id_names[3] = "Three";
    id_names[1] = "One";
    id_names[4] = "Four";
    id_names[1] = "Uno"; // overwrite
    id_names[5] = "Five";

    for (std::map<int, std::string>::iterator it3 = id_names.begin();
         it3 != id_names.end(); ++it3) {
        std::cout << "  " << it3->first << " -> " << it3->second << std::endl;
    }

    // --- empty, size, clear ---
    std::cout << "\n=== empty, size, clear ===" << std::endl;
    std::cout << "id_names.empty() = " << (id_names.empty() ? "true" : "false") << std::endl;
    std::cout << "id_names.size() = " << id_names.size() << std::endl;
    id_names.clear();
    std::cout << "After clear: empty=" << (id_names.empty() ? "true" : "false") << std::endl;

    return 0;
}

/*
Expected output:
=== insert ===
After inserts:
  [Alice] = 30
  [Bob] = 25
  [Charlie] = 35
  (size=3)
Insert duplicate 'Alice': success=false, value=30

=== operator[] ===
ages["Alice"] = 30
ages["Diana"] = 28
After ages["Bob"] = 26: 26
ages["Unknown"] = 0 (created with default value)
Current map:
  [Alice] = 30
  [Bob] = 26
  [Charlie] = 35
  [Diana] = 28
  [Eve] = 22
  [Unknown] = 0
  (size=6)

=== find ===
Found Charlie: 35
Zara not found

=== count ===
count("Alice") = 1
count("Nobody") = 0

=== erase ===
After erasing 'Unknown': size=5
After erasing 'Eve': size=4

=== Iteration (ordered by key) ===
Forward:
  Alice => 30
  Bob => 26
  Charlie => 35
  Diana => 28
Reverse:
  Diana => 28
  Charlie => 35
  Bob => 26
  Alice => 30

=== lower_bound and upper_bound ===
lower_bound("Bob"): Bob => 26
upper_bound("Bob"): Charlie => 35

=== Map with int keys ===
  1 -> Uno
  3 -> Three
  4 -> Four
  5 -> Five

=== empty, size, clear ===
id_names.empty() = false
id_names.size() = 4
After clear: empty=true
*/
