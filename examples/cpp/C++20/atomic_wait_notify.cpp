// CodeNebula - C++20 Example: std::atomic::wait, notify_one, notify_all
// Compile: g++ -std=c++20 -Wall -Wextra -pthread -o example atomic_wait_notify.cpp

#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

int main() {
    std::cout << "=== std::atomic wait/notify ===\n";
    std::cout << "(Efficient blocking without spinning or condition_variable)\n\n";

    // atomic::wait(old) blocks until the value differs from old
    // atomic::notify_one() wakes one waiting thread
    // atomic::notify_all() wakes all waiting threads

    std::cout << "--- Basic wait/notify_one ---\n";
    std::atomic<int> value{0};

    std::jthread waiter([&value] {
        std::cout << "Waiter: waiting for value != 0\n";
        value.wait(0);  // Block until value is not 0
        std::cout << "Waiter: woke up, value = " << value.load() << "\n";
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "Main: setting value to 42\n";
    value.store(42);
    value.notify_one();

    waiter.join();

    std::cout << "\n--- notify_all: waking multiple waiters ---\n";
    std::atomic<int> phase{0};

    auto phase_worker = [&phase](int id) {
        std::cout << "Worker " << id << " waiting for phase 1\n";
        phase.wait(0);
        std::cout << "Worker " << id << " entered phase 1 (value="
                  << phase.load() << ")\n";
    };

    std::vector<std::jthread> workers;
    for (int i = 0; i < 4; ++i) {
        workers.emplace_back(phase_worker, i);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "Main: advancing to phase 1\n";
    phase.store(1);
    phase.notify_all();  // Wake ALL waiters

    for (auto& w : workers) w.join();

    std::cout << "\n--- Multi-phase protocol ---\n";
    std::atomic<int> state{0};
    // States: 0=init, 1=data_ready, 2=data_processed, 3=done

    std::jthread producer([&state] {
        std::cout << "Producer: preparing data\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        state.store(1);
        state.notify_one();

        state.wait(1);  // Wait until consumer processes
        std::cout << "Producer: consumer processed, finalizing\n";
        state.store(3);
        state.notify_one();
    });

    std::jthread consumer([&state] {
        state.wait(0);  // Wait for data_ready
        std::cout << "Consumer: processing data (state="
                  << state.load() << ")\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        state.store(2);
        state.notify_one();

        state.wait(2);  // Wait for done
        std::cout << "Consumer: done (state=" << state.load() << ")\n";
    });

    producer.join();
    consumer.join();

    std::cout << "\n--- Atomic bool for simple signaling ---\n";
    std::atomic<bool> ready{false};

    std::jthread signal_thread([&ready] {
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        ready.store(true);
        ready.notify_all();
    });

    ready.wait(false);
    std::cout << "Signal received!\n";

    return 0;
}
