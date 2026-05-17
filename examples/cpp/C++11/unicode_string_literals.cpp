// CodeNebula - C++11 Example: Unicode String Literals
// Compile: g++ -std=c++11 -Wall -Wextra -o example unicode_string_literals.cpp
//
// This example demonstrates:
// - u8"" for UTF-8 encoded string literals
// - u"" for UTF-16 encoded string literals (char16_t)
// - U"" for UTF-32 encoded string literals (char32_t)
// - Raw string literals combined with Unicode prefixes
// - Size differences between encodings

#include <iostream>
#include <cstdint>
#include <cstring>

// ============================================================
// 1. Helper to print byte contents
// ============================================================
void printBytes(const char* label, const void* data, size_t len) {
    const unsigned char* bytes = static_cast<const unsigned char*>(data);
    std::cout << "  " << label << " (" << len << " bytes): ";
    for (size_t i = 0; i < len && i < 20; ++i) {
        if (i > 0) std::cout << " ";
        std::cout << std::hex;
        if (bytes[i] < 0x10) std::cout << "0";
        std::cout << static_cast<unsigned>(bytes[i]);
    }
    if (len > 20) std::cout << " ...";
    std::cout << std::dec << std::endl;
}

// ============================================================
// 2. UTF-8 string literals (u8"")
// ============================================================
void demonstrateUtf8() {
    std::cout << "--- UTF-8 strings (u8\"\") ---" << std::endl;

    const char* ascii = u8"Hello";
    std::cout << "  u8\"Hello\": " << ascii << std::endl;
    std::cout << "  strlen: " << std::strlen(ascii) << std::endl;

    // Multi-byte characters in UTF-8
    const char* withEuro = u8"Cost: \u20AC100";
    std::cout << "  u8\"Cost: <euro>100\": " << withEuro << std::endl;
    std::cout << "  strlen: " << std::strlen(withEuro)
              << " (euro = 3 bytes in UTF-8)" << std::endl;

    printBytes("u8\"AB\"", u8"AB", 2);
}

// ============================================================
// 3. UTF-16 string literals (u"")
// ============================================================
void demonstrateUtf16() {
    std::cout << "\n--- UTF-16 strings (u\"\") ---" << std::endl;

    const char16_t* hello = u"Hello";
    size_t len = 0;
    while (hello[len] != 0) ++len;
    std::cout << "  u\"Hello\" length: " << len << " code units" << std::endl;
    std::cout << "  Total bytes: " << len * sizeof(char16_t) << std::endl;

    // BMP characters fit in one char16_t
    const char16_t* withEuro = u"Price: \u20AC50";
    size_t elen = 0;
    while (withEuro[elen] != 0) ++elen;
    std::cout << "  u\"Price: <euro>50\" length: " << elen << " code units" << std::endl;

    printBytes("u\"AB\"", u"AB", 4);
}

// ============================================================
// 4. UTF-32 string literals (U"")
// ============================================================
void demonstrateUtf32() {
    std::cout << "\n--- UTF-32 strings (U\"\") ---" << std::endl;

    const char32_t* hello = U"Hello";
    size_t len = 0;
    while (hello[len] != 0) ++len;
    std::cout << "  U\"Hello\" length: " << len << " code points" << std::endl;
    std::cout << "  Total bytes: " << len * sizeof(char32_t) << std::endl;

    // Every character is exactly one char32_t
    const char32_t* mixed = U"A\u20AC\U0001F600";  // A + Euro + Smiley
    size_t mlen = 0;
    while (mixed[mlen] != 0) ++mlen;
    std::cout << "  U\"A<euro><smiley>\" length: " << mlen << " code points" << std::endl;

    printBytes("U\"AB\"", U"AB", 8);
}

// ============================================================
// 5. Encoding size comparison
// ============================================================
void compareSizes() {
    std::cout << "\n--- Encoding size comparison for 'A' ---" << std::endl;
    std::cout << "  u8\"A\": " << std::strlen(u8"A") << " byte(s)" << std::endl;

    const char16_t* u16a = u"A";
    size_t l16 = 0; while (u16a[l16]) ++l16;
    std::cout << "  u\"A\":  " << l16 * sizeof(char16_t) << " byte(s)" << std::endl;

    const char32_t* u32a = U"A";
    size_t l32 = 0; while (u32a[l32]) ++l32;
    std::cout << "  U\"A\":  " << l32 * sizeof(char32_t) << " byte(s)" << std::endl;
}

int main() {
    std::cout << "=== Unicode String Literals ===" << std::endl;

    demonstrateUtf8();
    demonstrateUtf16();
    demonstrateUtf32();
    compareSizes();

    return 0;
}

// Expected output:
// === Unicode String Literals ===
// --- UTF-8 strings (u8"") ---
//   u8"Hello": Hello
//   strlen: 5
//   u8"Cost: <euro>100": Cost: ...100
//   strlen: 11 (euro = 3 bytes in UTF-8)
//   u8"AB" (2 bytes): 41 42
//
// --- UTF-16 strings (u"") ---
//   u"Hello" length: 5 code units
//   Total bytes: 10
//   u"Price: <euro>50" length: 11 code units
//   u"AB" (4 bytes): 41 00 42 00
//
// --- UTF-32 strings (U"") ---
//   U"Hello" length: 5 code points
//   Total bytes: 20
//   U"A<euro><smiley>" length: 3 code points
//   U"AB" (8 bytes): 41 00 00 00 42 00 00 00
//
// --- Encoding size comparison for 'A' ---
//   u8"A": 1 byte(s)
//   u"A":  2 byte(s)
//   U"A":  4 byte(s)
