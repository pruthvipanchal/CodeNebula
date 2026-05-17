// CodeNebula - C++98 Example: reverse_iterator
// Compile: g++ -std=c++98 -Wall -Wextra -o example reverse_iterator.cpp

// std::reverse_iterator is an adaptor that reverses the direction of a given
// iterator. Containers provide rbegin()/rend() which return reverse_iterators.
// Incrementing a reverse_iterator moves backward through the underlying range.

#include <iostream>
#include <iterator>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <string>
#include <algorithm>

int main() {
    // --- rbegin/rend with vector ---
    std::cout << "=== Vector rbegin/rend ===" << std::endl;
    int arr[] = {10, 20, 30, 40, 50};
    std::vector<int> vec(arr, arr + 5);

    std::cout << "Forward:  ";
    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Reverse:  ";
    for (std::vector<int>::reverse_iterator rit = vec.rbegin();
         rit != vec.rend(); ++rit) {
        std::cout << *rit << " ";
    }
    std::cout << std::endl;

    // --- Accessing elements via reverse_iterator ---
    std::cout << "\n=== Accessing elements ===" << std::endl;
    std::vector<int>::reverse_iterator rit = vec.rbegin();
    std::cout << "*rbegin() = " << *rit << " (last element)" << std::endl;
    ++rit;
    std::cout << "*(rbegin()+1) = " << *rit << " (second to last)" << std::endl;

    // Random access with reverse_iterator
    rit = vec.rbegin();
    std::cout << "rbegin()[0] = " << rit[0] << std::endl;
    std::cout << "rbegin()[2] = " << rit[2] << std::endl;
    std::cout << "rbegin()[4] = " << rit[4] << std::endl;

    // --- Modifying through reverse_iterator ---
    std::cout << "\n=== Modifying through reverse_iterator ===" << std::endl;
    std::cout << "Before: ";
    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Double elements from back to front
    int multiplier = 1;
    for (std::vector<int>::reverse_iterator ri = vec.rbegin();
         ri != vec.rend(); ++ri) {
        *ri *= multiplier;
        ++multiplier;
    }
    std::cout << "After multiplying by position from end: ";
    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // --- rbegin/rend with list ---
    std::cout << "\n=== List rbegin/rend ===" << std::endl;
    std::list<std::string> words;
    words.push_back("one");
    words.push_back("two");
    words.push_back("three");
    words.push_back("four");
    words.push_back("five");

    std::cout << "Forward:  ";
    for (std::list<std::string>::iterator it = words.begin();
         it != words.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Reverse:  ";
    for (std::list<std::string>::reverse_iterator ri = words.rbegin();
         ri != words.rend(); ++ri) {
        std::cout << *ri << " ";
    }
    std::cout << std::endl;

    // --- rbegin/rend with set ---
    std::cout << "\n=== Set rbegin/rend (descending order) ===" << std::endl;
    std::set<int> s;
    s.insert(30);
    s.insert(10);
    s.insert(50);
    s.insert(20);
    s.insert(40);

    std::cout << "Forward (ascending):  ";
    for (std::set<int>::iterator it = s.begin(); it != s.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Reverse (descending): ";
    for (std::set<int>::reverse_iterator ri = s.rbegin(); ri != s.rend(); ++ri) {
        std::cout << *ri << " ";
    }
    std::cout << std::endl;

    // --- rbegin/rend with map ---
    std::cout << "\n=== Map rbegin/rend ===" << std::endl;
    std::map<std::string, int> scores;
    scores["Alice"] = 95;
    scores["Bob"] = 87;
    scores["Charlie"] = 92;

    std::cout << "Forward:" << std::endl;
    for (std::map<std::string, int>::iterator it = scores.begin();
         it != scores.end(); ++it) {
        std::cout << "  " << it->first << " => " << it->second << std::endl;
    }

    std::cout << "Reverse:" << std::endl;
    for (std::map<std::string, int>::reverse_iterator ri = scores.rbegin();
         ri != scores.rend(); ++ri) {
        std::cout << "  " << ri->first << " => " << ri->second << std::endl;
    }

    // --- Constructing reverse_iterator from regular iterator ---
    std::cout << "\n=== Constructing reverse_iterator manually ===" << std::endl;
    std::vector<int> v2;
    for (int i = 1; i <= 5; ++i) {
        v2.push_back(i * 10);
    }

    std::vector<int>::iterator fwd = v2.begin() + 3; // points to 40
    std::cout << "*fwd = " << *fwd << std::endl;

    // Construct reverse_iterator from a forward iterator
    std::vector<int>::reverse_iterator rev(fwd);
    // A reverse_iterator constructed from 'it' points to *(it-1)
    std::cout << "*reverse_iterator(fwd) = " << *rev
              << " (points to element BEFORE fwd)" << std::endl;

    // --- base() - converting back to forward iterator ---
    std::cout << "\n=== base() conversion ===" << std::endl;
    std::vector<int>::reverse_iterator ri = v2.rbegin();
    ++ri; ++ri; // now points to 30 (in reverse direction)
    std::cout << "*ri = " << *ri << std::endl;

    std::vector<int>::iterator base_it = ri.base();
    // base() returns the underlying iterator, which is one past ri
    std::cout << "*ri.base() = " << *base_it
              << " (one element past *ri in forward direction)" << std::endl;

    // --- Using reverse_iterator with std::copy ---
    std::cout << "\n=== Copy in reverse ===" << std::endl;
    std::vector<int> original;
    for (int i = 1; i <= 5; ++i) {
        original.push_back(i);
    }

    std::vector<int> reversed;
    std::copy(original.rbegin(), original.rend(), std::back_inserter(reversed));

    std::cout << "Original: ";
    std::copy(original.begin(), original.end(),
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    std::cout << "Reversed: ";
    std::copy(reversed.begin(), reversed.end(),
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    // --- Using reverse_iterator with std::find ---
    std::cout << "\n=== Find last occurrence ===" << std::endl;
    int data[] = {1, 2, 3, 2, 5, 2, 7};
    std::vector<int> search_vec(data, data + 7);

    // Find LAST occurrence of 2 by searching in reverse
    std::vector<int>::reverse_iterator rfound =
        std::find(search_vec.rbegin(), search_vec.rend(), 2);
    if (rfound != search_vec.rend()) {
        // Convert to forward index
        std::ptrdiff_t idx = std::distance(search_vec.begin(), rfound.base()) - 1;
        std::cout << "Last '2' found at index: " << idx << std::endl;
    }

    // --- Const reverse iterator ---
    std::cout << "\n=== Const reverse iterator ===" << std::endl;
    const std::vector<int>& cvec = original;
    std::cout << "Const reverse: ";
    for (std::vector<int>::const_reverse_iterator cri = cvec.rbegin();
         cri != cvec.rend(); ++cri) {
        std::cout << *cri << " ";
    }
    std::cout << std::endl;

    return 0;
}

/*
Expected output:
=== Vector rbegin/rend ===
Forward:  10 20 30 40 50
Reverse:  50 40 30 20 10

=== Accessing elements ===
*rbegin() = 50 (last element)
*(rbegin()+1) = 40 (second to last)
rbegin()[0] = 50
rbegin()[2] = 30
rbegin()[4] = 10

=== Modifying through reverse_iterator ===
Before: 10 20 30 40 50
After multiplying by position from end: 50 80 90 80 50

=== List rbegin/rend ===
Forward:  one two three four five
Reverse:  five four three two one

=== Set rbegin/rend (descending order) ===
Forward (ascending):  10 20 30 40 50
Reverse (descending): 50 40 30 20 10

=== Map rbegin/rend ===
Forward:
  Alice => 95
  Bob => 87
  Charlie => 92
Reverse:
  Charlie => 92
  Bob => 87
  Alice => 95

=== Constructing reverse_iterator manually ===
*fwd = 40
*reverse_iterator(fwd) = 30 (points to element BEFORE fwd)

=== base() conversion ===
*ri = 30
*ri.base() = 40 (one element past *ri in forward direction)

=== Copy in reverse ===
Original: 1 2 3 4 5
Reversed: 5 4 3 2 1

=== Find last occurrence ===
Last '2' found at index: 5

=== Const reverse iterator ===
Const reverse: 5 4 3 2 1
*/
