// CodeNebula - C++26 Example: std::flat_map Improvements
// Compile: g++ -std=c++26 -Wall -Wextra -o example flat_map_improvements.cpp
// Note: Requires C++26 compiler support (GCC 15+ / Clang 19+ expected)

// std::flat_map (C++23) stores keys and values in sorted contiguous arrays.
// C++26 adds improvements: better exception safety, improved insert/emplace,
// and heterogeneous operations with transparent comparators.

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

// --- C++26 flat_map Improvements ---
//
// #include <flat_map>
//
// std::flat_map<int, std::string> fm;
// fm.insert({1, "one"});
// fm[2] = "two";
//
// // C++26: extract underlying containers
// auto& keys = fm.keys();       // sorted vector<int>
// auto& vals = fm.values();     // vector<string> in key order
//
// // C++26: improved heterogeneous lookup
// std::flat_map<std::string, int, std::less<>> fm2;
// fm2["hello"] = 1;
// auto it = fm2.find("hello"sv);  // No temporary string created

// --- Simulation using sorted vectors ---

template<typename Key, typename Value>
class flat_map_sim {
    std::vector<std::pair<Key, Value>> data_;

    auto find_pos(const Key& k) {
        return std::lower_bound(data_.begin(), data_.end(), k,
            [](const auto& p, const Key& key) { return p.first < key; });
    }
public:
    void insert(const Key& k, const Value& v) {
        auto it = find_pos(k);
        if (it != data_.end() && it->first == k) { it->second = v; return; }
        data_.insert(it, {k, v});
    }
    Value& operator[](const Key& k) {
        auto it = find_pos(k);
        if (it == data_.end() || it->first != k)
            it = data_.insert(it, {k, Value{}});
        return it->second;
    }
    std::size_t size() const { return data_.size(); }
    bool contains(const Key& k) const {
        auto it = std::lower_bound(data_.begin(), data_.end(), k,
            [](const auto& p, const Key& key) { return p.first < key; });
        return it != data_.end() && it->first == k;
    }
    auto begin() const { return data_.begin(); }
    auto end() const { return data_.end(); }
};

int main() {
    std::cout << "=== C++26 std::flat_map Improvements (Simulated) ===" << std::endl;

    flat_map_sim<int, std::string> fm;
    fm.insert(3, "three");
    fm.insert(1, "one");
    fm.insert(2, "two");
    fm[4] = "four";

    std::cout << "Flat map (sorted by key):" << std::endl;
    for (const auto& [k, v] : fm)
        std::cout << "  " << k << " -> " << v << std::endl;

    std::cout << "Size: " << fm.size() << std::endl;
    std::cout << "Contains 2: " << std::boolalpha << fm.contains(2) << std::endl;
    std::cout << "Contains 5: " << fm.contains(5) << std::endl;

    // Update existing
    fm[2] = "TWO";
    std::cout << "After update, 2 -> " << fm[2] << std::endl;

    std::cout << "flat_map: cache-friendly sorted associative container." << std::endl;
    return 0;
}

// Expected output:
// === C++26 std::flat_map Improvements (Simulated) ===
// Flat map (sorted by key):
//   1 -> one
//   2 -> two
//   3 -> three
//   4 -> four
// Size: 4
// Contains 2: true
// Contains 5: false
// After update, 2 -> TWO
// flat_map: cache-friendly sorted associative container.
