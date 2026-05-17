// CodeNebula - C++26 Example: Structured Bindings in Conditions
// Compile: g++ -std=c++26 -Wall -Wextra -o example structured_bindings_conditions.cpp
// Note: Requires C++26 compiler support (GCC 15+ / Clang 19+ expected)

// C++26 allows structured bindings in if and switch conditions.
// This combines declaration and boolean testing in one statement,
// similar to how if(auto x = expr) already works for single values.

#include <iostream>
#include <map>
#include <string>
#include <optional>
#include <tuple>

// --- C++26 Structured Binding in Conditions ---
//
// std::map<int, std::string> m{{1, "one"}};
//
// // Structured binding directly in if-condition
// if (auto [iter, success] = m.insert({2, "two"}); success) {
//     std::cout << "Inserted: " << iter->second << "\n";
// }
//
// // The above already works in C++17! C++26 extends this to allow
// // the structured binding itself to be the condition (no semicolon):
// if (auto [iter, inserted] = m.try_emplace(3, "three")) {
//     // 'inserted' (a bool) is the condition value  -- proposed extension
// }

// --- Simulation using C++17/20 features ---

std::pair<bool, std::string> find_user(int id) {
    if (id == 42) return {true, "Alice"};
    if (id == 7)  return {true, "Bob"};
    return {false, ""};
}

std::tuple<bool, int, std::string> parse_record(const std::string& s) {
    if (s == "valid") return {true, 100, "data_ok"};
    return {false, 0, "parse_error"};
}

int main() {
    std::cout << "=== C++26 Structured Bindings in Conditions (Simulated) ===" << std::endl;

    // C++17 already supports structured bindings with init-statement in if
    std::map<int, std::string> m{{1, "one"}, {2, "two"}};

    if (auto [iter, success] = m.insert({3, "three"}); success) {
        std::cout << "Inserted key 3: " << iter->second << std::endl;
    }

    if (auto [iter, success] = m.insert({2, "duplicate"}); !success) {
        std::cout << "Key 2 already exists: " << iter->second << std::endl;
    }

    // Simulating structured binding as condition
    if (auto [found, name] = find_user(42); found) {
        std::cout << "Found user: " << name << std::endl;
    }

    if (auto [found, name] = find_user(99); !found) {
        std::cout << "User 99 not found" << std::endl;
    }

    // Tuple decomposition in conditions
    if (auto [ok, code, msg] = parse_record("valid"); ok) {
        std::cout << "Parsed: code=" << code << " msg=" << msg << std::endl;
    }

    if (auto [ok, code, msg] = parse_record("bad"); !ok) {
        std::cout << "Parse failed: " << msg << std::endl;
    }

    std::cout << "Structured bindings in conditions reduce boilerplate." << std::endl;
    return 0;
}

// Expected output:
// === C++26 Structured Bindings in Conditions (Simulated) ===
// Inserted key 3: three
// Key 2 already exists: two
// Found user: Alice
// User 99 not found
// Parsed: code=100 msg=data_ok
// Parse failed: parse_error
// Structured bindings in conditions reduce boilerplate.
