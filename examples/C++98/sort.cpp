// CodeNebula - C++98 Example: sort
// Compile: g++ -std=c++98 -Wall -Wextra -o example sort.cpp

// std::sort sorts elements in-place using introsort (typically).
// By default it sorts in ascending order using operator<.
// A custom comparator can be provided for different orderings.

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

void print_vec(const std::vector<int>& v, const char* label) {
    std::cout << label << ": ";
    for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

bool descending(int a, int b) {
    return a > b;
}

bool by_length(const std::string& a, const std::string& b) {
    return a.size() < b.size();
}

int main() {
    // Example 1: default ascending sort
    int arr[] = {5, 2, 8, 1, 9, 3, 7};
    std::vector<int> v(arr, arr + 7);
    print_vec(v, "Before sort");

    std::sort(v.begin(), v.end());
    print_vec(v, "Ascending");

    // Example 2: descending sort with comparator
    std::sort(v.begin(), v.end(), descending);
    print_vec(v, "Descending");

    // Example 3: sort strings by length
    std::vector<std::string> words;
    words.push_back("banana");
    words.push_back("fig");
    words.push_back("apple");
    words.push_back("kiwi");

    std::sort(words.begin(), words.end(), by_length);
    std::cout << "Sorted by length: ";
    for (std::vector<std::string>::const_iterator it = words.begin();
         it != words.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}

// Expected output:
// Before sort: 5 2 8 1 9 3 7
// Ascending: 1 2 3 5 7 8 9
// Descending: 9 8 7 5 3 2 1
// Sorted by length: fig kiwi apple banana
