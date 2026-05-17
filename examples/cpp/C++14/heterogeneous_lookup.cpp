// CodeNebula - C++14 Example: Heterogeneous Lookup
// Compile: g++ -std=c++14 -Wall -Wextra -o example heterogeneous_lookup.cpp

// Demonstrates heterogeneous lookup in ordered containers using transparent
// comparators like std::less<>. In C++14, set::find() and map::find() can
// accept keys of different types without creating temporaries. Real-world
// use: looking up string keys with const char* (avoids std::string allocation),
// searching by a subset of a composite key.

#include <iostream>
#include <set>
#include <map>
#include <string>
#include <functional>

int main()
{
    // ------------------------------------------------------------------
    // 1. Problem: without transparent comparator, const char* creates
    //    a temporary std::string for every lookup
    // ------------------------------------------------------------------
    std::cout << "=== Without Heterogeneous Lookup ===" << std::endl;
    std::set<std::string> regular_set = {"apple", "banana", "cherry"};

    // This works but creates a temporary std::string from "banana":
    auto it1 = regular_set.find("banana");
    std::cout << "  regular find(\"banana\"): "
              << (it1 != regular_set.end() ? "found" : "not found") << std::endl;
    std::cout << "  (temporary std::string created for comparison)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. With transparent comparator: std::less<> enables heterogeneous lookup
    // ------------------------------------------------------------------
    std::cout << "=== With Heterogeneous Lookup (std::less<>) ===" << std::endl;
    std::set<std::string, std::less<>> fast_set = {"apple", "banana", "cherry"};

    // This compares const char* directly against std::string - no temporary!
    auto it2 = fast_set.find("banana");
    std::cout << "  fast find(\"banana\"): "
              << (it2 != fast_set.end() ? "found" : "not found") << std::endl;
    std::cout << "  (no temporary std::string created)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. Heterogeneous lookup with std::map
    // ------------------------------------------------------------------
    std::cout << "=== Map with Heterogeneous Lookup ===" << std::endl;
    std::map<std::string, int, std::less<>> scores;
    scores["Alice"] = 95;
    scores["Bob"]   = 87;
    scores["Carol"] = 92;

    // find() with const char* - no std::string temporary
    auto it3 = scores.find("Bob");
    if (it3 != scores.end())
        std::cout << "  Bob's score: " << it3->second << std::endl;

    // count() also supports heterogeneous lookup
    std::cout << "  count(\"Alice\"): " << scores.count("Alice") << std::endl;
    std::cout << "  count(\"Dave\") : " << scores.count("Dave") << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. lower_bound / upper_bound with heterogeneous lookup
    // ------------------------------------------------------------------
    std::cout << "=== Range Queries ===" << std::endl;
    std::set<std::string, std::less<>> names =
        {"Alice", "Amanda", "Bob", "Carol", "Charlie", "Dave"};

    // Find all names in range [B, D) without creating temporary strings
    auto lo = names.lower_bound("B");
    auto hi = names.lower_bound("D");

    std::cout << "  Names in [B, D):" << std::endl;
    for (auto it = lo; it != hi; ++it)
        std::cout << "    " << *it << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 5. Multiset with heterogeneous lookup
    // ------------------------------------------------------------------
    std::cout << "=== Multiset Heterogeneous Lookup ===" << std::endl;
    std::multiset<std::string, std::less<>> tags =
        {"c++", "c++", "python", "rust", "c++", "python"};

    std::cout << "  count(\"c++\")   : " << tags.count("c++") << std::endl;
    std::cout << "  count(\"python\"): " << tags.count("python") << std::endl;
    std::cout << "  count(\"java\")  : " << tags.count("java") << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 6. Performance benefit summary
    // ------------------------------------------------------------------
    std::cout << "=== Performance Summary ===" << std::endl;
    std::cout << "  std::set<string>           : find(\"x\") allocates temporary" << std::endl;
    std::cout << "  std::set<string, less<>>   : find(\"x\") compares directly" << std::endl;
    std::cout << "  Benefit: zero allocations for string lookups with const char*" << std::endl;

    return 0;
}

/*
Expected output:

=== Without Heterogeneous Lookup ===
  regular find("banana"): found
  (temporary std::string created for comparison)

=== With Heterogeneous Lookup (std::less<>) ===
  fast find("banana"): found
  (no temporary std::string created)

=== Map with Heterogeneous Lookup ===
  Bob's score: 87
  count("Alice"): 1
  count("Dave") : 0

=== Range Queries ===
  Names in [B, D):
    Bob
    Carol
    Charlie

=== Multiset Heterogeneous Lookup ===
  count("c++")   : 3
  count("python"): 2
  count("java")  : 0

=== Performance Summary ===
  std::set<string>           : find("x") allocates temporary
  std::set<string, less<>>   : find("x") compares directly
  Benefit: zero allocations for string lookups with const char*
*/
