// CodeNebula - C++20 Example: std::latch (One-shot Barrier)
// Compile: g++ -std=c++20 -Wall -Wextra -pthread -o example latch.cpp

#include <iostream>
#include <latch>
#include <string>
#include <thread>
#include <vector>

int main() {
    std::cout << "=== std::latch - one-shot synchronization ===\n";
    std::cout << "(A latch counts down from N; threads wait until it reaches 0)\n\n";

    constexpr int num_workers = 4;

    // Latch initialized with count = num_workers
    std::latch work_done(num_workers);

    std::cout << "--- Workers starting ---\n";
    std::vector<std::jthread> workers;
    for (int i = 0; i < num_workers; ++i) {
        workers.emplace_back([&work_done, i] {
            // Simulate varying work time
            std::this_thread::sleep_for(std::chrono::milliseconds(20 * (i + 1)));
            std::cout << "Worker " << i << " finished its task\n";
            work_done.count_down();  // Decrement the latch counter
        });
    }

    // Main thread waits until all workers are done
    work_done.wait();
    std::cout << "All workers done! Main thread continues.\n";

    for (auto& w : workers) w.join();

    std::cout << "\n=== Latch as a start gate ===\n";

    std::latch start_gate(1);  // All threads wait on this
    std::latch finish_line(3); // Main waits on this

    auto runner = [&](const std::string& name) {
        std::cout << name << " ready at start line\n";
        start_gate.wait();  // Wait for the start signal
        std::cout << name << " running!\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::cout << name << " finished!\n";
        finish_line.count_down();
    };

    std::jthread r1(runner, "Alice");
    std::jthread r2(runner, "Bob");
    std::jthread r3(runner, "Carol");

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "GO!\n";
    start_gate.count_down();  // Release all runners

    finish_line.wait();  // Wait for all to finish
    std::cout << "All runners crossed the finish line!\n";

    std::cout << "\n=== arrive_and_wait (count_down + wait) ===\n";

    std::latch sync(3);
    auto task = [&sync](int id) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10 * id));
        std::cout << "Task " << id << " arriving and waiting\n";
        sync.arrive_and_wait();  // Atomic count_down + wait
        std::cout << "Task " << id << " proceeding\n";
    };

    std::jthread t1(task, 1);
    std::jthread t2(task, 2);
    std::jthread t3(task, 3);

    return 0;
}
