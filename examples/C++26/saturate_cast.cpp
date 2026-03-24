// CodeNebula - C++26 Example: std::saturate_cast
// Compile: g++ -std=c++26 -Wall -Wextra -o example saturate_cast.cpp
// Note: Requires C++26 compiler support (GCC 15+ / Clang 19+ expected)

// C++26 introduces std::saturate_cast for safe type narrowing. When
// converting between integer types, values are clamped to the target
// type's range instead of wrapping or triggering undefined behavior.

#include <iostream>
#include <cstdint>
#include <limits>
#include <type_traits>

// --- C++26 std::saturate_cast Syntax ---
//
// #include <numeric>
//
// int big = 300;
// uint8_t small = std::saturate_cast<uint8_t>(big);  // 255 (clamped)
//
// int neg = -10;
// unsigned u = std::saturate_cast<unsigned>(neg);     // 0 (clamped)
//
// int64_t large = 1'000'000;
// int16_t s = std::saturate_cast<int16_t>(large);     // 32767 (clamped)

// --- Simulation using C++20 features ---

template<typename To, typename From>
constexpr To saturate_cast_sim(From value) {
    using ToLimits = std::numeric_limits<To>;

    // Handle signed -> unsigned conversion (negative values clamp to 0)
    if constexpr (std::is_signed_v<From> && std::is_unsigned_v<To>) {
        if (value < 0) return To{0};
        if (static_cast<std::make_unsigned_t<From>>(value) > ToLimits::max())
            return ToLimits::max();
        return static_cast<To>(value);
    }
    // Handle unsigned -> signed (large values clamp to max)
    else if constexpr (std::is_unsigned_v<From> && std::is_signed_v<To>) {
        if (value > static_cast<std::make_unsigned_t<To>>(ToLimits::max()))
            return ToLimits::max();
        return static_cast<To>(value);
    }
    // Same signedness
    else {
        if (value > static_cast<From>(ToLimits::max())) return ToLimits::max();
        if (value < static_cast<From>(ToLimits::min())) return ToLimits::min();
        return static_cast<To>(value);
    }
}

int main() {
    std::cout << "=== C++26 std::saturate_cast (Simulated) ===" << std::endl;

    // int -> uint8_t (overflow clamped)
    int big = 300;
    auto r1 = saturate_cast_sim<uint8_t>(big);
    std::cout << "saturate_cast<uint8_t>(300) = " << (int)r1 << std::endl;

    // Negative -> unsigned (clamped to 0)
    int neg = -42;
    auto r2 = saturate_cast_sim<unsigned>(neg);
    std::cout << "saturate_cast<unsigned>(-42) = " << r2 << std::endl;

    // int64 -> int16 (large value clamped)
    int64_t large = 1'000'000;
    auto r3 = saturate_cast_sim<int16_t>(large);
    std::cout << "saturate_cast<int16_t>(1000000) = " << r3 << std::endl;

    // Negative int64 -> int8
    int64_t very_neg = -500;
    auto r4 = saturate_cast_sim<int8_t>(very_neg);
    std::cout << "saturate_cast<int8_t>(-500) = " << (int)r4 << std::endl;

    // Normal conversion (fits)
    auto r5 = saturate_cast_sim<uint8_t>(42);
    std::cout << "saturate_cast<uint8_t>(42) = " << (int)r5 << std::endl;

    // Constexpr usage
    constexpr auto ce = saturate_cast_sim<uint8_t>(999);
    static_assert(ce == 255);
    std::cout << "constexpr saturate_cast<uint8_t>(999) = " << (int)ce << std::endl;

    std::cout << "saturate_cast: safe narrowing without UB or wrapping." << std::endl;
    return 0;
}

// Expected output:
// === C++26 std::saturate_cast (Simulated) ===
// saturate_cast<uint8_t>(300) = 255
// saturate_cast<unsigned>(-42) = 0
// saturate_cast<int16_t>(1000000) = 32767
// saturate_cast<int8_t>(-500) = -128
// saturate_cast<uint8_t>(42) = 42
// constexpr saturate_cast<uint8_t>(999) = 255
// saturate_cast: safe narrowing without UB or wrapping.
