// CodeNebula - C++98 Example: ostreambuf_iterator
// Compile: g++ -std=c++98 -Wall -Wextra -o example ostreambuf_iterator.cpp

#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
#include <algorithm>

int main() {
    // ostreambuf_iterator writes characters one by one to a streambuf
    // More efficient than ostream_iterator<char> as it bypasses formatting

    // Write to cout via ostreambuf_iterator
    std::ostreambuf_iterator<char> out_it(std::cout);
    std::string msg = "Hello via ostreambuf_iterator!\n";
    std::copy(msg.begin(), msg.end(), out_it);

    // Write to a stringstream
    std::ostringstream oss;
    std::ostreambuf_iterator<char> ss_it(oss);
    std::string data = "Buffered output";
    std::copy(data.begin(), data.end(), ss_it);
    std::cout << "Stringstream contains: " << oss.str() << std::endl;

    // Transform characters: convert to uppercase while writing
    std::string lower = "make me uppercase";
    std::ostringstream oss2;
    for (std::string::iterator it = lower.begin(); it != lower.end(); ++it) {
        std::ostreambuf_iterator<char> writer(oss2);
        char c = static_cast<char>(std::toupper(static_cast<unsigned char>(*it)));
        *writer = c;
    }
    std::cout << "Uppercased: " << oss2.str() << std::endl;

    return 0;
}

// Expected output:
// Hello via ostreambuf_iterator!
// Stringstream contains: Buffered output
// Uppercased: MAKE ME UPPERCASE
