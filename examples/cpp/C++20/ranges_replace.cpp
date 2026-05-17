// CodeNebula - C++20 Example: Ranges Replace
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_replace.cpp

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

int main() {
    // ranges::replace - replace all occurrences of a value
    std::vector<int> nums = {1, 2, 3, 2, 5, 2, 7};
    std::cout << "Original: ";
    for (int n : nums) std::cout << n << ' ';
    std::cout << '\n';

    std::ranges::replace(nums, 2, 99);
    std::cout << "After replace(2 -> 99): ";
    for (int n : nums) std::cout << n << ' ';
    std::cout << '\n';

    // ranges::replace_if - replace elements matching a predicate
    std::vector<int> vals = {10, 25, 30, 45, 50, 65, 70};
    std::cout << "\nBefore replace_if: ";
    for (int v : vals) std::cout << v << ' ';
    std::cout << '\n';

    std::ranges::replace_if(vals, [](int x) { return x > 40; }, 0);
    std::cout << "After replace_if(>40 -> 0): ";
    for (int v : vals) std::cout << v << ' ';
    std::cout << '\n';

    // Using projections with replace
    struct Product {
        std::string name;
        int category;
    };
    std::vector<Product> products = {
        {"Widget", 1}, {"Gadget", 2}, {"Gizmo", 1}, {"Doohickey", 3}
    };

    std::ranges::replace(products, 1, 99, &Product::category);
    std::cout << "\nProducts after replacing category 1 with 99:\n";
    for (const auto& p : products)
        std::cout << "  " << p.name << " (cat " << p.category << ")\n";

    // replace_if with projection
    std::vector<Product> items = {
        {"Alpha", 5}, {"Beta", 12}, {"Gamma", 3}, {"Delta", 20}
    };
    std::ranges::replace_if(items, [](int c) { return c >= 10; },
                            0, &Product::category);
    std::cout << "\nItems after replace_if(category>=10 -> 0):\n";
    for (const auto& item : items)
        std::cout << "  " << item.name << " (cat " << item.category << ")\n";

    return 0;
}
