// CodeNebula - C++98 Example: list
// Compile: g++ -std=c++98 -Wall -Wextra -o example list.cpp

// std::list is a doubly-linked list. It provides constant-time insertion
// and removal anywhere in the sequence, but no random access.

#include <iostream>
#include <list>

// Helper to print a list
void print_list(const std::string& label, const std::list<int>& lst) {
    std::cout << label << ": ";
    for (std::list<int>::const_iterator it = lst.begin(); it != lst.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

// Predicate for remove_if: remove even numbers
bool is_even(int val) {
    return val % 2 == 0;
}

// Comparison for sort: descending
bool descending(int a, int b) {
    return a > b;
}

int main() {
    // --- push_back and push_front ---
    std::cout << "=== push_back and push_front ===" << std::endl;
    std::list<int> lst;
    lst.push_back(10);
    lst.push_back(20);
    lst.push_back(30);
    lst.push_front(5);
    lst.push_front(1);
    print_list("After pushes", lst);

    // --- front and back ---
    std::cout << "\n=== front and back ===" << std::endl;
    std::cout << "front: " << lst.front() << std::endl;
    std::cout << "back: " << lst.back() << std::endl;

    // --- Bidirectional iteration ---
    std::cout << "\n=== Bidirectional iteration ===" << std::endl;
    std::cout << "Forward: ";
    for (std::list<int>::iterator it = lst.begin(); it != lst.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Reverse: ";
    for (std::list<int>::reverse_iterator rit = lst.rbegin(); rit != lst.rend(); ++rit) {
        std::cout << *rit << " ";
    }
    std::cout << std::endl;

    // --- insert ---
    std::cout << "\n=== insert ===" << std::endl;
    std::list<int>::iterator pos = lst.begin();
    ++pos; ++pos; // advance to third element
    lst.insert(pos, 7);
    print_list("After insert 7 at position 2", lst);

    // --- erase ---
    std::cout << "\n=== erase ===" << std::endl;
    pos = lst.begin();
    ++pos; // second element
    lst.erase(pos);
    print_list("After erase at position 1", lst);

    // --- sort (member function) ---
    std::cout << "\n=== sort ===" << std::endl;
    lst.sort();
    print_list("After sort (ascending)", lst);

    lst.sort(descending);
    print_list("After sort (descending)", lst);

    // --- reverse ---
    std::cout << "\n=== reverse ===" << std::endl;
    lst.reverse();
    print_list("After reverse", lst);

    // --- remove ---
    std::cout << "\n=== remove ===" << std::endl;
    lst.push_back(10);
    lst.push_back(10);
    print_list("Before remove(10)", lst);
    lst.remove(10);
    print_list("After remove(10)", lst);

    // --- remove_if ---
    std::cout << "\n=== remove_if ===" << std::endl;
    lst.push_back(2);
    lst.push_back(4);
    lst.push_back(6);
    print_list("Before remove_if(even)", lst);
    lst.remove_if(is_even);
    print_list("After remove_if(even)", lst);

    // --- splice ---
    std::cout << "\n=== splice ===" << std::endl;
    std::list<int> other;
    other.push_back(100);
    other.push_back(200);
    other.push_back(300);
    print_list("lst before splice", lst);
    print_list("other before splice", other);

    // Splice entire other list into lst at the beginning
    lst.splice(lst.begin(), other);
    print_list("lst after splice", lst);
    std::cout << "other size after splice: " << other.size() << std::endl;

    // --- unique (removes consecutive duplicates) ---
    std::cout << "\n=== unique ===" << std::endl;
    std::list<int> dup;
    dup.push_back(1);
    dup.push_back(1);
    dup.push_back(2);
    dup.push_back(2);
    dup.push_back(2);
    dup.push_back(3);
    dup.push_back(1);
    print_list("Before unique", dup);
    dup.unique();
    print_list("After unique", dup);

    // --- merge (merges two sorted lists) ---
    std::cout << "\n=== merge ===" << std::endl;
    std::list<int> a;
    a.push_back(1);
    a.push_back(3);
    a.push_back(5);
    std::list<int> b;
    b.push_back(2);
    b.push_back(4);
    b.push_back(6);
    print_list("a", a);
    print_list("b", b);
    a.merge(b);
    print_list("After a.merge(b)", a);
    std::cout << "b size after merge: " << b.size() << std::endl;

    // --- size and empty ---
    std::cout << "\n=== size and empty ===" << std::endl;
    std::cout << "a.size() = " << a.size() << std::endl;
    std::cout << "b.empty() = " << (b.empty() ? "true" : "false") << std::endl;

    return 0;
}

/*
Expected output:
=== push_back and push_front ===
After pushes: 1 5 10 20 30

=== front and back ===
front: 1
back: 30

=== Bidirectional iteration ===
Forward: 1 5 10 20 30
Reverse: 30 20 10 5 1

=== insert ===
After insert 7 at position 2: 1 5 7 10 20 30

=== erase ===
After erase at position 1: 1 7 10 20 30

=== sort ===
After sort (ascending): 1 7 10 20 30
After sort (descending): 30 20 10 7 1

=== reverse ===
After reverse: 1 7 10 20 30

=== remove ===
Before remove(10): 1 7 10 20 30 10 10
After remove(10): 1 7 20 30

=== remove_if ===
Before remove_if(even): 1 7 20 30 2 4 6
After remove_if(even): 1 7

=== splice ===
lst before splice: 1 7
other before splice: 100 200 300
lst after splice: 100 200 300 1 7
other size after splice: 0

=== unique ===
Before unique: 1 1 2 2 2 3 1
After unique: 1 2 3 1

=== merge ===
a: 1 3 5
b: 2 4 6
After a.merge(b): 1 2 3 4 5 6
b size after merge: 0

=== size and empty ===
a.size() = 6
b.empty() = true
*/
