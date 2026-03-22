// CodeNebula - C++98 Example: Unions
// Compile: g++ -std=c++98 -Wall -Wextra -o example unions.cpp

// Demonstrates unions in C++98: shared memory between members, size behavior,
// type-punning, tagged unions (discriminated unions), and practical uses.

#include <iostream>
#include <cstring>

// ------------------------------------------------------------------
// 1. Basic union - all members share the same memory
// ------------------------------------------------------------------
union BasicValue {
    int    i;
    float  f;
    char   c;
};

// ------------------------------------------------------------------
// 2. Tagged (discriminated) union - safe pattern using an enum tag
// ------------------------------------------------------------------
enum ValueType {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING
};

struct TaggedValue {
    ValueType type;
    union {
        int   intVal;
        float floatVal;
        char  strVal[32];
    } data;
};

void printTaggedValue(const TaggedValue& v)
{
    switch (v.type) {
        case TYPE_INT:
            std::cout << "  [int]    " << v.data.intVal << std::endl;
            break;
        case TYPE_FLOAT:
            std::cout << "  [float]  " << v.data.floatVal << std::endl;
            break;
        case TYPE_STRING:
            std::cout << "  [string] " << v.data.strVal << std::endl;
            break;
    }
}

// ------------------------------------------------------------------
// 3. Union for examining byte representation (type-punning)
// ------------------------------------------------------------------
union FloatBytes {
    float value;
    unsigned char bytes[sizeof(float)];
};

int main()
{
    // ------------------------------------------------------------------
    // Demo 1: Shared memory in a basic union
    // ------------------------------------------------------------------
    std::cout << "=== Basic Union ===" << std::endl;

    BasicValue val;

    // Write as int
    val.i = 42;
    std::cout << "  After setting i = 42:" << std::endl;
    std::cout << "    val.i = " << val.i << std::endl;
    std::cout << "    val.f = " << val.f << " (garbage - reading wrong member)" << std::endl;
    std::cout << "    val.c = " << static_cast<int>(val.c) << " (low byte of int)" << std::endl;

    // Write as float - overwrites the same memory
    val.f = 3.14f;
    std::cout << "  After setting f = 3.14:" << std::endl;
    std::cout << "    val.f = " << val.f << std::endl;
    std::cout << "    val.i = " << val.i << " (reinterpreted bits)" << std::endl;

    // Write as char - overwrites only the first byte
    val.c = 'X';
    std::cout << "  After setting c = 'X':" << std::endl;
    std::cout << "    val.c = " << val.c << " (ASCII " << static_cast<int>(val.c) << ")" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 2: Union size = size of largest member
    // ------------------------------------------------------------------
    std::cout << "=== Union Size ===" << std::endl;
    std::cout << "  sizeof(int)        : " << sizeof(int) << std::endl;
    std::cout << "  sizeof(float)      : " << sizeof(float) << std::endl;
    std::cout << "  sizeof(char)       : " << sizeof(char) << std::endl;
    std::cout << "  sizeof(BasicValue) : " << sizeof(BasicValue)
              << " (equals largest member)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 3: All members share the same address
    // ------------------------------------------------------------------
    std::cout << "=== Shared Address ===" << std::endl;
    std::cout << "  Address of val   : " << static_cast<void*>(&val) << std::endl;
    std::cout << "  Address of val.i : " << static_cast<void*>(&val.i) << std::endl;
    std::cout << "  Address of val.f : " << static_cast<void*>(&val.f) << std::endl;
    std::cout << "  Address of val.c : " << static_cast<void*>(&val.c) << std::endl;
    std::cout << "  (All addresses are the same)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 4: Tagged union (discriminated union pattern)
    // ------------------------------------------------------------------
    std::cout << "=== Tagged Union ===" << std::endl;

    TaggedValue values[3];

    values[0].type = TYPE_INT;
    values[0].data.intVal = 100;

    values[1].type = TYPE_FLOAT;
    values[1].data.floatVal = 2.718f;

    values[2].type = TYPE_STRING;
    std::strcpy(values[2].data.strVal, "Hello, C++98!");

    for (int i = 0; i < 3; ++i) {
        printTaggedValue(values[i]);
    }
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 5: Examining float byte representation
    // ------------------------------------------------------------------
    std::cout << "=== Float Byte Representation ===" << std::endl;

    FloatBytes fb;
    fb.value = 1.0f;

    std::cout << "  Float value: " << fb.value << std::endl;
    std::cout << "  Bytes (hex):";
    for (std::size_t i = 0; i < sizeof(float); ++i) {
        // Print each byte in hex
        int byte = static_cast<int>(fb.bytes[i]);
        std::cout << " ";
        if (byte < 16) std::cout << "0";
        // Manual hex output for C++98 compatibility
        const char hex[] = "0123456789ABCDEF";
        std::cout << hex[byte / 16] << hex[byte % 16];
    }
    std::cout << std::endl;

    fb.value = -1.0f;
    std::cout << "  Float value: " << fb.value << std::endl;
    std::cout << "  Bytes (hex):";
    for (std::size_t i = 0; i < sizeof(float); ++i) {
        int byte = static_cast<int>(fb.bytes[i]);
        std::cout << " ";
        const char hex[] = "0123456789ABCDEF";
        std::cout << hex[byte / 16] << hex[byte % 16];
    }
    std::cout << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 6: Anonymous union inside a struct
    // ------------------------------------------------------------------
    std::cout << "=== Anonymous Union in Struct ===" << std::endl;
    std::cout << "  sizeof(TaggedValue)       : " << sizeof(TaggedValue) << std::endl;
    std::cout << "  sizeof(TaggedValue::data) : "
              << sizeof(values[0].data) << std::endl;
    std::cout << "  (Struct adds the enum tag overhead + padding)" << std::endl;

    return 0;
}

/*
Expected output (values may vary by platform/endianness):

=== Basic Union ===
  After setting i = 42:
    val.i = 42
    val.f = 5.88545e-44 (garbage - reading wrong member)
    val.c = 42 (low byte of int)
  After setting f = 3.14:
    val.f = 3.14
    val.i = 1078523331 (reinterpreted bits)
  After setting c = 'X':
    val.c = X (ASCII 88)

=== Union Size ===
  sizeof(int)        : 4
  sizeof(float)      : 4
  sizeof(char)       : 1
  sizeof(BasicValue) : 4 (equals largest member)

=== Shared Address ===
  Address of val   : 0x7ffd...
  Address of val.i : 0x7ffd...
  Address of val.f : 0x7ffd...
  Address of val.c : 0x7ffd...
  (All addresses are the same)

=== Tagged Union ===
  [int]    100
  [float]  2.718
  [string] Hello, C++98!

=== Float Byte Representation ===
  Float value: 1
  Bytes (hex): 00 00 80 3F   (little-endian IEEE 754)
  Float value: -1
  Bytes (hex): 00 00 80 BF

=== Anonymous Union in Struct ===
  sizeof(TaggedValue)       : 36
  sizeof(TaggedValue::data) : 32
  (Struct adds the enum tag overhead + padding)
*/
