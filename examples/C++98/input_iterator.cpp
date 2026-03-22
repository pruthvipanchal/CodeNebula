// CodeNebula - C++98 Example: input_iterator
// Compile: g++ -std=c++98 -Wall -Wextra -o example input_iterator.cpp

// Input iterators support single-pass reading. std::istream_iterator is the
// classic example - it reads values from an input stream one at a time.

#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm> // for std::copy
#include <numeric>   // for std::accumulate

int main() {
    // --- Basic istream_iterator from stringstream ---
    std::cout << "=== Basic istream_iterator ===" << std::endl;
    std::istringstream iss("10 20 30 40 50");

    // Create input iterators
    std::istream_iterator<int> it(iss);   // points to first value
    std::istream_iterator<int> end;       // default = end-of-stream sentinel

    std::cout << "Reading integers from stream:" << std::endl;
    while (it != end) {
        std::cout << "  Read: " << *it << std::endl;
        ++it;
    }

    // --- Reading into a vector ---
    std::cout << "\n=== Reading into a vector ===" << std::endl;
    std::istringstream iss2("5 15 25 35 45 55");
    std::vector<int> vec;

    // Use istream_iterator with std::copy and back_inserter
    std::copy(std::istream_iterator<int>(iss2),
              std::istream_iterator<int>(),
              std::back_inserter(vec));

    std::cout << "Vector contents: ";
    for (std::vector<int>::iterator vit = vec.begin(); vit != vec.end(); ++vit) {
        std::cout << *vit << " ";
    }
    std::cout << std::endl;
    std::cout << "Size: " << vec.size() << std::endl;

    // --- Constructing vector directly from range ---
    std::cout << "\n=== Construct vector from iterator range ===" << std::endl;
    std::istringstream iss3("100 200 300");
    std::vector<int> vec2(std::istream_iterator<int>(iss3),
                          (std::istream_iterator<int>()));
    // Note: extra parentheses around second arg to avoid "most vexing parse"

    std::cout << "Direct-constructed vector: ";
    for (std::vector<int>::iterator vit = vec2.begin(); vit != vec2.end(); ++vit) {
        std::cout << *vit << " ";
    }
    std::cout << std::endl;

    // --- Using with std::accumulate ---
    std::cout << "\n=== accumulate with istream_iterator ===" << std::endl;
    std::istringstream iss4("1 2 3 4 5");
    int sum = std::accumulate(std::istream_iterator<int>(iss4),
                              std::istream_iterator<int>(),
                              0);
    std::cout << "Sum of 1+2+3+4+5 = " << sum << std::endl;

    // --- Reading strings ---
    std::cout << "\n=== Reading strings ===" << std::endl;
    std::istringstream iss5("hello world foo bar");
    std::istream_iterator<std::string> sit(iss5);
    std::istream_iterator<std::string> send;

    std::cout << "Words: ";
    while (sit != send) {
        std::cout << "[" << *sit << "] ";
        ++sit;
    }
    std::cout << std::endl;

    // --- Reading doubles ---
    std::cout << "\n=== Reading doubles ===" << std::endl;
    std::istringstream iss6("1.1 2.2 3.3 4.4");
    std::vector<double> dvec;
    std::copy(std::istream_iterator<double>(iss6),
              std::istream_iterator<double>(),
              std::back_inserter(dvec));

    std::cout << "Doubles: ";
    for (std::vector<double>::iterator dit = dvec.begin(); dit != dvec.end(); ++dit) {
        std::cout << *dit << " ";
    }
    std::cout << std::endl;

    // --- Key properties of input iterators ---
    std::cout << "\n=== Input iterator properties ===" << std::endl;
    std::cout << "1. Single-pass: can only traverse the sequence once" << std::endl;
    std::cout << "2. Read-only: *it returns a value, cannot assign through it" << std::endl;
    std::cout << "3. Supports: ++it, it++, *it, it == end, it != end" << std::endl;
    std::cout << "4. Does NOT support: --it, it + n, it[n]" << std::endl;

    return 0;
}

/*
Expected output:
=== Basic istream_iterator ===
Reading integers from stream:
  Read: 10
  Read: 20
  Read: 30
  Read: 40
  Read: 50

=== Reading into a vector ===
Vector contents: 5 15 25 35 45 55
Size: 6

=== Construct vector from iterator range ===
Direct-constructed vector: 100 200 300

=== accumulate with istream_iterator ===
Sum of 1+2+3+4+5 = 15

=== Reading strings ===
Words: [hello] [world] [foo] [bar]

=== Reading doubles ===
Doubles: 1.1 2.2 3.3 4.4

=== Input iterator properties ===
1. Single-pass: can only traverse the sequence once
2. Read-only: *it returns a value, cannot assign through it
3. Supports: ++it, it++, *it, it == end, it != end
4. Does NOT support: --it, it + n, it[n]
*/
