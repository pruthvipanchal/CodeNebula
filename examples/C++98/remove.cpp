// CodeNebula - C++98 Example: remove
// Compile: g++ -std=c++98 -Wall -Wextra -o example remove.cpp

// std::remove "removes" elements equal to a value by shifting remaining elements
// forward. It does NOT resize the container -- it returns an iterator to the
// new logical end. Use the erase-remove idiom to actually shrink the container.

#include <iostream>
#include <vector>
#include <algorithm>

void print_vec(const char* label, const std::vector<int>& v) {
    std::cout << label;
    for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "(size=" << v.size() << ")" << std::endl;
}

int main() {
    int arr[] = {1, 3, 2, 3, 4, 3, 5};
    std::vector<int> v(arr, arr + 7);
    print_vec("Original:       ", v);

    // std::remove alone -- shifts elements but does not erase
    std::vector<int> v2(v);
    std::vector<int>::iterator new_end = std::remove(v2.begin(), v2.end(), 3);
    std::cout << "After remove 3: ";
    for (std::vector<int>::iterator it = v2.begin(); it != new_end; ++it) {
        std::cout << *it << " ";
    }
    std::cout << "(logical size=" << (new_end - v2.begin()) << ")" << std::endl;

    // Erase-remove idiom: actually shrink the vector
    v.erase(std::remove(v.begin(), v.end(), 3), v.end());
    print_vec("Erase-remove 3: ", v);

    // Remove a value not present (no change)
    std::vector<int> v3(v);
    v3.erase(std::remove(v3.begin(), v3.end(), 99), v3.end());
    print_vec("Remove 99:      ", v3);

    return 0;
}

// Expected output:
// Original:       1 3 2 3 4 3 5 (size=7)
// After remove 3: 1 2 4 5 (logical size=4)
// Erase-remove 3: 1 2 4 5 (size=4)
// Remove 99:      1 2 4 5 (size=4)
