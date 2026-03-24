// CodeNebula - C++17 Example: hardware_destructive/constructive_interference_size
// Compile: g++ -std=c++17 -Wall -Wextra -o example interference_sizes.cpp

// Demonstrates the C++17 cache-line constants for avoiding false sharing
// (destructive interference) and promoting true sharing (constructive
// interference). Note: not all compilers define these; we provide fallbacks.

#include <iostream>
#include <new>

// Many compilers (notably GCC/Clang) do not yet define these constants.
// We provide a portable fallback to demonstrate the concept.
#ifdef __cpp_lib_hardware_interference_size
    constexpr std::size_t destructive_size =
        std::hardware_destructive_interference_size;
    constexpr std::size_t constructive_size =
        std::hardware_constructive_interference_size;
    constexpr bool has_stdlib_support = true;
#else
    // Typical cache line size on x86-64 and ARM64
    constexpr std::size_t destructive_size  = 64;
    constexpr std::size_t constructive_size = 64;
    constexpr bool has_stdlib_support = false;
#endif

// ------------------------------------------------------------------
// Avoid false sharing: pad each counter to its own cache line
// ------------------------------------------------------------------
struct alignas(destructive_size) PaddedCounter {
    int value = 0;
    // Padding fills the rest of the cache line, preventing false sharing
    // when adjacent PaddedCounters are modified by different threads.
};

// ------------------------------------------------------------------
// Promote true sharing: keep related data within one cache line
// ------------------------------------------------------------------
struct alignas(constructive_size) CoLocatedPair {
    int x = 0;
    int y = 0;
    // Both x and y live in the same cache line, so one thread
    // accessing both fields benefits from spatial locality.
};

int main()
{
    // ------------------------------------------------------------------
    // 1. Report the interference sizes
    // ------------------------------------------------------------------
    std::cout << "=== Hardware Interference Sizes ===" << std::endl;
    std::cout << "  stdlib support: " << (has_stdlib_support ? "yes" : "no (using fallback)") << std::endl;
    std::cout << "  destructive_interference_size  = " << destructive_size << " bytes" << std::endl;
    std::cout << "  constructive_interference_size = " << constructive_size << " bytes" << std::endl;

    // ------------------------------------------------------------------
    // 2. Demonstrate alignment of padded counters
    // ------------------------------------------------------------------
    PaddedCounter counters[4];

    std::cout << "\n=== Padded Counters (avoid false sharing) ===" << std::endl;
    std::cout << "  sizeof(PaddedCounter)  = " << sizeof(PaddedCounter) << std::endl;
    std::cout << "  alignof(PaddedCounter) = " << alignof(PaddedCounter) << std::endl;
    for (int i = 0; i < 4; ++i) {
        auto addr = reinterpret_cast<std::uintptr_t>(&counters[i]);
        std::cout << "  counters[" << i << "] at offset "
                  << (addr - reinterpret_cast<std::uintptr_t>(&counters[0]))
                  << std::endl;
    }

    // ------------------------------------------------------------------
    // 3. Co-located pair for true sharing
    // ------------------------------------------------------------------
    CoLocatedPair pair;
    auto base = reinterpret_cast<std::uintptr_t>(&pair);
    auto x_off = reinterpret_cast<std::uintptr_t>(&pair.x) - base;
    auto y_off = reinterpret_cast<std::uintptr_t>(&pair.y) - base;

    std::cout << "\n=== Co-Located Pair (promote true sharing) ===" << std::endl;
    std::cout << "  sizeof(CoLocatedPair)  = " << sizeof(CoLocatedPair) << std::endl;
    std::cout << "  x at offset " << x_off << std::endl;
    std::cout << "  y at offset " << y_off << std::endl;
    std::cout << "  Both within " << constructive_size << "-byte line: "
              << ((y_off + sizeof(int) <= constructive_size) ? "yes" : "no")
              << std::endl;

    return 0;
}

/*
Expected output (typical x86-64):

=== Hardware Interference Sizes ===
  stdlib support: no (using fallback)
  destructive_interference_size  = 64 bytes
  constructive_interference_size = 64 bytes

=== Padded Counters (avoid false sharing) ===
  sizeof(PaddedCounter)  = 64
  alignof(PaddedCounter) = 64
  counters[0] at offset 0
  counters[1] at offset 64
  counters[2] at offset 128
  counters[3] at offset 192

=== Co-Located Pair (promote true sharing) ===
  sizeof(CoLocatedPair)  = 64
  x at offset 0
  y at offset 4
  Both within 64-byte line: yes
*/
