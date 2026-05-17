// CodeNebula - C++23 Example: Range-Based For with Initializer
// Compile: g++ -std=c++23 -Wall -Wextra -o example range_for_initializer.cpp
// Note: Range-for init-statement was introduced in C++20 (P0614R1).
// This file demonstrates C++23 usage patterns and combinations.

// The init-statement in range-based for allows:
//   for (init; decl : range) { ... }
// This keeps temporary objects alive and limits variable scope.

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <numeric>

std::vector<int> get_scores() {
    return {85, 92, 78, 95, 88, 71, 96};
}

std::map<std::string, int> get_inventory() {
    return {{"apples", 5}, {"bananas", 12}, {"oranges", 8}, {"grapes", 3}};
}

int main() {
    std::cout << "=== Range-Based For with Initializer ===" << std::endl;

    // Keep temporary alive: without init-statement, the temporary
    // returned by get_scores() would dangle
    std::cout << "Scores above 80:" << std::endl;
    for (auto scores = get_scores(); int s : scores) {
        if (s > 80) std::cout << "  " << s << std::endl;
    }

    // Init-statement with index tracking
    std::cout << "\n=== With index counter ===" << std::endl;
    std::vector<std::string> fruits = {"apple", "banana", "cherry", "date"};
    for (int i = 0; const auto& f : fruits) {
        std::cout << "  [" << i++ << "] " << f << std::endl;
    }

    // Init-statement with computed value
    std::cout << "\n=== With pre-computed value ===" << std::endl;
    std::vector<int> data = {10, 20, 30, 40, 50};
    for (auto avg = std::accumulate(data.begin(), data.end(), 0) /
                    static_cast<int>(data.size());
         int val : data) {
        std::cout << "  " << val << (val > avg ? " (above avg)" : " (at/below avg)")
                  << std::endl;
    }

    // Init-statement with map (structured bindings)
    std::cout << "\n=== Map iteration with init ===" << std::endl;
    for (auto inv = get_inventory(); const auto& [item, count] : inv) {
        std::cout << "  " << item << ": " << count
                  << (count < 5 ? " (low stock!)" : "") << std::endl;
    }

    // Init-statement with lock (conceptual - common real-world use)
    std::cout << "\n=== Scoped variable in range-for ===" << std::endl;
    for (auto prefix = std::string(">> "); char c : std::string("C++23")) {
        std::cout << prefix << c << std::endl;
    }

    return 0;
}

/*
Expected output:
=== Range-Based For with Initializer ===
Scores above 80:
  85
  92
  95
  88
  96

=== With index counter ===
  [0] apple
  [1] banana
  [2] cherry
  [3] date

=== With pre-computed value ===
  10 (at/below avg)
  20 (at/below avg)
  30 (at/below avg)
  40 (above avg)
  50 (above avg)

=== Map iteration with init ===
  apples: 5 (low stock!)
  bananas: 12
  grapes: 3 (low stock!)
  oranges: 8

=== Scoped variable in range-for ===
>> C
>> +
>> +
>> 2
>> 3
*/
