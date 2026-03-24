// CodeNebula - C++17 Example: std::string_view
// Compile: g++ -std=c++17 -Wall -Wextra -o example string_view.cpp

// Demonstrates std::string_view, a lightweight non-owning reference to a
// contiguous character sequence. It avoids copies when you only need to read
// a string, and works with std::string, C-strings, and substrings.

#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <algorithm>

// ------------------------------------------------------------------
// 1. Function taking string_view: accepts string, char*, literals
// ------------------------------------------------------------------
void greet(std::string_view name) {
    std::cout << "  Hello, " << name << "! (length=" << name.size() << ")" << std::endl;
}

// ------------------------------------------------------------------
// 2. Efficient substring without copying
// ------------------------------------------------------------------
std::string_view extract_filename(std::string_view path) {
    auto pos = path.find_last_of('/');
    if (pos == std::string_view::npos) pos = path.find_last_of('\\');
    return (pos != std::string_view::npos) ? path.substr(pos + 1) : path;
}

// ------------------------------------------------------------------
// 3. Tokenizer using string_view (zero allocations)
// ------------------------------------------------------------------
std::vector<std::string_view> split(std::string_view str, char delim) {
    std::vector<std::string_view> tokens;
    std::size_t start = 0;
    while (start < str.size()) {
        auto end = str.find(delim, start);
        if (end == std::string_view::npos) end = str.size();
        if (end > start) {
            tokens.push_back(str.substr(start, end - start));
        }
        start = end + 1;
    }
    return tokens;
}

int main()
{
    // 1. Accepting different string types without overloads
    std::cout << "=== string_view as parameter ===" << std::endl;
    std::string s = "Alice";
    const char* cs = "Bob";
    greet(s);          // from std::string
    greet(cs);         // from const char*
    greet("Charlie");  // from string literal

    // 2. Non-owning substring
    std::cout << "\n=== substring (no copy) ===" << std::endl;
    std::string_view path = "/home/user/documents/report.pdf";
    auto filename = extract_filename(path);
    std::cout << "  path: " << path << std::endl;
    std::cout << "  file: " << filename << std::endl;

    // 3. Member functions
    std::cout << "\n=== member functions ===" << std::endl;
    std::string_view sv = "  Hello, World!  ";
    std::cout << "  original : [" << sv << "]" << std::endl;
    sv.remove_prefix(2);  // remove leading spaces
    sv.remove_suffix(2);  // remove trailing spaces
    std::cout << "  trimmed  : [" << sv << "]" << std::endl;
    std::cout << "  front    : '" << sv.front() << "'" << std::endl;
    std::cout << "  back     : '" << sv.back() << "'" << std::endl;
    std::cout << "  substr(0,5): " << sv.substr(0, 5) << std::endl;

    // 4. Searching
    std::cout << "\n=== searching ===" << std::endl;
    std::string_view text = "The quick brown fox jumps over the lazy dog";
    std::cout << "  text: " << text << std::endl;
    std::cout << "  find(\"fox\")  : position " << text.find("fox") << std::endl;
    std::cout << "  find(\"cat\")  : "
              << (text.find("cat") == std::string_view::npos ? "not found" : "found")
              << std::endl;
    std::cout << "  starts_with? : " << (text.substr(0, 3) == "The") << std::endl;

    // 5. Zero-copy tokenization
    std::cout << "\n=== split (zero-copy) ===" << std::endl;
    std::string_view csv = "apple,banana,cherry,date";
    auto tokens = split(csv, ',');
    for (auto t : tokens) {
        std::cout << "  [" << t << "]" << std::endl;
    }

    // 6. Comparison with string
    std::cout << "\n=== comparison ===" << std::endl;
    std::string str = "hello";
    std::string_view view = str;
    std::cout << "  str == view: " << std::boolalpha << (str == view) << std::endl;
    std::cout << "  view == \"hello\": " << (view == "hello") << std::endl;

    return 0;
}

/*
Expected output:

=== string_view as parameter ===
  Hello, Alice! (length=5)
  Hello, Bob! (length=3)
  Hello, Charlie! (length=7)

=== substring (no copy) ===
  path: /home/user/documents/report.pdf
  file: report.pdf

=== member functions ===
  original : [  Hello, World!  ]
  trimmed  : [Hello, World!]
  front    : 'H'
  back     : '!'
  substr(0,5): Hello

=== searching ===
  text: The quick brown fox jumps over the lazy dog
  find("fox")  : position 16
  find("cat")  : not found
  starts_with? : 1

=== split (zero-copy) ===
  [apple]
  [banana]
  [cherry]
  [date]

=== comparison ===
  str == view: true
  view == "hello": true
*/
