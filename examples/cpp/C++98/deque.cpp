// CodeNebula - C++98 Example: deque
// Compile: g++ -std=c++98 -Wall -Wextra -o example deque.cpp

// std::deque (double-ended queue) supports fast insertion and removal
// at both ends, plus random access to elements.

#include <iostream>
#include <deque>

void print_deque(const std::string& label, const std::deque<int>& dq) {
    std::cout << label << ": ";
    for (std::deque<int>::const_iterator it = dq.begin(); it != dq.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "(size=" << dq.size() << ")" << std::endl;
}

int main() {
    // --- Construction ---
    std::cout << "=== Construction ===" << std::endl;
    std::deque<int> dq;
    std::deque<int> dq2(5, 77);
    print_deque("Empty deque", dq);
    print_deque("dq2(5, 77)", dq2);

    // --- push_back and push_front ---
    std::cout << "\n=== push_back and push_front ===" << std::endl;
    dq.push_back(10);
    dq.push_back(20);
    dq.push_back(30);
    print_deque("After push_back 10,20,30", dq);

    dq.push_front(5);
    dq.push_front(1);
    print_deque("After push_front 5,1", dq);

    // --- pop_back and pop_front ---
    std::cout << "\n=== pop_back and pop_front ===" << std::endl;
    dq.pop_back();
    print_deque("After pop_back", dq);

    dq.pop_front();
    print_deque("After pop_front", dq);

    // --- Random access ---
    std::cout << "\n=== Random access ===" << std::endl;
    std::cout << "dq[0] = " << dq[0] << std::endl;
    std::cout << "dq[1] = " << dq[1] << std::endl;
    std::cout << "dq.at(2) = " << dq.at(2) << std::endl;
    std::cout << "dq.front() = " << dq.front() << std::endl;
    std::cout << "dq.back() = " << dq.back() << std::endl;

    // --- Modification via index ---
    std::cout << "\n=== Modification via index ===" << std::endl;
    dq[0] = 99;
    dq.at(1) = 88;
    print_deque("After dq[0]=99, dq.at(1)=88", dq);

    // --- Insert and erase ---
    std::cout << "\n=== Insert and erase ===" << std::endl;
    dq.insert(dq.begin() + 1, 555);
    print_deque("After insert 555 at pos 1", dq);

    dq.erase(dq.begin() + 1);
    print_deque("After erase at pos 1", dq);

    // --- Iteration ---
    std::cout << "\n=== Iteration ===" << std::endl;
    // Rebuild for cleaner output
    dq.clear();
    for (int i = 1; i <= 6; ++i) {
        dq.push_back(i * 10);
    }

    std::cout << "Forward:  ";
    for (std::deque<int>::iterator it = dq.begin(); it != dq.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Reverse:  ";
    for (std::deque<int>::reverse_iterator rit = dq.rbegin(); rit != dq.rend(); ++rit) {
        std::cout << *rit << " ";
    }
    std::cout << std::endl;

    std::cout << "By index: ";
    for (std::deque<int>::size_type i = 0; i < dq.size(); ++i) {
        std::cout << dq[i] << " ";
    }
    std::cout << std::endl;

    // --- resize ---
    std::cout << "\n=== resize ===" << std::endl;
    dq.resize(3);
    print_deque("After resize(3)", dq);

    dq.resize(6, 0);
    print_deque("After resize(6, 0)", dq);

    // --- swap ---
    std::cout << "\n=== swap ===" << std::endl;
    std::deque<int> other(3, 42);
    print_deque("dq before swap", dq);
    print_deque("other before swap", other);
    dq.swap(other);
    print_deque("dq after swap", dq);
    print_deque("other after swap", other);

    // --- empty and clear ---
    std::cout << "\n=== empty and clear ===" << std::endl;
    std::cout << "dq.empty() = " << (dq.empty() ? "true" : "false") << std::endl;
    dq.clear();
    std::cout << "After clear: dq.empty() = " << (dq.empty() ? "true" : "false") << std::endl;

    return 0;
}

/*
Expected output:
=== Construction ===
Empty deque: (size=0)
dq2(5, 77): 77 77 77 77 77 (size=5)

=== push_back and push_front ===
After push_back 10,20,30: 10 20 30 (size=3)
After push_front 5,1: 1 5 10 20 30 (size=5)

=== pop_back and pop_front ===
After pop_back: 1 5 10 20 (size=4)
After pop_front: 5 10 20 (size=3)

=== Random access ===
dq[0] = 5
dq[1] = 10
dq.at(2) = 20
dq.front() = 5
dq.back() = 20

=== Modification via index ===
After dq[0]=99, dq.at(1)=88: 99 88 20 (size=3)

=== Insert and erase ===
After insert 555 at pos 1: 99 555 88 20 (size=4)
After erase at pos 1: 99 88 20 (size=3)

=== Iteration ===
Forward:  10 20 30 40 50 60
Reverse:  60 50 40 30 20 10
By index: 10 20 30 40 50 60

=== resize ===
After resize(3): 10 20 30 (size=3)
After resize(6, 0): 10 20 30 0 0 0 (size=6)

=== swap ===
dq before swap: 10 20 30 0 0 0 (size=6)
other before swap: 42 42 42 (size=3)
dq after swap: 42 42 42 (size=3)
other after swap: 10 20 30 0 0 0 (size=6)

=== empty and clear ===
dq.empty() = false
After clear: dq.empty() = true
*/
