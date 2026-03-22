// CodeNebula - C++98 Example: istream_iterator
// Compile: g++ -std=c++98 -Wall -Wextra -o example istream_iterator.cpp

#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>

int main() {
    // Use a stringstream to simulate input
    std::istringstream input("10 20 30 40 50");

    // Read integers from stream using istream_iterator
    std::istream_iterator<int> begin(input);
    std::istream_iterator<int> end; // default = end-of-stream

    std::vector<int> nums(begin, end);

    std::cout << "Read from stream: ";
    for (std::vector<int>::iterator it = nums.begin(); it != nums.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Copy from another stream to a vector using back_inserter
    std::istringstream input2("100 200 300");
    std::vector<int> more;
    std::copy(std::istream_iterator<int>(input2),
              std::istream_iterator<int>(),
              std::back_inserter(more));

    std::cout << "Second read: ";
    for (std::vector<int>::iterator it = more.begin(); it != more.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}

// Expected output:
// Read from stream: 10 20 30 40 50
// Second read: 100 200 300
