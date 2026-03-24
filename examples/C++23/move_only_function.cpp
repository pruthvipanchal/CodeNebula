// CodeNebula - C++23 Example: std::move_only_function
// Compile: g++ -std=c++23 -Wall -Wextra -o example move_only_function.cpp
// Note: Requires GCC 13+ / Clang 17+

#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// std::move_only_function is like std::function but supports non-copyable
// callables. It is itself move-only. It also has const/noexcept qualifiers
// in its signature, unlike std::function which always calls via const.

// A move-only callable: captures a unique_ptr
auto make_greeter(std::string name) {
    auto msg = std::make_unique<std::string>("Hello from " + name + "!");
    return [msg = std::move(msg)]() {
        std::cout << *msg << "\n";
    };
}

// A task queue using move_only_function
class TaskQueue {
    std::vector<std::move_only_function<void()>> tasks_;
public:
    void add(std::move_only_function<void()> task) {
        tasks_.push_back(std::move(task));
    }
    void run_all() {
        for (auto& task : tasks_) {
            task();
        }
        tasks_.clear();
    }
    std::size_t size() const { return tasks_.size(); }
};

int main() {
    std::cout << "=== std::move_only_function ===\n\n";

    // Basic usage with a move-only lambda
    std::move_only_function<void()> fn = make_greeter("Alice");
    std::cout << "Calling move-only function:\n";
    fn();

    // Move to another variable (copying would fail to compile)
    auto fn2 = std::move(fn);
    std::cout << "\nAfter move, calling from new variable:\n";
    fn2();

    // Check that original is empty after move
    std::cout << "Original is empty after move: "
              << (!fn ? "yes" : "no") << "\n";

    // Task queue with heterogeneous move-only tasks
    std::cout << "\n--- Task Queue ---\n";
    TaskQueue queue;

    queue.add(make_greeter("Bob"));
    queue.add([counter = std::make_unique<int>(0)]() mutable {
        ++(*counter);
        std::cout << "Counter task: " << *counter << "\n";
    });
    queue.add([]() {
        std::cout << "Simple lambda task\n";
    });

    std::cout << "Queue has " << queue.size() << " tasks\n";
    queue.run_all();
    std::cout << "Queue has " << queue.size() << " tasks after run_all\n";

    // With return value
    std::move_only_function<int(int, int)> adder = [](int a, int b) {
        return a + b;
    };
    std::cout << "\nadder(3, 4) = " << adder(3, 4) << "\n";

    return 0;
}

// Expected output:
// === std::move_only_function ===
//
// Calling move-only function:
// Hello from Alice!
//
// After move, calling from new variable:
// Hello from Alice!
// Original is empty after move: yes
//
// --- Task Queue ---
// Queue has 3 tasks
// Hello from Bob!
// Counter task: 1
// Simple lambda task
// Queue has 0 tasks after run_all
//
// adder(3, 4) = 7
