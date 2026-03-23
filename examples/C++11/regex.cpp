// CodeNebula - C++11 Example: std::regex Basic Patterns
// Compile: g++ -std=c++11 -Wall -Wextra -o example regex.cpp

// std::regex provides regular expression support in C++11. The default
// grammar is ECMAScript. Patterns are compiled into regex objects that
// can be reused for matching, searching, and replacing.

#include <iostream>
#include <regex>
#include <string>

int main() {
    // Basic pattern construction
    std::regex digit_pattern(R"(\d+)");
    std::regex email_pattern(R"(\w+@\w+\.\w+)");
    std::regex word_pattern(R"(\b\w+\b)");

    // Test strings
    std::string text = "Contact us at info@example.com or call 555-1234";

    // Check if pattern exists in string
    std::cout << "Pattern checks on: \"" << text << "\"" << std::endl;
    std::cout << "  Has digits: "
              << (std::regex_search(text, digit_pattern) ? "yes" : "no") << std::endl;
    std::cout << "  Has email:  "
              << (std::regex_search(text, email_pattern) ? "yes" : "no") << std::endl;

    // Case-insensitive matching
    std::regex ci_pattern("hello", std::regex_constants::icase);
    std::cout << "\nCase-insensitive:" << std::endl;
    std::cout << "  \"HELLO\" matches: "
              << (std::regex_search(std::string("HELLO"), ci_pattern) ? "yes" : "no")
              << std::endl;
    std::cout << "  \"hElLo\" matches: "
              << (std::regex_search(std::string("hElLo"), ci_pattern) ? "yes" : "no")
              << std::endl;

    // Common pattern types
    std::cout << "\nPattern examples:" << std::endl;

    // Phone number pattern
    std::regex phone(R"(\d{3}-\d{4})");
    std::string phones[] = {"555-1234", "abc-defg", "123-45"};
    for (const auto& p : phones) {
        bool match = std::regex_match(p, phone);
        std::cout << "  \"" << p << "\" is phone: " << (match ? "yes" : "no") << std::endl;
    }

    // Date pattern (YYYY-MM-DD)
    std::regex date(R"(\d{4}-\d{2}-\d{2})");
    std::string dates[] = {"2024-01-15", "24-1-5", "2024/01/15"};
    for (const auto& d : dates) {
        bool match = std::regex_match(d, date);
        std::cout << "  \"" << d << "\" is date: " << (match ? "yes" : "no") << std::endl;
    }

    // Alternation and grouping
    std::regex color(R"(red|green|blue)");
    std::string colors[] = {"red", "green", "yellow", "blue"};
    std::cout << "\nColor matches:" << std::endl;
    for (const auto& c : colors) {
        std::cout << "  \"" << c << "\": "
                  << (std::regex_match(c, color) ? "match" : "no match") << std::endl;
    }

    // regex_error handling
    try {
        std::regex bad_pattern("[invalid");
    } catch (const std::regex_error& e) {
        std::cout << "\nregex_error: " << e.what() << std::endl;
    }

    return 0;
}

// Expected output:
// Pattern checks on: "Contact us at info@example.com or call 555-1234"
//   Has digits: yes
//   Has email:  yes
//
// Case-insensitive:
//   "HELLO" matches: yes
//   "hElLo" matches: yes
//
// Pattern examples:
//   "555-1234" is phone: yes
//   "abc-defg" is phone: no
//   "123-45" is phone: no
//   "2024-01-15" is date: yes
//   "24-1-5" is date: no
//   "2024/01/15" is date: no
//
// Color matches:
//   "red": match
//   "green": match
//   "yellow": no match
//   "blue": match
//
// regex_error: <error message>
