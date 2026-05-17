// CodeNebula - C++98 Example: Class Templates
// Compile: g++ -std=c++98 -Wall -Wextra -o example class_templates.cpp

// Class templates allow creating generic data structures that work with any
// type. This example implements a Stack<T> with push, pop, top, size, and
// isEmpty, plus a Pair<T,U> template to show multi-parameter templates.

#include <iostream>
#include <string>
#include <cstdlib>  // for exit()

// ------------------------------------------------------------------
// Template class: Stack<T>
// A simple fixed-capacity stack backed by an array.
// ------------------------------------------------------------------
template <typename T>
class Stack {
private:
    static const int MAX_SIZE = 100;
    T data[MAX_SIZE];
    int count;

public:
    // Constructor
    Stack() : count(0) {}

    // Push an element onto the stack
    void push(const T& value) {
        if (count >= MAX_SIZE) {
            std::cerr << "Error: Stack overflow!" << std::endl;
            return;
        }
        data[count] = value;
        ++count;
    }

    // Pop the top element off the stack
    void pop() {
        if (count <= 0) {
            std::cerr << "Error: Stack underflow!" << std::endl;
            return;
        }
        --count;
    }

    // Return a reference to the top element
    T& top() {
        if (count <= 0) {
            std::cerr << "Error: top() called on empty stack!" << std::endl;
            std::exit(1);
        }
        return data[count - 1];
    }

    const T& top() const {
        if (count <= 0) {
            std::cerr << "Error: top() called on empty stack!" << std::endl;
            std::exit(1);
        }
        return data[count - 1];
    }

    // Return the number of elements
    int size() const {
        return count;
    }

    // Check if the stack is empty
    bool isEmpty() const {
        return count == 0;
    }

    // Print all elements from bottom to top
    void print() const {
        std::cout << "Stack [bottom->top]: ";
        for (int i = 0; i < count; ++i) {
            std::cout << data[i];
            if (i < count - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }
};

// ------------------------------------------------------------------
// Template class with two type parameters: Pair<T, U>
// ------------------------------------------------------------------
template <typename T, typename U>
class Pair {
private:
    T first;
    U second;

public:
    Pair(const T& f, const U& s) : first(f), second(s) {}

    T getFirst() const { return first; }
    U getSecond() const { return second; }

    void setFirst(const T& f) { first = f; }
    void setSecond(const U& s) { second = s; }

    void print() const {
        std::cout << "(" << first << ", " << second << ")";
    }
};

// ------------------------------------------------------------------
// Helper function template that works with the Stack class template
// ------------------------------------------------------------------
template <typename T>
void drainStack(Stack<T>& s) {
    std::cout << "Draining stack: ";
    while (!s.isEmpty()) {
        std::cout << s.top();
        s.pop();
        if (!s.isEmpty()) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "=== C++98 Class Templates ===" << std::endl;

    // --- Stack<int> ---
    std::cout << "\n--- Stack<int> ---" << std::endl;
    Stack<int> intStack;

    std::cout << "isEmpty: " << (intStack.isEmpty() ? "true" : "false") << std::endl;
    // Expected: true

    intStack.push(10);
    intStack.push(20);
    intStack.push(30);
    intStack.print();
    // Expected: Stack [bottom->top]: 10, 20, 30

    std::cout << "top:  " << intStack.top() << std::endl;
    // Expected: 30
    std::cout << "size: " << intStack.size() << std::endl;
    // Expected: 3

    intStack.pop();
    std::cout << "After pop, top: " << intStack.top() << std::endl;
    // Expected: 20

    // --- Stack<std::string> ---
    std::cout << "\n--- Stack<std::string> ---" << std::endl;
    Stack<std::string> strStack;
    strStack.push("hello");
    strStack.push("world");
    strStack.push("C++98");
    strStack.print();
    // Expected: Stack [bottom->top]: hello, world, C++98

    drainStack(strStack);
    // Expected: Draining stack: C++98 -> world -> hello

    std::cout << "isEmpty after drain: "
              << (strStack.isEmpty() ? "true" : "false") << std::endl;
    // Expected: true

    // --- Stack<double> ---
    std::cout << "\n--- Stack<double> ---" << std::endl;
    Stack<double> dblStack;
    dblStack.push(1.1);
    dblStack.push(2.2);
    dblStack.push(3.3);
    dblStack.print();
    // Expected: Stack [bottom->top]: 1.1, 2.2, 3.3

    // --- Pair<T,U> ---
    std::cout << "\n--- Pair<T,U> ---" << std::endl;

    Pair<std::string, int> student("Alice", 95);
    std::cout << "Student: ";
    student.print();
    std::cout << std::endl;
    // Expected: (Alice, 95)

    Pair<int, double> coord(3, 4.5);
    std::cout << "Coord:   ";
    coord.print();
    std::cout << std::endl;
    // Expected: (3, 4.5)

    // Modify a pair
    student.setSecond(100);
    std::cout << "Updated: ";
    student.print();
    std::cout << std::endl;
    // Expected: (Alice, 100)

    // Stack of Pairs
    std::cout << "\n--- Stack<Pair<string,int>> ---" << std::endl;
    Stack< Pair<std::string, int> > pairStack;  // note the space before >
    pairStack.push(Pair<std::string, int>("Alice", 90));
    pairStack.push(Pair<std::string, int>("Bob", 85));

    std::cout << "Top pair: ";
    pairStack.top().print();
    std::cout << std::endl;
    // Expected: (Bob, 85)

    return 0;
}

/*
Expected Output:
=== C++98 Class Templates ===

--- Stack<int> ---
isEmpty: true
Stack [bottom->top]: 10, 20, 30
top:  30
size: 3
After pop, top: 20

--- Stack<std::string> ---
Stack [bottom->top]: hello, world, C++98
Draining stack: C++98 -> world -> hello
isEmpty after drain: true

--- Stack<double> ---
Stack [bottom->top]: 1.1, 2.2, 3.3

--- Pair<T,U> ---
Student: (Alice, 95)
Coord:   (3, 4.5)
Updated: (Alice, 100)

--- Stack<Pair<string,int>> ---
Top pair: (Bob, 85)
*/
