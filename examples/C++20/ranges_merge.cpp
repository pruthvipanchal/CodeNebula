// CodeNebula - C++20 Example: Ranges Merge
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_merge.cpp

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

int main() {
    // ranges::merge - merge two sorted ranges into one sorted output
    std::vector<int> a = {1, 3, 5, 7, 9};
    std::vector<int> b = {2, 4, 6, 8, 10};
    std::vector<int> merged(a.size() + b.size());

    std::ranges::merge(a, b, merged.begin());
    std::cout << "A: ";
    for (int x : a) std::cout << x << ' ';
    std::cout << "\nB: ";
    for (int x : b) std::cout << x << ' ';
    std::cout << "\nMerged: ";
    for (int x : merged) std::cout << x << ' ';
    std::cout << '\n';

    // Merge with custom comparator (descending sorted inputs)
    std::vector<int> desc1 = {9, 7, 5, 3};
    std::vector<int> desc2 = {8, 6, 4, 2};
    std::vector<int> desc_merged(desc1.size() + desc2.size());

    std::ranges::merge(desc1, desc2, desc_merged.begin(),
                       std::ranges::greater{});
    std::cout << "\nDescending merge: ";
    for (int x : desc_merged) std::cout << x << ' ';
    std::cout << '\n';

    // Merge with projection
    struct Item {
        std::string name;
        int priority;
    };
    std::vector<Item> list1 = {{"Task A", 1}, {"Task C", 3}};
    std::vector<Item> list2 = {{"Task B", 2}, {"Task D", 4}};
    std::vector<Item> all(4);

    std::ranges::merge(list1, list2, all.begin(), {}, &Item::priority, &Item::priority);
    std::cout << "\nMerged by priority:\n";
    for (const auto& item : all)
        std::cout << "  " << item.name << " (pri " << item.priority << ")\n";

    // ranges::inplace_merge - merge two sorted halves within one container
    std::vector<int> data = {1, 4, 7, 10, 2, 5, 8, 11};
    std::cout << "\nBefore inplace_merge: ";
    for (int d : data) std::cout << d << ' ';
    std::cout << '\n';

    std::ranges::inplace_merge(data, data.begin() + 4);
    std::cout << "After inplace_merge:  ";
    for (int d : data) std::cout << d << ' ';
    std::cout << '\n';

    return 0;
}
