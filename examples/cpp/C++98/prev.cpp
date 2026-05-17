// CodeNebula - C++98 Example: prev (advance-based pattern)
// Compile: g++ -std=c++98 -Wall -Wextra -o example prev.cpp

// NOTE: std::prev() was introduced in C++11. In C++98, we implement the same
// pattern using std::advance with a negative offset. This returns a new
// iterator pointing to the previous position without modifying the original.

#include <iostream>
#include <iterator>
#include <vector>
#include <list>
#include <set>

// C++98 implementation of the "prev" pattern.
// Returns an iterator moved n positions backward from 'it'.
// Requires at least a bidirectional iterator for negative advance.
template <typename BidirectionalIterator>
BidirectionalIterator prev_iter(BidirectionalIterator it, int n = 1) {
    std::advance(it, -n); // modifies the local copy
    return it;
}

// Also provide next_iter for convenience
template <typename Iterator>
Iterator next_iter(Iterator it, int n = 1) {
    std::advance(it, n);
    return it;
}

int main() {
    // --- prev_iter with vector ---
    std::cout << "=== prev_iter with vector ===" << std::endl;
    int arr[] = {10, 20, 30, 40, 50, 60, 70};
    std::vector<int> vec(arr, arr + 7);

    std::vector<int>::iterator it = vec.end();
    // Note: vec.end() points past the last element, cannot dereference directly

    std::vector<int>::iterator p1 = prev_iter(it);
    std::cout << "*prev_iter(end) = " << *p1 << " (last element)" << std::endl;

    std::vector<int>::iterator p3 = prev_iter(it, 3);
    std::cout << "*prev_iter(end, 3) = " << *p3 << std::endl;

    // Start from a middle position
    std::vector<int>::iterator mid = vec.begin() + 4; // points to 50
    std::cout << "\n*mid = " << *mid << std::endl;
    std::cout << "*prev_iter(mid) = " << *prev_iter(mid) << std::endl;
    std::cout << "*prev_iter(mid, 2) = " << *prev_iter(mid, 2) << std::endl;
    std::cout << "*mid (unchanged) = " << *mid << std::endl;

    // --- prev_iter with list ---
    std::cout << "\n=== prev_iter with list ===" << std::endl;
    std::list<std::string> words;
    words.push_back("alpha");
    words.push_back("beta");
    words.push_back("gamma");
    words.push_back("delta");
    words.push_back("epsilon");

    std::list<std::string>::iterator last = prev_iter(words.end());
    std::cout << "Last element: " << *last << std::endl;

    std::list<std::string>::iterator second_last = prev_iter(words.end(), 2);
    std::cout << "Second to last: " << *second_last << std::endl;

    std::list<std::string>::iterator third = prev_iter(words.end(), 3);
    std::cout << "Third from end: " << *third << std::endl;

    // --- prev_iter with set ---
    std::cout << "\n=== prev_iter with set ===" << std::endl;
    std::set<int> s;
    s.insert(100);
    s.insert(200);
    s.insert(300);
    s.insert(400);
    s.insert(500);

    std::cout << "Last element: " << *prev_iter(s.end()) << std::endl;
    std::cout << "2nd from end: " << *prev_iter(s.end(), 2) << std::endl;
    std::cout << "3rd from end: " << *prev_iter(s.end(), 3) << std::endl;

    // --- Practical: print last N elements ---
    std::cout << "\n=== Practical: last N elements ===" << std::endl;
    std::list<int> nums;
    for (int i = 1; i <= 10; ++i) {
        nums.push_back(i * 10);
    }

    std::cout << "Full list: ";
    for (std::list<int>::iterator i = nums.begin(); i != nums.end(); ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;

    int n = 3;
    std::cout << "Last " << n << " elements: ";
    std::list<int>::iterator start = prev_iter(nums.end(), n);
    for (std::list<int>::iterator i = start; i != nums.end(); ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;

    // --- Practical: erase the last element ---
    std::cout << "\n=== Practical: erase last element ===" << std::endl;
    std::cout << "Before: ";
    for (std::list<int>::iterator i = nums.begin(); i != nums.end(); ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;

    nums.erase(prev_iter(nums.end()));
    std::cout << "After erase last: ";
    for (std::list<int>::iterator i = nums.begin(); i != nums.end(); ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;

    // --- Practical: comparing adjacent elements backward ---
    std::cout << "\n=== Practical: backward adjacency check ===" << std::endl;
    std::vector<int> sorted_vec;
    sorted_vec.push_back(1);
    sorted_vec.push_back(3);
    sorted_vec.push_back(5);
    sorted_vec.push_back(7);
    sorted_vec.push_back(9);

    std::cout << "Is sorted (checking backward):" << std::endl;
    bool is_sorted = true;
    for (std::vector<int>::iterator curr = sorted_vec.begin() + 1;
         curr != sorted_vec.end(); ++curr) {
        std::vector<int>::iterator previous = prev_iter(curr);
        std::cout << "  " << *previous << " <= " << *curr << " ? "
                  << (*previous <= *curr ? "yes" : "no") << std::endl;
        if (*previous > *curr) {
            is_sorted = false;
        }
    }
    std::cout << "Result: " << (is_sorted ? "sorted" : "not sorted") << std::endl;

    // --- Combining next_iter and prev_iter ---
    std::cout << "\n=== Combining next_iter and prev_iter ===" << std::endl;
    std::list<int> combo;
    for (int i = 1; i <= 5; ++i) {
        combo.push_back(i * 100);
    }

    std::list<int>::iterator center = next_iter(combo.begin(), 2);
    std::cout << "Center: " << *center << std::endl;
    std::cout << "Prev:   " << *prev_iter(center) << std::endl;
    std::cout << "Next:   " << *next_iter(center) << std::endl;
    std::cout << "Window: " << *prev_iter(center) << " ["
              << *center << "] " << *next_iter(center) << std::endl;

    // --- Summary ---
    std::cout << "\n=== Summary ===" << std::endl;
    std::cout << "prev_iter(it, n): returns iterator moved n steps backward" << std::endl;
    std::cout << "  - Does NOT modify the original iterator" << std::endl;
    std::cout << "  - Requires bidirectional or random access iterator" << std::endl;
    std::cout << "  - In C++11, use std::prev(it, n) instead" << std::endl;

    return 0;
}

/*
Expected output:
=== prev_iter with vector ===
*prev_iter(end) = 70 (last element)
*prev_iter(end, 3) = 50

*mid = 50
*prev_iter(mid) = 40
*prev_iter(mid, 2) = 30
*mid (unchanged) = 50

=== prev_iter with list ===
Last element: epsilon
Second to last: delta
Third from end: gamma

=== prev_iter with set ===
Last element: 500
2nd from end: 400
3rd from end: 300

=== Practical: last N elements ===
Full list: 10 20 30 40 50 60 70 80 90 100
Last 3 elements: 80 90 100

=== Practical: erase last element ===
Before: 10 20 30 40 50 60 70 80 90 100
After erase last: 10 20 30 40 50 60 70 80 90

=== Practical: backward adjacency check ===
Is sorted (checking backward):
  1 <= 3 ? yes
  3 <= 5 ? yes
  5 <= 7 ? yes
  7 <= 9 ? yes
Result: sorted

=== Combining next_iter and prev_iter ===
Center: 300
Prev:   200
Next:   400
Window: 200 [300] 400

=== Summary ===
prev_iter(it, n): returns iterator moved n steps backward
  - Does NOT modify the original iterator
  - Requires bidirectional or random access iterator
  - In C++11, use std::prev(it, n) instead
*/
