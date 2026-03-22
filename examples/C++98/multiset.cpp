// CodeNebula - C++98 Example: multiset
// Compile: g++ -std=c++98 -Wall -Wextra -o example multiset.cpp

// std::multiset is like std::set but allows duplicate elements.
// Elements are sorted and duplicates are stored adjacently.

#include <iostream>
#include <set>

void print_multiset(const std::string& label, const std::multiset<int>& ms) {
    std::cout << label << ": { ";
    for (std::multiset<int>::const_iterator it = ms.begin(); it != ms.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "} (size=" << ms.size() << ")" << std::endl;
}

int main() {
    // --- Insert duplicates ---
    std::cout << "=== insert duplicates ===" << std::endl;
    std::multiset<int> ms;
    ms.insert(30);
    ms.insert(10);
    ms.insert(20);
    ms.insert(30);  // duplicate
    ms.insert(10);  // duplicate
    ms.insert(30);  // another duplicate
    ms.insert(40);
    print_multiset("After inserts", ms);

    // Insert always succeeds for multiset (returns iterator, not pair)
    std::multiset<int>::iterator inserted = ms.insert(20);
    std::cout << "Inserted another 20 at value: " << *inserted << std::endl;
    print_multiset("After inserting another 20", ms);

    // --- count ---
    std::cout << "\n=== count ===" << std::endl;
    std::cout << "count(10) = " << ms.count(10) << std::endl;
    std::cout << "count(20) = " << ms.count(20) << std::endl;
    std::cout << "count(30) = " << ms.count(30) << std::endl;
    std::cout << "count(40) = " << ms.count(40) << std::endl;
    std::cout << "count(99) = " << ms.count(99) << std::endl;

    // --- find ---
    std::cout << "\n=== find ===" << std::endl;
    std::multiset<int>::iterator it = ms.find(30);
    if (it != ms.end()) {
        std::cout << "Found 30: " << *it << std::endl;
    }

    it = ms.find(99);
    std::cout << "find(99): " << (it == ms.end() ? "not found" : "found") << std::endl;

    // --- equal_range ---
    std::cout << "\n=== equal_range ===" << std::endl;
    print_multiset("Current multiset", ms);

    std::pair<std::multiset<int>::iterator, std::multiset<int>::iterator> range;

    range = ms.equal_range(30);
    std::cout << "equal_range(30): ";
    for (std::multiset<int>::iterator r = range.first; r != range.second; ++r) {
        std::cout << *r << " ";
    }
    std::cout << std::endl;

    range = ms.equal_range(10);
    std::cout << "equal_range(10): ";
    for (std::multiset<int>::iterator r = range.first; r != range.second; ++r) {
        std::cout << *r << " ";
    }
    std::cout << std::endl;

    range = ms.equal_range(99);
    std::cout << "equal_range(99): "
              << (range.first == range.second ? "empty range" : "has elements")
              << std::endl;

    // --- lower_bound and upper_bound ---
    std::cout << "\n=== lower_bound and upper_bound ===" << std::endl;
    std::multiset<int>::iterator lb = ms.lower_bound(20);
    std::cout << "lower_bound(20) = " << *lb << std::endl;

    std::multiset<int>::iterator ub = ms.upper_bound(20);
    std::cout << "upper_bound(20) = " << *ub << std::endl;

    // --- erase ---
    std::cout << "\n=== erase ===" << std::endl;
    print_multiset("Before erase", ms);

    // Erase by value: removes ALL elements with that value
    std::multiset<int>::size_type erased = ms.erase(30);
    std::cout << "erase(30): removed " << erased << " elements" << std::endl;
    print_multiset("After erase(30)", ms);

    // Erase single element by iterator
    it = ms.find(10);
    if (it != ms.end()) {
        ms.erase(it); // removes only one 10
    }
    print_multiset("After erasing one 10", ms);

    // --- Iteration ---
    std::cout << "\n=== Iteration ===" << std::endl;
    std::cout << "Forward:  ";
    for (std::multiset<int>::iterator it2 = ms.begin(); it2 != ms.end(); ++it2) {
        std::cout << *it2 << " ";
    }
    std::cout << std::endl;

    std::cout << "Reverse:  ";
    for (std::multiset<int>::reverse_iterator rit = ms.rbegin(); rit != ms.rend(); ++rit) {
        std::cout << *rit << " ";
    }
    std::cout << std::endl;

    // --- Construct from array ---
    std::cout << "\n=== Construct from array ===" << std::endl;
    int arr[] = {5, 3, 5, 1, 3, 5, 2};
    std::multiset<int> ms2(arr, arr + 7);
    print_multiset("From array {5,3,5,1,3,5,2}", ms2);

    return 0;
}

/*
Expected output:
=== insert duplicates ===
After inserts: { 10 10 20 30 30 30 40 } (size=7)
Inserted another 20 at value: 20
After inserting another 20: { 10 10 20 20 30 30 30 40 } (size=8)

=== count ===
count(10) = 2
count(20) = 2
count(30) = 3
count(40) = 1
count(99) = 0

=== find ===
Found 30: 30
find(99): not found

=== equal_range ===
Current multiset: { 10 10 20 20 30 30 30 40 } (size=8)
equal_range(30): 30 30 30
equal_range(10): 10 10
equal_range(99): empty range

=== lower_bound and upper_bound ===
lower_bound(20) = 20
upper_bound(20) = 30

=== erase ===
Before erase: { 10 10 20 20 30 30 30 40 } (size=8)
erase(30): removed 3 elements
After erase(30): { 10 10 20 20 40 } (size=5)
After erasing one 10: { 10 20 20 40 } (size=4)

=== Iteration ===
Forward:  10 20 20 40
Reverse:  40 20 20 10

=== Construct from array ===
From array {5,3,5,1,3,5,2}: { 1 2 3 3 5 5 5 } (size=7)
*/
