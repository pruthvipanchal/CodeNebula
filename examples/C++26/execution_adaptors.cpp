// CodeNebula - C++26 Example: then, when_all, let_value Adaptors
// Compile: g++ -std=c++26 -Wall -Wextra -o example execution_adaptors.cpp
// Note: Requires C++26 compiler support

#include <iostream>
#include <functional>
#include <string>
#include <tuple>

// C++26 std::execution provides sender adaptors to build async pipelines:
//
//   then(sender, f)       - transforms the result: f(value) -> new_value
//   when_all(s1, s2, ...) - waits for all senders, delivers tuple of results
//   let_value(sender, f)  - like then, but f returns a new sender (flatmap)

namespace exec_sim {
    template <typename T>
    struct just_sender { T value; };

    template <typename T>
    just_sender<T> just(T v) { return {std::move(v)}; }

    // then: transform the value
    template <typename S, typename F>
    auto then(S s, F f) {
        auto result = f(s.value);
        return just(result);
    }

    // when_all: combine multiple senders into one producing a tuple
    template <typename S1, typename S2>
    auto when_all(S1 s1, S2 s2) {
        return just(std::make_tuple(s1.value, s2.value));
    }

    template <typename S1, typename S2, typename S3>
    auto when_all(S1 s1, S2 s2, S3 s3) {
        return just(std::make_tuple(s1.value, s2.value, s3.value));
    }

    // let_value: flatmap — function returns a sender
    template <typename S, typename F>
    auto let_value(S s, F f) {
        return f(s.value);  // f returns a sender
    }

    // sync_wait: extract the value
    template <typename T>
    T sync_wait(just_sender<T> s) { return s.value; }
}

int main() {
    std::cout << "--- then adaptor ---\n";
    auto s1 = exec_sim::then(exec_sim::just(7), [](int v) { return v * 3; });
    std::cout << "just(7) | then(*3) = " << exec_sim::sync_wait(s1) << "\n";

    std::cout << "\n--- when_all adaptor ---\n";
    auto combined = exec_sim::when_all(
        exec_sim::just(10),
        exec_sim::just(20),
        exec_sim::just(30)
    );
    auto [a, b, c] = exec_sim::sync_wait(combined);
    std::cout << "when_all(10, 20, 30) = (" << a << ", " << b << ", " << c << ")\n";

    std::cout << "\n--- let_value adaptor ---\n";
    // let_value: the function receives a value and returns a new sender
    auto lv = exec_sim::let_value(exec_sim::just(5), [](int v) {
        // Based on v, produce a new computation
        return exec_sim::then(exec_sim::just(v), [](int x) { return x * x + 1; });
    });
    std::cout << "let_value(5, x -> x*x+1) = " << exec_sim::sync_wait(lv) << "\n";

    std::cout << "\n--- Chained pipeline ---\n";
    auto pipeline = exec_sim::then(
        exec_sim::then(exec_sim::just(2), [](int v) { return v + 8; }),
        [](int v) { return v * v; }
    );
    std::cout << "just(2) | then(+8) | then(^2) = " << exec_sim::sync_wait(pipeline) << "\n";

    return 0;
}

// Expected output:
// --- then adaptor ---
// just(7) | then(*3) = 21
//
// --- when_all adaptor ---
// when_all(10, 20, 30) = (10, 20, 30)
//
// --- let_value adaptor ---
// let_value(5, x -> x*x+1) = 26
//
// --- Chained pipeline ---
// just(2) | then(+8) | then(^2) = 100
