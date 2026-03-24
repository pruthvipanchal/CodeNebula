// CodeNebula - C++20 Example: std::barrier (Reusable Synchronization)
// Compile: g++ -std=c++20 -Wall -Wextra -pthread -o example barrier.cpp

#include <barrier>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

int main() {
    std::cout << "=== std::barrier - reusable synchronization point ===\n";
    std::cout << "(Unlike latch, barrier can be used for multiple phases)\n\n";

    constexpr int num_threads = 3;
    constexpr int num_phases = 3;
    int phase_counter = 0;

    // Completion function runs once per phase when all threads arrive
    auto on_completion = [&phase_counter]() noexcept {
        ++phase_counter;
        std::cout << "--- Phase " << phase_counter << " complete ---\n";
    };

    std::barrier sync_point(num_threads, on_completion);

    auto worker = [&](int id) {
        for (int phase = 0; phase < num_phases; ++phase) {
            // Do phase work
            std::cout << "Thread " << id << " working on phase " << (phase + 1) << "\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(10 * (id + 1)));

            // Wait for all threads to complete this phase
            sync_point.arrive_and_wait();
        }
    };

    std::vector<std::jthread> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(worker, i);
    }

    for (auto& t : threads) t.join();
    std::cout << "All " << num_phases << " phases completed.\n";

    std::cout << "\n=== Barrier with arrive_and_drop ===\n";
    std::cout << "(Thread leaves the barrier, reducing expected count)\n\n";

    int active_count = 3;
    std::barrier shrinking_barrier(3, [&active_count]() noexcept {
        std::cout << "  [Barrier: " << active_count << " threads completed phase]\n";
    });

    auto optional_worker = [&](int id, int phases_to_do) {
        for (int p = 0; p < phases_to_do; ++p) {
            std::cout << "Thread " << id << " phase " << (p + 1) << "\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(15));
            shrinking_barrier.arrive_and_wait();
        }
        if (phases_to_do < 3) {
            // Drop out early - reduces expected count for future phases
            std::cout << "Thread " << id << " dropping out\n";
            --active_count;
            shrinking_barrier.arrive_and_drop();
        }
    };

    std::jthread t0(optional_worker, 0, 3);  // Participates in all 3 phases
    std::jthread t1(optional_worker, 1, 3);  // Participates in all 3 phases
    std::jthread t2(optional_worker, 2, 1);  // Drops out after phase 1

    t0.join();
    t1.join();
    t2.join();
    std::cout << "Done with shrinking barrier example.\n";

    return 0;
}
