// CodeNebula - C++26 Example: std::expected Monadic Improvements
// Compile: g++ -std=c++26 -Wall -Wextra -o example expected_monadic.cpp
// Note: Requires C++26 compiler support

#include <iostream>
#include <string>
#include <functional>

// C++23 added std::expected with and_then, transform, or_else, transform_error.
// C++26 improves with: fully constexpr chains, optional interop, better CTAD.

namespace sim {
    template <typename T, typename E>
    class expected {
        bool has_val_; union { T val_; E err_; };
    public:
        expected(T v) : has_val_(true), val_(std::move(v)) {}
        struct unexpected_tag {};
        expected(unexpected_tag, E e) : has_val_(false), err_(std::move(e)) {}
        ~expected() { if (has_val_) val_.~T(); else err_.~E(); }
        bool has_value() const { return has_val_; }
        const T& value() const { return val_; }
        const E& error() const { return err_; }

        template <typename F>
        auto and_then(F f) const -> decltype(f(val_)) {
            if (has_val_) return f(val_);
            using R = decltype(f(val_));
            return R(typename R::unexpected_tag{}, err_);
        }
        template <typename F>
        auto transform(F f) const -> expected<decltype(f(val_)), E> {
            if (has_val_) return {f(val_)};
            return {unexpected_tag{}, err_};
        }
        template <typename F>
        auto or_else(F f) const -> expected {
            if (has_val_) return *this; return f(err_);
        }
    };
    template <typename T, typename E>
    expected<T, E> make_unexpected(E e) {
        return expected<T, E>(typename expected<T, E>::unexpected_tag{}, std::move(e));
    }
}

int main() {
    std::cout << "--- std::expected Monadic (C++26) ---\n\n";
    using Result = sim::expected<int, std::string>;

    auto parse = [](const std::string& s) -> Result {
        if (s.empty()) return sim::make_unexpected<int, std::string>("empty input");
        return std::stoi(s);
    };
    auto validate = [](int v) -> Result {
        if (v < 0) return sim::make_unexpected<int, std::string>("negative");
        return v;
    };

    auto ok = parse("42").and_then(validate).transform([](int v) { return v * 2; });
    std::cout << "Success: " << ok.value() << "\n";

    auto err = parse("").and_then(validate);
    std::cout << "Error:   \"" << err.error() << "\"\n";

    auto recovered = parse("").or_else([](const std::string&) -> Result { return 0; });
    std::cout << "Recover: " << recovered.value() << "\n";
    std::cout << "\nC++26 makes these chains fully constexpr.\n";
    return 0;
}

// Expected output:
// --- std::expected Monadic (C++26) ---
//
// Success: 84
// Error:   "empty input"
// Recover: 0
//
// C++26 makes these chains fully constexpr.
