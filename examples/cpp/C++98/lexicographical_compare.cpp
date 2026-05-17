// CodeNebula - C++98 Example: lexicographical_compare
// Compile: g++ -std=c++98 -Wall -Wextra -o example lexicographical_compare.cpp

// std::lexicographical_compare compares two ranges element by element
// in dictionary (lexicographic) order. Returns true if the first
// range is "less than" the second.

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cctype>

bool case_insensitive(char a, char b) {
    return std::tolower(a) < std::tolower(b);
}

int main() {
    // Compare integer sequences
    int a[] = {1, 2, 3, 4};
    int b[] = {1, 2, 4, 0};
    int c[] = {1, 2, 3, 4};
    int d[] = {1, 2, 3};

    bool r1 = std::lexicographical_compare(a, a + 4, b, b + 4);
    std::cout << "[1,2,3,4] < [1,2,4,0]? " << (r1 ? "yes" : "no")
              << std::endl;

    bool r2 = std::lexicographical_compare(a, a + 4, c, c + 4);
    std::cout << "[1,2,3,4] < [1,2,3,4]? " << (r2 ? "yes" : "no")
              << std::endl;

    // Shorter prefix is "less than" longer sequence
    bool r3 = std::lexicographical_compare(d, d + 3, a, a + 4);
    std::cout << "[1,2,3] < [1,2,3,4]? " << (r3 ? "yes" : "no")
              << std::endl;

    // Compare strings (works on any sequence of chars)
    std::string s1 = "apple";
    std::string s2 = "banana";
    bool r4 = std::lexicographical_compare(s1.begin(), s1.end(),
                                           s2.begin(), s2.end());
    std::cout << "\"apple\" < \"banana\"? " << (r4 ? "yes" : "no")
              << std::endl;

    // Case-insensitive comparison
    std::string s3 = "Hello";
    std::string s4 = "hello";
    bool r5 = std::lexicographical_compare(s3.begin(), s3.end(),
                                           s4.begin(), s4.end(),
                                           case_insensitive);
    std::cout << "\"Hello\" < \"hello\" (case-insensitive)? "
              << (r5 ? "yes" : "no") << std::endl;

    return 0;
}

// Expected output:
// [1,2,3,4] < [1,2,4,0]? yes
// [1,2,3,4] < [1,2,3,4]? no
// [1,2,3] < [1,2,3,4]? yes
// "apple" < "banana"? yes
// "Hello" < "hello" (case-insensitive)? no
