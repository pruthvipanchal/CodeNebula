// CodeNebula - C++98 Example: set
// Compile: g++ -std=c++98 -Wall -Wextra -o example set.cpp

// std::set is an ordered associative container that stores unique elements.
// Elements are sorted by their value using the comparison function (default: less<T>).
// Insertion, lookup, and removal are O(log n).

#include <iostream>
#include <set>
#include <functional> // for std::greater

void print_set(const std::string& label, const std::set<int>& s) {
    std::cout << label << ": { ";
    for (std::set<int>::const_iterator it = s.begin(); it != s.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "} (size=" << s.size() << ")" << std::endl;
}

int main() {
    // --- insert ---
    std::cout << "=== insert ===" << std::endl;
    std::set<int> s;
    s.insert(30);
    s.insert(10);
    s.insert(50);
    s.insert(20);
    s.insert(40);
    print_set("After inserting 30,10,50,20,40", s);

    // Inserting duplicates: returns pair<iterator, bool>
    std::pair<std::set<int>::iterator, bool> result = s.insert(30);
    std::cout << "Insert 30 again: success=" << (result.second ? "true" : "false") << std::endl;

    result = s.insert(99);
    std::cout << "Insert 99: success=" << (result.second ? "true" : "false")
              << ", value=" << *(result.first) << std::endl;
    print_set("After insert attempts", s);

    // --- find ---
    std::cout << "\n=== find ===" << std::endl;
    std::set<int>::iterator it = s.find(20);
    if (it != s.end()) {
        std::cout << "Found: " << *it << std::endl;
    }

    it = s.find(999);
    if (it == s.end()) {
        std::cout << "999 not found" << std::endl;
    }

    // --- count ---
    std::cout << "\n=== count ===" << std::endl;
    std::cout << "count(20) = " << s.count(20) << std::endl;
    std::cout << "count(999) = " << s.count(999) << std::endl;

    // --- erase ---
    std::cout << "\n=== erase ===" << std::endl;
    print_set("Before erase", s);

    // Erase by value
    std::set<int>::size_type erased = s.erase(30);
    std::cout << "Erased 30: count=" << erased << std::endl;

    erased = s.erase(999);
    std::cout << "Erased 999: count=" << erased << std::endl;

    // Erase by iterator
    s.erase(s.begin());
    print_set("After erasing first element", s);

    // --- Iteration (elements are always sorted) ---
    std::cout << "\n=== Iteration ===" << std::endl;
    s.clear();
    s.insert(5);
    s.insert(3);
    s.insert(8);
    s.insert(1);
    s.insert(9);

    std::cout << "Forward:  ";
    for (std::set<int>::iterator it2 = s.begin(); it2 != s.end(); ++it2) {
        std::cout << *it2 << " ";
    }
    std::cout << std::endl;

    std::cout << "Reverse:  ";
    for (std::set<int>::reverse_iterator rit = s.rbegin(); rit != s.rend(); ++rit) {
        std::cout << *rit << " ";
    }
    std::cout << std::endl;

    // --- lower_bound and upper_bound ---
    std::cout << "\n=== lower_bound and upper_bound ===" << std::endl;
    print_set("Set", s);

    std::set<int>::iterator lb = s.lower_bound(3);
    std::cout << "lower_bound(3) = " << *lb << std::endl;

    std::set<int>::iterator ub = s.upper_bound(3);
    std::cout << "upper_bound(3) = " << *ub << std::endl;

    lb = s.lower_bound(6);
    std::cout << "lower_bound(6) = " << *lb << " (first element >= 6)" << std::endl;

    // --- equal_range ---
    std::cout << "\n=== equal_range ===" << std::endl;
    std::pair<std::set<int>::iterator, std::set<int>::iterator> range = s.equal_range(5);
    std::cout << "equal_range(5): [" << *range.first << ", " << *range.second << ")" << std::endl;

    // --- Custom comparison: descending order ---
    std::cout << "\n=== Custom comparison (descending) ===" << std::endl;
    std::set<int, std::greater<int> > desc_set;
    desc_set.insert(10);
    desc_set.insert(30);
    desc_set.insert(20);
    desc_set.insert(50);
    desc_set.insert(40);
    std::cout << "Descending set: { ";
    for (std::set<int, std::greater<int> >::iterator it3 = desc_set.begin();
         it3 != desc_set.end(); ++it3) {
        std::cout << *it3 << " ";
    }
    std::cout << "}" << std::endl;

    // --- Constructing from range ---
    std::cout << "\n=== Construct from range ===" << std::endl;
    int arr[] = {4, 2, 7, 2, 9, 4, 1};
    std::set<int> from_arr(arr, arr + 7);
    print_set("Set from array {4,2,7,2,9,4,1}", from_arr);

    return 0;
}

/*
Expected output:
=== insert ===
After inserting 30,10,50,20,40: { 10 20 30 40 50 } (size=5)
Insert 30 again: success=false
Insert 99: success=true, value=99
After insert attempts: { 10 20 30 40 50 99 } (size=6)

=== find ===
Found: 20
999 not found

=== count ===
count(20) = 1
count(999) = 0

=== erase ===
Before erase: { 10 20 30 40 50 99 } (size=6)
Erased 30: count=1
Erased 999: count=0
After erasing first element: { 20 40 50 99 } (size=4)

=== Iteration ===
Forward:  1 3 5 8 9
Reverse:  9 8 5 3 1

=== lower_bound and upper_bound ===
Set: { 1 3 5 8 9 } (size=5)
lower_bound(3) = 3
upper_bound(3) = 5
lower_bound(6) = 8 (first element >= 6)

=== equal_range ===
equal_range(5): [5, 8)

=== Custom comparison (descending) ===
Descending set: { 50 40 30 20 10 }

=== Construct from range ===
Set from array {4,2,7,2,9,4,1}: { 1 2 4 7 9 } (size=5)
*/
