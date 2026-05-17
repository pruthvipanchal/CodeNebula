// CodeNebula - C++26 Example: std::optional::and_then in C++26 Context
// Compile: g++ -std=c++26 -Wall -Wextra -o example optional_and_then.cpp
// Note: Requires C++26 compiler support

#include <iostream>
#include <optional>
#include <string>
#include <charconv>
#include <cmath>

// C++23 added optional monadic ops (and_then, transform, or_else).
// C++26 improves: full constexpr, better expected interop, ref forwarding.
//   and_then(f): flatmap (f returns optional)
//   transform(f): map (f returns value, wrapped in optional)
//   or_else(f): recovery (f returns optional when empty)

std::optional<int> parse_int(const std::string& s) {
    int result = 0;
    auto [ptr, ec] = std::from_chars(s.data(), s.data() + s.size(), result);
    if (ec != std::errc{} || ptr != s.data() + s.size()) return std::nullopt;
    return result;
}

std::optional<int> validate_positive(int v) { return v > 0 ? std::optional{v} : std::nullopt; }

std::optional<double> safe_sqrt(int v) {
    return v >= 0 ? std::optional{std::sqrt(static_cast<double>(v))} : std::nullopt;
}

int main() {
    std::cout << "--- std::optional::and_then (C++26) ---\n\n";

    // Success chain: parse -> validate -> sqrt
    auto ok = parse_int("49").and_then(validate_positive).and_then(safe_sqrt);
    std::cout << "parse(\"49\") | validate | sqrt = " << ok.value_or(-1.0) << "\n";

    // Fail at parse
    auto f1 = parse_int("abc").and_then(validate_positive).and_then(safe_sqrt);
    std::cout << "parse(\"abc\") | ... = " << (f1 ? std::to_string(*f1) : "nullopt") << "\n";

    // Fail at validate
    auto f2 = parse_int("-5").and_then(validate_positive);
    std::cout << "parse(\"-5\") | validate = " << (f2 ? std::to_string(*f2) : "nullopt") << "\n";

    // transform
    auto dbl = parse_int("21").transform([](int v) { return v * 2; });
    std::cout << "\ntransform(*2): " << dbl.value_or(0) << "\n";

    // or_else: fallback
    auto fb = parse_int("bad").or_else([]() -> std::optional<int> { return 0; });
    std::cout << "or_else fallback: " << fb.value_or(-1) << "\n";

    std::cout << "\nC++26: optional monadic ops are fully constexpr.\n";
    return 0;
}

// Expected output:
// --- std::optional::and_then (C++26) ---
//
// parse("49") | validate | sqrt = 7
// parse("abc") | ... = nullopt
// parse("-5") | validate = nullopt
//
// transform(*2): 42
// or_else fallback: 0
//
// C++26: optional monadic ops are fully constexpr.
