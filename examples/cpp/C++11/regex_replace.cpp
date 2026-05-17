// CodeNebula - C++11 Example: std::regex_replace
// Compile: g++ -std=c++11 -Wall -Wextra -o example regex_replace.cpp

// std::regex_replace substitutes all matches of a pattern with a
// replacement string. It supports backreferences ($1, $2) to insert
// captured groups into the replacement.

#include <iostream>
#include <regex>
#include <string>

int main() {
    // Simple replacement
    std::string text = "Hello World Hello World";
    std::regex hello_re("Hello");
    std::string result = std::regex_replace(text, hello_re, "Hi");
    std::cout << "Simple replace:" << std::endl;
    std::cout << "  Before: " << text << std::endl;
    std::cout << "  After:  " << result << std::endl;

    // Replace with backreferences
    std::string date = "2024-01-15";
    std::regex date_re(R"((\d{4})-(\d{2})-(\d{2}))");
    std::string reformatted = std::regex_replace(date, date_re, "$2/$3/$1");
    std::cout << "\nDate reformatting:" << std::endl;
    std::cout << "  YYYY-MM-DD: " << date << std::endl;
    std::cout << "  MM/DD/YYYY: " << reformatted << std::endl;

    // Mask sensitive data
    std::string ssn = "My SSN is 123-45-6789 and hers is 987-65-4321";
    std::regex ssn_re(R"(\d{3}-\d{2}-(\d{4}))");
    std::string masked = std::regex_replace(ssn, ssn_re, "***-**-$1");
    std::cout << "\nSSN masking:" << std::endl;
    std::cout << "  Before: " << ssn << std::endl;
    std::cout << "  After:  " << masked << std::endl;

    // Remove matches (replace with empty string)
    std::string html = "<p>Hello <b>World</b></p>";
    std::regex tag_re(R"(<[^>]+>)");
    std::string plain = std::regex_replace(html, tag_re, "");
    std::cout << "\nStrip HTML tags:" << std::endl;
    std::cout << "  Before: " << html << std::endl;
    std::cout << "  After:  " << plain << std::endl;

    // Replace only first match using format_first_only
    std::string multi = "aaa bbb ccc aaa bbb";
    std::regex aaa_re("aaa");
    std::string first_only = std::regex_replace(multi, aaa_re, "XXX",
        std::regex_constants::format_first_only);
    std::cout << "\nFirst match only:" << std::endl;
    std::cout << "  Before: " << multi << std::endl;
    std::cout << "  After:  " << first_only << std::endl;

    // Normalize whitespace
    std::string messy = "too   many     spaces   here";
    std::regex space_re(R"(\s+)");
    std::string clean = std::regex_replace(messy, space_re, " ");
    std::cout << "\nNormalize spaces:" << std::endl;
    std::cout << "  Before: \"" << messy << "\"" << std::endl;
    std::cout << "  After:  \"" << clean << "\"" << std::endl;

    // Surround matches with markup
    std::string code = "Use print() and read() functions";
    std::regex func_re(R"((\w+)\(\))");
    std::string highlighted = std::regex_replace(code, func_re, "[$1()]");
    std::cout << "\nHighlight functions:" << std::endl;
    std::cout << "  Before: " << code << std::endl;
    std::cout << "  After:  " << highlighted << std::endl;

    return 0;
}

// Expected output:
// Simple replace:
//   Before: Hello World Hello World
//   After:  Hi World Hi World
//
// Date reformatting:
//   YYYY-MM-DD: 2024-01-15
//   MM/DD/YYYY: 01/15/2024
//
// SSN masking:
//   Before: My SSN is 123-45-6789 and hers is 987-65-4321
//   After:  My SSN is ***-**-6789 and hers is ***-**-4321
//
// Strip HTML tags:
//   Before: <p>Hello <b>World</b></p>
//   After:  Hello World
//
// First match only:
//   Before: aaa bbb ccc aaa bbb
//   After:  XXX bbb ccc aaa bbb
//
// Normalize spaces:
//   Before: "too   many     spaces   here"
//   After:  "too many spaces here"
//
// Highlight functions:
//   Before: Use print() and read() functions
//   After:  Use [print()] and [read()] functions
