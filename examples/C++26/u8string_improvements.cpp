// CodeNebula - C++26 Example: std::u8string Improvements
// Compile: g++ -std=c++26 -Wall -Wextra -o example u8string_improvements.cpp
// Note: Requires C++26 compiler support (GCC 15+ / Clang 19+ expected)

// C++26 improves std::u8string (std::basic_string<char8_t>) with better
// I/O support, formatting integration, and conversions to/from other
// string types. This makes UTF-8 strings practical for everyday use.

#include <iostream>
#include <string>
#include <cstdint>

// --- C++26 u8string Improvements ---
//
// std::u8string u8s = u8"Hello, C++26!";
//
// // C++26: direct output support
// std::println("{}", u8s);  // Works with std::format/print
//
// // C++26: improved conversions
// std::string s = std::string_from(u8s);  // Proposed conversion
// std::u8string back = std::u8string_from(s);
//
// // All std::string operations work
// u8s += u8" More text";
// u8s.find(u8"C++26");
// u8s.substr(0, 5);

// --- Simulation using C++20 features ---

// Helper: convert u8string to regular string for I/O
std::string from_u8string(const std::u8string& u8s) {
    return std::string(reinterpret_cast<const char*>(u8s.data()), u8s.size());
}

// Helper: convert regular string to u8string
std::u8string to_u8string(const std::string& s) {
    return std::u8string(reinterpret_cast<const char8_t*>(s.data()), s.size());
}

// Count UTF-8 code points
std::size_t utf8_length(const std::u8string& s) {
    std::size_t count = 0;
    for (std::size_t i = 0; i < s.size(); ) {
        auto byte = static_cast<uint8_t>(s[i]);
        if (byte < 0x80) i += 1;
        else if ((byte & 0xE0) == 0xC0) i += 2;
        else if ((byte & 0xF0) == 0xE0) i += 3;
        else i += 4;
        ++count;
    }
    return count;
}

int main() {
    std::cout << "=== C++26 std::u8string Improvements (Simulated) ===" << std::endl;

    // Construction
    std::u8string greeting = u8"Hello, C++26!";
    std::cout << "u8string: \"" << from_u8string(greeting) << "\"" << std::endl;

    // String operations
    greeting += u8" Welcome.";
    std::cout << "After append: \"" << from_u8string(greeting) << "\"" << std::endl;

    auto pos = greeting.find(u8"C++26");
    std::cout << "\"C++26\" at position: " << pos << std::endl;

    auto sub = greeting.substr(0, 5);
    std::cout << "substr(0,5): \"" << from_u8string(sub) << "\"" << std::endl;

    // Size vs code point count
    std::u8string mixed = u8"ABC\xc3\xa9\xc3\xa0"; // ABCea (e-acute, a-grave)
    std::cout << "\nMixed u8string: \"" << from_u8string(mixed) << "\"" << std::endl;
    std::cout << "  size() bytes:  " << mixed.size() << std::endl;
    std::cout << "  code points:   " << utf8_length(mixed) << std::endl;

    // Conversion round-trip
    std::string regular = "Convert me";
    std::u8string converted = to_u8string(regular);
    std::string back = from_u8string(converted);
    std::cout << "\nRound-trip: \"" << regular << "\" -> u8 -> \"" << back << "\"" << std::endl;
    std::cout << "Match: " << std::boolalpha << (regular == back) << std::endl;

    std::cout << "u8string: owning UTF-8 string with full string API." << std::endl;
    return 0;
}

// Expected output:
// === C++26 std::u8string Improvements (Simulated) ===
// u8string: "Hello, C++26!"
// After append: "Hello, C++26! Welcome."
// "C++26" at position: 7
// substr(0,5): "Hello"
//
// Mixed u8string: "ABC..."
//   size() bytes:  7
//   code points:   5
//
// Round-trip: "Convert me" -> u8 -> "Convert me"
// Match: true
// u8string: owning UTF-8 string with full string API.
