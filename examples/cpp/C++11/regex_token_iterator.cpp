// CodeNebula - C++11 Example: std::regex_token_iterator
// Compile: g++ -std=c++11 -Wall -Wextra -o example regex_token_iterator.cpp

// std::regex_token_iterator iterates over specific sub-matches or the
// parts between matches. With submatch index -1, it acts as a splitter.
// With indices 0, 1, 2..., it extracts specific capture groups.

#include <iostream>
#include <regex>
#include <string>
#include <vector>

int main() {
    // === Splitting strings (submatch = -1) ===
    std::string csv = "Alice,30,London,Engineer";
    std::regex comma_re(",");

    std::cout << "Split by comma:" << std::endl;
    std::sregex_token_iterator it(csv.begin(), csv.end(), comma_re, -1);
    std::sregex_token_iterator end;
    for (; it != end; ++it) {
        std::cout << "  \"" << *it << "\"" << std::endl;
    }

    // Split by multiple delimiters
    std::string mixed = "one;two,three:four five";
    std::regex delim_re(R"([;,:\s]+)");
    std::cout << "\nSplit by mixed delimiters:" << std::endl;
    for (std::sregex_token_iterator t(mixed.begin(), mixed.end(), delim_re, -1);
         t != end; ++t) {
        std::cout << "  \"" << *t << "\"" << std::endl;
    }

    // === Extract submatch 0 (full match) ===
    std::string text = "Call 555-1234 or 555-5678 today";
    std::regex phone_re(R"(\d{3}-\d{4})");
    std::cout << "\nAll phone numbers (submatch 0):" << std::endl;
    for (std::sregex_token_iterator t(text.begin(), text.end(), phone_re, 0);
         t != end; ++t) {
        std::cout << "  " << *t << std::endl;
    }

    // === Extract specific capture groups ===
    std::string pairs = "name=Alice age=30 city=London";
    std::regex kv_re(R"((\w+)=(\w+))");

    // Extract just keys (group 1)
    std::cout << "\nKeys only (group 1):" << std::endl;
    for (std::sregex_token_iterator t(pairs.begin(), pairs.end(), kv_re, 1);
         t != end; ++t) {
        std::cout << "  " << *t << std::endl;
    }

    // Extract just values (group 2)
    std::cout << "\nValues only (group 2):" << std::endl;
    for (std::sregex_token_iterator t(pairs.begin(), pairs.end(), kv_re, 2);
         t != end; ++t) {
        std::cout << "  " << *t << std::endl;
    }

    // === Multiple submatch indices ===
    std::string data = "2024-01-15 2024-06-30 2024-12-25";
    std::regex date_re(R"((\d{4})-(\d{2})-(\d{2}))");

    // Extract year and day (groups 1 and 3), interleaved
    std::cout << "\nYear and day (groups 1,3):" << std::endl;
    std::vector<int> indices = {1, 3};
    for (std::sregex_token_iterator t(data.begin(), data.end(), date_re, indices);
         t != end; ++t) {
        std::cout << "  " << *t << std::endl;
    }

    // === Collect into a vector ===
    std::string words_str = "hello world foo bar baz";
    std::regex space_re(R"(\s+)");
    std::sregex_token_iterator first(words_str.begin(), words_str.end(), space_re, -1);
    std::vector<std::string> words(first, end);
    std::cout << "\nVector of words (" << words.size() << "): ";
    for (const auto& w : words) std::cout << "[" << w << "] ";
    std::cout << std::endl;

    return 0;
}

// Expected output:
// Split by comma:
//   "Alice"
//   "30"
//   "London"
//   "Engineer"
//
// Split by mixed delimiters:
//   "one"
//   "two"
//   "three"
//   "four"
//   "five"
//
// All phone numbers (submatch 0):
//   555-1234
//   555-5678
//
// Keys only (group 1):
//   name
//   age
//   city
//
// Values only (group 2):
//   Alice
//   30
//   London
//
// Year and day (groups 1,3):
//   2024
//   15
//   2024
//   30
//   2024
//   25
//
// Vector of words (5): [hello] [world] [foo] [bar] [baz]
