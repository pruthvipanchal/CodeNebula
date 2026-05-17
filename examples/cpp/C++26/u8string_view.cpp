// CodeNebula - C++26 Example: std::u8string_view
// Compile: g++ -std=c++26 -Wall -Wextra -o example u8string_view.cpp
// Note: Requires C++26 compiler support (GCC 15+ / Clang 19+ expected)

// C++26 improves std::u8string_view for working with UTF-8 encoded
// text. It provides a non-owning view over char8_t sequences with
// better interop with std::string_view and I/O facilities.

#include <iostream>
#include <string>
#include <string_view>
#include <cstdint>
#include <vector>

// --- C++26 u8string_view Improvements ---
//
// std::u8string_view u8sv = u8"Hello, \u4e16\u754c!";  // "Hello, World!" in Chinese
//
// // C++26: improved conversions and interop
// // Better integration with std::format and std::print
// std::println("{}", u8sv);  // Would print UTF-8 text
//
// // u8string_view works like string_view but for char8_t
// u8sv.starts_with(u8"Hello");
// u8sv.contains(u8"\u4e16");
// auto sub = u8sv.substr(0, 5);

// --- Simulation using C++20 features ---

// Helper to convert u8string to regular string for output
std::string to_stdout_string(std::u8string_view u8sv) {
    return std::string(reinterpret_cast<const char*>(u8sv.data()), u8sv.size());
}

// Count UTF-8 code points (not bytes)
std::size_t count_codepoints(std::u8string_view sv) {
    std::size_t count = 0;
    for (std::size_t i = 0; i < sv.size(); ) {
        uint8_t byte = static_cast<uint8_t>(sv[i]);
        if (byte < 0x80) i += 1;
        else if ((byte & 0xE0) == 0xC0) i += 2;
        else if ((byte & 0xF0) == 0xE0) i += 3;
        else i += 4;
        ++count;
    }
    return count;
}

int main() {
    std::cout << "=== C++26 std::u8string_view (Simulated) ===" << std::endl;

    // Create u8string_view
    std::u8string_view hello = u8"Hello, UTF-8!";
    std::cout << "u8string_view: \"" << to_stdout_string(hello) << "\"" << std::endl;
    std::cout << "  Size (bytes): " << hello.size() << std::endl;
    std::cout << "  Code points:  " << count_codepoints(hello) << std::endl;

    // Multi-byte UTF-8 content
    std::u8string_view emoji = u8"Stars: \xe2\x98\x85\xe2\x98\x86\xe2\x98\x85";
    std::cout << "\nUTF-8 with multi-byte: \"" << to_stdout_string(emoji) << "\"" << std::endl;
    std::cout << "  Size (bytes): " << emoji.size() << std::endl;
    std::cout << "  Code points:  " << count_codepoints(emoji) << std::endl;

    // Basic operations
    std::cout << "\nOperations:" << std::endl;
    std::cout << "  starts_with u8\"Hello\": " << std::boolalpha
              << hello.starts_with(u8"Hello") << std::endl;
    std::cout << "  ends_with u8\"UTF-8!\": " << hello.ends_with(u8"UTF-8!") << std::endl;
    std::cout << "  empty: " << hello.empty() << std::endl;

    // Substr
    auto sub = hello.substr(0, 5);
    std::cout << "  substr(0,5): \"" << to_stdout_string(sub) << "\"" << std::endl;

    // Type distinction from regular string_view
    static_assert(!std::is_same_v<std::string_view, std::u8string_view>);
    std::cout << "\nu8string_view != string_view (type-safe UTF-8)." << std::endl;

    std::cout << "u8string_view provides type-safe UTF-8 string references." << std::endl;
    return 0;
}

// Expected output:
// === C++26 std::u8string_view (Simulated) ===
// u8string_view: "Hello, UTF-8!"
//   Size (bytes): 13
//   Code points:  13
//
// UTF-8 with multi-byte: "Stars: ..."
//   Size (bytes): 16
//   Code points:  10
//
// Operations:
//   starts_with u8"Hello": true
//   ends_with u8"UTF-8!": true
//   empty: false
//   substr(0,5): "Hello"
//
// u8string_view != string_view (type-safe UTF-8).
// u8string_view provides type-safe UTF-8 string references.
