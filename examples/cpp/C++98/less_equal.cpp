// CodeNebula - C++98 Example: std::less_equal
// Compile: g++ -std=c++98 -Wall -Wextra -o example less_equal.cpp

#include <iostream>
#include <functional>
#include <algorithm>

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int n = 8;

    // Count elements <= 4
    int count = std::count_if(arr, arr + n,
                              std::bind2nd(std::less_equal<int>(), 4));
    std::cout << "Elements <= 4: " << count << std::endl;

    // Find first element <= 3
    int* pos = std::find_if(arr, arr + n,
                            std::bind2nd(std::less_equal<int>(), 3));
    if (pos != arr + n) {
        std::cout << "First <= 3: " << *pos << std::endl;
    }

    // Partition: elements <= 5 moved to front
    int data[] = {8, 3, 7, 1, 5, 9, 2, 6};
    std::partition(data, data + 8,
                   std::bind2nd(std::less_equal<int>(), 5));

    std::cout << "After partition (<= 5 first): ";
    for (int i = 0; i < 8; ++i) std::cout << data[i] << " ";
    std::cout << std::endl;

    return 0;
}

// Expected output:
// Elements <= 4: 4
// First <= 3: 1
// After partition (<= 5 first): 2 3 1 5 7 9 8 6
