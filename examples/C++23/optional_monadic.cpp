// CodeNebula - C++23 Example: std::optional Monadic Operations
// Compile: g++ -std=c++23 -Wall -Wextra -o example optional_monadic.cpp
// Note: Requires GCC 13+ / Clang 17+

#include <iostream>
#include <optional>
#include <string>
#include <charconv>

// C++23 adds monadic operations to std::optional:
//   and_then(f) - if has value, call f(value) returning optional (flatmap)
//   transform(f) - if has value, call f(value) and wrap result in optional (map)
//   or_else(f)   - if empty, call f() returning optional (fallback)

// Simulated database/parsing functions returning optional
std::optional<std::string> find_user(int id) {
    if (id == 1) return "Alice";
    if (id == 2) return "Bob";
    return std::nullopt;
}

std::optional<std::string> find_email(const std::string& name) {
    if (name == "Alice") return "alice@example.com";
    return std::nullopt;
}

std::optional<int> parse_int(const std::string& s) {
    int value{};
    auto [ptr, ec] = std::from_chars(s.data(), s.data() + s.size(), value);
    if (ec == std::errc{} && ptr == s.data() + s.size())
        return value;
    return std::nullopt;
}

int main() {
    std::cout << "=== std::optional monadic operations ===\n\n";

    // --- and_then: chain optional-returning functions ---
    std::cout << "--- and_then (flatmap) ---\n";
    auto email1 = find_user(1).and_then(find_email);
    std::cout << "User 1 email: " << email1.value_or("(not found)") << "\n";

    auto email2 = find_user(2).and_then(find_email);
    std::cout << "User 2 email: " << email2.value_or("(not found)") << "\n";

    auto email3 = find_user(99).and_then(find_email);
    std::cout << "User 99 email: " << email3.value_or("(not found)") << "\n\n";

    // --- transform: apply function to value inside optional ---
    std::cout << "--- transform (map) ---\n";
    auto name_len = find_user(1).transform([](const std::string& s) {
        return s.size();
    });
    std::cout << "User 1 name length: " << name_len.value_or(0) << "\n";

    auto upper_name = find_user(1).transform([](std::string s) {
        for (auto& c : s) c = static_cast<char>(std::toupper(c));
        return s;
    });
    std::cout << "User 1 upper: " << upper_name.value_or("N/A") << "\n\n";

    // --- or_else: provide fallback ---
    std::cout << "--- or_else (fallback) ---\n";
    auto user = find_user(99).or_else([]() -> std::optional<std::string> {
        std::cout << "  (user not found, using default)\n";
        return "Guest";
    });
    std::cout << "Result: " << user.value() << "\n\n";

    // --- Chaining all three ---
    std::cout << "--- Chaining and_then + transform + or_else ---\n";
    auto result = parse_int("42")
        .and_then([](int v) -> std::optional<int> {
            return v > 0 ? std::optional{v * 2} : std::nullopt;
        })
        .transform([](int v) { return "Result: " + std::to_string(v); })
        .or_else([]() -> std::optional<std::string> { return "fallback"; });

    std::cout << result.value() << "\n";

    auto bad = parse_int("abc")
        .transform([](int v) { return v * 2; })
        .or_else([]() -> std::optional<int> { return -1; });
    std::cout << "parse_int(\"abc\") chain: " << bad.value() << "\n";

    return 0;
}

// Expected output:
// === std::optional monadic operations ===
//
// --- and_then (flatmap) ---
// User 1 email: alice@example.com
// User 2 email: (not found)
// User 99 email: (not found)
//
// --- transform (map) ---
// User 1 name length: 5
// User 1 upper: ALICE
//
// --- or_else (fallback) ---
//   (user not found, using default)
// Result: Guest
//
// --- Chaining and_then + transform + or_else ---
// Result: 84
// parse_int("abc") chain: -1
