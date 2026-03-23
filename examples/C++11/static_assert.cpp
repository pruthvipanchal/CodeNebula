// CodeNebula - C++11 Example: static_assert (Compile-Time Assertions)
// Compile: g++ -std=c++11 -Wall -Wextra -o example static_assert.cpp

// Demonstrates static_assert for compile-time assertions. Unlike runtime
// assert(), static_assert catches errors during compilation, making it
// invaluable for template constraints and platform assumptions.

#include <iostream>
#include <type_traits>
#include <cstdint>

// Real-world scenario: ensure platform assumptions hold
static_assert(sizeof(int) >= 4, "int must be at least 32 bits");
static_assert(sizeof(void*) >= 4, "Pointers must be at least 32 bits");
static_assert(sizeof(char) == 1, "char must be exactly 1 byte");

// Template that only works with integral types
template <typename T>
T safeAdd(T a, T b)
{
    static_assert(std::is_integral<T>::value,
                  "safeAdd requires an integral type");
    return a + b;
}

// Template that only works with unsigned types
template <typename T>
T bitwiseRotateLeft(T value, int shift)
{
    static_assert(std::is_unsigned<T>::value,
                  "bitwiseRotateLeft requires an unsigned type");
    const int bits = sizeof(T) * 8;
    shift %= bits;
    return (value << shift) | (value >> (bits - shift));
}

// Struct with alignment requirements
struct alignas(16) AlignedData {
    float x, y, z, w;
};

static_assert(alignof(AlignedData) == 16, "AlignedData must be 16-byte aligned");
static_assert(sizeof(AlignedData) == 16, "AlignedData must be exactly 16 bytes");

// Ensure enum sizes for binary protocol
enum class MessageType : uint8_t { Ping = 1, Pong = 2, Data = 3 };
static_assert(sizeof(MessageType) == 1, "MessageType must fit in 1 byte");

int main()
{
    // ------------------------------------------------------------------
    // 1. Platform checks (already verified at compile time above)
    // ------------------------------------------------------------------
    std::cout << "=== Platform checks passed ===" << std::endl;
    std::cout << "  sizeof(int)   : " << sizeof(int) << " bytes" << std::endl;
    std::cout << "  sizeof(void*) : " << sizeof(void*) << " bytes" << std::endl;
    std::cout << "  sizeof(char)  : " << sizeof(char) << " byte" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. Template constraints with static_assert
    // ------------------------------------------------------------------
    int sum = safeAdd(10, 20);
    long longSum = safeAdd(100L, 200L);
    // safeAdd(1.5, 2.5);  // ERROR: static_assert fires for double

    std::cout << "=== Template constraints ===" << std::endl;
    std::cout << "  safeAdd(10, 20)   : " << sum << std::endl;
    std::cout << "  safeAdd(100L,200L): " << longSum << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. Bitwise operation safety
    // ------------------------------------------------------------------
    uint32_t rotated = bitwiseRotateLeft(uint32_t(0x12345678), 8);
    // bitwiseRotateLeft(int(-1), 8);  // ERROR: signed type not allowed

    std::cout << "=== Bitwise rotation ===" << std::endl;
    std::cout << "  rotateLeft(0x12345678, 8) = 0x"
              << std::hex << rotated << std::dec << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. Struct layout verification
    // ------------------------------------------------------------------
    std::cout << "=== Struct layout ===" << std::endl;
    std::cout << "  sizeof(AlignedData) : " << sizeof(AlignedData) << std::endl;
    std::cout << "  alignof(AlignedData): " << alignof(AlignedData) << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 5. Enum size verification
    // ------------------------------------------------------------------
    std::cout << "=== Enum size ===" << std::endl;
    std::cout << "  sizeof(MessageType): " << sizeof(MessageType) << " byte" << std::endl;
    std::cout << "  Ping = " << static_cast<int>(MessageType::Ping) << std::endl;
    std::cout << "  Data = " << static_cast<int>(MessageType::Data) << std::endl;

    return 0;
}

/*
Expected output:

=== Platform checks passed ===
  sizeof(int)   : 4 bytes
  sizeof(void*) : 8 bytes
  sizeof(char)  : 1 byte

=== Template constraints ===
  safeAdd(10, 20)   : 30
  safeAdd(100L,200L): 300

=== Bitwise rotation ===
  rotateLeft(0x12345678, 8) = 0x34567812

=== Struct layout ===
  sizeof(AlignedData) : 16
  alignof(AlignedData): 16

=== Enum size ===
  sizeof(MessageType): 1 byte
  Ping = 1
  Data = 3
*/
