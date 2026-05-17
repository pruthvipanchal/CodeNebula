// CodeNebula - C++26 Example: std::complex Improvements
// Compile: g++ -std=c++26 -Wall -Wextra -o example complex_improvements.cpp
// Note: Requires C++26 compiler support

#include <iostream>
#include <complex>
#include <iomanip>
#include <cmath>

// C++26 improves std::complex with:
//   - Full constexpr support for all operations (arithmetic, abs, norm, etc.)
//   - Better interplay with extended floating-point types (float16_t, etc.)
//   - Improved NaN/infinity handling in edge cases
//   - constexpr transcendentals (exp, log, sin, cos on complex)
//
// These changes enable compile-time complex number computations for
// signal processing, physics simulations, and compile-time FFT.

int main() {
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "--- std::complex Improvements (C++26) ---\n\n";

    // Basic complex arithmetic
    std::complex<double> z1(3.0, 4.0);  // 3 + 4i
    std::complex<double> z2(1.0, -2.0); // 1 - 2i

    std::cout << "z1 = " << z1 << "\n";
    std::cout << "z2 = " << z2 << "\n";
    std::cout << "z1 + z2 = " << (z1 + z2) << "\n";
    std::cout << "z1 * z2 = " << (z1 * z2) << "\n";
    std::cout << "z1 / z2 = " << (z1 / z2) << "\n";

    // Magnitude and phase
    std::cout << "\n--- Magnitude and Phase ---\n";
    std::cout << "abs(z1)  = " << std::abs(z1)  << "  (magnitude)\n";
    std::cout << "norm(z1) = " << std::norm(z1) << "  (squared magnitude)\n";
    std::cout << "arg(z1)  = " << std::arg(z1)  << "  (phase in radians)\n";
    std::cout << "conj(z1) = " << std::conj(z1) << "  (conjugate)\n";

    // Transcendental functions
    std::cout << "\n--- Transcendental Functions ---\n";
    std::complex<double> z3(0.0, M_PI); // i*pi
    std::cout << "exp(i*pi) = " << std::exp(z3) << "  (Euler's identity)\n";
    std::cout << "log(z1)   = " << std::log(z1) << "\n";
    std::cout << "sqrt(z2)  = " << std::sqrt(z2) << "\n";

    // Polar form construction
    std::cout << "\n--- Polar Construction ---\n";
    double r = 5.0, theta = M_PI / 4.0;
    auto polar_z = std::polar(r, theta);
    std::cout << "polar(5, pi/4) = " << polar_z << "\n";
    std::cout << "  abs = " << std::abs(polar_z) << ", arg = " << std::arg(polar_z) << "\n";

    // C++26: constexpr complex arithmetic
    // constexpr std::complex<double> cz(3.0, 4.0);
    // constexpr double mag = std::abs(cz);  // C++26: constexpr
    // static_assert(mag == 5.0);
    std::cout << "\nC++26: complex operations are fully constexpr.\n";
    return 0;
}

// Expected output:
// --- std::complex Improvements (C++26) ---
//
// z1 = (3.0000,4.0000)
// z2 = (1.0000,-2.0000)
// z1 + z2 = (4.0000,2.0000)
// z1 * z2 = (11.0000,-2.0000)
// z1 / z2 = (-1.0000,2.0000)
//
// --- Magnitude and Phase ---
// abs(z1)  = 5.0000  (magnitude)
// norm(z1) = 25.0000  (squared magnitude)
// arg(z1)  = 0.9273  (phase in radians)
// conj(z1) = (3.0000,-4.0000)  (conjugate)
//
// --- Transcendental Functions ---
// exp(i*pi) = (-1.0000,0.0000)  (Euler's identity)
// log(z1)   = (1.6094,0.9273)
// sqrt(z2)  = (1.2720,-0.7862)
//
// --- Polar Construction ---
// polar(5, pi/4) = (3.5355,3.5355)
//   abs = 5.0000, arg = 0.7854
//
// C++26: complex operations are fully constexpr.
