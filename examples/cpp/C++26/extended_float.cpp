// CodeNebula - C++26 Example: Extended Floating-Point Types
// Compile: g++ -std=c++26 -Wall -Wextra -o example extended_float.cpp
// Note: Requires C++26 compiler support (GCC 15+ / Clang 19+ expected)

// C++23 introduced <stdfloat> with fixed-width floating-point types.
// C++26 extends support with improved conversions, formatting, and
// arithmetic operations for float16_t, float32_t, float64_t, float128_t.

#include <iostream>
#include <cstdint>
#include <limits>
#include <cmath>

// --- C++26 Extended Float Syntax ---
//
// #include <stdfloat>
//
// std::float16_t  f16 = 1.5f16;    // 16-bit IEEE 754 half-precision
// std::float32_t  f32 = 3.14f32;   // 32-bit IEEE 754 single-precision
// std::float64_t  f64 = 2.718f64;  // 64-bit IEEE 754 double-precision
// std::float128_t f128 = 1.0f128;  // 128-bit IEEE 754 quad-precision
// std::bfloat16_t bf16 = 1.0bf16;  // bfloat16 (brain floating point)
//
// // Arithmetic works naturally
// auto sum = f32 + f32;             // result is float32_t
// auto wide = f16 * f64;            // promoted to float64_t

// --- Simulation using standard C++ types ---

// Simulate fixed-width floats with standard types
using float32_sim = float;       // Typically 32-bit IEEE 754
using float64_sim = double;      // Typically 64-bit IEEE 754

// Simulate float16 with a simple wrapper
struct float16_sim {
    float value; // Store as float, conceptually 16-bit
    float16_sim(float v = 0.0f) : value(v) {}
    operator float() const { return value; }
};

int main() {
    std::cout << "=== C++26 Extended Floating-Point Types (Simulated) ===" << std::endl;

    float32_sim f32 = 3.14f;
    float64_sim f64 = 2.718281828459045;
    float16_sim f16(1.5f);

    std::cout << "float16_t  (sim): " << static_cast<float>(f16)
              << " (" << 16 << " bits)" << std::endl;
    std::cout << "float32_t  (sim): " << f32
              << " (" << sizeof(f32) * 8 << " bits)" << std::endl;
    std::cout << "float64_t  (sim): " << f64
              << " (" << sizeof(f64) * 8 << " bits)" << std::endl;

    // Precision comparison
    std::cout << "\nPrecision (digits10):" << std::endl;
    std::cout << "  float:  " << std::numeric_limits<float>::digits10 << std::endl;
    std::cout << "  double: " << std::numeric_limits<double>::digits10 << std::endl;
    std::cout << "  long double: " << std::numeric_limits<long double>::digits10 << std::endl;

    // Range comparison
    std::cout << "\nMax values:" << std::endl;
    std::cout << "  float:  " << std::numeric_limits<float>::max() << std::endl;
    std::cout << "  double: " << std::numeric_limits<double>::max() << std::endl;

    // Arithmetic
    auto sum = f32 + f32;
    std::cout << "\n3.14 + 3.14 = " << sum << std::endl;
    std::cout << "sqrt(f64)   = " << std::sqrt(f64) << std::endl;

    std::cout << "Extended floats provide portable, width-guaranteed types." << std::endl;
    return 0;
}

// Expected output:
// === C++26 Extended Floating-Point Types (Simulated) ===
// float16_t  (sim): 1.5 (16 bits)
// float32_t  (sim): 3.14 (32 bits)
// float64_t  (sim): 2.71828 (64 bits)
//
// Precision (digits10):
//   float:  6
//   double: 15
//   long double: 18
//
// Max values:
//   float:  3.40282e+38
//   double: 1.79769e+308
//
// 3.14 + 3.14 = 6.28
// sqrt(f64)   = 1.64872
// Extended floats provide portable, width-guaranteed types.
