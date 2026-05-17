// CodeNebula - C++98 Example: advance
// Compile: g++ -std=c++98 -Wall -Wextra -o example advance.cpp

// std::advance moves an iterator by n positions. It automatically uses the
// most efficient method: O(1) for random access, O(n) for bidirectional/forward.
// Unlike it + n, std::advance works with ALL iterator categories.

#include <iostream>
#include <iterator>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <string>

int main() {
    // --- advance with vector (random access: O(1)) ---
    std::cout << "=== advance with vector ===" << std::endl;
    int arr[] = {10, 20, 30, 40, 50, 60, 70};
    std::vector<int> vec(arr, arr + 7);

    std::vector<int>::iterator vit = vec.begin();
    std::cout << "Start: " << *vit << std::endl;

    std::advance(vit, 3);
    std::cout << "After advance(3): " << *vit << std::endl;

    std::advance(vit, 2);
    std::cout << "After advance(2): " << *vit << std::endl;

    std::advance(vit, -4);
    std::cout << "After advance(-4): " << *vit << std::endl;

    // --- advance with list (bidirectional: O(n), supports negative) ---
    std::cout << "\n=== advance with list ===" << std::endl;
    std::list<std::string> words;
    words.push_back("alpha");
    words.push_back("beta");
    words.push_back("gamma");
    words.push_back("delta");
    words.push_back("epsilon");

    std::list<std::string>::iterator lit = words.begin();
    std::cout << "Start: " << *lit << std::endl;

    std::advance(lit, 2);
    std::cout << "After advance(2): " << *lit << std::endl;

    std::advance(lit, -1);
    std::cout << "After advance(-1): " << *lit << std::endl;

    std::advance(lit, 3);
    std::cout << "After advance(3): " << *lit << std::endl;

    // --- advance with set (bidirectional) ---
    std::cout << "\n=== advance with set ===" << std::endl;
    std::set<int> s;
    s.insert(100);
    s.insert(200);
    s.insert(300);
    s.insert(400);
    s.insert(500);

    std::set<int>::iterator sit = s.begin();
    std::cout << "Start: " << *sit << std::endl;

    std::advance(sit, 3);
    std::cout << "After advance(3): " << *sit << std::endl;

    std::advance(sit, -2);
    std::cout << "After advance(-2): " << *sit << std::endl;

    // --- advance with map ---
    std::cout << "\n=== advance with map ===" << std::endl;
    std::map<std::string, int> scores;
    scores["Alice"] = 95;
    scores["Bob"] = 87;
    scores["Charlie"] = 92;
    scores["Diana"] = 88;

    std::map<std::string, int>::iterator mit = scores.begin();
    std::cout << "Start: " << mit->first << "=" << mit->second << std::endl;

    std::advance(mit, 2);
    std::cout << "After advance(2): " << mit->first << "=" << mit->second << std::endl;

    // --- advance with raw pointers ---
    std::cout << "\n=== advance with raw pointers ===" << std::endl;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int* ptr = data;
    std::cout << "Start: " << *ptr << std::endl;

    std::advance(ptr, 5);
    std::cout << "After advance(5): " << *ptr << std::endl;

    std::advance(ptr, -3);
    std::cout << "After advance(-3): " << *ptr << std::endl;

    // --- Practical: accessing nth element of any container ---
    std::cout << "\n=== Practical: nth element access ===" << std::endl;

    // Get the 3rd element of a list (can't use list[2])
    std::list<int> numbers;
    numbers.push_back(11);
    numbers.push_back(22);
    numbers.push_back(33);
    numbers.push_back(44);
    numbers.push_back(55);

    std::list<int>::iterator nth = numbers.begin();
    std::advance(nth, 2); // 0-indexed, so advance 2 = 3rd element
    std::cout << "3rd element of list: " << *nth << std::endl;

    // Get the 4th element of a set
    std::set<int> ordered;
    ordered.insert(50);
    ordered.insert(10);
    ordered.insert(30);
    ordered.insert(20);
    ordered.insert(40);

    std::set<int>::iterator nth_set = ordered.begin();
    std::advance(nth_set, 3);
    std::cout << "4th smallest in set: " << *nth_set << std::endl;

    // --- Practical: erase range using advance ---
    std::cout << "\n=== Practical: erase range ===" << std::endl;
    std::list<int> erase_list;
    for (int i = 1; i <= 8; ++i) {
        erase_list.push_back(i * 10);
    }

    std::cout << "Before erase: ";
    for (std::list<int>::iterator it = erase_list.begin();
         it != erase_list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Erase elements at positions 2 through 4
    std::list<int>::iterator erase_begin = erase_list.begin();
    std::advance(erase_begin, 2);
    std::list<int>::iterator erase_end = erase_begin;
    std::advance(erase_end, 3);
    erase_list.erase(erase_begin, erase_end);

    std::cout << "After erasing positions 2-4: ";
    for (std::list<int>::iterator it = erase_list.begin();
         it != erase_list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // --- advance modifies in place (no return value) ---
    std::cout << "\n=== Note: advance modifies in place ===" << std::endl;
    std::cout << "std::advance returns void." << std::endl;
    std::cout << "It modifies the iterator passed to it." << std::endl;
    std::cout << "For a non-modifying version, C++11 has std::next/std::prev." << std::endl;
    std::cout << "In C++98, we can write helper functions (see next.cpp, prev.cpp)." << std::endl;

    return 0;
}

/*
Expected output:
=== advance with vector ===
Start: 10
After advance(3): 40
After advance(2): 60
After advance(-4): 20

=== advance with list ===
Start: alpha
After advance(2): gamma
After advance(-1): beta
After advance(3): epsilon

=== advance with set ===
Start: 100
After advance(3): 400
After advance(-2): 200

=== advance with map ===
Start: Alice=95
After advance(2): Charlie=92

=== advance with raw pointers ===
Start: 1
After advance(5): 6
After advance(-3): 3

=== Practical: nth element access ===
3rd element of list: 33
4th smallest in set: 40

=== Practical: erase range ===
Before erase: 10 20 30 40 50 60 70 80
After erasing positions 2-4: 10 20 60 70 80

=== Note: advance modifies in place ===
std::advance returns void.
It modifies the iterator passed to it.
For a non-modifying version, C++11 has std::next/std::prev.
In C++98, we can write helper functions (see next.cpp, prev.cpp).
*/
