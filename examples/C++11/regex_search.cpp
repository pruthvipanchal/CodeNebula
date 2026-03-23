// CodeNebula - C++11 Example: std::regex_search
// Compile: g++ -std=c++11 -Wall -Wextra -o example regex_search.cpp

// std::regex_search finds the FIRST occurrence of a pattern anywhere
// in the string. Unlike regex_match, it doesn't require the entire
// string to match -- partial matches are found.

#include <iostream>
#include <regex>
#include <string>

int main() {
    std::string text = "The price is $42.50 and tax is $3.75 today.";

    // Find first number in text
    std::regex number_re(R"(\d+\.?\d*)");
    std::smatch match;

    if (std::regex_search(text, match, number_re)) {
        std::cout << "First number found:" << std::endl;
        std::cout << "  Match:    \"" << match[0] << "\"" << std::endl;
        std::cout << "  Position: " << match.position() << std::endl;
        std::cout << "  Length:   " << match.length() << std::endl;
        std::cout << "  Prefix:   \"" << match.prefix() << "\"" << std::endl;
        std::cout << "  Suffix:   \"" << match.suffix() << "\"" << std::endl;
    }

    // Find all matches by iterating through suffixes
    std::regex price_re(R"(\$(\d+\.\d{2}))");
    std::cout << "\nAll prices in: \"" << text << "\"" << std::endl;
    std::string::const_iterator search_start = text.cbegin();
    int count = 0;
    while (std::regex_search(search_start, text.cend(), match, price_re)) {
        std::cout << "  $" << match[1] << std::endl;
        search_start = match.suffix().first;
        ++count;
    }
    std::cout << "  Total found: " << count << std::endl;

    // Search with capturing groups
    std::string log = "ERROR [2024-01-15 14:30:22] Connection timeout on port 8080";
    std::regex log_re(R"((ERROR|WARN|INFO)\s+\[([^\]]+)\]\s+(.*))");

    if (std::regex_search(log, match, log_re)) {
        std::cout << "\nLog parsing:" << std::endl;
        std::cout << "  Level:   " << match[1] << std::endl;
        std::cout << "  Time:    " << match[2] << std::endl;
        std::cout << "  Message: " << match[3] << std::endl;
    }

    // Search for URLs
    std::string html = "Visit https://example.com or http://test.org for info";
    std::regex url_re(R"(https?://[\w.]+)");
    std::cout << "\nURLs found:" << std::endl;
    search_start = html.cbegin();
    while (std::regex_search(search_start, html.cend(), match, url_re)) {
        std::cout << "  " << match[0] << std::endl;
        search_start = match.suffix().first;
    }

    // Search returns false when no match
    std::regex zip_re(R"(\d{5})");
    std::string no_zip = "No zip code here!";
    if (!std::regex_search(no_zip, zip_re)) {
        std::cout << "\nNo zip code found in: \"" << no_zip << "\"" << std::endl;
    }

    // Match position details
    std::string data = "abc 123 def 456";
    std::regex num_re(R"(\d+)");
    if (std::regex_search(data, match, num_re)) {
        std::cout << "\nPosition details:" << std::endl;
        std::cout << "  Match:  \"" << match[0] << "\"" << std::endl;
        std::cout << "  At pos: " << match.position(0) << std::endl;
        std::cout << "  Ready:  " << (match.ready() ? "yes" : "no") << std::endl;
        std::cout << "  Empty:  " << (match.empty() ? "yes" : "no") << std::endl;
    }

    return 0;
}

// Expected output:
// First number found:
//   Match:    "42.50"
//   Position: 14
//   Length:   5
//   Prefix:   "The price is $"
//   Suffix:   " and tax is $3.75 today."
//
// All prices in: "The price is $42.50 and tax is $3.75 today."
//   $42.50
//   $3.75
//   Total found: 2
//
// Log parsing:
//   Level:   ERROR
//   Time:    2024-01-15 14:30:22
//   Message: Connection timeout on port 8080
//
// URLs found:
//   https://example.com
//   http://test.org
//
// No zip code found in: "No zip code here!"
//
// Position details:
//   Match:  "123"
//   At pos: 4
//   Ready:  yes
//   Empty:  no
