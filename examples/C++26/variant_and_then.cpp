// CodeNebula - C++26 Example: std::variant::and_then in C++26 Context
// Compile: g++ -std=c++26 -Wall -Wextra -o example variant_and_then.cpp
// Note: Requires C++26 compiler support

#include <iostream>
#include <variant>
#include <string>

// C++26 proposes monadic operations for std::variant:
//   variant.visit(f) - member visit (replaces free std::visit)
//   transform(var,f) - map the held value
// These enable composable pipelines similar to optional/expected.

namespace var_sim {
    template <typename V, typename F>
    auto visit(V&& var, F&& f) {
        return std::visit(std::forward<F>(f), std::forward<V>(var));
    }
    template <typename... Ts, typename F>
    auto transform(const std::variant<Ts...>& var, F f) {
        return std::visit([&](const auto& v) -> std::variant<Ts...> {
            return f(v);
        }, var);
    }
}

using Value = std::variant<int, double, std::string>;

std::string describe(const Value& v) {
    return var_sim::visit(v, [](const auto& val) -> std::string {
        using T = std::decay_t<decltype(val)>;
        if constexpr (std::is_same_v<T, int>) return "int(" + std::to_string(val) + ")";
        else if constexpr (std::is_same_v<T, double>) return "double(" + std::to_string(val) + ")";
        else return "string(\"" + val + "\")";
    });
}

int main() {
    std::cout << "--- std::variant Monadic Ops (C++26) ---\n\n";
    Value v1 = 42; Value v2 = 3.14; Value v3 = std::string("hello");
    std::cout << "v1: " << describe(v1) << "\n";
    std::cout << "v2: " << describe(v2) << "\n";
    std::cout << "v3: " << describe(v3) << "\n";

    // Transform: double numeric values
    std::cout << "\n--- Transform ---\n";
    auto doubled = var_sim::transform(v1, [](const auto& val) -> Value {
        using T = std::decay_t<decltype(val)>;
        if constexpr (std::is_arithmetic_v<T>) return static_cast<T>(val * 2);
        else return val;
    });
    std::cout << "transform(42, *2) = " << describe(doubled) << "\n";

    // Visitor dispatch
    std::cout << "\n--- Dispatch ---\n";
    for (const auto& v : {Value{10}, Value{2.5}, Value{std::string("C++26")}}) {
        var_sim::visit(v, [](const auto& val) {
            using T = std::decay_t<decltype(val)>;
            if constexpr (std::is_same_v<T, int>) std::cout << "  Int: " << val << "\n";
            else if constexpr (std::is_same_v<T, double>) std::cout << "  Dbl: " << val << "\n";
            else std::cout << "  Str: " << val << "\n";
        });
    }
    std::cout << "\nC++26: variant gains composable monadic operations.\n";
    return 0;
}

// Expected output:
// --- std::variant Monadic Ops (C++26) ---
//
// v1: int(42)
// v2: double(3.140000)
// v3: string("hello")
//
// --- Transform ---
// transform(42, *2) = int(84)
//
// --- Dispatch ---
//   Int: 10
//   Dbl: 2.5
//   Str: C++26
//
// C++26: variant gains composable monadic operations.
