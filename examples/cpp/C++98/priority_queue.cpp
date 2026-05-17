// CodeNebula - C++98 Example: priority_queue
// Compile: g++ -std=c++98 -Wall -Wextra -o example priority_queue.cpp

// std::priority_queue is a container adaptor that provides constant-time
// access to the largest (by default) element. It is a max-heap.

#include <iostream>
#include <queue>
#include <vector>
#include <functional> // for std::greater
#include <string>

// Custom comparison functor for priority_queue
// This creates a min-heap based on priority value
struct Task {
    int priority;
    std::string name;

    Task(int p, const std::string& n) : priority(p), name(n) {}
};

// Comparator: higher priority number = lower priority in queue (min-heap style)
// For priority_queue, the comparator returns true if the first arg has LOWER
// priority than the second (i.e., should be placed below in the heap).
struct TaskCompare {
    bool operator()(const Task& a, const Task& b) const {
        // Higher priority number means it should come out LATER
        // So we say a has lower priority if a.priority > b.priority
        return a.priority > b.priority;
    }
};

int main() {
    // --- Default max-heap ---
    std::cout << "=== Default priority_queue (max-heap) ===" << std::endl;
    std::priority_queue<int> maxpq;

    maxpq.push(30);
    maxpq.push(10);
    maxpq.push(50);
    maxpq.push(20);
    maxpq.push(40);

    std::cout << "Pushed: 30, 10, 50, 20, 40" << std::endl;
    std::cout << "Size: " << maxpq.size() << std::endl;
    std::cout << "Top (max): " << maxpq.top() << std::endl;

    std::cout << "\nPopping all (descending order):" << std::endl;
    while (!maxpq.empty()) {
        std::cout << "  " << maxpq.top() << std::endl;
        maxpq.pop();
    }

    // --- Min-heap using std::greater ---
    std::cout << "\n=== Min-heap using std::greater ===" << std::endl;
    std::priority_queue<int, std::vector<int>, std::greater<int> > minpq;

    minpq.push(30);
    minpq.push(10);
    minpq.push(50);
    minpq.push(20);
    minpq.push(40);

    std::cout << "Pushed: 30, 10, 50, 20, 40" << std::endl;
    std::cout << "Top (min): " << minpq.top() << std::endl;

    std::cout << "\nPopping all (ascending order):" << std::endl;
    while (!minpq.empty()) {
        std::cout << "  " << minpq.top() << std::endl;
        minpq.pop();
    }

    // --- Custom comparison with struct ---
    std::cout << "\n=== Custom comparison (Task priority) ===" << std::endl;
    std::priority_queue<Task, std::vector<Task>, TaskCompare> task_queue;

    task_queue.push(Task(3, "Low priority task"));
    task_queue.push(Task(1, "Critical task"));
    task_queue.push(Task(2, "Medium priority task"));
    task_queue.push(Task(1, "Another critical task"));
    task_queue.push(Task(5, "Background task"));

    std::cout << "Processing tasks (lowest priority number first):" << std::endl;
    while (!task_queue.empty()) {
        const Task& t = task_queue.top();
        std::cout << "  [Priority " << t.priority << "] " << t.name << std::endl;
        task_queue.pop();
    }

    // --- Constructing from a range ---
    std::cout << "\n=== Construct from range ===" << std::endl;
    int arr[] = {15, 25, 5, 35, 45};
    std::priority_queue<int> from_arr(arr, arr + 5);

    std::cout << "Built from array {15, 25, 5, 35, 45}:" << std::endl;
    while (!from_arr.empty()) {
        std::cout << "  " << from_arr.top() << std::endl;
        from_arr.pop();
    }

    // --- empty and size ---
    std::cout << "\n=== empty and size ===" << std::endl;
    std::priority_queue<int> pq;
    std::cout << "empty: " << (pq.empty() ? "true" : "false") << std::endl;
    pq.push(42);
    std::cout << "After push: empty=" << (pq.empty() ? "true" : "false")
              << ", size=" << pq.size() << std::endl;

    return 0;
}

/*
Expected output:
=== Default priority_queue (max-heap) ===
Pushed: 30, 10, 50, 20, 40
Size: 5
Top (max): 50

Popping all (descending order):
  50
  40
  30
  20
  10

=== Min-heap using std::greater ===
Pushed: 30, 10, 50, 20, 40
Top (min): 10

Popping all (ascending order):
  10
  20
  30
  40
  50

=== Custom comparison (Task priority) ===
Processing tasks (lowest priority number first):
  [Priority 1] Critical task
  [Priority 1] Another critical task
  [Priority 2] Medium priority task
  [Priority 3] Low priority task
  [Priority 5] Background task

=== Construct from range ===
Built from array {15, 25, 5, 35, 45}:
  45
  35
  25
  15
  5

=== empty and size ===
empty: true
After push: empty=false, size=1
*/
