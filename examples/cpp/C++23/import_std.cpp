// CodeNebula - C++23 Example: import std; Module
// Compile: g++ -std=c++23 -Wall -Wextra -fmodules-ts -o example import_std.cpp
// Note: Requires GCC 14+ / Clang 18+ with modules support
// Module support varies significantly between compilers and build systems.
// This file may require special build steps to precompile the std module.

// C++23 introduces "import std;" which imports the entire standard library
// as a single module. This replaces #include directives and provides:
// - Faster compilation (modules are parsed once and cached)
// - No macro leakage from headers
// - Cleaner dependency model

import std;

// With "import std;", all standard library names are available
// without individual #include directives.

// A simple function using various std library components
auto get_sorted_squares(std::span<const int> input) -> std::vector<int> {
    std::vector<int> result;
    result.reserve(input.size());

    std::ranges::transform(input, std::back_inserter(result),
        [](int x) { return x * x; });

    std::ranges::sort(result);
    return result;
}

int main() {
    std::cout << "=== import std; module ===\n\n";

    // All of <iostream>, <vector>, <string>, etc. available via import std;
    std::string greeting = "Hello from C++23 modules!";
    std::cout << greeting << "\n\n";

    // Using containers
    std::vector<int> nums = {5, -3, 1, -4, 2};
    std::cout << "Input: ";
    for (int n : nums) std::cout << n << " ";
    std::cout << "\n";

    auto squares = get_sorted_squares(nums);
    std::cout << "Sorted squares: ";
    for (int s : squares) std::cout << s << " ";
    std::cout << "\n\n";

    // Using <algorithm> and <numeric>
    auto sum = std::accumulate(squares.begin(), squares.end(), 0);
    std::cout << "Sum of squares: " << sum << "\n";

    auto [mn, mx] = std::ranges::minmax(nums);
    std::cout << "Min: " << mn << ", Max: " << mx << "\n\n";

    // Using <chrono>
    auto now = std::chrono::system_clock::now();
    auto today = std::chrono::floor<std::chrono::days>(now);
    std::chrono::year_month_day ymd{today};
    std::cout << "Today: " << ymd << "\n\n";

    // Using <optional> and <expected>
    std::optional<int> opt = 42;
    auto doubled = opt.transform([](int v) { return v * 2; });
    std::cout << "optional transform: " << doubled.value() << "\n";

    // Using <format>
    std::string formatted = std::format("Formatted: {} + {} = {}", 3, 4, 7);
    std::cout << formatted << "\n";

    std::cout << "\nimport std; replaces all #include directives!\n";

    return 0;
}

// Expected output:
// === import std; module ===
//
// Hello from C++23 modules!
//
// Input: 5 -3 1 -4 2
// Sorted squares: 1 4 9 16 25
//
// Sum of squares: 55
// Min: -4, Max: 5
//
// Today: 2026-03-24
//
// optional transform: 84
// Formatted: 3 + 4 = 7
//
// import std; replaces all #include directives!
