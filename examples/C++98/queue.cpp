// CodeNebula - C++98 Example: queue
// Compile: g++ -std=c++98 -Wall -Wextra -o example queue.cpp

// std::queue is a container adaptor that provides FIFO (First In, First Out)
// access. By default it uses std::deque as the underlying container.

#include <iostream>
#include <queue>
#include <list>
#include <string>

int main() {
    // --- Basic operations ---
    std::cout << "=== Basic operations ===" << std::endl;
    std::queue<int> q;
    std::cout << "Empty: " << (q.empty() ? "true" : "false") << std::endl;
    std::cout << "Size: " << q.size() << std::endl;

    // --- push ---
    std::cout << "\n=== push ===" << std::endl;
    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);
    q.push(50);
    std::cout << "Pushed: 10, 20, 30, 40, 50" << std::endl;
    std::cout << "Size: " << q.size() << std::endl;

    // --- front and back ---
    std::cout << "\n=== front and back ===" << std::endl;
    std::cout << "front: " << q.front() << std::endl;
    std::cout << "back: " << q.back() << std::endl;

    // front() and back() return references; can modify
    q.front() = 11;
    q.back() = 55;
    std::cout << "After modifying: front=" << q.front() << ", back=" << q.back() << std::endl;

    // --- pop ---
    std::cout << "\n=== pop (FIFO order) ===" << std::endl;
    std::cout << "Popping all elements:" << std::endl;
    while (!q.empty()) {
        std::cout << "  front=" << q.front() << ", size=" << q.size() << std::endl;
        q.pop();
    }
    std::cout << "After popping all: empty=" << (q.empty() ? "true" : "false") << std::endl;

    // --- FIFO demonstration ---
    std::cout << "\n=== FIFO order demonstration ===" << std::endl;
    std::queue<std::string> print_queue;
    print_queue.push("Job A (first in)");
    print_queue.push("Job B");
    print_queue.push("Job C");
    print_queue.push("Job D (last in)");

    std::cout << "Processing print queue (FIFO):" << std::endl;
    while (!print_queue.empty()) {
        std::cout << "  Processing: " << print_queue.front() << std::endl;
        print_queue.pop();
    }

    // --- Queue with list as underlying container ---
    std::cout << "\n=== Queue with list backend ===" << std::endl;
    std::queue<int, std::list<int> > list_queue;
    list_queue.push(100);
    list_queue.push(200);
    list_queue.push(300);
    std::cout << "list-backed queue front: " << list_queue.front() << std::endl;
    std::cout << "list-backed queue back: " << list_queue.back() << std::endl;
    std::cout << "Size: " << list_queue.size() << std::endl;

    // --- Comparison operators ---
    std::cout << "\n=== Comparison operators ===" << std::endl;
    std::queue<int> q1, q2;
    q1.push(1); q1.push(2); q1.push(3);
    q2.push(1); q2.push(2); q2.push(3);
    std::cout << "q1 == q2: " << (q1 == q2 ? "true" : "false") << std::endl;

    q2.push(4);
    std::cout << "After q2.push(4): q1 < q2: " << (q1 < q2 ? "true" : "false") << std::endl;
    std::cout << "q1 != q2: " << (q1 != q2 ? "true" : "false") << std::endl;

    // --- Practical: BFS-like level processing ---
    std::cout << "\n=== Practical: level-by-level processing ===" << std::endl;
    std::queue<int> bfs;
    bfs.push(1);

    int level = 0;
    while (!bfs.empty() && level < 3) {
        int level_size = static_cast<int>(bfs.size());
        std::cout << "Level " << level << ": ";
        for (int i = 0; i < level_size; ++i) {
            int node = bfs.front();
            bfs.pop();
            std::cout << node << " ";
            // Simulate adding children
            if (level < 2) {
                bfs.push(node * 2);
                bfs.push(node * 2 + 1);
            }
        }
        std::cout << std::endl;
        ++level;
    }

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

=== front and back ===
front: 10
back: 50
After modifying: front=11, back=55

=== pop (FIFO order) ===
Popping all elements:
  front=11, size=5
  front=20, size=4
  front=30, size=3
  front=40, size=2
  front=55, size=1
After popping all: empty=true

=== FIFO order demonstration ===
Processing print queue (FIFO):
  Processing: Job A (first in)
  Processing: Job B
  Processing: Job C
  Processing: Job D (last in)

=== Queue with list backend ===
list-backed queue front: 100
list-backed queue back: 300
Size: 3

=== Comparison operators ===
q1 == q2: true
After q2.push(4): q1 < q2: true
q1 != q2: true

=== Practical: level-by-level processing ===
Level 0: 1
Level 1: 2 3
Level 2: 4 5 6 7
*/
