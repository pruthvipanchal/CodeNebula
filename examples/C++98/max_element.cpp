// CodeNebula - C++98 Example: max_element
// Compile: g++ -std=c++98 -Wall -Wextra -o example max_element.cpp

// std::max_element returns an iterator to the largest element in
// a range. With a custom comparator, "largest" can be redefined.

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

bool by_last_char(const std::string& a, const std::string& b) {
    return a[a.size() - 1] < b[b.size() - 1];
}

int main() {
    // Find maximum in an integer vector
    int arr[] = {42, 17, 93, 5, 68, 31};
    const int n = sizeof(arr) / sizeof(arr[0]);
    std::vector<int> v(arr, arr + n);

    std::cout << "Elements: ";
    for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::vector<int>::iterator it = std::max_element(v.begin(), v.end());
    std::cout << "Maximum: " << *it << std::endl;
    std::cout << "At index: " << (it - v.begin()) << std::endl;

    // Find word with highest last character
    std::vector<std::string> words;
    words.push_back("alpha");
    words.push_back("bravo");
    words.push_back("zulu");
    words.push_back("delta");

    std::vector<std::string>::iterator sit =
        std::max_element(words.begin(), words.end(), by_last_char);
    std::cout << "Max by last char: " << *sit << std::endl;

    // Lexicographically largest string (default)
    sit = std::max_element(words.begin(), words.end());
    std::cout << "Lexicographic max: " << *sit << std::endl;

    return 0;
}

// Expected output:
// Elements: 42 17 93 5 68 31
// Maximum: 93
// At index: 2
// Max by last char: zulu
// Lexicographic max: zulu
