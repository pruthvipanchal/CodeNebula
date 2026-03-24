// CodeNebula - C++20 Example: Ranges Rotate
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_rotate.cpp

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

int main() {
    // ranges::rotate - rotate elements left so middle becomes first
    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7};
    std::cout << "Original: ";
    for (int n : nums) std::cout << n << ' ';
    std::cout << '\n';

    // Rotate so element at index 3 becomes the first element
    std::ranges::rotate(nums, nums.begin() + 3);
    std::cout << "Rotated left by 3: ";
    for (int n : nums) std::cout << n << ' ';
    std::cout << '\n';

    // Rotate right by rotating left by (size - n)
    std::vector<int> data = {10, 20, 30, 40, 50};
    int right_shift = 2;
    std::ranges::rotate(data, data.begin() + (data.size() - right_shift));
    std::cout << "\nRight-rotated by 2: ";
    for (int d : data) std::cout << d << ' ';
    std::cout << '\n';

    // ranges::rotate_copy - copy rotated result without modifying source
    std::vector<int> src = {1, 2, 3, 4, 5};
    std::vector<int> dst(src.size());

    std::ranges::rotate_copy(src, src.begin() + 2, dst.begin());
    std::cout << "\nSource:       ";
    for (int s : src) std::cout << s << ' ';
    std::cout << '\n';
    std::cout << "Rotate-copy:  ";
    for (int d : dst) std::cout << d << ' ';
    std::cout << '\n';

    // Rotate a string
    std::string text = "HelloWorld";
    std::cout << "\nOriginal: " << text << '\n';
    std::ranges::rotate(text, text.begin() + 5);
    std::cout << "Rotated:  " << text << '\n';

    // Practical: move an element to the front
    std::vector<std::string> items = {"apple", "banana", "cherry", "date"};
    auto it = std::ranges::find(items, "cherry");
    if (it != items.end()) {
        std::ranges::rotate(items, it);
    }
    std::cout << "\nAfter moving 'cherry' to front: ";
    for (const auto& s : items) std::cout << s << ' ';
    std::cout << '\n';

    return 0;
}
