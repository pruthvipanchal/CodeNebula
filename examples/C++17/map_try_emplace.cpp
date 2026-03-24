// CodeNebula - C++17 Example: std::map try_emplace and insert_or_assign
// Compile: g++ -std=c++17 -Wall -Wextra -o example map_try_emplace.cpp

// Demonstrates C++17 additions to std::map: try_emplace (inserts only if
// key doesn't exist, avoiding unnecessary moves) and insert_or_assign
// (inserts or overwrites, returning whether insertion occurred).

#include <iostream>
#include <map>
#include <string>

// A type that reports when it's constructed or moved
struct Value {
    std::string data;
    Value(const std::string& s) : data(s) {
        std::cout << "    Constructed: \"" << data << "\"" << std::endl;
    }
    Value(Value&& other) noexcept : data(std::move(other.data)) {
        std::cout << "    Moved: \"" << data << "\"" << std::endl;
    }
    Value& operator=(Value&& other) noexcept {
        data = std::move(other.data);
        std::cout << "    Move-assigned: \"" << data << "\"" << std::endl;
        return *this;
    }
};

void print_map(const std::map<int, Value>& m) {
    for (const auto& [k, v] : m) {
        std::cout << "    " << k << " -> \"" << v.data << "\"" << std::endl;
    }
}

int main()
{
    // ------------------------------------------------------------------
    // 1. try_emplace: insert only if key absent
    // ------------------------------------------------------------------
    std::cout << "=== try_emplace ===" << std::endl;
    std::map<int, Value> m;

    std::cout << "  Insert key 1:" << std::endl;
    auto [it1, ok1] = m.try_emplace(1, "first");
    std::cout << "    inserted: " << ok1 << std::endl;

    std::cout << "  Try key 1 again:" << std::endl;
    auto [it2, ok2] = m.try_emplace(1, "duplicate");
    std::cout << "    inserted: " << ok2 << std::endl;
    std::cout << "    value: \"" << it2->second.data << "\" (unchanged)" << std::endl;

    // ------------------------------------------------------------------
    // 2. try_emplace does NOT move arguments on failure
    // ------------------------------------------------------------------
    std::cout << "\n=== try_emplace Preserves Arguments ===" << std::endl;
    std::string val = "preserved";
    m.try_emplace(1, std::move(val));  // Key 1 exists; val NOT moved
    std::cout << "  val after failed try_emplace: \"" << val << "\"" << std::endl;

    // ------------------------------------------------------------------
    // 3. insert_or_assign: insert or overwrite
    // ------------------------------------------------------------------
    std::cout << "\n=== insert_or_assign ===" << std::endl;
    std::map<int, std::string> scores;

    auto [s1, ins1] = scores.insert_or_assign(1, "Alice");
    std::cout << "  Key 1 inserted: " << ins1 << " -> \"" << s1->second << "\"" << std::endl;

    auto [s2, ins2] = scores.insert_or_assign(1, "Alice Updated");
    std::cout << "  Key 1 assigned: " << ins2 << " -> \"" << s2->second << "\"" << std::endl;

    auto [s3, ins3] = scores.insert_or_assign(2, "Bob");
    std::cout << "  Key 2 inserted: " << ins3 << " -> \"" << s3->second << "\"" << std::endl;

    // ------------------------------------------------------------------
    // 4. try_emplace with hint (iterator position)
    // ------------------------------------------------------------------
    std::cout << "\n=== try_emplace with Hint ===" << std::endl;
    std::map<int, std::string> config;
    config[10] = "ten";
    config[30] = "thirty";

    // Hint: insert near the end
    auto hint = config.end();
    auto it = config.try_emplace(hint, 20, "twenty");
    std::cout << "  Inserted with hint: " << it->first << " -> " << it->second << std::endl;

    std::cout << "\n  Final map:" << std::endl;
    for (const auto& [k, v] : config) {
        std::cout << "    " << k << " -> " << v << std::endl;
    }

    return 0;
}

/*
Expected output:

=== try_emplace ===
  Insert key 1:
    Constructed: "first"
    inserted: 1
  Try key 1 again:
    inserted: 0
    value: "first" (unchanged)

=== try_emplace Preserves Arguments ===
  val after failed try_emplace: "preserved"

=== insert_or_assign ===
  Key 1 inserted: 1 -> "Alice"
  Key 1 assigned: 0 -> "Alice Updated"
  Key 2 inserted: 1 -> "Bob"

=== try_emplace with Hint ===
  Inserted with hint: 20 -> twenty

  Final map:
    10 -> ten
    20 -> twenty
    30 -> thirty
*/
