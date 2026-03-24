// CodeNebula - C++20 Example: co_yield with Generator Pattern
// Compile: g++ -std=c++20 -Wall -Wextra -o example co_yield.cpp

// co_yield suspends a coroutine and produces a value to the caller.
// This enables lazy generation of sequences — values are computed
// on demand, one at a time, without storing the entire sequence.

#include <iostream>
#include <coroutine>
#include <cstdint>

// A reusable Generator<T> type
template <typename T>
struct Generator {
    struct promise_type {
        T current_value;

        Generator get_return_object() {
            return Generator{std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        std::suspend_always yield_value(T value) {
            current_value = value;
            return {};
        }
        void return_void() {}
        void unhandled_exception() { std::terminate(); }
    };

    std::coroutine_handle<promise_type> handle;

    explicit Generator(std::coroutine_handle<promise_type> h) : handle(h) {}
    ~Generator() { if (handle) handle.destroy(); }
    Generator(const Generator&) = delete;
    Generator(Generator&& o) noexcept : handle(o.handle) { o.handle = nullptr; }
    Generator& operator=(const Generator&) = delete;

    bool next() {
        handle.resume();
        return !handle.done();
    }
    T value() const { return handle.promise().current_value; }
};

// Generator: range of integers
Generator<int> range(int start, int end, int step = 1) {
    for (int i = start; i < end; i += step) {
        co_yield i;
    }
}

// Generator: infinite sequence of powers of two
Generator<std::uint64_t> powers_of_two() {
    std::uint64_t val = 1;
    while (true) {
        co_yield val;
        val *= 2;
    }
}

// Generator: string tokens (character by character)
Generator<char> vowels() {
    for (char c : {'a', 'e', 'i', 'o', 'u'}) {
        co_yield c;
    }
}

// Generator: triangular numbers (1, 3, 6, 10, 15, ...)
Generator<int> triangular_numbers() {
    int sum = 0;
    for (int n = 1; ; ++n) {
        sum += n;
        co_yield sum;
    }
}

int main() {
    std::cout << "=== co_yield Generator Pattern ===\n\n";

    // Range generator
    std::cout << "range(0, 10, 2): ";
    auto r = range(0, 10, 2);
    while (r.next()) std::cout << r.value() << " ";
    std::cout << "\n";

    // Powers of two (take first 10)
    std::cout << "powers_of_two (first 10): ";
    auto p = powers_of_two();
    for (int i = 0; i < 10 && p.next(); ++i)
        std::cout << p.value() << " ";
    std::cout << "\n";

    // Vowels
    std::cout << "vowels: ";
    auto v = vowels();
    while (v.next()) std::cout << v.value() << " ";
    std::cout << "\n";

    // Triangular numbers (first 7)
    std::cout << "triangular (first 7): ";
    auto t = triangular_numbers();
    for (int i = 0; i < 7 && t.next(); ++i)
        std::cout << t.value() << " ";
    std::cout << "\n";

    return 0;
}

// Expected output:
// === co_yield Generator Pattern ===
//
// range(0, 10, 2): 0 2 4 6 8
// powers_of_two (first 10): 1 2 4 8 16 32 64 128 256 512
// vowels: a e i o u
// triangular (first 7): 1 3 6 10 15 21 28
