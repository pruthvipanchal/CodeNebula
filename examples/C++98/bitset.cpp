// CodeNebula - C++98 Example: bitset
// Compile: g++ -std=c++98 -Wall -Wextra -o example bitset.cpp

// std::bitset is a fixed-size sequence of N bits. It provides efficient
// bit manipulation and can be constructed from integers or strings.

#include <iostream>
#include <bitset>
#include <string>

int main() {
    // --- Construction ---
    std::cout << "=== Construction ===" << std::endl;

    // Default: all zeros
    std::bitset<8> b1;
    std::cout << "Default (8 bits):   " << b1 << std::endl;

    // From unsigned long
    std::bitset<8> b2(0xA5); // 10100101
    std::cout << "From 0xA5:          " << b2 << std::endl;

    // From string
    std::bitset<8> b3(std::string("11001010"));
    std::cout << "From \"11001010\":    " << b3 << std::endl;

    // Larger bitset
    std::bitset<16> b16(0xFF00);
    std::cout << "16-bit from 0xFF00: " << b16 << std::endl;

    // --- set, reset, flip ---
    std::cout << "\n=== set, reset, flip ===" << std::endl;
    std::bitset<8> bits;
    std::cout << "Initial:        " << bits << std::endl;

    bits.set(0);      // set bit 0
    bits.set(3);      // set bit 3
    bits.set(7);      // set bit 7
    std::cout << "After set 0,3,7: " << bits << std::endl;

    bits.reset(3);    // clear bit 3
    std::cout << "After reset 3:  " << bits << std::endl;

    bits.flip(4);     // toggle bit 4
    std::cout << "After flip 4:   " << bits << std::endl;

    bits.set();       // set all bits
    std::cout << "After set():    " << bits << std::endl;

    bits.reset();     // clear all bits
    std::cout << "After reset():  " << bits << std::endl;

    bits.flip();      // toggle all bits
    std::cout << "After flip():   " << bits << std::endl;

    // --- test ---
    std::cout << "\n=== test ===" << std::endl;
    std::bitset<8> t(std::string("10110010"));
    std::cout << "Bitset: " << t << std::endl;
    for (int i = 7; i >= 0; --i) {
        std::cout << "  bit " << i << " = " << t.test(static_cast<std::size_t>(i)) << std::endl;
    }

    // --- count, size, any, none ---
    std::cout << "\n=== count, size, any, none ===" << std::endl;
    std::bitset<8> c(std::string("10110010"));
    std::cout << "Bitset:  " << c << std::endl;
    std::cout << "count:   " << c.count() << " (number of 1s)" << std::endl;
    std::cout << "size:    " << c.size() << " (total bits)" << std::endl;
    std::cout << "any:     " << (c.any() ? "true" : "false") << std::endl;
    std::cout << "none:    " << (c.none() ? "true" : "false") << std::endl;

    std::bitset<8> empty;
    std::cout << "\nEmpty:   " << empty << std::endl;
    std::cout << "any:     " << (empty.any() ? "true" : "false") << std::endl;
    std::cout << "none:    " << (empty.none() ? "true" : "false") << std::endl;

    // --- to_string and to_ulong ---
    std::cout << "\n=== to_string and to_ulong ===" << std::endl;
    std::bitset<8> conv(42);
    std::cout << "Bitset:     " << conv << std::endl;
    std::cout << "to_string:  " << conv.to_string() << std::endl;
    std::cout << "to_ulong:   " << conv.to_ulong() << std::endl;

    // --- Bitwise operators ---
    std::cout << "\n=== Bitwise operators ===" << std::endl;
    std::bitset<8> a(std::string("11001100"));
    std::bitset<8> b(std::string("10101010"));
    std::cout << "a:       " << a << std::endl;
    std::cout << "b:       " << b << std::endl;
    std::cout << "a & b:   " << (a & b) << std::endl;
    std::cout << "a | b:   " << (a | b) << std::endl;
    std::cout << "a ^ b:   " << (a ^ b) << std::endl;
    std::cout << "~a:      " << (~a) << std::endl;

    // --- Shift operators ---
    std::cout << "\n=== Shift operators ===" << std::endl;
    std::bitset<8> sh(std::string("00110011"));
    std::cout << "Original:  " << sh << std::endl;
    std::cout << "sh << 2:   " << (sh << 2) << std::endl;
    std::cout << "sh >> 2:   " << (sh >> 2) << std::endl;

    // --- Compound assignment operators ---
    std::cout << "\n=== Compound assignment ===" << std::endl;
    std::bitset<8> x(std::string("11110000"));
    std::bitset<8> y(std::string("00111100"));
    std::cout << "x:       " << x << std::endl;
    std::cout << "y:       " << y << std::endl;
    x &= y;
    std::cout << "x &= y:  " << x << std::endl;
    x |= std::bitset<8>(std::string("10000001"));
    std::cout << "x |= :   " << x << std::endl;
    x <<= 1;
    std::cout << "x <<= 1: " << x << std::endl;

    // --- Comparison ---
    std::cout << "\n=== Comparison ===" << std::endl;
    std::bitset<8> p(std::string("11001100"));
    std::bitset<8> q(std::string("11001100"));
    std::bitset<8> r(std::string("11001101"));
    std::cout << "p == q: " << (p == q ? "true" : "false") << std::endl;
    std::cout << "p != r: " << (p != r ? "true" : "false") << std::endl;

    // --- operator[] ---
    std::cout << "\n=== operator[] ===" << std::endl;
    std::bitset<8> idx(std::string("00000000"));
    idx[0] = 1;
    idx[2] = 1;
    idx[4] = 1;
    std::cout << "After setting bits 0,2,4: " << idx << std::endl;
    std::cout << "idx[0]=" << idx[0] << ", idx[1]=" << idx[1] << std::endl;

    return 0;
}

/*
Expected output:
=== Construction ===
Default (8 bits):   00000000
From 0xA5:          10100101
From "11001010":    11001010
16-bit from 0xFF00: 1111111100000000

=== set, reset, flip ===
Initial:        00000000
After set 0,3,7: 10001001
After reset 3:  10000001
After flip 4:   10010001
After set():    11111111
After reset():  00000000
After flip():   11111111

=== test ===
Bitset: 10110010
  bit 7 = 1
  bit 6 = 0
  bit 5 = 1
  bit 4 = 1
  bit 3 = 0
  bit 2 = 0
  bit 1 = 1
  bit 0 = 0

=== count, size, any, none ===
Bitset:  10110010
count:   4 (number of 1s)
size:    8 (total bits)
any:     true
none:    false

Empty:   00000000
any:     false
none:    true

=== to_string and to_ulong ===
Bitset:     00101010
to_string:  00101010
to_ulong:   42

=== Bitwise operators ===
a:       11001100
b:       10101010
a & b:   10001000
a | b:   11101110
a ^ b:   01100110
~a:      00110011

=== Shift operators ===
Original:  00110011
sh << 2:   11001100
sh >> 2:   00001100

=== Compound assignment ===
x:       11110000
y:       00111100
x &= y:  00110000
x |= :   10110001
x <<= 1: 01100010

=== Comparison ===
p == q: true
p != r: true

=== operator[] ===
After setting bits 0,2,4: 00010101
idx[0]=1, idx[1]=0
*/
