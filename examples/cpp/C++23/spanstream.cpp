// CodeNebula - C++23 Example: std::spanstream
// Compile: g++ -std=c++23 -Wall -Wextra -o example spanstream.cpp
// Note: Requires GCC 13+ / Clang 17+

#include <iostream>
#include <span>
#include <spanstream>
#include <array>
#include <cstring>

// std::spanstream provides stream I/O over a fixed-size buffer (std::span).
// Unlike stringstream, it never allocates memory - it uses the provided buffer.
// Variants: ispanstream (input), ospanstream (output), spanstream (both).

int main() {
    std::cout << "=== std::spanstream fixed-buffer I/O ===\n\n";

    // --- Output to a fixed buffer ---
    std::cout << "--- ospanstream (output) ---\n";
    char out_buf[64] = {};
    std::ospanstream oss(std::span<char>(out_buf));

    oss << "Hello " << 42 << " " << 3.14;

    std::cout << "Written to buffer: \"" << out_buf << "\"\n";
    auto written = oss.span();
    std::cout << "Span size: " << written.size() << "\n\n";

    // --- Input from a fixed buffer ---
    std::cout << "--- ispanstream (input) ---\n";
    char in_buf[] = "100 200 300";
    std::ispanstream iss(std::span<char>(in_buf));

    int a, b, c;
    iss >> a >> b >> c;
    std::cout << "Read values: " << a << ", " << b << ", " << c << "\n\n";

    // --- Bidirectional spanstream ---
    std::cout << "--- spanstream (bidirectional) ---\n";
    std::array<char, 128> buf{};
    std::spanstream ss(std::span<char>(buf));

    // Write
    ss << "Name: Alice Age: 30";

    // Seek back to start and read
    ss.seekg(0);
    std::string label1, name, label2;
    int age;
    ss >> label1 >> name >> label2 >> age;

    std::cout << "Parsed: name=" << name << ", age=" << age << "\n\n";

    // --- Buffer reuse without allocation ---
    std::cout << "--- Buffer reuse ---\n";
    char reuse_buf[32] = {};
    std::ospanstream reuse_oss(std::span<char>(reuse_buf));

    reuse_oss << "First";
    std::cout << "First write: \"" << reuse_buf << "\"\n";

    // Reset and rewrite
    std::memset(reuse_buf, 0, sizeof(reuse_buf));
    reuse_oss.span(std::span<char>(reuse_buf));
    reuse_oss << "Second";
    std::cout << "After reset:  \"" << reuse_buf << "\"\n";

    std::cout << "\nspanstream never allocates heap memory!\n";

    return 0;
}

// Expected output:
// === std::spanstream fixed-buffer I/O ===
//
// --- ospanstream (output) ---
// Written to buffer: "Hello 42 3.14"
// Span size: 13
//
// --- ispanstream (input) ---
// Read values: 100, 200, 300
//
// --- spanstream (bidirectional) ---
// Parsed: name=Alice, age=30
//
// --- Buffer reuse ---
// First write: "First"
// After reset:  "Second"
//
// spanstream never allocates heap memory!
