// CodeNebula - C++98 Example: istreambuf_iterator
// Compile: g++ -std=c++98 -Wall -Wextra -o example istreambuf_iterator.cpp

#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
#include <algorithm>

int main() {
    // istreambuf_iterator reads characters one by one from a streambuf
    // Unlike istream_iterator, it does NOT skip whitespace
    std::istringstream iss("Hello World!\nLine two.");

    // Read all characters including spaces and newlines
    std::istreambuf_iterator<char> begin(iss);
    std::istreambuf_iterator<char> end;

    std::string content(begin, end);
    std::cout << "Read (preserving whitespace): [" << content << "]" << std::endl;

    // Count specific characters
    std::istringstream iss2("aabbbcccc");
    int count = std::count(std::istreambuf_iterator<char>(iss2),
                           std::istreambuf_iterator<char>(),
                           'c');
    std::cout << "Number of 'c' chars: " << count << std::endl;

    // Compare two streams character by character
    std::istringstream s1("abc");
    std::istringstream s2("abc");
    bool equal = std::equal(std::istreambuf_iterator<char>(s1),
                            std::istreambuf_iterator<char>(),
                            std::istreambuf_iterator<char>(s2));
    std::cout << "Streams equal: " << (equal ? "yes" : "no") << std::endl;

    return 0;
}

// Expected output:
// Read (preserving whitespace): [Hello World!
// Line two.]
// Number of 'c' chars: 4
// Streams equal: yes
