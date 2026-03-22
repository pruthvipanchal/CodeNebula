// CodeNebula - C++98 Example: next (advance-based pattern)
// Compile: g++ -std=c++98 -Wall -Wextra -o example next.cpp

// NOTE: std::next() was introduced in C++11. In C++98, we can implement the
// same pattern using std::advance. This file demonstrates an advance-based
// "next" helper that returns a new iterator without modifying the original.

#include <iostream>
#include <iterator>
#include <vector>
#include <list>
#include <set>

// C++98 implementation of the "next" pattern.
// Returns an iterator advanced n positions forward from 'it'.
// The original iterator is NOT modified.
template <typename Iterator>
Iterator next_iter(Iterator it, int n = 1) {
    std::advance(it, n); // modifies the local copy
    return it;
}

int main() {
    // --- next_iter with vector ---
    std::cout << "=== next_iter with vector ===" << std::endl;
    int arr[] = {10, 20, 30, 40, 50, 60, 70};
    std::vector<int> vec(arr, arr + 7);

    std::vector<int>::iterator it = vec.begin();
    std::cout << "*it = " << *it << std::endl;

    // Get next without modifying 'it'
    std::vector<int>::iterator n1 = next_iter(it);
    std::cout << "*next_iter(it) = " << *n1 << std::endl;
    std::cout << "*it (unchanged) = " << *it << std::endl;

    std::vector<int>::iterator n3 = next_iter(it, 3);
    std::cout << "*next_iter(it, 3) = " << *n3 << std::endl;
    std::cout << "*it (still unchanged) = " << *it << std::endl;

    // --- next_iter with list ---
    std::cout << "\n=== next_iter with list ===" << std::endl;
    std::list<std::string> words;
    words.push_back("alpha");
    words.push_back("beta");
    words.push_back("gamma");
    words.push_back("delta");
    words.push_back("epsilon");

    std::list<std::string>::iterator lit = words.begin();
    std::cout << "*lit = " << *lit << std::endl;

    std::list<std::string>::iterator lit2 = next_iter(lit, 2);
    std::cout << "*next_iter(lit, 2) = " << *lit2 << std::endl;
    std::cout << "*lit (unchanged) = " << *lit << std::endl;

    // Chain next_iter calls
    std::cout << "*next_iter(next_iter(lit, 1), 1) = "
              << *next_iter(next_iter(lit, 1), 1) << std::endl;

    // --- next_iter with set ---
    std::cout << "\n=== next_iter with set ===" << std::endl;
    std::set<int> s;
    s.insert(100);
    s.insert(200);
    s.insert(300);
    s.insert(400);
    s.insert(500);

    std::set<int>::iterator sit = s.begin();
    std::cout << "*sit = " << *sit << std::endl;
    std::cout << "*next_iter(sit, 2) = " << *next_iter(sit, 2) << std::endl;
    std::cout << "*next_iter(sit, 4) = " << *next_iter(sit, 4) << std::endl;

    // --- Practical: look ahead without modifying position ---
    std::cout << "\n=== Practical: look-ahead ===" << std::endl;
    std::list<int> nums;
    nums.push_back(1);
    nums.push_back(5);
    nums.push_back(2);
    nums.push_back(8);
    nums.push_back(3);

    std::cout << "Pairs of consecutive elements:" << std::endl;
    for (std::list<int>::iterator curr = nums.begin();
         next_iter(curr) != nums.end(); ++curr) {
        std::cout << "  (" << *curr << ", " << *next_iter(curr) << ")" << std::endl;
    }

    // --- Practical: insert before the last element ---
    std::cout << "\n=== Practical: insert before last ===" << std::endl;
    std::list<int> insert_list;
    insert_list.push_back(10);
    insert_list.push_back(20);
    insert_list.push_back(30);

    std::cout << "Before: ";
    for (std::list<int>::iterator i = insert_list.begin();
         i != insert_list.end(); ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;

    // Insert 25 before the last element using next_iter to find position
    std::list<int>::iterator last_elem = next_iter(insert_list.begin(), 2);
    insert_list.insert(last_elem, 25);

    std::cout << "After inserting 25 before last: ";
    for (std::list<int>::iterator i = insert_list.begin();
         i != insert_list.end(); ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;

    // --- Practical: erase the nth element ---
    std::cout << "\n=== Practical: erase nth element ===" << std::endl;
    std::list<int> erase_list;
    for (int i = 1; i <= 6; ++i) {
        erase_list.push_back(i * 10);
    }

    std::cout << "Before: ";
    for (std::list<int>::iterator i = erase_list.begin();
         i != erase_list.end(); ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;

    // Erase the 3rd element (index 2)
    erase_list.erase(next_iter(erase_list.begin(), 2));

    std::cout << "After erasing index 2: ";
    for (std::list<int>::iterator i = erase_list.begin();
         i != erase_list.end(); ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;

    // --- Comparison: advance vs next_iter ---
    std::cout << "\n=== advance vs next_iter ===" << std::endl;
    std::cout << "std::advance(it, n): modifies 'it' in place, returns void" << std::endl;
    std::cout << "next_iter(it, n):    returns new iterator, 'it' unchanged" << std::endl;
    std::cout << "In C++11, use std::next(it, n) instead of this helper." << std::endl;

    return 0;
}

/*
Expected output:
=== next_iter with vector ===
*it = 10
*next_iter(it) = 20
*it (unchanged) = 10
*next_iter(it, 3) = 40
*it (still unchanged) = 10

=== next_iter with list ===
*lit = alpha
*next_iter(lit, 2) = gamma
*lit (unchanged) = alpha
*next_iter(next_iter(lit, 1), 1) = gamma

=== next_iter with set ===
*sit = 100
*next_iter(sit, 2) = 300
*next_iter(sit, 4) = 500

=== Practical: look-ahead ===
Pairs of consecutive elements:
  (1, 5)
  (5, 2)
  (2, 8)
  (8, 3)

=== Practical: insert before last ===
Before: 10 20 30
After inserting 25 before last: 10 20 25 30

=== Practical: erase nth element ===
Before: 10 20 30 40 50 60
After erasing index 2: 10 20 40 50 60

=== advance vs next_iter ===
std::advance(it, n): modifies 'it' in place, returns void
next_iter(it, n):    returns new iterator, 'it' unchanged
In C++11, use std::next(it, n) instead of this helper.
*/
