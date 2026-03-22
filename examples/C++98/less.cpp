// CodeNebula - C++98 Example: std::less
// Compile: g++ -std=c++98 -Wall -Wextra -o example less.cpp

#include <iostream>
#include <functional>
#include <algorithm>
#include <set>

int main() {
    int arr[] = {5, 2, 8, 1, 9, 3};
    int n = 6;

    // std::less is the default comparator for sort (ascending)
    std::sort(arr, arr + n, std::less<int>());

    std::cout << "Sorted ascending: ";
    for (int i = 0; i < n; ++i) std::cout << arr[i] << " ";
    std::cout << std::endl;

    // Count elements less than 5
    int count = std::count_if(arr, arr + n,
                              std::bind2nd(std::less<int>(), 5));
    std::cout << "Elements < 5: " << count << std::endl;

    // std::set uses std::less<T> by default
    std::set<int, std::less<int> > s;
    s.insert(40); s.insert(10); s.insert(30); s.insert(20);

    std::cout << "Set (ordered by less): ";
    for (std::set<int>::iterator it = s.begin(); it != s.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}

// Expected output:
// Sorted ascending: 1 2 3 5 8 9
// Elements < 5: 3
// Set (ordered by less): 10 20 30 40
