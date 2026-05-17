// CodeNebula - C++20 Example: co_return with Task/Future Pattern
// Compile: g++ -std=c++20 -Wall -Wextra -o example co_return.cpp

// co_return completes a coroutine and optionally provides a final value.
// It is the coroutine equivalent of 'return'. The value goes through
// the promise_type's return_value() or return_void() method.

#include <iostream>
#include <coroutine>
#include <string>

// --- Task<T>: a coroutine that produces a single result via co_return ---
template <typename T>
struct Task {
    struct promise_type {
        T result;
        std::exception_ptr exception = nullptr;

        Task get_return_object() {
            return Task{std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void return_value(T value) { result = std::move(value); }
        void unhandled_exception() { exception = std::current_exception(); }
    };

    std::coroutine_handle<promise_type> handle;

    explicit Task(std::coroutine_handle<promise_type> h) : handle(h) {}
    ~Task() { if (handle) handle.destroy(); }
    Task(const Task&) = delete;
    Task(Task&& o) noexcept : handle(o.handle) { o.handle = nullptr; }
    Task& operator=(const Task&) = delete;

    T result() const {
        if (handle.promise().exception)
            std::rethrow_exception(handle.promise().exception);
        return handle.promise().result;
    }
};

// --- VoidTask: a coroutine that completes without a value ---
struct VoidTask {
    struct promise_type {
        bool completed = false;
        VoidTask get_return_object() {
            return VoidTask{std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void return_void() { completed = true; }
        void unhandled_exception() { std::terminate(); }
    };

    std::coroutine_handle<promise_type> handle;
    explicit VoidTask(std::coroutine_handle<promise_type> h) : handle(h) {}
    ~VoidTask() { if (handle) handle.destroy(); }
    VoidTask(const VoidTask&) = delete;
    VoidTask(VoidTask&& o) noexcept : handle(o.handle) { o.handle = nullptr; }
    VoidTask& operator=(const VoidTask&) = delete;

    bool completed() const { return handle.promise().completed; }
};

// Coroutine returning an int via co_return
Task<int> compute_sum(int a, int b) {
    std::cout << "  Computing " << a << " + " << b << "...\n";
    co_return a + b;
}

// Coroutine returning a string via co_return
Task<std::string> greet(const std::string& name) {
    std::cout << "  Building greeting for " << name << "...\n";
    co_return "Hello, " + name + "!";
}

// Coroutine with conditional co_return
Task<int> safe_divide(int a, int b) {
    if (b == 0) {
        std::cout << "  Division by zero — returning -1\n";
        co_return -1;  // early co_return
    }
    std::cout << "  Computing " << a << " / " << b << "...\n";
    co_return a / b;
}

// Void coroutine using co_return (no value)
VoidTask log_message(const std::string& msg) {
    std::cout << "  [LOG] " << msg << "\n";
    co_return;  // completes without a value
}

int main() {
    std::cout << "=== co_return with Task Pattern ===\n\n";

    auto sum = compute_sum(10, 20);
    std::cout << "Result: " << sum.result() << "\n\n";

    auto greeting = greet("C++20");
    std::cout << "Result: " << greeting.result() << "\n\n";

    auto div1 = safe_divide(100, 7);
    std::cout << "Result: " << div1.result() << "\n\n";

    auto div2 = safe_divide(42, 0);
    std::cout << "Result: " << div2.result() << "\n\n";

    auto log = log_message("Task completed successfully");
    std::cout << "Void task completed: " << std::boolalpha << log.completed() << "\n";

    return 0;
}

// Expected output:
// === co_return with Task Pattern ===
//
//   Computing 10 + 20...
// Result: 30
//
//   Building greeting for C++20...
// Result: Hello, C++20!
//
//   Computing 100 / 7...
// Result: 14
//
//   Division by zero — returning -1
// Result: -1
//
//   [LOG] Task completed successfully
// Void task completed: true
