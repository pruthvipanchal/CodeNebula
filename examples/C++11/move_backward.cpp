// CodeNebula - C++11 Example: std::move_backward
// Compile: g++ -std=c++11 -Wall -Wextra -o example move_backward.cpp

// std::move_backward moves elements from a source range to a destination
// in reverse order (from last to first). It is essential when the source
// and destination ranges overlap and the destination starts after the source.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

void print_vec(const std::vector<std::string>& v, const char* label) {
    std::cout << label << ": ";
    for (const auto& s : v) {
        std::cout << "'" << s << "' ";
    }
    std::cout << std::endl;
}

int main() {
    // Basic move_backward: move to a separate destination
    std::vector<std::string> source = {"one", "two", "three"};
    std::vector<std::string> dest(3);

    // Note: destination iterator points to the END of the target range
    std::move_backward(source.begin(), source.end(), dest.end());

    print_vec(dest, "Dest after move_backward");
    print_vec(source, "Source after move (moved-from)");

    // Overlapping ranges: shift elements right within the same vector
    std::vector<std::string> data = {"A", "B", "C", "D", "E", "", ""};
    print_vec(data, "Before shift right");

    // Move elements [0..5) to positions [2..7) - overlapping!
    std::move_backward(data.begin(), data.begin() + 5, data.end());
    print_vec(data, "After shift right by 2");

    // Insert at position by shifting existing elements
    std::vector<std::string> items = {"alpha", "beta", "delta", "epsilon", ""};
    // Shift elements [2..4) right by 1 to make room at index 2
    std::move_backward(items.begin() + 2, items.begin() + 4, items.begin() + 5);
    items[2] = "gamma";  // insert into the gap
    print_vec(items, "After insert 'gamma' at [2]");

    // Compare with std::move for non-overlapping ranges
    std::vector<std::string> a = {"X", "Y", "Z"};
    std::vector<std::string> b(3);
    std::move_backward(a.begin(), a.end(), b.end());

    std::cout << "Backward moved: ";
    for (const auto& s : b) std::cout << "'" << s << "' ";
    std::cout << std::endl;

    return 0;
}

// Expected output:
// Dest after move_backward: 'one' 'two' 'three'
// Source after move (moved-from): '' '' ''
// Before shift right: 'A' 'B' 'C' 'D' 'E' '' ''
// After shift right by 2: 'A' 'B' 'A' 'B' 'C' 'D' 'E'
// After insert 'gamma' at [2]: 'alpha' 'beta' 'gamma' 'delta' 'epsilon'
// Backward moved: 'X' 'Y' 'Z'
