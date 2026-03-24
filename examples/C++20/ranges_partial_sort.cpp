// CodeNebula - C++20 Example: Ranges Partial Sort
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_partial_sort.cpp

#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>

int main() {
    // ranges::partial_sort - sort only the first N elements
    std::vector<int> nums = {9, 3, 7, 1, 5, 8, 2, 6, 4};
    std::cout << "Original: ";
    for (int n : nums) std::cout << n << ' ';
    std::cout << '\n';

    // Place the 4 smallest elements sorted at the front
    std::ranges::partial_sort(nums, nums.begin() + 4);
    std::cout << "Partial sort (top 4): ";
    for (int n : nums) std::cout << n << ' ';
    std::cout << '\n';

    // partial_sort descending for top-N largest
    std::vector<int> scores = {72, 95, 88, 61, 100, 43, 79, 55};
    std::ranges::partial_sort(scores, scores.begin() + 3,
                              std::ranges::greater{});
    std::cout << "\nTop 3 scores: ";
    for (int i = 0; i < 3; ++i) std::cout << scores[i] << ' ';
    std::cout << '\n';

    // ranges::partial_sort_copy - copy the sorted first N into another range
    std::vector<int> source = {50, 20, 80, 10, 60, 30, 90, 40, 70};
    std::vector<int> top5(5);

    std::ranges::partial_sort_copy(source, top5);
    std::cout << "\nSource:           ";
    for (int s : source) std::cout << s << ' ';
    std::cout << '\n';
    std::cout << "Smallest 5 sorted: ";
    for (int t : top5) std::cout << t << ' ';
    std::cout << '\n';

    // ranges::nth_element - place the Nth element in its sorted position
    std::vector<int> data = {15, 3, 22, 7, 19, 11, 1, 8};
    std::cout << "\nBefore nth_element: ";
    for (int d : data) std::cout << d << ' ';
    std::cout << '\n';

    // Find the median (element at index 3 in sorted order)
    std::ranges::nth_element(data, data.begin() + 3);
    std::cout << "After nth_element(3): ";
    for (int d : data) std::cout << d << ' ';
    std::cout << '\n';
    std::cout << "Median position value: " << data[3] << '\n';

    return 0;
}
