// CodeNebula - C++11 Example: std::stoul, std::stoull
// Compile: g++ -std=c++11 -Wall -Wextra -o example stoul.cpp

// std::stoul and std::stoull convert strings to unsigned long and
// unsigned long long. They support multiple bases and are ideal for
// parsing large unsigned values like addresses and bitmasks.

#include <iostream>
#include <string>
#include <stdexcept>

int main() {
    // Basic unsigned conversions
    unsigned long ul = std::stoul("4294967295");
    unsigned long long ull = std::stoull("18446744073709551615");
    std::cout << "stoul max:  " << ul << std::endl;
    std::cout << "stoull max: " << ull << std::endl;

    // Regular values
    unsigned long a = std::stoul("12345");
    unsigned long long b = std::stoull("9876543210");
    std::cout << "\nstoul(\"12345\"):      " << a << std::endl;
    std::cout << "stoull(\"9876543210\"): " << b << std::endl;

    // Hexadecimal parsing (common for addresses and colors)
    unsigned long color = std::stoul("FF8800", nullptr, 16);
    unsigned long addr = std::stoul("DEADBEEF", nullptr, 16);
    std::cout << "\nHex parsing:" << std::endl;
    std::cout << "  color 0xFF8800: " << color << std::endl;
    std::cout << "  addr 0xDEADBEEF: " << addr << std::endl;

    // Binary parsing (useful for bitmasks)
    unsigned long mask = std::stoul("10110011", nullptr, 2);
    std::cout << "\nBinary \"10110011\" = " << mask << std::endl;

    // Octal parsing
    unsigned long perm = std::stoul("755", nullptr, 8);
    std::cout << "Octal \"755\" = " << perm << std::endl;

    // Auto-detect base
    unsigned long auto1 = std::stoul("0xFF", nullptr, 0);
    unsigned long auto2 = std::stoul("0777", nullptr, 0);
    unsigned long auto3 = std::stoul("100", nullptr, 0);
    std::cout << "\nAuto-detect:" << std::endl;
    std::cout << "  \"0xFF\" = " << auto1 << std::endl;
    std::cout << "  \"0777\" = " << auto2 << std::endl;
    std::cout << "  \"100\"  = " << auto3 << std::endl;

    // Position tracking
    std::string input = "42px";
    std::size_t pos;
    unsigned long pixels = std::stoul(input, &pos);
    std::string unit = input.substr(pos);
    std::cout << "\nParsing \"" << input << "\": value=" << pixels
              << " unit=\"" << unit << "\"" << std::endl;

    // Practical: parsing IP addresses
    std::string ip = "192.168.1.100";
    std::size_t offset = 0;
    std::cout << "\nIP octets from \"" << ip << "\":" << std::endl;
    for (int i = 0; i < 4; ++i) {
        unsigned long octet = std::stoul(ip.substr(offset), &pos);
        offset += pos + 1;  // skip the dot
        std::cout << "  [" << i << "] = " << octet << std::endl;
    }

    // Error handling
    try {
        std::stoul("-1");  // wraps around (unsigned)
        std::cout << "\nstoul(\"-1\") = " << std::stoul("-1") << " (wraps)" << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "\nstoul(\"-1\") out_of_range: " << e.what() << std::endl;
    }

    try {
        std::stoul("abc");
    } catch (const std::invalid_argument& e) {
        std::cout << "stoul(\"abc\") invalid: " << e.what() << std::endl;
    }

    return 0;
}

// Expected output (max values platform-dependent):
// stoul max:  4294967295
// stoull max: 18446744073709551615
//
// stoul("12345"):      12345
// stoull("9876543210"): 9876543210
//
// Hex parsing:
//   color 0xFF8800: 16746496
//   addr 0xDEADBEEF: 3735928559
//
// Binary "10110011" = 179
// Octal "755" = 493
//
// Auto-detect:
//   "0xFF" = 255
//   "0777" = 511
//   "100"  = 100
//
// Parsing "42px": value=42 unit="px"
//
// IP octets from "192.168.1.100":
//   [0] = 192
//   [1] = 168
//   [2] = 1
//   [3] = 100
//
// stoul("-1") = 4294967295 (wraps)
// stoul("abc") invalid: stoul
