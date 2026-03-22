// CodeNebula - C++98 Example: output_iterator
// Compile: g++ -std=c++98 -Wall -Wextra -o example output_iterator.cpp

// Output iterators support single-pass writing. std::ostream_iterator writes
// values to an output stream. Other output iterators include back_inserter,
// front_inserter, and inserter.

#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>
#include <list>
#include <set>
#include <algorithm> // for std::copy, std::transform

int square(int x) { return x * x; }
int negate_val(int x) { return -x; }

int main() {
    // --- ostream_iterator to cout ---
    std::cout << "=== ostream_iterator to cout ===" << std::endl;
    std::ostream_iterator<int> cout_it(std::cout, " ");

    // Write individual values
    *cout_it = 10; ++cout_it;
    *cout_it = 20; ++cout_it;
    *cout_it = 30; ++cout_it;
    std::cout << std::endl;

    // --- Copy vector to cout ---
    std::cout << "\n=== Copy vector to cout ===" << std::endl;
    int arr[] = {1, 2, 3, 4, 5};
    std::vector<int> vec(arr, arr + 5);

    std::cout << "With space delimiter: ";
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    std::cout << "With comma delimiter: ";
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, ", "));
    std::cout << std::endl;

    std::cout << "With newline delimiter:" << std::endl;
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, "\n"));

    // --- ostream_iterator to stringstream ---
    std::cout << "\n=== ostream_iterator to stringstream ===" << std::endl;
    std::ostringstream oss;
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(oss, "-"));
    std::cout << "Stringstream result: " << oss.str() << std::endl;

    // --- ostream_iterator with strings ---
    std::cout << "\n=== ostream_iterator with strings ===" << std::endl;
    std::vector<std::string> words;
    words.push_back("hello");
    words.push_back("world");
    words.push_back("foo");
    words.push_back("bar");

    std::cout << "Words: ";
    std::copy(words.begin(), words.end(),
              std::ostream_iterator<std::string>(std::cout, " | "));
    std::cout << std::endl;

    // --- back_inserter ---
    std::cout << "\n=== back_inserter ===" << std::endl;
    std::vector<int> src;
    src.push_back(10);
    src.push_back(20);
    src.push_back(30);

    std::vector<int> dest;
    std::copy(src.begin(), src.end(), std::back_inserter(dest));

    std::cout << "Copied via back_inserter: ";
    std::copy(dest.begin(), dest.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    // --- front_inserter ---
    std::cout << "\n=== front_inserter ===" << std::endl;
    std::list<int> front_dest;
    std::copy(src.begin(), src.end(), std::front_inserter(front_dest));

    std::cout << "Copied via front_inserter (reversed): ";
    std::copy(front_dest.begin(), front_dest.end(),
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    // --- inserter ---
    std::cout << "\n=== inserter ===" << std::endl;
    std::set<int> my_set;
    int data[] = {5, 3, 8, 1, 9, 2, 7};
    std::copy(data, data + 7, std::inserter(my_set, my_set.begin()));

    std::cout << "Set via inserter (sorted): ";
    std::copy(my_set.begin(), my_set.end(),
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    // --- transform with output iterator ---
    std::cout << "\n=== transform with ostream_iterator ===" << std::endl;
    std::cout << "Squares: ";
    std::transform(vec.begin(), vec.end(),
                   std::ostream_iterator<int>(std::cout, " "),
                   square);
    std::cout << std::endl;

    std::cout << "Negated: ";
    std::transform(vec.begin(), vec.end(),
                   std::ostream_iterator<int>(std::cout, " "),
                   negate_val);
    std::cout << std::endl;

    // --- transform into a new container ---
    std::cout << "\n=== transform with back_inserter ===" << std::endl;
    std::vector<int> squared;
    std::transform(vec.begin(), vec.end(), std::back_inserter(squared), square);

    std::cout << "Squared vector: ";
    std::copy(squared.begin(), squared.end(),
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    // --- Key properties of output iterators ---
    std::cout << "\n=== Output iterator properties ===" << std::endl;
    std::cout << "1. Single-pass: can only traverse the sequence once" << std::endl;
    std::cout << "2. Write-only: *it = value assigns, cannot read through it" << std::endl;
    std::cout << "3. Supports: ++it, it++, *it = val" << std::endl;
    std::cout << "4. Does NOT support: *it (read), it == end, --it, it + n" << std::endl;

    return 0;
}

/*
Expected output:
=== ostream_iterator to cout ===
10 20 30

=== Copy vector to cout ===
With space delimiter: 1 2 3 4 5
With comma delimiter: 1, 2, 3, 4, 5,
With newline delimiter:
1
2
3
4
5

=== ostream_iterator to stringstream ===
Stringstream result: 1-2-3-4-5-

=== ostream_iterator with strings ===
Words: hello | world | foo | bar |

=== back_inserter ===
Copied via back_inserter: 10 20 30

=== front_inserter ===
Copied via front_inserter (reversed): 30 20 10

=== inserter ===
Set via inserter (sorted): 1 2 3 5 7 8 9

=== transform with ostream_iterator ===
Squares: 1 4 9 16 25
Negated: -1 -2 -3 -4 -5

=== transform with back_inserter ===
Squared vector: 1 4 9 16 25

=== Output iterator properties ===
1. Single-pass: can only traverse the sequence once
2. Write-only: *it = value assigns, cannot read through it
3. Supports: ++it, it++, *it = val
4. Does NOT support: *it (read), it == end, --it, it + n
*/
