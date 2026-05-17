// CodeNebula - C++26 Example: std::spanstream Improvements
// Compile: g++ -std=c++26 -Wall -Wextra -o example spanstream.cpp
// Note: Requires C++26 compiler support

#include <iostream>
#include <sstream>
#include <string>
#include <array>
#include <cstring>

// std::spanstream (C++23) provides stream I/O over fixed buffers (no heap).
// C++26 adds: constexpr support, std::format interplay, better error reporting.
// Types: ispanstream (input), ospanstream (output), spanstream (both)

namespace span_sim {
    class ospanstream {  // Simulates writing to a fixed buffer
        char* buf_; std::size_t cap_, pos_ = 0;
    public:
        ospanstream(char* buf, std::size_t cap) : buf_(buf), cap_(cap) {}
        ospanstream& operator<<(const char* s) {
            auto len = std::min(std::strlen(s), cap_ - pos_);
            std::memcpy(buf_ + pos_, s, len); pos_ += len; return *this;
        }
        ospanstream& operator<<(int v) {
            char tmp[32]; int n = std::snprintf(tmp, sizeof(tmp), "%d", v);
            if (n > 0) { auto c = std::min((std::size_t)n, cap_ - pos_);
                std::memcpy(buf_ + pos_, tmp, c); pos_ += c; }
            return *this;
        }
        std::size_t size() const { return pos_; }
        std::string_view view() const { return {buf_, pos_}; }
    };

    class ispanstream {  // Simulates reading from a fixed buffer
        std::istringstream iss_;
    public:
        explicit ispanstream(std::string_view sv) : iss_(std::string(sv)) {}
        ispanstream& operator>>(int& v) { iss_ >> v; return *this; }
        ispanstream& operator>>(std::string& s) { iss_ >> s; return *this; }
    };
}

int main() {
    std::cout << "--- std::spanstream (C++26) ---\n\n";

    // Write to stack buffer (zero heap allocation)
    std::array<char, 128> buffer{};
    span_sim::ospanstream out(buffer.data(), buffer.size());
    out << "Score: " << 42 << " Level: " << 7;
    std::cout << "Written: \"" << out.view() << "\"\n";
    std::cout << "Bytes: " << out.size() << " / " << buffer.size() << "\n";

    // Read from fixed buffer
    std::cout << "\n--- Reading ---\n";
    span_sim::ispanstream in("100 200 300");
    int a, b, c; in >> a >> b >> c;
    std::cout << "Values: " << a << ", " << b << ", " << c << "\n";

    // Parse mixed data
    span_sim::ispanstream mixed("player1 9500");
    std::string name; int score;
    mixed >> name >> score;
    std::cout << "Name: " << name << ", Score: " << score << "\n";
    std::cout << "\nspanstream: zero-allocation stream I/O.\n";
    return 0;
}

// Expected output:
// --- std::spanstream (C++26) ---
//
// Written: "Score: 42 Level: 7"
// Bytes: 18 / 128
//
// --- Reading ---
// Values: 100, 200, 300
// Name: player1, Score: 9500
//
// spanstream: zero-allocation stream I/O.
