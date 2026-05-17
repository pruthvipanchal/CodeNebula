// CodeNebula - C++20 Example: Ranges Partition
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_partition.cpp

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

int main() {
    // ranges::partition - reorder so elements satisfying predicate come first
    std::vector<int> nums = {8, 3, 5, 1, 9, 2, 7, 4, 6};
    std::cout << "Original: ";
    for (int n : nums) std::cout << n << ' ';
    std::cout << '\n';

    auto pivot = std::ranges::partition(nums, [](int x) { return x <= 5; });
    std::cout << "Partitioned (<=5 first): ";
    for (int n : nums) std::cout << n << ' ';
    std::cout << '\n';
    std::cout << "Second partition starts at: " << *pivot.begin() << '\n';

    // ranges::stable_partition - preserves relative order within each group
    std::vector<int> data = {8, 3, 5, 1, 9, 2, 7, 4, 6};
    std::cout << "\nBefore stable_partition: ";
    for (int d : data) std::cout << d << ' ';
    std::cout << '\n';

    auto sp = std::ranges::stable_partition(data, [](int x) { return x % 2 == 0; });
    std::cout << "Stable (evens first):   ";
    for (int d : data) std::cout << d << ' ';
    std::cout << '\n';
    std::cout << "Odd section starts at: " << *sp.begin() << '\n';

    // ranges::is_partitioned - check if already partitioned
    std::vector<int> sorted = {2, 4, 6, 1, 3, 5};
    bool partitioned = std::ranges::is_partitioned(sorted,
                           [](int x) { return x % 2 == 0; });
    std::cout << "\n{2,4,6,1,3,5} partitioned by even? "
              << (partitioned ? "yes" : "no") << '\n';

    // Partition with projection
    struct Student {
        std::string name;
        int grade;
    };
    std::vector<Student> students = {
        {"Alice", 85}, {"Bob", 42}, {"Carol", 91},
        {"Dave", 38}, {"Eve", 76}
    };

    std::ranges::stable_partition(students,
        [](int g) { return g >= 60; }, &Student::grade);

    std::cout << "\nStudents (passing first):\n";
    for (const auto& s : students)
        std::cout << "  " << s.name << ": " << s.grade << '\n';

    return 0;
}
