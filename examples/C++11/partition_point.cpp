// CodeNebula - C++11 Example: std::partition_point
// Compile: g++ -std=c++11 -Wall -Wextra -o partition_point partition_point.cpp

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::cout << "=== std::partition_point ===" << std::endl;

    // Partition then find the boundary
    std::vector<int> numbers = {1, 9, 2, 8, 3, 7, 4, 6, 5};

    auto isEven = [](int n) { return n % 2 == 0; };
    std::partition(numbers.begin(), numbers.end(), isEven);

    std::cout << "After partition (evens first): ";
    for (int n : numbers) std::cout << n << " ";
    std::cout << std::endl;

    // Find where evens end and odds begin
    auto boundary = std::partition_point(numbers.begin(), numbers.end(), isEven);

    std::cout << "Evens: ";
    for (auto it = numbers.begin(); it != boundary; ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    std::cout << "Odds:  ";
    for (auto it = boundary; it != numbers.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    // With a sorted range (already partitioned by < threshold)
    std::vector<int> sorted = {10, 20, 30, 40, 50, 60, 70, 80, 90};

    auto threshold = std::partition_point(sorted.begin(), sorted.end(),
                                          [](int n) { return n <= 50; });

    std::cout << "\nSorted: ";
    for (int n : sorted) std::cout << n << " ";
    std::cout << std::endl;

    std::cout << "Elements <= 50: ";
    for (auto it = sorted.begin(); it != threshold; ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    std::cout << "Elements > 50:  ";
    for (auto it = threshold; it != sorted.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    return 0;
}

// Expected Output:
// === std::partition_point ===
// After partition (evens first): 6 4 2 8 3 7 9 1 5
// Evens: 6 4 2 8
// Odds:  3 7 9 1 5
//
// Sorted: 10 20 30 40 50 60 70 80 90
// Elements <= 50: 10 20 30 40 50
// Elements > 50:  60 70 80 90
