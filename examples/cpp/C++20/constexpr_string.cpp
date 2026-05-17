// CodeNebula - C++20 Example: Constexpr std::string
// Compile: g++ -std=c++20 -Wall -Wextra -o example constexpr_string.cpp

// Demonstrates constexpr std::string in C++20: string operations at compile
// time using transient allocation. Strings must not escape constexpr context.

#include <iostream>
#include <string>
#include <array>

// ------------------------------------------------------------------
// 1. constexpr string concatenation
// ------------------------------------------------------------------
constexpr int concat_length(const char* a, const char* b) {
    std::string s = std::string(a) + std::string(b);
    return static_cast<int>(s.size());
}

// ------------------------------------------------------------------
// 2. constexpr string comparison
// ------------------------------------------------------------------
constexpr bool is_palindrome(const char* str) {
    std::string s(str);
    int left = 0;
    int right = static_cast<int>(s.size()) - 1;
    while (left < right) {
        if (s[left] != s[right]) return false;
        ++left;
        --right;
    }
    return true;
}

// ------------------------------------------------------------------
// 3. constexpr string search
// ------------------------------------------------------------------
constexpr bool contains(const char* haystack, const char* needle) {
    std::string h(haystack);
    std::string n(needle);
    return h.find(n) != std::string::npos;
}

constexpr int find_position(const char* haystack, const char* needle) {
    std::string h(haystack);
    auto pos = h.find(needle);
    return pos == std::string::npos ? -1 : static_cast<int>(pos);
}

// ------------------------------------------------------------------
// 4. constexpr word counting
// ------------------------------------------------------------------
constexpr int count_words(const char* text) {
    std::string s(text);
    if (s.empty()) return 0;

    int count = 0;
    bool in_word = false;
    for (char c : s) {
        if (c == ' ' || c == '\t' || c == '\n') {
            in_word = false;
        } else if (!in_word) {
            in_word = true;
            ++count;
        }
    }
    return count;
}

// ------------------------------------------------------------------
// 5. constexpr character counting
// ------------------------------------------------------------------
constexpr int count_char(const char* text, char target) {
    std::string s(text);
    int count = 0;
    for (char c : s)
        if (c == target) ++count;
    return count;
}

// ------------------------------------------------------------------
// 6. constexpr string to extract result into fixed array
// ------------------------------------------------------------------
constexpr auto make_uppercase_chars(const char* input) {
    std::string s(input);
    struct Result {
        char data[32]{};
        int size = 0;
    };
    Result r;
    for (char c : s) {
        char upper = (c >= 'a' && c <= 'z') ? static_cast<char>(c - 32) : c;
        r.data[r.size++] = upper;
    }
    return r;
}

// ------------------------------------------------------------------
// 7. constexpr string reversal check
// ------------------------------------------------------------------
constexpr auto reversed_chars(const char* input) {
    std::string s(input);
    struct Result {
        char data[32]{};
        int size = 0;
    };
    Result r;
    r.size = static_cast<int>(s.size());
    for (int i = 0; i < r.size; ++i)
        r.data[i] = s[r.size - 1 - i];
    return r;
}

int main()
{
    std::cout << "=== constexpr String Concatenation ===" << std::endl;
    constexpr int len = concat_length("Hello, ", "World!");
    std::cout << "  \"Hello, \" + \"World!\" length = " << len << std::endl;
    static_assert(len == 13);

    std::cout << "\n=== constexpr Palindrome Check ===" << std::endl;
    constexpr bool p1 = is_palindrome("racecar");
    constexpr bool p2 = is_palindrome("hello");
    constexpr bool p3 = is_palindrome("madam");
    constexpr bool p4 = is_palindrome("abba");
    std::cout << "  racecar: " << p1 << std::endl;
    std::cout << "  hello:   " << p2 << std::endl;
    std::cout << "  madam:   " << p3 << std::endl;
    std::cout << "  abba:    " << p4 << std::endl;

    std::cout << "\n=== constexpr String Search ===" << std::endl;
    constexpr bool has_world = contains("Hello, World!", "World");
    constexpr bool has_xyz = contains("Hello, World!", "xyz");
    constexpr int pos = find_position("Hello, World!", "World");
    std::cout << "  Contains 'World': " << has_world << std::endl;
    std::cout << "  Contains 'xyz':   " << has_xyz << std::endl;
    std::cout << "  'World' at pos:   " << pos << std::endl;

    std::cout << "\n=== constexpr Word Count ===" << std::endl;
    constexpr int w1 = count_words("The quick brown fox");
    constexpr int w2 = count_words("Hello");
    constexpr int w3 = count_words("  spaces   between  words  ");
    std::cout << "  \"The quick brown fox\": " << w1 << " words" << std::endl;
    std::cout << "  \"Hello\": " << w2 << " word" << std::endl;
    std::cout << "  \"  spaces   between  words  \": " << w3 << " words" << std::endl;

    std::cout << "\n=== constexpr Char Count ===" << std::endl;
    constexpr int es = count_char("Mississippi", 's');
    constexpr int ps = count_char("Mississippi", 'p');
    std::cout << "  's' in Mississippi: " << es << std::endl;
    std::cout << "  'p' in Mississippi: " << ps << std::endl;

    std::cout << "\n=== constexpr Uppercase ===" << std::endl;
    constexpr auto upper = make_uppercase_chars("Hello C++20!");
    std::cout << "  ";
    for (int i = 0; i < upper.size; ++i)
        std::cout << upper.data[i];
    std::cout << std::endl;

    std::cout << "\n=== constexpr Reverse ===" << std::endl;
    constexpr auto rev = reversed_chars("C++20");
    std::cout << "  Reversed: ";
    for (int i = 0; i < rev.size; ++i)
        std::cout << rev.data[i];
    std::cout << std::endl;

    return 0;
}

/*
Expected output:

=== constexpr String Concatenation ===
  "Hello, " + "World!" length = 13

=== constexpr Palindrome Check ===
  racecar: 1
  hello:   0
  madam:   1
  abba:    1

=== constexpr String Search ===
  Contains 'World': 1
  Contains 'xyz':   0
  'World' at pos:   7

=== constexpr Word Count ===
  "The quick brown fox": 4 words
  "Hello": 1 word
  "  spaces   between  words  ": 3 words

=== constexpr Char Count ===
  's' in Mississippi: 4
  'p' in Mississippi: 2

=== constexpr Uppercase ===
  HELLO C++20!

=== constexpr Reverse ===
  Reversed: 02++C
*/
