// CodeNebula - C++20 Example: std::identity
// Compile: g++ -std=c++20 -Wall -Wextra -o example identity.cpp

#include <functional>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

int main() {
    // std::identity returns its argument unchanged
    std::identity id;
    std::cout << "identity(42):      " << id(42) << '\n';
    std::cout << "identity(3.14):    " << id(3.14) << '\n';
    std::cout << "identity(\"hello\"): " << id(std::string("hello")) << '\n';

    // Primary use: default projection in ranges algorithms
    std::vector<int> nums = {5, 3, 8, 1, 9, 2, 7};
    std::ranges::sort(nums, std::less<>{}, std::identity{});
    std::cout << "\nSorted: ";
    for (int n : nums) std::cout << n << ' ';
    std::cout << '\n';

    // Useful in generic/template code as a default projection
    auto find_max = [](auto& range, auto proj = std::identity{}) {
        return *std::ranges::max_element(range, {}, proj);
    };

    std::vector<int> values = {10, 40, 20, 50, 30};
    std::cout << "\nMax value: " << find_max(values) << '\n';

    // Same function with a custom projection
    struct Item {
        std::string name;
        double price;
    };
    std::vector<Item> items = {
        {"Widget", 9.99}, {"Gadget", 24.99},
        {"Gizmo", 14.99}, {"Doohickey", 4.99}
    };

    auto expensive = find_max(items, &Item::price);
    std::cout << "Most expensive: " << expensive.name
              << " ($" << expensive.price << ")\n";

    // identity in generic wrappers that optionally transform values
    auto apply_and_print = [](const auto& range, auto transform = std::identity{}) {
        for (const auto& elem : range)
            std::cout << transform(elem) << ' ';
        std::cout << '\n';
    };

    std::vector<int> data = {1, 2, 3, 4, 5};
    std::cout << "\nWith identity:  ";
    apply_and_print(data);
    std::cout << "With transform: ";
    apply_and_print(data, [](int x) { return x * x; });

    // Use with std::transform as a copy operation
    std::vector<int> src = {10, 20, 30};
    std::vector<int> dst(3);
    std::ranges::transform(src, dst.begin(), std::identity{});
    std::cout << "\nCopied via identity: ";
    for (int d : dst) std::cout << d << ' ';
    std::cout << '\n';

    return 0;
}
