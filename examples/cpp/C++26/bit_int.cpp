// CodeNebula - C++26 Example: std::bit_int (Proposed)
// Compile: g++ -std=c++26 -Wall -Wextra -o example bit_int.cpp
// Note: Requires C++26 compiler support

#include <iostream>
#include <cstdint>

// C++26 proposes std::bit_int<N> -- exact-width integer with N bits.
// Useful for hardware registers, protocol fields, cryptography.
// Arithmetic wraps via two's complement at N bits.

namespace bit_sim {
    template <int N>
    class bit_int {
        static_assert(N > 0 && N <= 64);
        int64_t value_;
        static constexpr int64_t mask(int64_t v) {
            constexpr uint64_t umask = (N == 64) ? ~uint64_t{0} : ((uint64_t{1} << N) - 1);
            uint64_t masked = static_cast<uint64_t>(v) & umask;
            if (N < 64 && (masked & (uint64_t{1} << (N - 1)))) masked |= ~umask;
            return static_cast<int64_t>(masked);
        }
    public:
        static constexpr int64_t min_val = -(int64_t{1} << (N - 1));
        static constexpr int64_t max_val = (int64_t{1} << (N - 1)) - 1;
        constexpr bit_int(int64_t v = 0) : value_(mask(v)) {}
        constexpr int64_t value() const { return value_; }
        constexpr bit_int operator+(bit_int o) const { return bit_int(value_ + o.value_); }
        constexpr bit_int operator-(bit_int o) const { return bit_int(value_ - o.value_); }
        constexpr bit_int operator*(bit_int o) const { return bit_int(value_ * o.value_); }
    };
}

int main() {
    std::cout << "--- std::bit_int (C++26 Proposed) ---\n\n";
    using int4 = bit_sim::bit_int<4>;
    std::cout << "bit_int<4> range: [" << int4::min_val << ", " << int4::max_val << "]\n";

    int4 a(5), b(3);
    std::cout << "a=5, b=3\n";
    std::cout << "a + b = " << (a + b).value() << "  (wraps: 8 -> -8)\n";
    std::cout << "a - b = " << (a - b).value() << "\n";
    std::cout << "a * b = " << (a * b).value() << "  (wraps: 15 -> -1)\n";

    std::cout << "\n--- Various Widths ---\n";
    using int8_t_ = bit_sim::bit_int<8>;
    using int12 = bit_sim::bit_int<12>;
    std::cout << "bit_int<8>  range: [" << int8_t_::min_val << ", " << int8_t_::max_val << "]\n";
    std::cout << "bit_int<12> range: [" << int12::min_val << ", " << int12::max_val << "]\n";

    std::cout << "\n--- Overflow ---\n";
    int8_t_ x(127);
    std::cout << "bit_int<8>(127)+1 = " << (x + int8_t_(1)).value() << "\n";
    std::cout << "bit_int<8>(-128)-1 = " << (int8_t_(-128) - int8_t_(1)).value() << "\n";
    std::cout << "\nbit_int<N> provides exact-width integer semantics.\n";
    return 0;
}

// Expected output:
// --- std::bit_int (C++26 Proposed) ---
//
// bit_int<4> range: [-8, 7]
// a=5, b=3
// a + b = -8  (wraps: 8 -> -8)
// a - b = 2
// a * b = -1  (wraps: 15 -> -1)
//
// --- Various Widths ---
// bit_int<8>  range: [-128, 127]
// bit_int<12> range: [-2048, 2047]
//
// --- Overflow ---
// bit_int<8>(127)+1 = -128
// bit_int<8>(-128)-1 = 127
//
// bit_int<N> provides exact-width integer semantics.
