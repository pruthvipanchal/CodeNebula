// CodeNebula - C++20 Example: Ranges All Of / Any Of / None Of
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_all_any_none.cpp

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

int main() {
    std::vector<int> nums = {2, 4, 6, 8, 10};
    std::cout << "Data: ";
    for (int n : nums) std::cout << n << ' ';
    std::cout << '\n';

    // ranges::all_of - true if all elements satisfy the predicate
    bool all_even = std::ranges::all_of(nums, [](int x) { return x % 2 == 0; });
    std::cout << "All even? " << (all_even ? "yes" : "no") << '\n';

    bool all_pos = std::ranges::all_of(nums, [](int x) { return x > 0; });
    std::cout << "All positive? " << (all_pos ? "yes" : "no") << '\n';

    // ranges::any_of - true if at least one element satisfies the predicate
    bool any_gt5 = std::ranges::any_of(nums, [](int x) { return x > 5; });
    std::cout << "\nAny > 5? " << (any_gt5 ? "yes" : "no") << '\n';

    bool any_neg = std::ranges::any_of(nums, [](int x) { return x < 0; });
    std::cout << "Any negative? " << (any_neg ? "yes" : "no") << '\n';

    // ranges::none_of - true if no element satisfies the predicate
    bool none_neg = std::ranges::none_of(nums, [](int x) { return x < 0; });
    std::cout << "\nNone negative? " << (none_neg ? "yes" : "no") << '\n';

    bool none_even = std::ranges::none_of(nums, [](int x) { return x % 2 == 0; });
    std::cout << "None even? " << (none_even ? "yes" : "no") << '\n';

    // With projection
    struct Student {
        std::string name;
        int score;
    };
    std::vector<Student> students = {
        {"Alice", 85}, {"Bob", 72}, {"Carol", 91}, {"Dave", 68}
    };

    bool all_pass = std::ranges::all_of(students,
        [](int s) { return s >= 60; }, &Student::score);
    std::cout << "\nAll students passed (>=60)? " << (all_pass ? "yes" : "no") << '\n';

    bool any_honors = std::ranges::any_of(students,
        [](int s) { return s >= 90; }, &Student::score);
    std::cout << "Any honors (>=90)? " << (any_honors ? "yes" : "no") << '\n';

    bool none_failed = std::ranges::none_of(students,
        [](int s) { return s < 50; }, &Student::score);
    std::cout << "None failed (<50)? " << (none_failed ? "yes" : "no") << '\n';

    // Empty range behavior
    std::vector<int> empty;
    std::cout << "\nEmpty range: all_of=" << std::ranges::all_of(empty, [](int) { return false; })
              << " any_of=" << std::ranges::any_of(empty, [](int) { return true; })
              << " none_of=" << std::ranges::none_of(empty, [](int) { return false; }) << '\n';

    return 0;
}
