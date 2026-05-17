// CodeNebula - C++20 Example: std::format String Formatting
// Compile: g++ -std=c++20 -Wall -Wextra -o example format.cpp

#include <format>
#include <iostream>
#include <string>
#include <vector>
#include <numbers>

int main() {
    // Basic string formatting with positional arguments
    std::string greeting = std::format("Hello, {}!", "World");
    std::cout << greeting << '\n';

    // Multiple arguments
    std::string info = std::format("{} is {} years old", "Alice", 30);
    std::cout << info << '\n';

    // Integer formatting
    int num = 42;
    std::cout << std::format("Decimal: {}", num) << '\n';
    std::cout << std::format("Hex:     {:#x}", num) << '\n';
    std::cout << std::format("Octal:   {:#o}", num) << '\n';
    std::cout << std::format("Binary:  {:#b}", num) << '\n';

    // Floating point formatting
    double pi = std::numbers::pi;
    std::cout << '\n';
    std::cout << std::format("Default:    {}", pi) << '\n';
    std::cout << std::format("Fixed:      {:.2f}", pi) << '\n';
    std::cout << std::format("Scientific: {:.4e}", pi) << '\n';
    std::cout << std::format("General:    {:.6g}", pi) << '\n';

    // Width and alignment
    std::cout << '\n';
    std::cout << std::format("|{:<20}|", "left") << '\n';
    std::cout << std::format("|{:>20}|", "right") << '\n';
    std::cout << std::format("|{:^20}|", "center") << '\n';
    std::cout << std::format("|{:*^20}|", "fill") << '\n';

    // Indexed arguments
    std::cout << '\n';
    std::cout << std::format("{0} {1} {0}", "ping", "pong") << '\n';

    // Padding numbers
    std::cout << '\n';
    for (int i = 1; i <= 5; ++i)
        std::cout << std::format("Item {:03}: ${:>8.2f}\n", i, i * 12.5);

    // format_to with back_inserter
    std::string buffer;
    std::format_to(std::back_inserter(buffer), "x={}, y={}", 10, 20);
    std::cout << '\n' << "Buffer: " << buffer << '\n';

    // Practical: table formatting
    std::cout << '\n';
    std::cout << std::format("{:<12} {:>8} {:>6}\n", "Name", "Score", "Grade");
    std::cout << std::format("{:-<12} {:->8} {:->6}\n", "", "", "");
    std::cout << std::format("{:<12} {:>8} {:>6}\n", "Alice", 95, "A");
    std::cout << std::format("{:<12} {:>8} {:>6}\n", "Bob", 82, "B");
    std::cout << std::format("{:<12} {:>8} {:>6}\n", "Carol", 71, "C");

    return 0;
}
