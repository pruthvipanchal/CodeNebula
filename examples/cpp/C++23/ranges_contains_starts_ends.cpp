// CodeNebula - C++23 Example: ranges::contains, starts_with, ends_with
// Compile: g++ -std=c++23 -Wall -Wextra -o example ranges_contains_starts_ends.cpp
// Note: Requires GCC 13+ / Clang 17+

// C++23 adds ranges::contains to check if a value exists in a range,
// ranges::contains_subrange to check for subsequences, and ranges::starts_with
// / ranges::ends_with to test range prefixes and suffixes.

#include <iostream>
#include <algorithm>
#include <ranges>
#include <vector>
#include <string>
#include <array>

int main() {
    std::vector<int> nums = {10, 20, 30, 40, 50};

    // ranges::contains - check if a value exists
    std::cout << "=== ranges::contains ===" << std::endl;
    std::cout << "  Contains 30: " << std::boolalpha
              << std::ranges::contains(nums, 30) << std::endl;
    std::cout << "  Contains 99: " << std::boolalpha
              << std::ranges::contains(nums, 99) << std::endl;

    // contains with projection
    std::vector<std::string> names = {"Alice", "Bob", "Charlie"};
    bool has_3_letter = std::ranges::contains(names, 3u,
        [](const std::string& s) { return s.size(); });
    std::cout << "  Contains 3-letter name: " << has_3_letter << std::endl;

    // ranges::contains_subrange - check if a subsequence exists
    std::cout << "\n=== ranges::contains_subrange ===" << std::endl;
    std::vector<int> sub = {20, 30, 40};
    std::cout << "  Contains [20,30,40]: "
              << std::ranges::contains_subrange(nums, sub) << std::endl;
    std::vector<int> bad_sub = {20, 40};
    std::cout << "  Contains [20,40]: "
              << std::ranges::contains_subrange(nums, bad_sub) << std::endl;

    // ranges::starts_with - check prefix
    std::cout << "\n=== ranges::starts_with ===" << std::endl;
    std::vector<int> prefix = {10, 20, 30};
    std::cout << "  Starts with [10,20,30]: "
              << std::ranges::starts_with(nums, prefix) << std::endl;
    std::vector<int> bad_prefix = {10, 30};
    std::cout << "  Starts with [10,30]: "
              << std::ranges::starts_with(nums, bad_prefix) << std::endl;

    // ranges::ends_with - check suffix
    std::cout << "\n=== ranges::ends_with ===" << std::endl;
    std::vector<int> suffix = {40, 50};
    std::cout << "  Ends with [40,50]: "
              << std::ranges::ends_with(nums, suffix) << std::endl;
    std::vector<int> bad_suffix = {30, 50};
    std::cout << "  Ends with [30,50]: "
              << std::ranges::ends_with(nums, bad_suffix) << std::endl;

    // Practical: validate file header/footer
    std::array<char, 8> file_data = {'P', 'K', 0x03, 0x04, 'd', 'a', 't', 'a'};
    std::array<char, 2> zip_magic = {'P', 'K'};
    std::cout << "\n=== Practical: file signature check ===" << std::endl;
    std::cout << "  Is ZIP file (starts with PK): "
              << std::ranges::starts_with(file_data, zip_magic) << std::endl;

    // Validate command sequence
    std::vector<std::string> cmds = {"BEGIN", "INSERT", "UPDATE", "COMMIT"};
    std::vector<std::string> valid_start = {"BEGIN"};
    std::vector<std::string> valid_end = {"COMMIT"};
    std::cout << "\n=== Transaction validation ===" << std::endl;
    std::cout << "  Starts with BEGIN: "
              << std::ranges::starts_with(cmds, valid_start) << std::endl;
    std::cout << "  Ends with COMMIT: "
              << std::ranges::ends_with(cmds, valid_end) << std::endl;

    return 0;
}

// Expected output:
// === ranges::contains ===
//   Contains 30: true
//   Contains 99: false
//   Contains 3-letter name: true
//
// === ranges::contains_subrange ===
//   Contains [20,30,40]: true
//   Contains [20,40]: false
//
// === ranges::starts_with ===
//   Starts with [10,20,30]: true
//   Starts with [10,30]: false
//
// === ranges::ends_with ===
//   Ends with [40,50]: true
//   Ends with [30,50]: false
//
// === Practical: file signature check ===
//   Is ZIP file (starts with PK): true
//
// === Transaction validation ===
//   Starts with BEGIN: true
//   Ends with COMMIT: true
