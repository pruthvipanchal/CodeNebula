// CodeNebula - C++98 Example: stack
// Compile: g++ -std=c++98 -Wall -Wextra -o example stack.cpp

// std::stack is a container adaptor that provides LIFO (Last In, First Out)
// access. By default it uses std::deque as the underlying container.

#include <iostream>
#include <stack>
#include <vector>
#include <list>

int main() {
    // --- Basic operations ---
    std::cout << "=== Basic operations ===" << std::endl;
    std::stack<int> s;

    std::cout << "Empty: " << (s.empty() ? "true" : "false") << std::endl;
    std::cout << "Size: " << s.size() << std::endl;

    // --- push ---
    std::cout << "\n=== push ===" << std::endl;
    s.push(10);
    s.push(20);
    s.push(30);
    s.push(40);
    s.push(50);
    std::cout << "Pushed: 10, 20, 30, 40, 50" << std::endl;
    std::cout << "Size: " << s.size() << std::endl;
    std::cout << "Top: " << s.top() << std::endl;

    // --- top (read and modify) ---
    std::cout << "\n=== top ===" << std::endl;
    std::cout << "Current top: " << s.top() << std::endl;
    s.top() = 55; // top() returns a reference, so we can modify it
    std::cout << "After s.top() = 55: " << s.top() << std::endl;

    // --- pop ---
    std::cout << "\n=== pop ===" << std::endl;
    std::cout << "Popping all elements:" << std::endl;
    while (!s.empty()) {
        std::cout << "  top=" << s.top() << ", size=" << s.size() << std::endl;
        s.pop();
    }
    std::cout << "After popping all: empty=" << (s.empty() ? "true" : "false") << std::endl;

    // --- LIFO demonstration ---
    std::cout << "\n=== LIFO order demonstration ===" << std::endl;
    std::stack<std::string> plates;
    plates.push("Plate A (first in)");
    plates.push("Plate B");
    plates.push("Plate C");
    plates.push("Plate D (last in)");

    std::cout << "Removing plates (LIFO):" << std::endl;
    while (!plates.empty()) {
        std::cout << "  " << plates.top() << std::endl;
        plates.pop();
    }

    // --- Stack with vector as underlying container ---
    std::cout << "\n=== Stack with vector backend ===" << std::endl;
    std::stack<int, std::vector<int> > vec_stack;
    vec_stack.push(100);
    vec_stack.push(200);
    vec_stack.push(300);
    std::cout << "vector-backed stack top: " << vec_stack.top() << std::endl;
    std::cout << "Size: " << vec_stack.size() << std::endl;

    // --- Stack with list as underlying container ---
    std::cout << "\n=== Stack with list backend ===" << std::endl;
    std::stack<int, std::list<int> > list_stack;
    list_stack.push(1);
    list_stack.push(2);
    list_stack.push(3);
    std::cout << "list-backed stack top: " << list_stack.top() << std::endl;

    // --- Practical example: bracket matching ---
    std::cout << "\n=== Practical: bracket matching ===" << std::endl;
    std::string expr = "((a+b)*(c-d))";
    std::stack<char> brackets;
    bool valid = true;

    std::cout << "Expression: " << expr << std::endl;
    for (std::string::size_type i = 0; i < expr.size(); ++i) {
        if (expr[i] == '(') {
            brackets.push(expr[i]);
        } else if (expr[i] == ')') {
            if (brackets.empty()) {
                valid = false;
                break;
            }
            brackets.pop();
        }
    }
    if (!brackets.empty()) {
        valid = false;
    }
    std::cout << "Brackets balanced: " << (valid ? "true" : "false") << std::endl;

    // --- Comparison operators ---
    std::cout << "\n=== Comparison operators ===" << std::endl;
    std::stack<int> s1, s2;
    s1.push(1); s1.push(2); s1.push(3);
    s2.push(1); s2.push(2); s2.push(3);
    std::cout << "s1 == s2: " << (s1 == s2 ? "true" : "false") << std::endl;

    s2.push(4);
    std::cout << "After s2.push(4): s1 < s2: " << (s1 < s2 ? "true" : "false") << std::endl;
    std::cout << "s1 != s2: " << (s1 != s2 ? "true" : "false") << std::endl;

    return 0;
}

/*
Expected output:
=== Basic operations ===
Empty: true
Size: 0

=== push ===
Pushed: 10, 20, 30, 40, 50
Size: 5
Top: 50

=== top ===
Current top: 50
After s.top() = 55: 55

=== pop ===
Popping all elements:
  top=55, size=5
  top=40, size=4
  top=30, size=3
  top=20, size=2
  top=10, size=1
After popping all: empty=true

=== LIFO order demonstration ===
Removing plates (LIFO):
  Plate D (last in)
  Plate C
  Plate B
  Plate A (first in)

=== Stack with vector backend ===
vector-backed stack top: 300
Size: 3

=== Stack with list backend ===
list-backed stack top: 3

=== Practical: bracket matching ===
Expression: ((a+b)*(c-d))
Brackets balanced: true

=== Comparison operators ===
s1 == s2: true
After s2.push(4): s1 < s2: true
s1 != s2: true
*/
