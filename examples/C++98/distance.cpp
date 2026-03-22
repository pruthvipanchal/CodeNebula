// CodeNebula - C++98 Example: distance
// Compile: g++ -std=c++98 -Wall -Wextra -o example distance.cpp

// std::distance computes the number of increments needed to go from 'first'
// to 'last'. For random access iterators it is O(1) (subtraction), for
// others it is O(n) (counting increments).

#include <iostream>
#include <iterator>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <string>
#include <algorithm>

int main() {
    // --- distance with vector (random access: O(1)) ---
    std::cout << "=== distance with vector ===" << std::endl;
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80};
    std::vector<int> vec(arr, arr + 8);

    std::cout << "distance(begin, end) = "
              << std::distance(vec.begin(), vec.end()) << std::endl;

    std::vector<int>::iterator it = vec.begin();
    std::advance(it, 3);
    std::cout << "distance(begin, begin+3) = "
              << std::distance(vec.begin(), it) << std::endl;

    std::cout << "distance(begin+3, end) = "
              << std::distance(it, vec.end()) << std::endl;

    // --- distance with list (bidirectional: O(n)) ---
    std::cout << "\n=== distance with list ===" << std::endl;
    std::list<std::string> words;
    words.push_back("one");
    words.push_back("two");
    words.push_back("three");
    words.push_back("four");
    words.push_back("five");

    std::cout << "distance(begin, end) = "
              << std::distance(words.begin(), words.end()) << std::endl;

    std::list<std::string>::iterator lit = words.begin();
    std::advance(lit, 2);
    std::cout << "distance(begin, 3rd element) = "
              << std::distance(words.begin(), lit)
              << " (element: " << *lit << ")" << std::endl;

    // --- distance with set ---
    std::cout << "\n=== distance with set ===" << std::endl;
    std::set<int> s;
    s.insert(50);
    s.insert(10);
    s.insert(30);
    s.insert(20);
    s.insert(40);

    std::cout << "distance(begin, end) = "
              << std::distance(s.begin(), s.end()) << std::endl;

    std::set<int>::iterator sit = s.find(30);
    std::cout << "distance(begin, find(30)) = "
              << std::distance(s.begin(), sit)
              << " (30 is at index " << std::distance(s.begin(), sit) << ")" << std::endl;

    // --- distance with raw pointers ---
    std::cout << "\n=== distance with raw pointers ===" << std::endl;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int* begin_ptr = data;
    int* end_ptr = data + 10;

    std::cout << "distance(begin, end) = "
              << std::distance(begin_ptr, end_ptr) << std::endl;

    int* mid = data + 5;
    std::cout << "distance(begin, mid) = "
              << std::distance(begin_ptr, mid) << std::endl;
    std::cout << "distance(mid, end) = "
              << std::distance(mid, end_ptr) << std::endl;

    // --- Practical: finding the index of an element ---
    std::cout << "\n=== Practical: find index of element ===" << std::endl;
    std::vector<int> nums;
    nums.push_back(100);
    nums.push_back(200);
    nums.push_back(300);
    nums.push_back(400);
    nums.push_back(500);

    std::vector<int>::iterator found = std::find(nums.begin(), nums.end(), 300);
    if (found != nums.end()) {
        std::ptrdiff_t index = std::distance(nums.begin(), found);
        std::cout << "300 found at index: " << index << std::endl;
    }

    found = std::find(nums.begin(), nums.end(), 999);
    if (found == nums.end()) {
        std::cout << "999 not found (would be at index "
                  << std::distance(nums.begin(), found) << " = size)" << std::endl;
    }

    // --- Practical: find index in a list ---
    std::cout << "\n=== Practical: find index in list ===" << std::endl;
    std::list<std::string> names;
    names.push_back("Alice");
    names.push_back("Bob");
    names.push_back("Charlie");
    names.push_back("Diana");

    std::list<std::string>::iterator name_it =
        std::find(names.begin(), names.end(), "Charlie");
    if (name_it != names.end()) {
        std::cout << "Charlie at index: "
                  << std::distance(names.begin(), name_it) << std::endl;
    }

    // --- Practical: counting elements in a range ---
    std::cout << "\n=== Practical: elements in a range ===" << std::endl;
    std::set<int> ordered;
    for (int i = 1; i <= 10; ++i) {
        ordered.insert(i * 10);
    }

    std::set<int>::iterator lb = ordered.lower_bound(30);
    std::set<int>::iterator ub = ordered.upper_bound(70);
    std::cout << "Elements in [30, 70]: "
              << std::distance(lb, ub) << std::endl;

    std::cout << "Elements: ";
    for (std::set<int>::iterator r = lb; r != ub; ++r) {
        std::cout << *r << " ";
    }
    std::cout << std::endl;

    // --- distance with map ---
    std::cout << "\n=== distance with map ===" << std::endl;
    std::map<std::string, int> scores;
    scores["Alice"] = 95;
    scores["Bob"] = 87;
    scores["Charlie"] = 92;
    scores["Diana"] = 88;
    scores["Eve"] = 91;

    std::cout << "Map size via distance: "
              << std::distance(scores.begin(), scores.end()) << std::endl;

    std::map<std::string, int>::iterator charlie = scores.find("Charlie");
    std::cout << "Charlie is entry #"
              << std::distance(scores.begin(), charlie) << " (0-indexed)" << std::endl;

    return 0;
}

/*
Expected output:
=== distance with vector ===
distance(begin, end) = 8
distance(begin, begin+3) = 3
distance(begin+3, end) = 5

=== distance with list ===
distance(begin, end) = 5
distance(begin, 3rd element) = 2 (element: three)

=== distance with set ===
distance(begin, end) = 5
distance(begin, find(30)) = 2 (30 is at index 2)

=== distance with raw pointers ===
distance(begin, end) = 10
distance(begin, mid) = 5
distance(mid, end) = 5

=== Practical: find index of element ===
300 found at index: 2
999 not found (would be at index 5 = size)

=== Practical: find index in list ===
Charlie at index: 2

=== Practical: elements in a range ===
Elements in [30, 70]: 5
Elements: 30 40 50 60 70

=== distance with map ===
Map size via distance: 5
Charlie is entry #2 (0-indexed)
*/
