// CodeNebula - C++26 Example: std::execution Senders/Receivers Overview
// Compile: g++ -std=c++26 -Wall -Wextra -o example execution.cpp
// Note: Requires C++26 compiler support

#include <iostream>
#include <functional>
#include <string>

// C++26 introduces std::execution (P2300) — a framework for structured
// asynchronous programming built on three core abstractions:
//
//   Scheduler  - represents an execution context (thread pool, GPU, etc.)
//   Sender     - describes a unit of async work that produces values
//   Receiver   - consumes the result of a sender (value, error, or stopped)
//
// The model: scheduler.schedule() -> sender -> connect(receiver) -> operation
// sync_wait(sender) blocks until the sender completes.

// --- Educational simulation of the sender/receiver model ---
namespace exec_sim {
    // A simple value sender: immediately completes with a value
    template <typename T>
    struct just_sender {
        T value;
        explicit just_sender(T v) : value(std::move(v)) {}
    };

    // Factory: creates a sender that holds a value
    template <typename T>
    just_sender<T> just(T value) { return just_sender<T>{std::move(value)}; }

    // 'then' adaptor: chains a function onto a sender
    template <typename S, typename F>
    struct then_sender {
        S inner;
        F func;
    };

    template <typename S, typename F>
    then_sender<S, F> then(S sender, F func) {
        return {std::move(sender), std::move(func)};
    }

    // sync_wait: "runs" the sender chain and returns the result
    template <typename T>
    T sync_wait(just_sender<T> s) { return s.value; }

    template <typename S, typename F>
    auto sync_wait(then_sender<S, F> s) {
        auto val = sync_wait(std::move(s.inner));
        return s.func(val);
    }
}

int main() {
    // Build a sender pipeline (in real C++26: namespace ex = std::execution;)
    auto work = exec_sim::then(
        exec_sim::then(
            exec_sim::just(10),           // Start with value 10
            [](int v) { return v * 2; }   // Multiply by 2
        ),
        [](int v) { return v + 5; }       // Add 5
    );

    // Execute synchronously
    int result = exec_sim::sync_wait(std::move(work));
    std::cout << "Pipeline result: " << result << "\n";

    // String pipeline
    auto text = exec_sim::then(
        exec_sim::just(std::string("hello")),
        [](std::string s) { s += " world"; return s; }
    );
    std::cout << "Text result: " << exec_sim::sync_wait(std::move(text)) << "\n";

    std::cout << "Sender/receiver model demonstrated successfully.\n";
    return 0;
}

// Expected output:
// Pipeline result: 25
// Text result: hello world
// Sender/receiver model demonstrated successfully.
