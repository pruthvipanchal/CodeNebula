// CodeNebula - C++20 Example: Ranges Sort
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_sort.cpp

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
#include <string>

int main() {
    // ranges::sort - sort a range in ascending order
    std::vector<int> nums = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    std::cout << "Original: ";
    for (int n : nums) std::cout << n << ' ';
    std::cout << '\n';

    std::ranges::sort(nums);
    std::cout << "Sorted:   ";
    for (int n : nums) std::cout << n << ' ';
    std::cout << '\n';

    // Sort in descending order
    std::ranges::sort(nums, std::ranges::greater{});
    std::cout << "Descending: ";
    for (int n : nums) std::cout << n << ' ';
    std::cout << '\n';

    // ranges::stable_sort - preserves order of equal elements
    struct Employee {
        std::string name;
        int department;
    };
    std::vector<Employee> staff = {
        {"Alice", 2}, {"Bob", 1}, {"Carol", 2},
        {"Dave", 1}, {"Eve", 3}, {"Frank", 2}
    };

    // Stable sort by department preserves name order within each dept
    std::ranges::stable_sort(staff, {}, &Employee::department);
    std::cout << "\nStable sorted by department:\n";
    for (const auto& e : staff)
        std::cout << "  Dept " << e.department << ": " << e.name << '\n';

    // Sort with projection - sort by string length
    std::vector<std::string> words = {"banana", "fig", "cherry", "apple", "date"};
    std::ranges::sort(words, {}, [](const std::string& s) { return s.size(); });
    std::cout << "\nSorted by length: ";
    for (const auto& w : words) std::cout << w << ' ';
    std::cout << '\n';

    // Sort a subrange
    std::vector<int> data = {50, 40, 30, 20, 10};
    std::ranges::sort(data.begin() + 1, data.begin() + 4);
    std::cout << "\nPartial sort [1,4): ";
    for (int d : data) std::cout << d << ' ';
    std::cout << '\n';

    return 0;
}
