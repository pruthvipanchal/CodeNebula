// CodeNebula - C++98 Example: multimap
// Compile: g++ -std=c++98 -Wall -Wextra -o example multimap.cpp

// std::multimap is like std::map but allows duplicate keys.
// Elements with equal keys are stored adjacently in insertion order.

#include <iostream>
#include <map>
#include <string>

void print_multimap(const std::string& label,
                    const std::multimap<std::string, int>& mm) {
    std::cout << label << ":" << std::endl;
    for (std::multimap<std::string, int>::const_iterator it = mm.begin();
         it != mm.end(); ++it) {
        std::cout << "  [" << it->first << "] = " << it->second << std::endl;
    }
    std::cout << "  (size=" << mm.size() << ")" << std::endl;
}

int main() {
    // --- Insert duplicate keys ---
    std::cout << "=== insert duplicate keys ===" << std::endl;
    std::multimap<std::string, int> scores;

    // A student can have multiple scores
    scores.insert(std::make_pair(std::string("Alice"), 95));
    scores.insert(std::make_pair(std::string("Bob"), 87));
    scores.insert(std::make_pair(std::string("Alice"), 88));
    scores.insert(std::make_pair(std::string("Charlie"), 92));
    scores.insert(std::make_pair(std::string("Bob"), 91));
    scores.insert(std::make_pair(std::string("Alice"), 76));

    print_multimap("Student scores", scores);

    // Note: multimap does NOT have operator[], since keys are not unique

    // --- count ---
    std::cout << "\n=== count ===" << std::endl;
    std::cout << "count(\"Alice\") = " << scores.count("Alice") << std::endl;
    std::cout << "count(\"Bob\") = " << scores.count("Bob") << std::endl;
    std::cout << "count(\"Charlie\") = " << scores.count("Charlie") << std::endl;
    std::cout << "count(\"Nobody\") = " << scores.count("Nobody") << std::endl;

    // --- find ---
    std::cout << "\n=== find ===" << std::endl;
    std::multimap<std::string, int>::iterator it = scores.find("Bob");
    if (it != scores.end()) {
        std::cout << "find(\"Bob\"): first match = "
                  << it->first << " => " << it->second << std::endl;
    }

    it = scores.find("Nobody");
    std::cout << "find(\"Nobody\"): "
              << (it == scores.end() ? "not found" : "found") << std::endl;

    // --- equal_range (the primary way to get all values for a key) ---
    std::cout << "\n=== equal_range ===" << std::endl;

    std::pair<std::multimap<std::string, int>::iterator,
              std::multimap<std::string, int>::iterator> range;

    range = scores.equal_range("Alice");
    std::cout << "All scores for Alice: ";
    for (std::multimap<std::string, int>::iterator r = range.first;
         r != range.second; ++r) {
        std::cout << r->second << " ";
    }
    std::cout << std::endl;

    range = scores.equal_range("Bob");
    std::cout << "All scores for Bob: ";
    for (std::multimap<std::string, int>::iterator r = range.first;
         r != range.second; ++r) {
        std::cout << r->second << " ";
    }
    std::cout << std::endl;

    range = scores.equal_range("Nobody");
    std::cout << "Scores for Nobody: "
              << (range.first == range.second ? "none" : "found") << std::endl;

    // --- lower_bound and upper_bound ---
    std::cout << "\n=== lower_bound and upper_bound ===" << std::endl;
    std::multimap<std::string, int>::iterator lb = scores.lower_bound("Bob");
    std::multimap<std::string, int>::iterator ub = scores.upper_bound("Bob");
    std::cout << "Elements for key 'Bob' (lb to ub):" << std::endl;
    for (std::multimap<std::string, int>::iterator r = lb; r != ub; ++r) {
        std::cout << "  " << r->first << " => " << r->second << std::endl;
    }

    // --- erase ---
    std::cout << "\n=== erase ===" << std::endl;
    print_multimap("Before erase", scores);

    // Erase one element by iterator
    it = scores.find("Alice");
    if (it != scores.end()) {
        std::cout << "Erasing first Alice entry (score=" << it->second << ")" << std::endl;
        scores.erase(it);
    }
    print_multimap("After erasing one Alice", scores);

    // Erase all entries for a key
    std::multimap<std::string, int>::size_type erased = scores.erase("Bob");
    std::cout << "Erased all Bobs: removed " << erased << " entries" << std::endl;
    print_multimap("After erasing all Bobs", scores);

    // --- Iteration ---
    std::cout << "\n=== Reverse iteration ===" << std::endl;
    std::cout << "Reverse:" << std::endl;
    for (std::multimap<std::string, int>::reverse_iterator rit = scores.rbegin();
         rit != scores.rend(); ++rit) {
        std::cout << "  [" << rit->first << "] = " << rit->second << std::endl;
    }

    // --- Integer key multimap ---
    std::cout << "\n=== Integer key multimap ===" << std::endl;
    std::multimap<int, std::string> priority_tasks;
    priority_tasks.insert(std::make_pair(1, std::string("Critical fix")));
    priority_tasks.insert(std::make_pair(3, std::string("Nice to have")));
    priority_tasks.insert(std::make_pair(1, std::string("Security patch")));
    priority_tasks.insert(std::make_pair(2, std::string("Performance")));
    priority_tasks.insert(std::make_pair(1, std::string("Data migration")));

    std::cout << "Tasks by priority:" << std::endl;
    for (std::multimap<int, std::string>::iterator it2 = priority_tasks.begin();
         it2 != priority_tasks.end(); ++it2) {
        std::cout << "  Priority " << it2->first << ": " << it2->second << std::endl;
    }

    return 0;
}

/*
Expected output:
=== insert duplicate keys ===
Student scores:
  [Alice] = 95
  [Alice] = 88
  [Alice] = 76
  [Bob] = 87
  [Bob] = 91
  [Charlie] = 92
  (size=6)

=== count ===
count("Alice") = 3
count("Bob") = 2
count("Charlie") = 1
count("Nobody") = 0

=== find ===
find("Bob"): first match = Bob => 87
find("Nobody"): not found

=== equal_range ===
All scores for Alice: 95 88 76
All scores for Bob: 87 91
Scores for Nobody: none

=== lower_bound and upper_bound ===
Elements for key 'Bob' (lb to ub):
  Bob => 87
  Bob => 91

=== erase ===
Before erase:
  [Alice] = 95
  [Alice] = 88
  [Alice] = 76
  [Bob] = 87
  [Bob] = 91
  [Charlie] = 92
  (size=6)
Erasing first Alice entry (score=95)
After erasing one Alice:
  [Alice] = 88
  [Alice] = 76
  [Bob] = 87
  [Bob] = 91
  [Charlie] = 92
  (size=5)
Erased all Bobs: removed 2 entries
After erasing all Bobs:
  [Alice] = 88
  [Alice] = 76
  [Charlie] = 92
  (size=3)

=== Reverse iteration ===
Reverse:
  [Charlie] = 92
  [Alice] = 76
  [Alice] = 88

=== Integer key multimap ===
Tasks by priority:
  Priority 1: Critical fix
  Priority 1: Security patch
  Priority 1: Data migration
  Priority 2: Performance
  Priority 3: Nice to have
*/
