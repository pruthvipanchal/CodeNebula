// CodeNebula - C++17 Example: Node Handles (extract / insert)
// Compile: g++ -std=c++17 -Wall -Wextra -o example node_handle.cpp

// Demonstrates C++17 node handles for associative containers. extract()
// removes a node without deallocation; insert() with a node handle transfers
// ownership. This enables moving elements between containers without copying,
// and also allows modifying keys of map elements in-place.

#include <iostream>
#include <map>
#include <set>
#include <string>

template <typename Map>
void print_map(const std::string& label, const Map& m) {
    std::cout << "  " << label << ": ";
    for (const auto& [k, v] : m) std::cout << "{" << k << ":" << v << "} ";
    std::cout << (m.empty() ? "(empty)" : "") << std::endl;
}

template <typename Set>
void print_set(const std::string& label, const Set& s) {
    std::cout << "  " << label << ": ";
    for (const auto& v : s) std::cout << v << " ";
    std::cout << (s.empty() ? "(empty)" : "") << std::endl;
}

int main()
{
    // ------------------------------------------------------------------
    // 1. Extract and insert: move nodes between maps
    // ------------------------------------------------------------------
    std::cout << "=== Move Nodes Between Maps ===" << std::endl;
    std::map<int, std::string> src = {{1, "one"}, {2, "two"}, {3, "three"}};
    std::map<int, std::string> dst = {{10, "ten"}};

    print_map("src before", src);
    print_map("dst before", dst);

    // Extract node with key 2 from src
    auto node = src.extract(2);
    std::cout << "  Extracted key " << node.key() << " -> \"" << node.mapped() << "\"" << std::endl;

    // Insert the node into dst (no copy, no allocation)
    dst.insert(std::move(node));

    print_map("src after", src);
    print_map("dst after", dst);

    // ------------------------------------------------------------------
    // 2. Modify a key using node handles (impossible without extract)
    // ------------------------------------------------------------------
    std::cout << "\n=== Modify Key In-Place ===" << std::endl;
    std::map<int, std::string> m = {{1, "alpha"}, {2, "beta"}, {3, "gamma"}};
    print_map("before", m);

    // Change key 2 to key 20
    auto nh = m.extract(2);
    nh.key() = 20;  // Modify the key!
    m.insert(std::move(nh));
    print_map("after (2->20)", m);

    // ------------------------------------------------------------------
    // 3. Extract by iterator
    // ------------------------------------------------------------------
    std::cout << "\n=== Extract by Iterator ===" << std::endl;
    auto it = m.find(3);
    auto nh2 = m.extract(it);
    std::cout << "  Extracted: {" << nh2.key() << ":" << nh2.mapped() << "}" << std::endl;
    print_map("remaining", m);

    // Re-insert with modified value
    nh2.mapped() = "GAMMA";
    m.insert(std::move(nh2));
    print_map("re-inserted", m);

    // ------------------------------------------------------------------
    // 4. Node handles with std::set
    // ------------------------------------------------------------------
    std::cout << "\n=== Set Node Handles ===" << std::endl;
    std::set<std::string> s1 = {"apple", "banana", "cherry"};
    std::set<std::string> s2 = {"date", "elderberry"};

    print_set("s1 before", s1);
    print_set("s2 before", s2);

    auto sn = s1.extract("banana");
    s2.insert(std::move(sn));

    print_set("s1 after", s1);
    print_set("s2 after", s2);

    // ------------------------------------------------------------------
    // 5. merge() transfers all compatible nodes
    // ------------------------------------------------------------------
    std::cout << "\n=== merge() ===" << std::endl;
    std::map<int, std::string> a = {{1, "A"}, {2, "B"}};
    std::map<int, std::string> b = {{2, "X"}, {3, "C"}, {4, "D"}};

    print_map("a before", a);
    print_map("b before", b);

    a.merge(b);  // Moves non-conflicting nodes from b to a

    print_map("a after merge", a);
    print_map("b after merge", b);  // Key 2 remains (conflict)

    return 0;
}

/*
Expected output:

=== Move Nodes Between Maps ===
  src before: {1:one} {2:two} {3:three}
  dst before: {10:ten}
  Extracted key 2 -> "two"
  src after: {1:one} {3:three}
  dst after: {2:two} {10:ten}

=== Modify Key In-Place ===
  before: {1:alpha} {2:beta} {3:gamma}
  after (2->20): {1:alpha} {3:gamma} {20:beta}

=== Extract by Iterator ===
  Extracted: {3:gamma}
  remaining: {1:alpha} {20:beta}
  re-inserted: {1:alpha} {3:GAMMA} {20:beta}

=== Set Node Handles ===
  s1 before: apple banana cherry
  s2 before: date elderberry
  s1 after: apple cherry
  s2 after: banana date elderberry

=== merge() ===
  a before: {1:A} {2:B}
  b before: {2:X} {3:C} {4:D}
  a after merge: {1:A} {2:B} {3:C} {4:D}
  b after merge: {2:X}
*/
