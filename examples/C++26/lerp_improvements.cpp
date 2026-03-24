// CodeNebula - C++26 Example: std::lerp Improvements
// Compile: g++ -std=c++26 -Wall -Wextra -o example lerp_improvements.cpp
// Note: Requires C++26 compiler support

#include <iostream>
#include <cmath>
#include <iomanip>

// std::lerp(a, b, t) was added in C++20 for linear interpolation.
// C++26 improves std::lerp with:
//   - Full constexpr support (usable in constant expressions)
//   - Better handling of edge cases (NaN, infinity, denormals)
//   - Guaranteed monotonicity: lerp(a,b,t1) <= lerp(a,b,t2) when t1 <= t2
//   - Exact results at endpoints: lerp(a,b,0)==a, lerp(a,b,1)==b
//
// Formula: lerp(a, b, t) = a + t * (b - a)

int main() {
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "--- std::lerp Improvements (C++26) ---\n\n";

    // Basic interpolation
    double a = 0.0, b = 10.0;
    std::cout << "Interpolating from " << a << " to " << b << ":\n";
    for (double t = 0.0; t <= 1.0; t += 0.25) {
        std::cout << "  lerp(" << a << ", " << b << ", " << t << ") = "
                  << std::lerp(a, b, t) << "\n";
    }

    // Extrapolation (t outside [0, 1])
    std::cout << "\nExtrapolation:\n";
    std::cout << "  lerp(0, 10, -0.5) = " << std::lerp(0.0, 10.0, -0.5) << "\n";
    std::cout << "  lerp(0, 10,  1.5) = " << std::lerp(0.0, 10.0, 1.5) << "\n";

    // Practical: smooth animation easing
    std::cout << "\nColor fade (RGB red channel 255 -> 0):\n";
    double start = 255.0, end = 0.0;
    for (int frame = 0; frame <= 4; ++frame) {
        double t = frame / 4.0;
        double val = std::lerp(start, end, t);
        std::cout << "  Frame " << frame << " (t=" << t << "): R=" << val << "\n";
    }

    // C++26 guarantees exactness at endpoints
    std::cout << "\nEndpoint exactness (C++26 guaranteed):\n";
    double p = 1.23456789, q = 9.87654321;
    std::cout << "  lerp(p, q, 0.0) == p? " << (std::lerp(p, q, 0.0) == p) << "\n";
    std::cout << "  lerp(p, q, 1.0) == q? " << (std::lerp(p, q, 1.0) == q) << "\n";

    // C++26: constexpr lerp
    // constexpr double val = std::lerp(1.0, 5.0, 0.5); // C++26: constexpr
    // static_assert(val == 3.0);
    std::cout << "\nC++26: std::lerp is constexpr with monotonicity guarantees.\n";
    return 0;
}

// Expected output:
// --- std::lerp Improvements (C++26) ---
//
// Interpolating from 0.0000 to 10.0000:
//   lerp(0.0000, 10.0000, 0.0000) = 0.0000
//   lerp(0.0000, 10.0000, 0.2500) = 2.5000
//   lerp(0.0000, 10.0000, 0.5000) = 5.0000
//   lerp(0.0000, 10.0000, 0.7500) = 7.5000
//   lerp(0.0000, 10.0000, 1.0000) = 10.0000
//
// Extrapolation:
//   lerp(0, 10, -0.5) = -5.0000
//   lerp(0, 10,  1.5) = 15.0000
//
// Color fade (RGB red channel 255 -> 0):
//   Frame 0 (t=0.0000): R=255.0000
//   Frame 1 (t=0.2500): R=191.2500
//   Frame 2 (t=0.5000): R=127.5000
//   Frame 3 (t=0.7500): R=63.7500
//   Frame 4 (t=1.0000): R=0.0000
//
// Endpoint exactness (C++26 guaranteed):
//   lerp(p, q, 0.0) == p? 1
//   lerp(p, q, 1.0) == q? 1
//
// C++26: std::lerp is constexpr with monotonicity guarantees.
