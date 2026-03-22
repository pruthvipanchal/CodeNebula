// CodeNebula - C++98 Example: bidirectional_iterator
// Compile: g++ -std=c++98 -Wall -Wextra -o example bidirectional_iterator.cpp

// Bidirectional iterators extend forward iterators with backward traversal (--).
// std::list, std::set, and std::map provide bidirectional iterators.

#include <iostream>
#include <list>
#include <set>
#include <map>
#include <algorithm>
#include <iterator>
#include <string>

int main() {
    // --- std::list bidirectional iteration ---
    std::cout << "=== List bidirectional iteration ===" << std::endl;
    std::list<int> lst;
    lst.push_back(10);
    lst.push_back(20);
    lst.push_back(30);
    lst.push_back(40);
    lst.push_back(50);

    // Forward traversal
    std::cout << "Forward:  ";
    for (std::list<int>::iterator it = lst.begin(); it != lst.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Backward traversal using --
    std::cout << "Backward: ";
    std::list<int>::iterator it = lst.end();
    while (it != lst.begin()) {
        --it;
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // --- Forward and backward from middle ---
    std::cout << "\n=== Navigate from middle ===" << std::endl;
    it = lst.begin();
    ++it; ++it; // now pointing at 30
    std::cout << "Starting at: " << *it << std::endl;

    ++it;
    std::cout << "After ++: " << *it << std::endl;

    --it;
    std::cout << "After --: " << *it << std::endl;

    --it;
    std::cout << "After --: " << *it << std::endl;

    // --- Reverse iterators (built from bidirectional iterators) ---
    std::cout << "\n=== Reverse iterators ===" << std::endl;
    std::cout << "rbegin->rend: ";
    for (std::list<int>::reverse_iterator rit = lst.rbegin();
         rit != lst.rend(); ++rit) {
        std::cout << *rit << " ";
    }
    std::cout << std::endl;

    // --- Modifying through bidirectional iterators ---
    std::cout << "\n=== Modify through iterator ===" << std::endl;
    std::cout << "Before: ";
    for (std::list<int>::iterator it2 = lst.begin(); it2 != lst.end(); ++it2) {
        std::cout << *it2 << " ";
    }
    std::cout << std::endl;

    // Double every other element going backward
    it = lst.end();
    int count = 0;
    while (it != lst.begin()) {
        --it;
        if (count % 2 == 0) {
            *it *= 2;
        }
        ++count;
    }
    std::cout << "After doubling every other (from back): ";
    for (std::list<int>::iterator it2 = lst.begin(); it2 != lst.end(); ++it2) {
        std::cout << *it2 << " ";
    }
    std::cout << std::endl;

    // --- std::set bidirectional iteration ---
    std::cout << "\n=== Set bidirectional iteration ===" << std::endl;
    std::set<int> s;
    s.insert(50);
    s.insert(10);
    s.insert(30);
    s.insert(20);
    s.insert(40);

    std::cout << "Forward:  ";
    for (std::set<int>::iterator sit = s.begin(); sit != s.end(); ++sit) {
        std::cout << *sit << " ";
    }
    std::cout << std::endl;

    std::cout << "Backward: ";
    std::set<int>::iterator sit = s.end();
    while (sit != s.begin()) {
        --sit;
        std::cout << *sit << " ";
    }
    std::cout << std::endl;

    // --- std::map bidirectional iteration ---
    std::cout << "\n=== Map bidirectional iteration ===" << std::endl;
    std::map<std::string, int> m;
    m["cherry"] = 3;
    m["apple"] = 1;
    m["banana"] = 2;
    m["date"] = 4;

    std::cout << "Forward:" << std::endl;
    for (std::map<std::string, int>::iterator mit = m.begin();
         mit != m.end(); ++mit) {
        std::cout << "  " << mit->first << " => " << mit->second << std::endl;
    }

    std::cout << "Backward:" << std::endl;
    std::map<std::string, int>::iterator mit = m.end();
    while (mit != m.begin()) {
        --mit;
        std::cout << "  " << mit->first << " => " << mit->second << std::endl;
    }

    // --- Using std::advance (works with bidirectional iterators) ---
    std::cout << "\n=== std::advance with bidirectional ===" << std::endl;
    std::list<int>::iterator adv = lst.begin();
    std::cout << "Start: " << *adv << std::endl;

    std::advance(adv, 3);
    std::cout << "After advance(3): " << *adv << std::endl;

    std::advance(adv, -2);
    std::cout << "After advance(-2): " << *adv << std::endl;

    // --- Using std::distance ---
    std::cout << "\n=== std::distance ===" << std::endl;
    std::list<int>::iterator first = lst.begin();
    std::list<int>::iterator last = lst.end();
    std::cout << "Distance begin to end: " << std::distance(first, last) << std::endl;

    // --- Key properties of bidirectional iterators ---
    std::cout << "\n=== Bidirectional iterator properties ===" << std::endl;
    std::cout << "1. Multi-pass: can traverse the same range multiple times" << std::endl;
    std::cout << "2. Read/Write: *it for reading and assigning" << std::endl;
    std::cout << "3. Supports: ++it, --it, *it, it == end, it != end" << std::endl;
    std::cout << "4. Does NOT support: it + n, it - n, it[n], it < it2" << std::endl;
    std::cout << "5. Category: std::bidirectional_iterator_tag" << std::endl;
    std::cout << "6. Containers: list, set, multiset, map, multimap" << std::endl;

    return 0;
}

/*
Expected output:
=== List bidirectional iteration ===
Forward:  10 20 30 40 50
Backward: 50 40 30 20 10

=== Navigate from middle ===
Starting at: 30
After ++: 40
After --: 30
After --: 20

=== Reverse iterators ===
rbegin->rend: 50 40 30 20 10

=== Modify through iterator ===
Before: 10 20 30 40 50
After doubling every other (from back): 20 20 60 40 100

=== Set bidirectional iteration ===
Forward:  10 20 30 40 50
Backward: 50 40 30 20 10

=== Map bidirectional iteration ===
Forward:
  apple => 1
  banana => 2
  cherry => 3
  date => 4
Backward:
  date => 4
  cherry => 3
  banana => 2
  apple => 1

=== std::advance with bidirectional ===
Start: 20
After advance(3): 40
After advance(-2): 60

=== std::distance ===
Distance begin to end: 5

=== Bidirectional iterator properties ===
1. Multi-pass: can traverse the same range multiple times
2. Read/Write: *it for reading and assigning
3. Supports: ++it, --it, *it, it == end, it != end
4. Does NOT support: it + n, it - n, it[n], it < it2
5. Category: std::bidirectional_iterator_tag
6. Containers: list, set, multiset, map, multimap
*/
