// CodeNebula - C++20 Example: Coroutines Overview
// Compile: g++ -std=c++20 -Wall -Wextra -o example coroutines.cpp

// C++20 coroutines introduce three new keywords:
//   co_await  — suspend and wait for a result
//   co_yield  — suspend and produce a value
//   co_return — complete the coroutine with a final value
// A function becomes a coroutine if its body uses any of these keywords.

#include <iostream>
#include <coroutine>

// --- A simple Generator coroutine type ---
// Demonstrates co_yield: produces a sequence of values lazily.
struct Generator {
    struct promise_type {
        int current_value;

        Generator get_return_object() {
            return Generator{std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        std::suspend_always yield_value(int value) {
            current_value = value;
            return {};
        }
        void return_void() {}
        void unhandled_exception() { std::terminate(); }
    };

    std::coroutine_handle<promise_type> handle;

    explicit Generator(std::coroutine_handle<promise_type> h) : handle(h) {}
    ~Generator() { if (handle) handle.destroy(); }

    // Non-copyable, movable
    Generator(const Generator&) = delete;
    Generator& operator=(const Generator&) = delete;
    Generator(Generator&& o) noexcept : handle(o.handle) { o.handle = nullptr; }

    bool next() {
        handle.resume();
        return !handle.done();
    }
    int value() const { return handle.promise().current_value; }
};

// A coroutine function using co_yield
Generator count_up_to(int limit) {
    for (int i = 1; i <= limit; ++i) {
        co_yield i;   // suspend, produce a value
    }
    // implicit co_return (return_void)
}

// A coroutine using co_yield for Fibonacci numbers
Generator fibonacci(int count) {
    int a = 0, b = 1;
    for (int i = 0; i < count; ++i) {
        co_yield a;
        int next = a + b;
        a = b;
        b = next;
    }
}

int main() {
    std::cout << "=== C++20 Coroutines Overview ===\n\n";

    // co_yield example: counting
    std::cout << "count_up_to(5): ";
    auto counter = count_up_to(5);
    while (counter.next()) {
        std::cout << counter.value() << " ";
    }
    std::cout << "\n";

    // co_yield example: fibonacci
    std::cout << "fibonacci(8):   ";
    auto fib = fibonacci(8);
    while (fib.next()) {
        std::cout << fib.value() << " ";
    }
    std::cout << "\n";

    std::cout << "\nCoroutine keywords:\n";
    std::cout << "  co_yield  - suspend and produce a value\n";
    std::cout << "  co_await  - suspend and wait for a result\n";
    std::cout << "  co_return - finish with a final value\n";

    return 0;
}

// Expected output:
// === C++20 Coroutines Overview ===
//
// count_up_to(5): 1 2 3 4 5
// fibonacci(8):   0 1 1 2 3 5 8 13
//
// Coroutine keywords:
//   co_yield  - suspend and produce a value
//   co_await  - suspend and wait for a result
//   co_return - finish with a final value
