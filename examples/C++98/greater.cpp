// CodeNebula - C++98 Example: std::greater
// Compile: g++ -std=c++98 -Wall -Wextra -o example greater.cpp

#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>

int main() {
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6};
    int n = 8;

    // Sort in descending order using std::greater
    std::sort(arr, arr + n, std::greater<int>());

    std::cout << "Sorted descending: ";
    for (int i = 0; i < n; ++i) std::cout << arr[i] << " ";
    std::cout << std::endl;

    // Count elements greater than 4 using bind2nd
    int count = std::count_if(arr, arr + n,
                              std::bind2nd(std::greater<int>(), 4));
    std::cout << "Elements > 4: " << count << std::endl;

    // Use with priority_queue-like behavior via make_heap
    std::vector<int> v;
    v.push_back(30); v.push_back(10); v.push_back(50); v.push_back(20);

    // greater creates a min-heap
    std::make_heap(v.begin(), v.end(), std::greater<int>());
    std::cout << "Min-heap top: " << v.front() << std::endl;

    return 0;
}

// Expected output:
// Sorted descending: 9 6 5 4 3 2 1 1
// Elements > 4: 3
// Min-heap top: 10
