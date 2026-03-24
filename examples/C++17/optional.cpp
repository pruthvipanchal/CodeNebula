// CodeNebula - C++17 Example: std::optional
// Compile: g++ -std=c++17 -Wall -Wextra -o example optional.cpp

// Demonstrates std::optional, a type that may or may not hold a value.
// It replaces sentinel values (-1, nullptr, etc.) and makes the "no value"
// case explicit and type-safe.

#include <iostream>
#include <optional>
#include <string>
#include <vector>
#include <cmath>

// ------------------------------------------------------------------
// 1. Function that may fail: return optional instead of sentinel
// ------------------------------------------------------------------
std::optional<double> safe_sqrt(double x) {
    if (x < 0.0) return std::nullopt;
    return std::sqrt(x);
}

// ------------------------------------------------------------------
// 2. Lookup that may not find a result
// ------------------------------------------------------------------
std::optional<std::string> find_user(int id) {
    std::vector<std::pair<int, std::string>> db = {
        {1, "Alice"}, {2, "Bob"}, {3, "Carol"}
    };
    for (const auto& [uid, name] : db) {
        if (uid == id) return name;
    }
    return std::nullopt;
}

// ------------------------------------------------------------------
// 3. Chaining optional results
// ------------------------------------------------------------------
std::optional<int> parse_int(const std::string& s) {
    try {
        std::size_t pos = 0;
        int val = std::stoi(s, &pos);
        if (pos == s.size()) return val;  // entire string consumed
        return std::nullopt;
    } catch (...) {
        return std::nullopt;
    }
}

int main()
{
    // 1. Basic construction and access
    std::cout << "=== construction ===" << std::endl;
    std::optional<int> a;                 // empty
    std::optional<int> b = 42;            // contains 42
    std::optional<int> c = std::nullopt;  // explicitly empty
    std::optional<int> d{std::in_place, 99};  // in-place construction

    std::cout << "  a has_value: " << std::boolalpha << a.has_value() << std::endl;
    std::cout << "  b has_value: " << b.has_value() << ", value: " << *b << std::endl;
    std::cout << "  c has_value: " << c.has_value() << std::endl;
    std::cout << "  d has_value: " << d.has_value() << ", value: " << d.value() << std::endl;

    // 2. value_or: provide a default
    std::cout << "\n=== value_or ===" << std::endl;
    std::cout << "  a.value_or(-1): " << a.value_or(-1) << std::endl;
    std::cout << "  b.value_or(-1): " << b.value_or(-1) << std::endl;

    // 3. safe_sqrt
    std::cout << "\n=== safe_sqrt ===" << std::endl;
    for (double x : {25.0, -4.0, 0.0, 2.0}) {
        auto result = safe_sqrt(x);
        std::cout << "  sqrt(" << x << ") = ";
        if (result) {
            std::cout << *result << std::endl;
        } else {
            std::cout << "undefined (negative)" << std::endl;
        }
    }

    // 4. Lookup
    std::cout << "\n=== find_user ===" << std::endl;
    for (int id : {1, 2, 5}) {
        auto user = find_user(id);
        std::cout << "  id=" << id << ": "
                  << user.value_or("(not found)") << std::endl;
    }

    // 5. Parsing with optional
    std::cout << "\n=== parse_int ===" << std::endl;
    for (const auto& s : {"42", "abc", "100", "12x"}) {
        auto val = parse_int(s);
        std::cout << "  \"" << s << "\" -> "
                  << (val ? std::to_string(*val) : "nullopt") << std::endl;
    }

    // 6. Resetting and emplacing
    std::cout << "\n=== reset and emplace ===" << std::endl;
    std::optional<std::string> opt = "hello";
    std::cout << "  before reset: " << *opt << std::endl;
    opt.reset();
    std::cout << "  after reset: " << (opt ? *opt : "(empty)") << std::endl;
    opt.emplace("world");
    std::cout << "  after emplace: " << *opt << std::endl;

    return 0;
}

/*
Expected output:

=== construction ===
  a has_value: false
  b has_value: true, value: 42
  c has_value: false
  d has_value: true, value: 99

=== value_or ===
  a.value_or(-1): -1
  b.value_or(-1): 42

=== safe_sqrt ===
  sqrt(25) = 5
  sqrt(-4) = undefined (negative)
  sqrt(0) = 0
  sqrt(2) = 1.41421

=== find_user ===
  id=1: Alice
  id=2: Bob
  id=5: (not found)

=== parse_int ===
  "42" -> 42
  "abc" -> nullopt
  "100" -> 100
  "12x" -> nullopt

=== reset and emplace ===
  before reset: hello
  after reset: (empty)
  after emplace: world
*/
