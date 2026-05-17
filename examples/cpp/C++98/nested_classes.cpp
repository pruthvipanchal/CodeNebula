// CodeNebula - C++98 Example: Nested Classes
// Compile: g++ -std=c++98 -Wall -Wextra -o example nested_classes.cpp
//
// This example demonstrates:
// - Defining a class inside another class
// - Access rules: nested class CAN access outer class's members (with object)
// - Outer class can access nested class's private members (in C++98, this
//   depends on the compiler; the standard made it official in C++11, but most
//   C++98 compilers allow it when the nested class is in scope)
// - Nested classes for encapsulation: hiding implementation details
// - Practical use: Node inside a container, State inside a state machine

#include <iostream>
#include <cstring>

// ============================================================
// 1. Basic nested class
// ============================================================
class Outer {
private:
    int outerData;

public:
    Outer(int v) : outerData(v) {}

    // Nested class defined INSIDE Outer
    class Inner {
    private:
        int innerData;
    public:
        Inner(int v) : innerData(v) {}

        void show() const {
            std::cout << "  Inner::innerData = " << innerData << std::endl;
        }

        // Inner can access Outer's private members IF given an Outer object
        void showOuter(const Outer& o) const {
            std::cout << "  Accessing Outer::outerData = " << o.outerData << std::endl;
        }
    };

    void demo() const {
        Inner i(100);
        i.show();
        i.showOuter(*this);
    }
};

// ============================================================
// 2. Practical: Stack with nested Node
// ============================================================
class Stack {
private:
    // Node is an implementation detail -- hidden from users of Stack
    struct Node {
        int   data;
        Node* next;
        Node(int d, Node* n) : data(d), next(n) {}
    };

    Node* top_;
    int   size_;

public:
    Stack() : top_(NULL), size_(0) {}

    ~Stack() {
        while (top_ != NULL) {
            Node* temp = top_;
            top_ = top_->next;
            delete temp;
        }
    }

    void push(int value) {
        top_ = new Node(value, top_);
        ++size_;
    }

    int pop() {
        if (top_ == NULL) {
            std::cout << "  ERROR: stack is empty!" << std::endl;
            return -1;
        }
        int value = top_->data;
        Node* temp = top_;
        top_ = top_->next;
        delete temp;
        --size_;
        return value;
    }

    int peek() const {
        if (top_ == NULL) {
            std::cout << "  ERROR: stack is empty!" << std::endl;
            return -1;
        }
        return top_->data;
    }

    bool empty() const { return top_ == NULL; }
    int  size() const  { return size_; }

    void print() const {
        std::cout << "  Stack [top->bottom]: ";
        Node* n = top_;
        while (n != NULL) {
            std::cout << n->data;
            if (n->next != NULL) std::cout << " -> ";
            n = n->next;
        }
        if (top_ == NULL) std::cout << "(empty)";
        std::cout << std::endl;
    }
};

// ============================================================
// 3. State Machine with nested State classes
// ============================================================
class TrafficLight {
public:
    // Nested: represents a traffic light state
    class State {
    private:
        char name[16];
        int  durationSec;
        char nextState[16];

    public:
        State() : durationSec(0) {
            name[0] = '\0';
            nextState[0] = '\0';
        }

        State(const char* n, int dur, const char* next) : durationSec(dur) {
            std::strncpy(name, n, 15);
            name[15] = '\0';
            std::strncpy(nextState, next, 15);
            nextState[15] = '\0';
        }

        const char* getName() const { return name; }
        int getDuration() const { return durationSec; }
        const char* getNextName() const { return nextState; }

        void display() const {
            std::cout << "  [" << name << "] duration=" << durationSec
                      << "s, next=" << nextState << std::endl;
        }
    };

private:
    State states[3];
    int   currentIndex;

    int findState(const char* name) const {
        for (int i = 0; i < 3; ++i) {
            if (std::strcmp(states[i].getName(), name) == 0) {
                return i;
            }
        }
        return -1;
    }

public:
    TrafficLight() : currentIndex(0) {
        states[0] = State("GREEN",  30, "YELLOW");
        states[1] = State("YELLOW", 5,  "RED");
        states[2] = State("RED",    20, "GREEN");
    }

    void showCurrent() const {
        std::cout << "  Current: ";
        states[currentIndex].display();
    }

    void advance() {
        const char* nextName = states[currentIndex].getNextName();
        int nextIdx = findState(nextName);
        if (nextIdx >= 0) {
            currentIndex = nextIdx;
        }
    }

    // Expose nested type for external use
    State getCurrentState() const { return states[currentIndex]; }
};

// ============================================================
// 4. Nested class with public access (used externally)
// ============================================================
class Matrix {
public:
    // Publicly nested: users can create Matrix::Dimensions
    class Dimensions {
    public:
        int rows;
        int cols;

        Dimensions(int r, int c) : rows(r), cols(c) {}

        void print() const {
            std::cout << "  " << rows << " x " << cols << std::endl;
        }
    };

private:
    Dimensions dims;
    double*    data;

public:
    Matrix(int r, int c) : dims(r, c), data(new double[r * c]) {
        for (int i = 0; i < r * c; ++i) {
            data[i] = 0.0;
        }
    }

    ~Matrix() { delete[] data; }

    Dimensions getDimensions() const { return dims; }

    void set(int r, int c, double val) {
        if (r >= 0 && r < dims.rows && c >= 0 && c < dims.cols) {
            data[r * dims.cols + c] = val;
        }
    }

    double get(int r, int c) const {
        if (r >= 0 && r < dims.rows && c >= 0 && c < dims.cols) {
            return data[r * dims.cols + c];
        }
        return 0.0;
    }

    void print() const {
        for (int r = 0; r < dims.rows; ++r) {
            std::cout << "  | ";
            for (int c = 0; c < dims.cols; ++c) {
                std::cout << get(r, c) << " ";
            }
            std::cout << "|" << std::endl;
        }
    }
};

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "1. BASIC NESTED CLASS" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        Outer o(42);
        o.demo();

        // Can also create Inner from outside using scope resolution
        Outer::Inner i(200);
        i.show();
        i.showOuter(o);
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "2. STACK WITH NESTED NODE (hidden implementation)" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        Stack s;
        s.push(10);
        s.push(20);
        s.push(30);
        s.print();

        std::cout << "  peek: " << s.peek() << std::endl;
        std::cout << "  pop:  " << s.pop() << std::endl;
        std::cout << "  pop:  " << s.pop() << std::endl;
        s.print();

        // Stack::Node n;  // COMPILE ERROR: Node is private
        std::cout << "  Stack::Node n;  // COMPILE ERROR: Node is private" << std::endl;
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "3. TRAFFIC LIGHT STATE MACHINE" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        TrafficLight tl;

        for (int cycle = 0; cycle < 6; ++cycle) {
            tl.showCurrent();
            tl.advance();
        }

        // Use the nested State type externally
        TrafficLight::State st = tl.getCurrentState();
        std::cout << "  Final state: " << st.getName() << std::endl;
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "4. MATRIX WITH PUBLIC NESTED DIMENSIONS" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        Matrix m(3, 3);
        m.set(0, 0, 1.0);
        m.set(1, 1, 2.0);
        m.set(2, 2, 3.0);

        std::cout << "  Matrix dimensions: ";
        Matrix::Dimensions d = m.getDimensions();
        d.print();

        m.print();

        // Create Dimensions independently
        Matrix::Dimensions custom(4, 5);
        std::cout << "  Custom dimensions: ";
        custom.print();
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "5. KEY POINTS" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "  - Nested classes are defined inside another class" << std::endl;
    std::cout << "  - Access from outside: Outer::Inner (if public)" << std::endl;
    std::cout << "  - Private nested classes hide implementation details" << std::endl;
    std::cout << "  - Nested class can access outer's private members (via object)" << std::endl;
    std::cout << "  - Common uses: Node in containers, State in state machines," << std::endl;
    std::cout << "    Iterator in collections, Impl in Pimpl pattern" << std::endl;

    return 0;
}

// Expected output:
// ========================================
// 1. BASIC NESTED CLASS
// ========================================
//   Inner::innerData = 100
//   Accessing Outer::outerData = 42
//   Inner::innerData = 200
//   Accessing Outer::outerData = 42
//
// ========================================
// 2. STACK WITH NESTED NODE
// ========================================
//   Stack [top->bottom]: 30 -> 20 -> 10
//   peek: 30
//   pop:  30
//   pop:  20
//   Stack [top->bottom]: 10
//   Stack::Node n;  // COMPILE ERROR: Node is private
//
// ========================================
// 3. TRAFFIC LIGHT STATE MACHINE
// ========================================
//   Current: [GREEN] duration=30s, next=YELLOW
//   Current: [YELLOW] duration=5s, next=RED
//   Current: [RED] duration=20s, next=GREEN
//   Current: [GREEN] duration=30s, next=YELLOW
//   Current: [YELLOW] duration=5s, next=RED
//   Current: [RED] duration=20s, next=GREEN
//   Final state: GREEN
//
// ========================================
// 4. MATRIX WITH PUBLIC NESTED DIMENSIONS
// ========================================
//   Matrix dimensions:   3 x 3
//   | 1 0 0 |
//   | 0 2 0 |
//   | 0 0 3 |
//   Custom dimensions:   4 x 5
