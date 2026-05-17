// CodeNebula - C++23 Example: std::print and std::println
// Compile: g++ -std=c++23 -Wall -Wextra -o example print.cpp
// Note: Requires GCC 14+ / Clang 18+ / MSVC 19.37+

// std::print and std::println provide Python-like formatted output.
// Based on std::format (C++20) but writing directly to stdout.
// std::println appends a newline; std::print does not.

#include <iostream>
#include <print>
#include <string>
#include <vector>
#include <numbers>

int main() {
    std::println("=== std::print and std::println ===");

    // Basic printing (println adds newline automatically)
    std::println("Hello, C++23!");
    std::print("No newline here... ");
    std::println("but this has one.");

    // Formatted output with placeholders
    std::println("\n=== Formatted Output ===");
    std::string name = "World";
    int year = 2024;
    std::println("Hello, {}! Welcome to {}.", name, year);

    // Number formatting
    std::println("\n=== Number Formatting ===");
    std::println("Integer:     {}", 42);
    std::println("Float:       {:.4f}", 3.14159265);
    std::println("Scientific:  {:.2e}", 299792458.0);
    std::println("Hex:         {:#x}", 255);
    std::println("Octal:       {:#o}", 255);
    std::println("Binary:      {:#b}", 42);

    // Width and alignment
    std::println("\n=== Alignment ===");
    std::println("|{:<15}|", "left");
    std::println("|{:>15}|", "right");
    std::println("|{:^15}|", "center");
    std::println("|{:*^15}|", "fill");

    // Positional arguments
    std::println("\n=== Positional ===");
    std::println("{0} + {1} = {2}", 3, 4, 7);
    std::println("{1} - {0} = {2}", 3, 10, 7);

    // Math constants
    std::println("\n=== Math Constants ===");
    std::println("pi      = {:.10f}", std::numbers::pi);
    std::println("e       = {:.10f}", std::numbers::e);
    std::println("sqrt(2) = {:.10f}", std::numbers::sqrt2);

    // Printing collections (manual loop)
    std::println("\n=== Collection ===");
    std::vector<int> nums = {10, 20, 30, 40, 50};
    for (std::size_t i = 0; i < nums.size(); ++i) {
        std::println("  nums[{}] = {}", i, nums[i]);
    }

    // Comparison with old style
    std::println("\n=== Why std::println? ===");
    std::println("  Simpler than: std::cout << x << \" \" << y << std::endl;");
    std::println("  Type-safe, no << chaining, Python-like formatting");

    return 0;
}

/*
Expected output:
=== std::print and std::println ===
Hello, C++23!
No newline here... but this has one.

=== Formatted Output ===
Hello, World! Welcome to 2024.

=== Number Formatting ===
Integer:     42
Float:       3.1416
Scientific:  3.00e+08
Hex:         0xff
Octal:       0377
Binary:      0b101010

=== Alignment ===
|left           |
|          right|
|    center     |
|*****fill******|

=== Positional ===
3 + 4 = 7
10 - 3 = 7

=== Math Constants ===
pi      = 3.1415926536
e       = 2.7182818285
sqrt(2) = 1.4142135624

=== Collection ===
  nums[0] = 10
  nums[1] = 20
  nums[2] = 30
  nums[3] = 40
  nums[4] = 50

=== Why std::println? ===
  Simpler than: std::cout << x << " " << y << std::endl;
  Type-safe, no << chaining, Python-like formatting
*/
