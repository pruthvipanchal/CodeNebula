// CodeNebula - C++20 Example: Ranges Min/Max Element
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_min_max_element.cpp

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

int main() {
    std::vector<int> nums = {42, 17, 93, 5, 68, 31};
    std::cout << "Data: ";
    for (int n : nums) std::cout << n << ' ';
    std::cout << '\n';

    // ranges::min_element - iterator to the smallest element
    auto min_it = std::ranges::min_element(nums);
    std::cout << "Min element: " << *min_it
              << " at index " << (min_it - nums.begin()) << '\n';

    // ranges::max_element - iterator to the largest element
    auto max_it = std::ranges::max_element(nums);
    std::cout << "Max element: " << *max_it
              << " at index " << (max_it - nums.begin()) << '\n';

    // ranges::minmax_element - both iterators in one pass
    auto [lo, hi] = std::ranges::minmax_element(nums);
    std::cout << "Minmax: [" << *lo << " at " << (lo - nums.begin())
              << ", " << *hi << " at " << (hi - nums.begin()) << "]\n";

    // With projection - find student with best and worst grade
    struct Student {
        std::string name;
        double gpa;
    };
    std::vector<Student> students = {
        {"Alice", 3.8}, {"Bob", 2.9}, {"Carol", 3.95},
        {"Dave", 3.1}, {"Eve", 3.6}
    };

    auto best = std::ranges::max_element(students, {}, &Student::gpa);
    auto worst = std::ranges::min_element(students, {}, &Student::gpa);
    std::cout << "\nBest GPA:  " << best->name << " (" << best->gpa << ")\n";
    std::cout << "Worst GPA: " << worst->name << " (" << worst->gpa << ")\n";

    auto [low_s, high_s] = std::ranges::minmax_element(students, {},
                                                        &Student::gpa);
    std::cout << "Minmax GPA: " << low_s->name << " to " << high_s->name << '\n';

    // Find longest string
    std::vector<std::string> words = {"code", "nebula", "programming", "cpp"};
    auto longest = std::ranges::max_element(words, {}, &std::string::size);
    std::cout << "\nLongest word: \"" << *longest
              << "\" (" << longest->size() << " chars)\n";

    return 0;
}
