// CodeNebula - C++26 Example: bulk, split, ensure_started
// Compile: g++ -std=c++26 -Wall -Wextra -o example execution_advanced.cpp
// Note: Requires C++26 compiler support

#include <iostream>
#include <vector>

// Advanced std::execution adaptors in C++26:
//   bulk(sender, count, f)  - parallel for-loop: f(i, value) for i in [0, count)
//   split(sender)           - allows a sender to be consumed multiple times
//   ensure_started(sender)  - eagerly starts work, returns sender with result

namespace exec_sim {
    template <typename T>
    struct just_sender { T value; };
    template <typename T>
    just_sender<T> just(T v) { return {std::move(v)}; }

    template <typename T, typename F>
    auto bulk(just_sender<T> s, std::size_t count, F f) {
        for (std::size_t i = 0; i < count; ++i) f(i, s.value);
        return s;
    }

    template <typename T>
    struct split_sender {
        T value;
        just_sender<T> get() const { return {value}; }
    };
    template <typename T>
    split_sender<T> split(just_sender<T> s) { return {s.value}; }

    template <typename T>
    just_sender<T> ensure_started(just_sender<T> s) {
        std::cout << "  [ensure_started] Work started eagerly\n";
        return s;
    }

    template <typename T>
    T sync_wait(just_sender<T> s) { return s.value; }
}

int main() {
    std::cout << "--- bulk adaptor ---\n";
    exec_sim::bulk(exec_sim::just(10), 5, [](std::size_t i, int val) {
        std::cout << "  bulk[" << i << "]: " << val << " * " << (i+1)
                  << " = " << val * static_cast<int>(i+1) << "\n";
    });

    std::cout << "\n--- split adaptor ---\n";
    auto shared = exec_sim::split(exec_sim::just(42));
    std::cout << "  Consumer 1: " << exec_sim::sync_wait(shared.get()) << "\n";
    std::cout << "  Consumer 2: " << exec_sim::sync_wait(shared.get()) << "\n";

    std::cout << "\n--- ensure_started adaptor ---\n";
    auto eager = exec_sim::ensure_started(exec_sim::just(99));
    std::cout << "  Result: " << exec_sim::sync_wait(eager) << "\n";
    return 0;
}

// Expected output:
// --- bulk adaptor ---
//   bulk[0]: 10 * 1 = 10
//   bulk[1]: 10 * 2 = 20
//   bulk[2]: 10 * 3 = 30
//   bulk[3]: 10 * 4 = 40
//   bulk[4]: 10 * 5 = 50
//
// --- split adaptor ---
//   Consumer 1: 42
//   Consumer 2: 42
//
// --- ensure_started adaptor ---
//   [ensure_started] Work started eagerly
//   Result: 99
