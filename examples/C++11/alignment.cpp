// CodeNebula - C++11 Example: Alignment (alignas and alignof)
// Compile: g++ -std=c++11 -Wall -Wextra -o example alignment.cpp
//
// This example demonstrates:
// - alignof to query alignment requirements of types
// - alignas to specify alignment for variables and types
// - std::alignment_of and std::aligned_storage utilities
// - Practical use cases: cache-line alignment, SIMD-friendly data

#include <iostream>
#include <cstdint>
#include <cstddef>
#include <type_traits>

// ============================================================
// 1. alignof - querying alignment of types
// ============================================================
void showAlignments() {
    std::cout << "--- Default alignments ---" << std::endl;
    std::cout << "  char:        " << alignof(char) << std::endl;
    std::cout << "  short:       " << alignof(short) << std::endl;
    std::cout << "  int:         " << alignof(int) << std::endl;
    std::cout << "  long:        " << alignof(long) << std::endl;
    std::cout << "  long long:   " << alignof(long long) << std::endl;
    std::cout << "  float:       " << alignof(float) << std::endl;
    std::cout << "  double:      " << alignof(double) << std::endl;
    std::cout << "  long double: " << alignof(long double) << std::endl;
    std::cout << "  void*:       " << alignof(void*) << std::endl;
    std::cout << "  std::max_align_t: " << alignof(std::max_align_t) << std::endl;
}

// ============================================================
// 2. alignas - specifying alignment
// ============================================================
struct DefaultStruct {
    char a;
    int b;
    char c;
};

struct alignas(16) Aligned16Struct {
    char a;
    int b;
    char c;
};

struct alignas(32) CacheLineAligned {
    double values[4];  // 32 bytes of data, aligned to 32 bytes
};

// ============================================================
// 3. alignas on individual members
// ============================================================
struct MixedAlignment {
    char tag;
    alignas(8) int data;     // Force 8-byte alignment for this member
    char flag;
    alignas(16) double vec;  // Force 16-byte alignment for this member
};

// ============================================================
// 4. alignas with variables
// ============================================================
alignas(64) int cacheLineSeparated[16];  // Aligned to cache line boundary

int main() {
    std::cout << "=== Alignment (alignas / alignof) ===" << std::endl;

    // Show default alignments
    showAlignments();

    // Struct alignment effects
    std::cout << "\n--- Struct alignment ---" << std::endl;
    std::cout << "  DefaultStruct:     size=" << sizeof(DefaultStruct)
              << ", align=" << alignof(DefaultStruct) << std::endl;
    std::cout << "  Aligned16Struct:   size=" << sizeof(Aligned16Struct)
              << ", align=" << alignof(Aligned16Struct) << std::endl;
    std::cout << "  CacheLineAligned:  size=" << sizeof(CacheLineAligned)
              << ", align=" << alignof(CacheLineAligned) << std::endl;
    std::cout << "  MixedAlignment:    size=" << sizeof(MixedAlignment)
              << ", align=" << alignof(MixedAlignment) << std::endl;

    // Runtime address verification
    std::cout << "\n--- Address alignment check ---" << std::endl;
    Aligned16Struct obj;
    std::uintptr_t addr = reinterpret_cast<std::uintptr_t>(&obj);
    std::cout << "  Aligned16Struct address: " << &obj << std::endl;
    std::cout << "  Divisible by 16: "
              << ((addr % 16 == 0) ? "yes" : "no") << std::endl;

    std::uintptr_t arrAddr = reinterpret_cast<std::uintptr_t>(&cacheLineSeparated);
    std::cout << "  Cache-line array address: " << &cacheLineSeparated << std::endl;
    std::cout << "  Divisible by 64: "
              << ((arrAddr % 64 == 0) ? "yes" : "no") << std::endl;

    // std::alignment_of type trait
    std::cout << "\n--- std::alignment_of trait ---" << std::endl;
    std::cout << "  alignment_of<int>: "
              << std::alignment_of<int>::value << std::endl;
    std::cout << "  alignment_of<Aligned16Struct>: "
              << std::alignment_of<Aligned16Struct>::value << std::endl;

    return 0;
}

// Expected output (values may vary by platform):
// === Alignment (alignas / alignof) ===
// --- Default alignments ---
//   char:        1
//   short:       2
//   int:         4
//   long:        4
//   long long:   8
//   float:       4
//   double:      8
//   long double: 16
//   void*:       8
//   std::max_align_t: 16
//
// --- Struct alignment ---
//   DefaultStruct:     size=12, align=4
//   Aligned16Struct:   size=16, align=16
//   CacheLineAligned:  size=32, align=32
//   MixedAlignment:    size=32, align=16
//
// --- Address alignment check ---
//   Aligned16Struct address: 0x7ffd...
//   Divisible by 16: yes
//   Cache-line array address: 0x...
//   Divisible by 64: yes
//
// --- std::alignment_of trait ---
//   alignment_of<int>: 4
//   alignment_of<Aligned16Struct>: 16
