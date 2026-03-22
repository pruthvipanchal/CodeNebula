// CodeNebula - C++98 Example: Friend Classes
// Compile: g++ -std=c++98 -Wall -Wextra -o example friend_classes.cpp
//
// This example demonstrates:
// - Declaring an entire class as a friend
// - The friend class can access all private/protected members
// - Friendship is one-directional (A friends B != B friends A)
// - Friendship is NOT inherited by derived classes
// - Practical use cases: Iterator pattern, Builder pattern

#include <iostream>
#include <cstring>

// ============================================================
// 1. Basic friend class: Engine and Mechanic
// ============================================================
class Engine {
private:
    int horsepower;
    double temperature;
    bool running;

    // Only Mechanic (and Engine itself) can see internals
    friend class Mechanic;

public:
    Engine(int hp) : horsepower(hp), temperature(20.0), running(false) {}

    void start() {
        running = true;
        temperature = 90.0;
        std::cout << "  Engine started (" << horsepower << " HP)" << std::endl;
    }

    void stop() {
        running = false;
        temperature = 20.0;
        std::cout << "  Engine stopped" << std::endl;
    }

    // Public interface -- limited info
    bool isRunning() const { return running; }
};

class Mechanic {
private:
    char name[32];

public:
    Mechanic(const char* n) {
        std::strncpy(name, n, 31);
        name[31] = '\0';
    }

    // Can access ALL private members of Engine
    void diagnose(const Engine& e) const {
        std::cout << "  Mechanic " << name << " diagnosing engine:" << std::endl;
        std::cout << "    Horsepower:  " << e.horsepower << std::endl;
        std::cout << "    Temperature: " << e.temperature << " C" << std::endl;
        std::cout << "    Running:     " << (e.running ? "yes" : "no") << std::endl;
    }

    void tuneUp(Engine& e) const {
        std::cout << "  Mechanic " << name << " tuning engine..." << std::endl;
        e.horsepower += 10;  // direct access to private member
        std::cout << "    New horsepower: " << e.horsepower << std::endl;
    }
};

// ============================================================
// 2. Friendship is ONE-DIRECTIONAL
// ============================================================
class ClassA {
private:
    int secretA;
    friend class ClassB;  // ClassB can access ClassA's privates

public:
    ClassA(int v) : secretA(v) {}

    void tryAccessB() const {
        // ClassB b(99);
        // b.secretB;  // ERROR: ClassA is NOT a friend of ClassB
        std::cout << "  ClassA CANNOT access ClassB's privates" << std::endl;
    }
};

class ClassB {
private:
    int secretB;

public:
    ClassB(int v) : secretB(v) {}

    void accessA(const ClassA& a) const {
        // ClassB IS a friend of ClassA -- can access secretA
        std::cout << "  ClassB accesses ClassA's secretA = " << a.secretA << std::endl;
    }
};

// ============================================================
// 3. Friendship is NOT inherited
// ============================================================
class Secret {
private:
    int value;
    friend class Trusted;

public:
    Secret(int v) : value(v) {}
};

class Trusted {
public:
    void access(const Secret& s) const {
        std::cout << "  Trusted accesses Secret value = " << s.value << std::endl;
    }
};

class UntrustedChild : public Trusted {
public:
    void tryAccess(const Secret& s) const {
        // s.value;  // ERROR: friendship is NOT inherited
        // UntrustedChild is NOT a friend of Secret
        (void)s;  // suppress unused warning
        std::cout << "  UntrustedChild CANNOT access Secret value" << std::endl;
    }
};

// ============================================================
// 4. Practical: LinkedList with friend Iterator
// ============================================================
class LinkedList {
private:
    struct Node {
        int    data;
        Node*  next;
        Node(int d, Node* n) : data(d), next(n) {}
    };

    Node* head;
    int   count;

    friend class ListIterator;  // Iterator needs access to Node

public:
    LinkedList() : head(NULL), count(0) {}

    ~LinkedList() {
        Node* current = head;
        while (current != NULL) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    void pushFront(int value) {
        head = new Node(value, head);
        ++count;
    }

    int size() const { return count; }

    void print() const {
        std::cout << "  [";
        Node* n = head;
        while (n != NULL) {
            if (n != head) std::cout << " -> ";
            std::cout << n->data;
            n = n->next;
        }
        std::cout << "]" << std::endl;
    }
};

class ListIterator {
private:
    LinkedList::Node* current;  // accesses private Node type

public:
    ListIterator(const LinkedList& list) : current(list.head) {}  // accesses private head

    bool hasNext() const {
        return current != NULL;
    }

    int next() {
        int val = current->data;  // accesses private Node::data
        current = current->next;
        return val;
    }

    void reset(const LinkedList& list) {
        current = list.head;
    }
};

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "1. BASIC FRIEND CLASS (Engine & Mechanic)" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        Engine e(200);
        Mechanic m("Bob");

        m.diagnose(e);
        std::cout << std::endl;

        e.start();
        m.diagnose(e);
        std::cout << std::endl;

        m.tuneUp(e);
        m.diagnose(e);
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "2. FRIENDSHIP IS ONE-DIRECTIONAL" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        ClassA a(42);
        ClassB b(99);

        b.accessA(a);     // OK: ClassB is friend of ClassA
        a.tryAccessB();   // ClassA is NOT friend of ClassB
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "3. FRIENDSHIP IS NOT INHERITED" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        Secret s(777);
        Trusted t;
        UntrustedChild uc;

        t.access(s);       // OK: Trusted is a friend
        uc.tryAccess(s);   // NOT OK: friendship not inherited
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "4. PRACTICAL: LINKED LIST + ITERATOR" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        LinkedList list;
        list.pushFront(30);
        list.pushFront(20);
        list.pushFront(10);

        std::cout << "  List: ";
        list.print();
        std::cout << "  Size: " << list.size() << std::endl;

        std::cout << "  Iterating with ListIterator:" << std::endl;
        ListIterator it(list);
        std::cout << "  ";
        while (it.hasNext()) {
            std::cout << it.next() << " ";
        }
        std::cout << std::endl;

        // Sum using iterator
        it.reset(list);
        int sum = 0;
        while (it.hasNext()) {
            sum += it.next();
        }
        std::cout << "  Sum = " << sum << std::endl;
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "5. SUMMARY" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "  - 'friend class X;' grants X full access to private members" << std::endl;
    std::cout << "  - One-directional: A friends B does NOT mean B friends A" << std::endl;
    std::cout << "  - NOT inherited: child of friend is NOT a friend" << std::endl;
    std::cout << "  - NOT transitive: friend of friend is NOT a friend" << std::endl;
    std::cout << "  - Use sparingly: tight coupling, but sometimes necessary" << std::endl;
    std::cout << "  - Common uses: iterators, builders, serializers, test classes" << std::endl;

    return 0;
}

// Expected output:
// ========================================
// 1. BASIC FRIEND CLASS (Engine & Mechanic)
// ========================================
//   Mechanic Bob diagnosing engine:
//     Horsepower:  200
//     Temperature: 20 C
//     Running:     no
//
//   Engine started (200 HP)
//   Mechanic Bob diagnosing engine:
//     Horsepower:  200
//     Temperature: 90 C
//     Running:     yes
//
//   Mechanic Bob tuning engine...
//     New horsepower: 210
//   ...
//
// ========================================
// 2. FRIENDSHIP IS ONE-DIRECTIONAL
// ========================================
//   ClassB accesses ClassA's secretA = 42
//   ClassA CANNOT access ClassB's privates
//
// ========================================
// 3. FRIENDSHIP IS NOT INHERITED
// ========================================
//   Trusted accesses Secret value = 777
//   UntrustedChild CANNOT access Secret value
//
// ========================================
// 4. PRACTICAL: LINKED LIST + ITERATOR
// ========================================
//   List:   [10 -> 20 -> 30]
//   Size: 3
//   Iterating with ListIterator:
//   10 20 30
//   Sum = 60
