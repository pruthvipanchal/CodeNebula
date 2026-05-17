// CodeNebula - C++17 Example: std::unordered_map try_emplace / insert_or_assign
// Compile: g++ -std=c++17 -Wall -Wextra -o example unordered_map_try_emplace.cpp

// Demonstrates C++17 try_emplace and insert_or_assign on std::unordered_map.
// These behave identically to their std::map counterparts but on hash tables.
// try_emplace avoids unnecessary moves; insert_or_assign upserts in one call.

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

int main()
{
    // ------------------------------------------------------------------
    // 1. try_emplace: insert only if key is absent
    // ------------------------------------------------------------------
    std::cout << "=== try_emplace ===" << std::endl;
    std::unordered_map<std::string, std::vector<int>> groups;

    // Insert new key with vector constructed in-place
    auto [it1, ok1] = groups.try_emplace("team_a", std::vector<int>{1, 2, 3});
    std::cout << "  team_a inserted: " << ok1 << std::endl;

    // Key already exists: no construction, no move
    auto [it2, ok2] = groups.try_emplace("team_a", std::vector<int>{99, 99});
    std::cout << "  team_a again:    " << ok2 << " (not replaced)" << std::endl;
    std::cout << "  team_a values:   ";
    for (int v : it2->second) std::cout << v << " ";
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. try_emplace preserves moved-from arguments
    // ------------------------------------------------------------------
    std::cout << "\n=== Argument Preservation ===" << std::endl;
    std::string key = "team_a";
    std::vector<int> data = {7, 8, 9};

    groups.try_emplace(key, std::move(data));  // Fails: key exists
    std::cout << "  key after failed try_emplace:  \"" << key << "\"" << std::endl;
    std::cout << "  data after failed try_emplace: size=" << data.size() << std::endl;

    // ------------------------------------------------------------------
    // 3. insert_or_assign: upsert pattern
    // ------------------------------------------------------------------
    std::cout << "\n=== insert_or_assign ===" << std::endl;
    std::unordered_map<std::string, int> scores;

    auto [s1, ins1] = scores.insert_or_assign("Alice", 95);
    std::cout << "  Alice inserted: " << ins1 << " score=" << s1->second << std::endl;

    auto [s2, ins2] = scores.insert_or_assign("Alice", 98);
    std::cout << "  Alice updated:  " << ins2 << " score=" << s2->second << std::endl;

    auto [s3, ins3] = scores.insert_or_assign("Bob", 87);
    std::cout << "  Bob inserted:   " << ins3 << " score=" << s3->second << std::endl;

    // ------------------------------------------------------------------
    // 4. Practical: word frequency counter using try_emplace
    // ------------------------------------------------------------------
    std::cout << "\n=== Word Frequency ===" << std::endl;
    std::vector<std::string> words = {
        "apple", "banana", "apple", "cherry", "banana", "apple"
    };

    std::unordered_map<std::string, int> freq;
    for (const auto& w : words) {
        auto [it, inserted] = freq.try_emplace(w, 0);
        it->second++;  // Increment whether newly inserted or existing
    }

    for (const auto& [word, count] : freq) {
        std::cout << "  " << word << ": " << count << std::endl;
    }

    // ------------------------------------------------------------------
    // 5. Practical: config defaults with try_emplace
    // ------------------------------------------------------------------
    std::cout << "\n=== Config Defaults ===" << std::endl;
    std::unordered_map<std::string, std::string> config;
    config["port"] = "8080";  // User-provided

    // Set defaults only for missing keys
    config.try_emplace("port", "3000");        // Exists: no overwrite
    config.try_emplace("host", "localhost");    // Missing: inserted
    config.try_emplace("timeout", "30");        // Missing: inserted

    for (const auto& [k, v] : config) {
        std::cout << "  " << k << " = " << v << std::endl;
    }

    return 0;
}

/*
Expected output (unordered_map order may vary):

=== try_emplace ===
  team_a inserted: 1
  team_a again:    0 (not replaced)
  team_a values:   1 2 3

=== Argument Preservation ===
  key after failed try_emplace:  "team_a"
  data after failed try_emplace: size=3

=== insert_or_assign ===
  Alice inserted: 1 score=95
  Alice updated:  0 score=98
  Bob inserted:   1 score=87

=== Word Frequency ===
  cherry: 1
  banana: 2
  apple: 3

=== Config Defaults ===
  timeout = 30
  host = localhost
  port = 8080
*/
