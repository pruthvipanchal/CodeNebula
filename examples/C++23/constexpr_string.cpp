// CodeNebula - C++23 Example: constexpr std::string Improvements
// Compile: g++ -std=c++23 -Wall -Wextra -o example constexpr_string.cpp
// Note: Requires GCC 13+ / Clang 17+

#include <algorithm>
#include <iostream>
#include <string>

// C++23 extends constexpr support for std::string, allowing more string
// operations at compile time. Building on C++20's constexpr allocation,
// C++23 adds constexpr to additional member functions and algorithms.

// Compile-time string manipulation
constexpr std::string make_greeting(std::string_view name) {
    std::string result = "Hello, ";
    result += name;
    result += "!";
    return result;
}

// Compile-time string reversal
constexpr std::string reverse_string(std::string_view input) {
    std::string s(input);
    std::ranges::reverse(s);
    return s;
}

// Compile-time uppercase
constexpr std::string to_upper(std::string_view input) {
    std::string s(input);
    for (auto& ch : s) {
        if (ch >= 'a' && ch <= 'z') {
            ch -= ('a' - 'A');
        }
    }
    return s;
}

// Compile-time concatenation and length
constexpr std::size_t count_words(std::string_view sv) {
    if (sv.empty()) return 0;
    std::size_t count = 0;
    bool in_word = false;
    for (char ch : sv) {
        if (ch == ' ') {
            in_word = false;
        } else if (!in_word) {
            in_word = true;
            ++count;
        }
    }
    return count;
}

int main() {
    std::cout << "=== constexpr std::string improvements in C++23 ===\n\n";

    // constexpr greeting (evaluated at compile time)
    constexpr auto greeting = make_greeting("World");
    // Note: constexpr std::string must be used/consumed at compile time.
    // We print the result at runtime but the computation was compile-time.
    std::cout << "Greeting: " << std::string(greeting) << "\n";

    // constexpr reversal
    constexpr auto reversed = reverse_string("CodeNebula");
    std::cout << "Reversed: " << std::string(reversed) << "\n";

    // constexpr uppercase
    constexpr auto upper = to_upper("hello world");
    std::cout << "Upper:    " << std::string(upper) << "\n\n";

    // constexpr word count
    constexpr auto wc = count_words("The quick brown fox");
    static_assert(wc == 4, "Should have 4 words");
    std::cout << "Word count in 'The quick brown fox': " << wc << "\n";

    // constexpr string comparison
    constexpr std::string a = "abc";
    constexpr std::string b = "abd";
    constexpr bool less = a < b;
    static_assert(less, "abc < abd");
    std::cout << "\"abc\" < \"abd\": " << less << "\n";

    // constexpr contains (C++23)
    constexpr std::string haystack = "hello world";
    constexpr bool has_world = haystack.contains("world");
    static_assert(has_world);
    std::cout << "\"hello world\".contains(\"world\"): " << has_world << "\n";

    return 0;
}

// Expected output:
// === constexpr std::string improvements in C++23 ===
//
// Greeting: Hello, World!
// Reversed: alubeNedoC
// Upper:    HELLO WORLD
//
// Word count in 'The quick brown fox': 4
// "abc" < "abd": 1
// "hello world".contains("world"): 1
