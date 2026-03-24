// CodeNebula - C++20 Example: std::span Container
// Compile: g++ -std=c++20 -Wall -Wextra -o example span.cpp

// std::span is a lightweight, non-owning view over a contiguous sequence
// of objects. It can be created from arrays, vectors, or any contiguous
// range. It avoids copying and supports both static and dynamic extents.

#include <array>
#include <iostream>
#include <numeric>
#include <span>
#include <vector>

// Accept a span instead of a specific container type
void print_span(std::span<const int> data) {
    std::cout << "[";
    for (std::size_t i = 0; i < data.size(); ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << data[i];
    }
    std::cout << "] (size=" << data.size() << ")\n";
}

// Compute sum using span
int sum(std::span<const int> data) {
    int total = 0;
    for (int v : data) total += v;
    return total;
}

// Modify elements through a mutable span
void double_values(std::span<int> data) {
    for (int& v : data) v *= 2;
}

// Static extent span: compile-time known size
void process_triple(std::span<const int, 3> triple) {
    std::cout << "Triple: " << triple[0] << ", "
              << triple[1] << ", " << triple[2] << "\n";
}

int main() {
    // Span from C-style array
    int arr[] = {1, 2, 3, 4, 5};
    std::cout << "From C array: ";
    print_span(arr);

    // Span from std::vector
    std::vector<int> vec = {10, 20, 30, 40, 50};
    std::cout << "From vector:  ";
    print_span(vec);

    // Span from std::array
    std::array<int, 4> stdarr = {100, 200, 300, 400};
    std::cout << "From array:   ";
    print_span(stdarr);

    // Sum via span
    std::cout << "\nSum of vec: " << sum(vec) << "\n";

    // Subspans
    std::span<int> full(vec);
    std::cout << "First 3:  ";
    print_span(full.first(3));
    std::cout << "Last 2:   ";
    print_span(full.last(2));
    std::cout << "Middle:   ";
    print_span(full.subspan(1, 3));

    // Mutable span modifies original data
    double_values(vec);
    std::cout << "\nAfter doubling: ";
    print_span(vec);

    // Static extent
    std::array<int, 3> tri = {7, 8, 9};
    process_triple(tri);

    // Span properties
    std::span<int> s(vec);
    std::cout << "\nSpan properties:\n";
    std::cout << "  size: " << s.size() << "\n";
    std::cout << "  size_bytes: " << s.size_bytes() << "\n";
    std::cout << "  empty: " << s.empty() << "\n";
    std::cout << "  front: " << s.front() << ", back: " << s.back() << "\n";

    return 0;
}

// Expected output:
// From C array: [1, 2, 3, 4, 5] (size=5)
// From vector:  [10, 20, 30, 40, 50] (size=5)
// From array:   [100, 200, 300, 400] (size=4)
//
// Sum of vec: 150
// First 3:  [10, 20, 30] (size=3)
// Last 2:   [40, 50] (size=2)
// Middle:   [20, 30, 40] (size=3)
//
// After doubling: [20, 40, 60, 80, 100] (size=5)
// Triple: 7, 8, 9
//
// Span properties:
//   size: 5
//   size_bytes: 20
//   empty: 0
//   front: 20, back: 100
