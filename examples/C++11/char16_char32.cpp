// CodeNebula - C++11 Example: char16_t and char32_t Types
// Compile: g++ -std=c++11 -Wall -Wextra -o example char16_char32.cpp
//
// This example demonstrates:
// - char16_t for UTF-16 encoded characters
// - char32_t for UTF-32 encoded characters
// - Size and alignment differences from char and wchar_t
// - Basic operations on these character types
// - u'' and U'' character literals

#include <iostream>
#include <cstdint>
#include <string>

// ============================================================
// 1. Helper to print code point values
// ============================================================
void printCodePoint(const char* label, char32_t cp) {
    std::cout << "  " << label << ": U+"
              << std::hex << static_cast<uint32_t>(cp)
              << " (decimal " << std::dec << static_cast<uint32_t>(cp) << ")"
              << std::endl;
}

// ============================================================
// 2. Working with char16_t
// ============================================================
void demonstrateChar16() {
    std::cout << "--- char16_t ---" << std::endl;
    std::cout << "  sizeof(char16_t): " << sizeof(char16_t) << " bytes" << std::endl;
    std::cout << "  alignof(char16_t): " << alignof(char16_t) << std::endl;

    // Basic Latin characters
    char16_t letterA = u'A';
    char16_t digit5 = u'5';
    char16_t euro = u'\u20AC';  // Euro sign

    std::cout << "  u'A' value: " << static_cast<uint16_t>(letterA) << std::endl;
    std::cout << "  u'5' value: " << static_cast<uint16_t>(digit5) << std::endl;
    std::cout << "  Euro sign (U+20AC) value: " << static_cast<uint16_t>(euro) << std::endl;

    // char16_t string (u"...")
    const char16_t* greeting = u"Hello";
    size_t len = 0;
    while (greeting[len] != u'\0') ++len;
    std::cout << "  u\"Hello\" length: " << len << " code units" << std::endl;
}

// ============================================================
// 3. Working with char32_t
// ============================================================
void demonstrateChar32() {
    std::cout << "\n--- char32_t ---" << std::endl;
    std::cout << "  sizeof(char32_t): " << sizeof(char32_t) << " bytes" << std::endl;
    std::cout << "  alignof(char32_t): " << alignof(char32_t) << std::endl;

    // Each char32_t holds exactly one Unicode code point
    char32_t smiley = U'\U0001F600';       // Grinning face
    char32_t musicNote = U'\U0001D11E';    // Musical symbol G clef
    char32_t heartSuit = U'\u2665';        // Heart suit

    printCodePoint("Smiley face", smiley);
    printCodePoint("G clef", musicNote);
    printCodePoint("Heart suit", heartSuit);

    // char32_t string (U"...")
    const char32_t* text = U"ABC\U0001F600";
    size_t len = 0;
    while (text[len] != U'\0') ++len;
    std::cout << "  U\"ABC<smiley>\" length: " << len << " code points" << std::endl;
}

// ============================================================
// 4. Comparison of character type sizes
// ============================================================
void compareSizes() {
    std::cout << "\n--- Size comparison ---" << std::endl;
    std::cout << "  sizeof(char):     " << sizeof(char) << " byte(s)" << std::endl;
    std::cout << "  sizeof(wchar_t):  " << sizeof(wchar_t) << " byte(s)" << std::endl;
    std::cout << "  sizeof(char16_t): " << sizeof(char16_t) << " byte(s)" << std::endl;
    std::cout << "  sizeof(char32_t): " << sizeof(char32_t) << " byte(s)" << std::endl;

    // char16_t and char32_t have guaranteed sizes
    static_assert(sizeof(char16_t) == 2, "char16_t must be 2 bytes");
    static_assert(sizeof(char32_t) == 4, "char32_t must be 4 bytes");
    std::cout << "  static_assert: sizes verified at compile time" << std::endl;
}

int main() {
    std::cout << "=== char16_t and char32_t Types ===" << std::endl;

    demonstrateChar16();
    demonstrateChar32();
    compareSizes();

    // Arithmetic on code points
    std::cout << "\n--- Code point arithmetic ---" << std::endl;
    char32_t base = U'A';
    for (int i = 0; i < 5; ++i) {
        char32_t ch = base + static_cast<char32_t>(i);
        std::cout << "  U'A' + " << i << " = code point "
                  << static_cast<uint32_t>(ch) << std::endl;
    }

    return 0;
}

// Expected output:
// === char16_t and char32_t Types ===
// --- char16_t ---
//   sizeof(char16_t): 2 bytes
//   alignof(char16_t): 2
//   u'A' value: 65
//   u'5' value: 53
//   Euro sign (U+20AC) value: 8364
//   u"Hello" length: 5 code units
//
// --- char32_t ---
//   sizeof(char32_t): 4 bytes
//   alignof(char32_t): 4
//   Smiley face: U+1f600 (decimal 128512)
//   G clef: U+1d11e (decimal 119070)
//   Heart suit: U+2665 (decimal 9829)
//   U"ABC<smiley>" length: 4 code points
//
// --- Size comparison ---
//   sizeof(char):     1 byte(s)
//   sizeof(wchar_t):  4 byte(s)
//   sizeof(char16_t): 2 byte(s)
//   sizeof(char32_t): 4 byte(s)
//   static_assert: sizes verified at compile time
//
// --- Code point arithmetic ---
//   U'A' + 0 = code point 65
//   U'A' + 1 = code point 66
//   U'A' + 2 = code point 67
//   U'A' + 3 = code point 68
//   U'A' + 4 = code point 69
