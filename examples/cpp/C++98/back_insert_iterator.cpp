// CodeNebula - C++98 Example: back_insert_iterator
// Compile: g++ -std=c++98 -Wall -Wextra -o example back_insert_iterator.cpp

// std::back_insert_iterator (and the helper std::back_inserter)
// creates an output iterator that appends elements to a container
// by calling push_back(). This avoids pre-sizing destination
// containers when used with algorithms.

#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <algorithm>
#include <iterator>

bool is_positive(int x) {
    return x > 0;
}

void print_vec(const std::vector<int>& v, const char* label) {
    std::cout << label << ": ";
    for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main() {
    // Example 1: copy with back_inserter (no pre-sizing needed)
    int arr[] = {10, 20, 30, 40, 50};
    std::vector<int> src(arr, arr + 5);
    std::vector<int> dest;  // empty -- back_inserter grows it

    std::copy(src.begin(), src.end(), std::back_inserter(dest));
    print_vec(dest, "Copied");

    // Example 2: copy_if equivalent using remove_copy_if
    // (C++98 has no copy_if, so we filter with remove_copy_if)
    int arr2[] = {-3, 5, -1, 8, -7, 2};
    std::vector<int> mixed(arr2, arr2 + 6);
    std::vector<int> positives;

    // Copy only positive numbers
    std::remove_copy_if(mixed.begin(), mixed.end(),
                        std::back_inserter(positives),
                        std::not1(std::ptr_fun(is_positive)));
    print_vec(positives, "Positives");

    // Example 3: back_inserter with transform
    std::vector<int> doubled;
    std::transform(src.begin(), src.end(),
                   std::back_inserter(doubled),
                   std::bind2nd(std::multiplies<int>(), 2));
    print_vec(doubled, "Doubled");

    // Example 4: back_inserter with different containers
    std::deque<int> dq;
    std::copy(src.begin(), src.end(), std::back_inserter(dq));
    std::cout << "Deque front: " << dq.front()
              << ", back: " << dq.back() << std::endl;

    return 0;
}

// Expected output:
// Copied: 10 20 30 40 50
// Positives: 5 8 2
// Doubled: 20 40 60 80 100
// Deque front: 10, back: 50
