// CodeNebula - C++98 Example: min_element
// Compile: g++ -std=c++98 -Wall -Wextra -o example min_element.cpp

// std::min_element returns an iterator to the smallest element in
// a range. With a custom comparator, "smallest" can be redefined.

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

bool shorter(const std::string& a, const std::string& b) {
    return a.size() < b.size();
}

int main() {
    // Find minimum in an integer vector
    int arr[] = {42, 17, 93, 5, 68, 31};
    const int n = sizeof(arr) / sizeof(arr[0]);
    std::vector<int> v(arr, arr + n);

    std::cout << "Elements: ";
    for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::vector<int>::iterator it = std::min_element(v.begin(), v.end());
    std::cout << "Minimum: " << *it << std::endl;
    std::cout << "At index: " << (it - v.begin()) << std::endl;

    // Find shortest string
    std::vector<std::string> words;
    words.push_back("elephant");
    words.push_back("cat");
    words.push_back("hippopotamus");
    words.push_back("dog");
    words.push_back("ox");

    std::vector<std::string>::iterator sit =
        std::min_element(words.begin(), words.end(), shorter);
    std::cout << "Shortest word: " << *sit << std::endl;

    // min_element on a raw array
    int raw[] = {100, 200, 50, 300};
    int* p = std::min_element(raw, raw + 4);
    std::cout << "Min in array: " << *p << std::endl;

    return 0;
}

// Expected output:
// Elements: 42 17 93 5 68 31
// Minimum: 5
// At index: 3
// Shortest word: ox
// Min in array: 50
