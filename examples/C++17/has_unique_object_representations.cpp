// CodeNebula - C++17 Example: std::has_unique_object_representations
// Compile: g++ -std=c++17 -Wall -Wextra -o example has_unique_object_representations.cpp

// Demonstrates std::has_unique_object_representations, a type trait that
// checks whether two objects with the same value always have identical
// byte representations. This is crucial for types used with hashing
// (memcmp-based equality) or serialization via raw memory.

#include <iostream>
#include <type_traits>
#include <cstdint>

// Packed struct: no padding, unique representation
struct Packed {
    uint32_t a;
    uint32_t b;
};

// Struct with likely padding: NOT unique representation
struct Padded {
    char c;       // 1 byte
    // padding    // 3 bytes (typically)
    int32_t i;    // 4 bytes
};

// Struct with bool: may have non-unique bits
struct WithBool {
    bool flag;
    int value;
};

// Empty struct
struct Empty {};

// Bitfield struct: padding bits possible
struct Bitfield {
    unsigned int x : 3;
    unsigned int y : 5;
};

int main()
{
    // ------------------------------------------------------------------
    // 1. Fundamental types
    // ------------------------------------------------------------------
    std::cout << "=== Fundamental Types ===" << std::endl;
    std::cout << "  char       : "
              << std::has_unique_object_representations_v<char> << std::endl;
    std::cout << "  int        : "
              << std::has_unique_object_representations_v<int> << std::endl;
    std::cout << "  unsigned   : "
              << std::has_unique_object_representations_v<unsigned> << std::endl;
    std::cout << "  uint8_t    : "
              << std::has_unique_object_representations_v<uint8_t> << std::endl;
    std::cout << "  uint32_t   : "
              << std::has_unique_object_representations_v<uint32_t> << std::endl;

    // Float/double do NOT have unique representations (NaN, -0 vs +0)
    std::cout << "  float      : "
              << std::has_unique_object_representations_v<float> << std::endl;
    std::cout << "  double     : "
              << std::has_unique_object_representations_v<double> << std::endl;

    // ------------------------------------------------------------------
    // 2. User-defined types
    // ------------------------------------------------------------------
    std::cout << "\n=== User-Defined Types ===" << std::endl;
    std::cout << "  Packed     : "
              << std::has_unique_object_representations_v<Packed> << std::endl;
    std::cout << "  Padded     : "
              << std::has_unique_object_representations_v<Padded> << std::endl;

    std::cout << "\n  sizeof(Padded) = " << sizeof(Padded)
              << " (char=1 + pad + int=4)" << std::endl;
    std::cout << "  sizeof(Packed) = " << sizeof(Packed)
              << " (two uint32_t, no pad)" << std::endl;

    // ------------------------------------------------------------------
    // 3. Practical: safe hashing guard
    // ------------------------------------------------------------------
    std::cout << "\n=== Hashing Safety Check ===" << std::endl;

    auto check_hashable = [](const char* name, bool unique) {
        if (unique)
            std::cout << "  " << name << ": safe for memcmp-based hashing" << std::endl;
        else
            std::cout << "  " << name << ": NOT safe for memcmp-based hashing" << std::endl;
    };

    check_hashable("Packed", std::has_unique_object_representations_v<Packed>);
    check_hashable("Padded", std::has_unique_object_representations_v<Padded>);
    check_hashable("int",    std::has_unique_object_representations_v<int>);
    check_hashable("double", std::has_unique_object_representations_v<double>);

    return 0;
}

/*
Expected output (typical x86-64):

=== Fundamental Types ===
  char       : 1
  int        : 1
  unsigned   : 1
  uint8_t    : 1
  uint32_t   : 1
  float      : 0
  double     : 0

=== User-Defined Types ===
  Packed     : 1
  Padded     : 0

  sizeof(Padded) = 8 (char=1 + pad + int=4)
  sizeof(Packed) = 8 (two uint32_t, no pad)

=== Hashing Safety Check ===
  Packed: safe for memcmp-based hashing
  Padded: NOT safe for memcmp-based hashing
  int: safe for memcmp-based hashing
  double: NOT safe for memcmp-based hashing
*/
