// CodeNebula - C++20 Example: co_await with a Simple Awaitable
// Compile: g++ -std=c++20 -Wall -Wextra -o example co_await.cpp

// co_await suspends a coroutine until an awaitable object is ready.
// An awaitable must provide: await_ready(), await_suspend(), await_resume().

#include <iostream>
#include <coroutine>

// --- Task type: a coroutine that co_awaits and produces a result ---
struct Task {
    struct promise_type {
        int result = 0;

        Task get_return_object() {
            return Task{std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void return_value(int v) { result = v; }
        void unhandled_exception() { std::terminate(); }
    };

    std::coroutine_handle<promise_type> handle;

    explicit Task(std::coroutine_handle<promise_type> h) : handle(h) {}
    ~Task() { if (handle) handle.destroy(); }
    Task(const Task&) = delete;
    Task(Task&& o) noexcept : handle(o.handle) { o.handle = nullptr; }
    Task& operator=(const Task&) = delete;

    int result() const { return handle.promise().result; }
};

// --- Custom awaitable: simulates an async computation ---
struct ComputeAwaitable {
    int input;
    int computed_result = 0;

    // await_ready: return true if result is already available (no suspend)
    bool await_ready() const noexcept {
        std::cout << "  await_ready() called — checking if ready\n";
        return false;  // not ready, must suspend
    }

    // await_suspend: called when the coroutine suspends
    void await_suspend(std::coroutine_handle<> h) noexcept {
        std::cout << "  await_suspend() called — computing result\n";
        computed_result = input * input + 1;  // simulate async work
        h.resume();  // resume immediately (in real code, a scheduler would do this)
    }

    // await_resume: return the result when the coroutine resumes
    int await_resume() const noexcept {
        std::cout << "  await_resume() called — returning " << computed_result << "\n";
        return computed_result;
    }
};

// A coroutine that uses co_await
Task compute_and_add(int a, int b) {
    std::cout << "Awaiting computation for " << a << "...\n";
    int result_a = co_await ComputeAwaitable{a};

    std::cout << "Awaiting computation for " << b << "...\n";
    int result_b = co_await ComputeAwaitable{b};

    std::cout << "Both computations done.\n";
    co_return result_a + result_b;
}

// Demonstrate co_await with std::suspend_always / std::suspend_never
Task trivial_awaits() {
    std::cout << "\nTrivial awaits:\n";
    co_await std::suspend_never{};   // does not suspend
    std::cout << "  After suspend_never — no suspension occurred\n";
    co_return 42;
}

int main() {
    std::cout << "=== co_await with Custom Awaitable ===\n\n";

    auto task1 = compute_and_add(3, 5);
    std::cout << "Final result: " << task1.result() << "\n";
    // 3*3+1 = 10, 5*5+1 = 26, sum = 36

    auto task2 = trivial_awaits();
    std::cout << "Trivial result: " << task2.result() << "\n";

    return 0;
}

// Expected output:
// === co_await with Custom Awaitable ===
//
// Awaiting computation for 3...
//   await_ready() called — checking if ready
//   await_suspend() called — computing result
//   await_resume() called — returning 10
// Awaiting computation for 5...
//   await_ready() called — checking if ready
//   await_suspend() called — computing result
//   await_resume() called — returning 26
// Both computations done.
// Final result: 36
//
// Trivial awaits:
//   After suspend_never — no suspension occurred
// Trivial result: 42
