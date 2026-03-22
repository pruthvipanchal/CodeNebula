// CodeNebula - C++98 Example: nth_element
// Compile: g++ -std=c++98 -Wall -Wextra -o example nth_element.cpp

// std::nth_element rearranges elements so that the element at the
// Nth position is the element that would be there if the range
// were fully sorted. All elements before it are <= and all after
// are >=, but neither partition is sorted.

#include <iostream>
#include <vector>
#include <algorithm>

void print_vec(const std::vector<int>& v, const char* label) {
    std::cout << label << ": ";
    for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main() {
    int arr[] = {9, 1, 8, 2, 7, 3, 6, 4, 5};
    const int n = sizeof(arr) / sizeof(arr[0]);
    std::vector<int> v(arr, arr + n);

    print_vec(v, "Original");

    // Place the median (index 4) in its correct sorted position
    std::nth_element(v.begin(), v.begin() + 4, v.end());
    std::cout << "Element at index 4 (median): " << v[4] << std::endl;

    // Find the 2nd smallest element (index 1)
    std::vector<int> v2(arr, arr + n);
    std::nth_element(v2.begin(), v2.begin() + 1, v2.end());
    std::cout << "2nd smallest (index 1): " << v2[1] << std::endl;

    // Find the 2nd largest using greater<int>
    std::vector<int> v3(arr, arr + n);
    std::nth_element(v3.begin(), v3.begin() + 1, v3.end(),
                     std::greater<int>());
    std::cout << "2nd largest: " << v3[1] << std::endl;

    return 0;
}

// Expected output:
// Original: 9 1 8 2 7 3 6 4 5
// Element at index 4 (median): 5
// 2nd smallest (index 1): 2
// 2nd largest: 8
